[Code]

// This file contains code paths for Windows 95, Windows 2000 and Windows Vista
// to get a list of processes that use a given module (DLL). For the processes
// that lock the file, the process ID, the full path to the executable, and file
// description is returned. This information can then used to present the user a
// list of processes / applications that she needs to close before a module can
// be replaced / a replacement will take effect.
//
// Since Windows Vista, processes that register with the Restart Manager can be
// asked to be restarted without any user interaction. The "Restartable" flag in
// the "ProcessEntry" indicates whether this is supported or not.
//
// Please note that this code only works for modules, not for files that are
// locked by processes in other ways, e.g. by opening them for exclusive read /
// write access.
//
// In contrast to existing solutions like [1] or [2], this one has the advantages
// of not requiring an external DLLs, being Open Source and having support for
// the Windows Vista Restart Manager API.
//
// [1] http://www.vincenzo.net/isxkb/index.php?title=PSVince
// [2] http://raz-soft.com/display-english-posts-only/files-in-use-extension-for-inno-setup/

{
    Common code
}

const
    // General constants.
    MAX_PATH            = 260;
    MAX_MODULE_NAME32   = 255;

    // Return codes.
    ERROR_SUCCESS        = 0;
    ERROR_MORE_DATA      = 234;
    INVALID_HANDLE_VALUE = -1;

    // For OpenProcess().
    PROCESS_VM_READ           = $0010;
    PROCESS_QUERY_INFORMATION = $0400;

type
    HMODULE   = DWORD;
    LONG      = Longint;
    ULONG     = Cardinal;
    BYTE_PTR  = DWORD;
    ULONG_PTR = DWORD;

    IdList=array of DWORD;

    ProcessEntry=record
        ID:DWORD;
        Path,Name:String;
        Restartable:Boolean;
    end;
    ProcessList=array of ProcessEntry;

function CloseHandle(hObject:THandle):Boolean;
external 'CloseHandle@Kernel32.dll';

// We need to always use ANSI version of this function, see the bottom note in GetFileDescription().
function GetFileVersionInfoSize(lptstrFilename:AnsiString;var lpdwHandle:DWORD):DWORD;
external 'GetFileVersionInfoSizeA@Version.dll';

// We need to always use ANSI version of this function, see the bottom note in GetFileDescription().
function GetFileVersionInfo(lptstrFilename:AnsiString;dwHandle,dwLen:DWORD;lpData:array of Byte):Boolean;
external 'GetFileVersionInfoA@Version.dll';

// We need to always use ANSI version of this function, see the bottom note in GetFileDescription().
function VerQueryValue(pBlock:array of Byte;lpSubBlock:AnsiString;var lplpBuffer:PAnsiChar;var puLen:UINT):Boolean;
external 'VerQueryValueA@Version.dll';

// Returns the file description as stored in the VS_VERSION_INFO resource. This
// is used as the process name rather than using the window title, as e.g. editors
// might display the current file rather than the application name in the title bar.
function GetFileDescription(FileName:String):String;
var
    Dummy,Size:DWORD;
    Info:array of Byte;
    Buffer:PAnsiChar;
    BufLen:UINT;
    BufStr:String;
    Offset:Integer;
    Language,Codepage,LanguageFB,CodepageFB:WORD;
begin
    Size:=GetFileVersionInfoSize(Filename,Dummy);
    if Size=0 then begin
        Exit;
    end;

    SetArrayLength(Info,Size);
    if not GetFileVersionInfo(FileName,0,Size,Info) then begin
        Exit;
    end;

    // Query the language and codepage in order to query locale specific strings.
    if not VerQueryValue(Info,'\VarFileInfo\Translation',Buffer,BufLen) then begin
        Exit;
    end;

    // This will fail if "Buffer" contains inner #0 characters, in which case
    // the "else" branch below is taken, and we are guessing some values.
    BufStr:=Buffer;

    if Length(BufStr)>=BufLen then begin
        Offset:=1;
        repeat
            // Decode the WORDs from the string.
            Language:=Ord(BufStr[Offset+1]);
            Language:=(Language shl 8)+Ord(BufStr[Offset]);

            Codepage:=Ord(BufStr[Offset+3]);
            Codepage:=(Codepage shl 8)+Ord(BufStr[Offset+2]);

            // Use the first entry or English as a fallback.
            if (Offset=1) or (Language=$0409) then begin
                LanguageFB:=Language;
                CodepageFB:=Codepage;
            end;

            Offset:=Offset+4;
        until (Language=GetUILanguage) or (Offset>BufLen);

        // If we did not find the UI language, use the fallback.
        if Language<>GetUILanguage then begin
            Language:=LanguageFB;
            Codepage:=CodepageFB;
        end;
    end else begin
        Language:=$0000;   // Process Default Language
        Codepage:=$04b0;   // 1200 (UTF-16, Little-Endian)
        LanguageFB:=$0000; // Process Default Language
        CodepageFB:=$04e4; // 1252 (West European, Latin)
    end;

    // Query the file description.
    BufStr:=Format('\StringFileInfo\%.4x%.4x\FileDescription',[Language,Codepage]);
    if not VerQueryValue(Info,BufStr,Buffer,BufLen) then begin
        // Try the fallback if the first choice failed.
        BufStr:=Format('\StringFileInfo\%.4x%.4x\FileDescription',[LanguageFB,CodepageFB]);
        if not VerQueryValue(Info,BufStr,Buffer,BufLen) then begin
            Exit;
        end;
    end;

    // As we cannot cast PAnsiChar to a Unicode string here, we always
    // need to use the ANSI functions for VerQueryValue etc.
    Result:=Buffer;
end;

{
    Code for Windows 95 and above
}

const
    TH32CS_SNAPPROCESS  = $0002;
    TH32CS_SNAPMODULE   = $0008;
    TH32CS_SNAPMODULE32 = $0010;

type
    PROCESSENTRY32=record
        dwSize,cntUsage,th32ProcessID:DWORD;
        th32DefaultHeapID:ULONG_PTR;
        th32ModuleID,cntThreads,th32ParentProcessID:DWORD;
        pcPriClassBase:LONG;
        dwFlags:DWORD;
        szExeFile:array[1..MAX_PATH] of Char;
    end;
    MODULEENTRY32=record
        dwSize,th32ModuleID,th32ProcessID,GlblcntUsage,ProccntUsage:DWORD;
        modBaseAddr:BYTE_PTR;
        modBaseSize:DWORD;
        hModule:HMODULE;
        szModule:array[1..MAX_MODULE_NAME32+1] of Char;
        szExePath:array[1..MAX_PATH] of Char;
    end;

function CreateToolhelp32Snapshot(dwFlags,th32ProcessID:DWORD):THandle;
external 'CreateToolhelp32Snapshot@Kernel32.dll stdcall delayload';

function Process32First(hSnapshot:THandle;var lppe:PROCESSENTRY32):Boolean;
#ifdef UNICODE
external 'Process32FirstW@Kernel32.dll stdcall delayload';
#else
external 'Process32FirstA@Kernel32.dll stdcall delayload';
#endif

function Process32Next(hSnapshot:THandle;var lppe:PROCESSENTRY32):Boolean;
#ifdef UNICODE
external 'Process32NextW@Kernel32.dll stdcall delayload';
#else
external 'Process32NextA@Kernel32.dll stdcall delayload';
#endif

function Module32First(hSnapshot:THandle;var lpme:MODULEENTRY32):Boolean;
#ifdef UNICODE
external 'Module32FirstW@Kernel32.dll stdcall delayload';
#else
external 'Module32FirstA@Kernel32.dll stdcall delayload';
#endif

function Module32Next(hSnapshot:THandle;var lpme:MODULEENTRY32):Boolean;
#ifdef UNICODE
external 'Module32NextW@Kernel32.dll stdcall delayload';
#else
external 'Module32NextA@Kernel32.dll stdcall delayload';
#endif

// Returns a list of running processes that currectly use the specified module.
// The module may be a filename to a DLL with or without path.
function FindProcessesUsingModules_Win95(Modules:TArrayOfString;var Processes:ProcessList):DWORD;
var
    Success:Boolean;
    ProcSnap:THandle;
    ProcEntry:PROCESSENTRY32;
    ModSnap:THandle;
    ModEntry:MODULEENTRY32;
    ModPath,ProcPath:String;
    i:Longint;
begin
    SetArrayLength(Processes,0);
    Result:=0;

    ProcSnap:=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if ProcSnap=INVALID_HANDLE_VALUE then begin
        Exit;
    end;

    // Compare strings case-insensitively.
    for i:=0 to GetArraylength(Modules)-1 do begin
        Modules[i]:=Lowercase(Modules[i]);
    end;

    // Loop over the processes in the system.
    ProcEntry.dwSize:=SizeOf(ProcEntry);
    Success:=Process32First(ProcSnap,ProcEntry);

    while Success do begin
        if ProcEntry.th32ProcessID>0 then begin
            ModSnap:=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE or TH32CS_SNAPMODULE32,ProcEntry.th32ProcessID);
            if ModSnap<>INVALID_HANDLE_VALUE then begin
                // Loop over the modules in the process.
                ModEntry.dwSize:=SizeOf(ModEntry);
                Success:=Module32First(ModSnap,ModEntry);

                // Assume the first module always is the executable itself.
                ProcPath:=ArrayToString(ModEntry.szExePath);
                Success:=Module32Next(ModSnap,ModEntry);

                while Success do begin
                    ModPath:=ArrayToString(ModEntry.szExePath);

                    for i:=0 to GetArraylength(Modules)-1 do begin
                        if Pos(Modules[i],Lowercase(ModPath))>0 then begin
                            i:=GetArrayLength(Processes);
                            SetArrayLength(Processes,i+1);
                            Processes[i].ID:=ProcEntry.th32ProcessID;
                            Processes[i].Path:=ProcPath;
                            Processes[i].Name:=GetFileDescription(ProcPath);
                            if Length(Processes[i].Name)=0 then begin
                                Processes[i].Name:=ExtractFileName(ProcPath);
                            end;
                            Processes[i].Restartable:=False;
                        end;
                    end;

                    Success:=Module32Next(ModSnap,ModEntry);
                end;

                CloseHandle(ModSnap);
            end;
        end;

        Success:=Process32Next(ProcSnap,ProcEntry);
    end;

    CloseHandle(ProcSnap);

    Result:=1;
end;

// Returns a list of running processes that currectly use the specified module.
// The module may be a filename to a DLL with or without path.
function FindProcessesUsingModule_Win95(Module:String;var Processes:ProcessList):DWORD;
var
    Modules:TArrayOfString;
begin
    SetArrayLength(Modules,1);
    Modules[0]:=Module;
    Result:=FindProcessesUsingModules_Win95(Modules,Processes);
end;

{
    Code for Windows 2000 and above
}

function EnumProcesses(pProcessIds:IdList;cb:DWORD;var pBytesReturned:DWORD):Boolean;
external 'EnumProcesses@Psapi.dll stdcall delayload';

function EnumProcessModules(hProcess:THandle;lphModule:IdList;cb:DWORD;var lpcbNeeded:DWORD):Boolean;
external 'EnumProcessModules@Psapi.dll stdcall delayload';

// Wrapper for EnumProcesses() that returns process IDs as a list.
function GetProcessList(var List:IdList):Boolean;
var
    Size:Longint;
    Bytes:DWORD;
begin
    // Start with space for 64 processes.
    Bytes:=32*SizeOf(Bytes);

    repeat
        Size:=Bytes*2;
        SetArrayLength(List,Size/SizeOf(Bytes));
        Result:=EnumProcesses(List,Size,Bytes);
    until (Bytes<Size) or (not Result);

    if Result then begin
        SetArrayLength(List,Bytes/SizeOf(Bytes));
    end else begin
        SetArrayLength(List,0);
    end;
end;

// Wrapper for EnumProcessModules() that returns module IDs as a list.
function GetModuleList(Process:THandle;var List:IdList):Boolean;
var
    Size:Longint;
    Bytes:DWORD;
begin
    // Start with space for 64 modules.
    Bytes:=32*SizeOf(Bytes);

    repeat
        Size:=Bytes*2;
        SetArrayLength(List,Size/SizeOf(Bytes));
        Result:=EnumProcessModules(Process,List,Size,Bytes);
    until (Bytes<Size) or (not Result);

    if Result then begin
        SetArrayLength(List,Bytes/SizeOf(Bytes));
    end else begin
        SetArrayLength(List,0);
    end;
end;

function OpenProcess(dwDesiredAccess:DWORD;bInheritHandle:BOOL;dwProcessId:DWORD):THandle;
external 'OpenProcess@Kernel32.dll stdcall delayload';

function GetModuleFileNameEx(hProcess:THandle;hModule:HMODULE;lpFilename:String;nSize:DWORD):DWORD;
#ifdef UNICODE
external 'GetModuleFileNameExW@Psapi.dll stdcall delayload';
#else
external 'GetModuleFileNameExA@Psapi.dll stdcall delayload';
#endif

// Returns a list of running processes that currectly use one of the specified modules.
// Each module may be a filename to a DLL with or without path.
function FindProcessesUsingModules_Win2000(Modules:TArrayOfString;var Processes:ProcessList):DWORD;
var
    ProcList,ModList:IdList;
    p,m,i:Longint;
    Process:THandle;
    Path:String;
    PathLength:DWORD;
begin
    SetArrayLength(Processes,0);
    Result:=0;

    if not GetProcessList(ProcList) then begin
        Exit;
    end;

    // Compare strings case-insensitively.
    for i:=0 to GetArraylength(Modules)-1 do begin
        Modules[i]:=Lowercase(Modules[i]);
    end;

    for p:=0 to GetArraylength(ProcList)-1 do begin
        Process:=OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ,False,ProcList[p]);
        if Process<>0 then begin
            if GetModuleList(Process,ModList) then begin
                for m:=0 to GetArraylength(ModList)-1 do begin
                    SetLength(Path,MAX_PATH);
                    PathLength:=GetModuleFileNameEx(Process,ModList[m],Path,MAX_PATH);
                    SetLength(Path,PathLength);

                    for i:=0 to GetArraylength(Modules)-1 do begin
                        if Pos(Modules[i],Lowercase(Path))>0 then begin
                            SetLength(Path,MAX_PATH);
                            PathLength:=GetModuleFileNameEx(Process,0,Path,MAX_PATH);
                            SetLength(Path,PathLength);

                            i:=GetArrayLength(Processes);
                            SetArrayLength(Processes,i+1);
                            Processes[i].ID:=ProcList[p];
                            Processes[i].Path:=Path;
                            Processes[i].Name:=GetFileDescription(Path);
                            if Length(Processes[i].Name)=0 then begin
                                Processes[i].Name:=ExtractFileName(Path);
                            end;
                            Processes[i].Restartable:=False;
                        end;
                    end;
                end;
            end;
            CloseHandle(Process);
        end;
    end;

    Result:=1;
end;

// Returns a list of running processes that currectly use the specified module.
// The module may be a filename to a DLL with or without path.
function FindProcessesUsingModule_Win2000(Module:String;var Processes:ProcessList):DWORD;
var
    Modules:TArrayOfString;
begin
    SetArrayLength(Modules,1);
    Modules[0]:=Module;
    Result:=FindProcessesUsingModules_Win2000(Modules,Processes);
end;

{
    Code for Windows Vista and above
}

const
    CCH_RM_SESSION_KEY  = 32;
    CCH_RM_MAX_APP_NAME = 255;
    CCH_RM_MAX_SVC_NAME = 63;

    RmUnknownApp  = 0;    // The application cannot be classified as any other type. An application of this type can only be shut down by a forced shutdown.
    RmMainWindow  = 1;    // A Windows application run as a stand-alone process that displays a top-level window.
    RmOtherWindow = 2;    // A Windows application that does not run as a stand-alone process and does not display a top-level window.
    RmService     = 3;    // The application is a Windows service.
    RmExplorer    = 4;    // The application is Windows Explorer.
    RmConsole     = 5;    // The application is a stand-alone console application.
    RmCritical    = 1000; // A system restart is required to complete the installation because a process cannot be shut down.

    RmStatusUnknown        = $0000;
    RmStatusRunning        = $0001;
    RmStatusStopped        = $0002;
    RmStatusStoppedOther   = $0004;
    RmStatusRestarted      = $0008;
    RmStatusErrorOnStop    = $0010;
    RmStatusErrorOnRestart = $0020;
    RmStatusShutdownMasked = $0040;
    RmStatusRestartMasked  = $0080;

    RmForceShutdown          = $0001;
    RmShutdownOnlyRegistered = $0010;

type
    SessionKey=array[1..CCH_RM_SESSION_KEY+1] of Char;

    FILETIME=record
        dwLowDateTime,dwHighDateTime:DWORD;
    end;
    RM_UNIQUE_PROCESS=record
        dwProcessId:DWORD;
        ProcessStartTime:FILETIME;
    end;
    RM_APP_TYPE=DWORD;
    RM_PROCESS_INFO=record
        Process:RM_UNIQUE_PROCESS;
        strAppName:array[1..CCH_RM_MAX_APP_NAME+1] of Char;
        strServiceShortName:array[1..CCH_RM_MAX_SVC_NAME+1] of Char;
        ApplicationType:RM_APP_TYPE;
        AppStatus:ULONG;
        TSSessionId:DWORD;
        bRestartable:BOOL;
    end;
    RM_WRITE_STATUS_CALLBACK=DWORD;

function RmStartSession(var pSessionHandle:DWORD;dwSessionFlags:DWORD;strSessionKey:SessionKey):DWORD;
external 'RmStartSession@Rstrtmgr.dll stdcall delayload';

function RmEndSession(dwSessionHandle:DWORD):DWORD;
external 'RmEndSession@Rstrtmgr.dll stdcall delayload';

function RmRegisterResources(dwSessionHandle:DWORD;hFiles:UINT;rgsFilenames:TArrayOfString;nApplications:UINT;rgApplications:array of RM_UNIQUE_PROCESS;nServices:UINT;rgsServiceNames:TArrayOfString):DWORD;
external 'RmRegisterResources@Rstrtmgr.dll stdcall delayload';

function RmGetList(dwSessionHandle:DWORD;var pnProcInfoNeeded,pnProcInfo:UINT;rgAffectedApps:array of RM_PROCESS_INFO;lpdwRebootReasons:IdList):DWORD;
external 'RmGetList@Rstrtmgr.dll stdcall delayload';

function RmShutdown(dwSessionHandle:DWORD;lActionFlags:ULONG;fnStatus:RM_WRITE_STATUS_CALLBACK):DWORD;
external 'RmShutdown@Rstrtmgr.dll stdcall delayload';

function RmRestart(dwSessionHandle:DWORD;dwRestartFlags:DWORD;fnStatus:RM_WRITE_STATUS_CALLBACK):DWORD;
external 'RmRestart@Rstrtmgr.dll stdcall delayload';

// Returns a list of running processes that currectly use one of the specified modules.
// Each module has to be a full path and filename to a DLL.
function FindProcessesUsingModules_WinVista(Modules:TArrayOfString;var Processes:ProcessList):DWORD;
var
    Handle:DWORD;
    Name:SessionKey;
    Apps:array of RM_UNIQUE_PROCESS;
    Services:TArrayOfString;
    Process:THandle;
    Path:String;
    PathLength:DWORD;
    Needed,Have,i:UINT;
    AppList:array of RM_PROCESS_INFO;
    ReasonList:IdList;
    Success:DWORD;
begin
    SetArrayLength(Processes,0);
    Result:=0;

    // NULL-terminate the array of chars.
    Name[CCH_RM_SESSION_KEY+1]:=#0;
    if RmStartSession(Handle,0,Name)<>ERROR_SUCCESS then begin
        Exit;
    end;

    if RmRegisterResources(Handle,GetArrayLength(Modules),Modules,0,Apps,0,Services)=ERROR_SUCCESS then begin
        // Reallocate the arrays until they are large enough to hold the process information.
        Needed:=1;
        repeat
            Have:=Needed;
            SetArrayLength(AppList,Have);
            SetArrayLength(ReasonList,Have);
            Success:=RmGetList(Handle,Needed,Have,AppList,ReasonList);
        until (Have>=Needed) and (Success<>ERROR_MORE_DATA);

        if (Success=ERROR_SUCCESS) and (Needed>0) then begin
            for i:=0 to Needed-1 do begin
                Process:=OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ,False,AppList[i].Process.dwProcessId);
                if Process<>0 then begin
                    SetLength(Path,MAX_PATH);
                    PathLength:=GetModuleFileNameEx(Process,0,Path,MAX_PATH);
                    SetLength(Path,PathLength);

                    Have:=GetArrayLength(Processes);
                    SetArrayLength(Processes,Have+1);
                    Processes[Have].ID:=AppList[i].Process.dwProcessId;
                    Processes[Have].Path:=Path;
                    Processes[Have].Name:=ArrayToString(AppList[i].strAppName);
                    Processes[Have].Restartable:=AppList[i].bRestartable;

                    CloseHandle(Process);
                end;
            end;
            Result:=Handle;
        end;
    end;
end;

// Returns a list of running processes that currectly use the specified module.
// The module has to be a full path and filename to a DLL.
function FindProcessesUsingModule_WinVista(Module:String;var Processes:ProcessList):DWORD;
var
    Modules:TArrayOfString;
begin
    SetArrayLength(Modules,1);
    Modules[0]:=Module;
    Result:=FindProcessesUsingModules_WinVista(Modules,Processes);
end;

{
    Wrapper code
}

// Returns a list of running processes that currectly use one of the specified modules.
// Automatically calls the best implementation for the running OS. The return value is
// non-zero on success, and equals the Restart Manager session handle on Vista and above.
function FindProcessesUsingModules(Modules:TArrayOfString;var Processes:ProcessList):DWORD;
var
    Version:TWindowsVersion;
begin
    GetWindowsVersionEx(Version);

    if (Version.Major<5) or (not Version.NTPlatform) then begin
        Result:=FindProcessesUsingModules_Win95(Modules,Processes);
    end else if Version.Major<6 then begin
        Result:=FindProcessesUsingModules_Win2000(Modules,Processes);
    end else begin
        Result:=FindProcessesUsingModules_WinVista(Modules,Processes);
    end;
end;

// Returns a list of running processes that currectly use the specified module.
// Automatically calls the best implementation for the running OS. The return value is
// non-zero on success, and equals the Restart Manager session handle on Vista and above.
function FindProcessesUsingModule(Module:String;var Processes:ProcessList):DWORD;
var
    Version:TWindowsVersion;
begin
    GetWindowsVersionEx(Version);

    if (Version.Major<5) or (not Version.NTPlatform) then begin
        Result:=FindProcessesUsingModule_Win95(Module,Processes);
    end else if Version.Major<6 then begin
        Result:=FindProcessesUsingModule_Win2000(Module,Processes);
    end else begin
        Result:=FindProcessesUsingModule_WinVista(Module,Processes);
    end;
end;

{
    Helper code
}

// Tries to replace an in-use file, e.g. a registered shell extension, by
// renaming it and then renaming the new file to the original name. Optionally,
// performs (un-)registering via regsvr32.
function ReplaceInUseFile(CurFile,NewFile:String;Register:Boolean;var ErrorMsg:String):Boolean;
var
    CurFilePath,CurFileName,NewFileName:String;
    CurFileStem,CurFileTemp:String;
    UnregisterFailed,RenameFailed:Boolean;
begin
    Result:=False;

    // Note that CurFile may not exist, in which case NewFile is just renamed.
    if not FileExists(NewFile) then begin
        Exit;
    end;

    CurFilePath:=ExtractFilePath(CurFile);
    CurFileName:=ExtractFileName(CurFile);
    NewFileName:=ExtractFileName(NewFile);

    // Get the file name without extension or period and use that as a suffix
    // for the temporary file.
    CurFileStem:=ChangeFileExt(CurFileName,'');
    CurFileTemp:=GenerateUniqueName(CurFilePath,'.'+CurFileStem);

    // Clean-up by trying to delete any previously renamed temporary files.
    DelTree(CurFilePath+'\*.'+CurFileStem,False,True,False);

    UnregisterFailed:=False;
    RenameFailed:=False;

    if FileExists(CurFile) then begin
        if Register and (not UnregisterServer(Is64BitInstallMode,CurFile,False)) then begin
            UnregisterFailed:=True;
        end;

        if (not DeleteFile(CurFile)) and (not RenameFile(CurFile,CurFileTemp)) then begin
            RenameFailed:=True;
        end;
    end;

    if not RenameFile(NewFile,CurFile) then begin
        ErrorMsg:='Unable to install a new version of "'+CurFileName+'". ' +
                  'Please finish the installation manually by following theses steps on the command line:' + #13 + #13;
        if FileExists(CurFile) then begin
            if UnregisterFailed then begin
                ErrorMsg := ErrorMsg + '- run "regsvr32 /u ' + CurFileName + '",' + #13;
            end;
            if RenameFailed then begin
                ErrorMsg := ErrorMsg + '- rename "' + CurFileName + '" to something else,' + #13;
            end;
        end;
        ErrorMsg         := ErrorMsg + '- rename "' + NewFileName + '" to "' + CurFileName + '",' + #13;
        ErrorMsg         := ErrorMsg + '- run "regsvr32 ' + CurFileName + '".';
    end else begin
        if Register then begin
            RegisterServer(Is64BitInstallMode,CurFile,False);
        end;
        Result:=True;
    end;
end;

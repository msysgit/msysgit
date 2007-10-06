#define APP_NAME     'Git'
#define APP_VERSION  '%APPVERSION%'
#define APP_URL      'http://code.google.com/p/msysgit/'
#define APP_BUILTINS 'etc\fileList-builtins.txt'

[Setup]
; Compiler-related
OutputBaseFilename={#emit APP_NAME+'-'+APP_VERSION}
OutputDir=%OUTPUTDIR%
SolidCompression=yes

; Installer-related
AllowNoIcons=yes
AppName={#emit APP_NAME}
AppPublisherURL={#emit APP_URL}
AppVersion={#emit APP_VERSION}
AppVerName={#emit APP_NAME+' '+APP_VERSION}
DefaultDirName={pf}\{#emit APP_NAME}
DefaultGroupName={#emit APP_NAME}
DisableReadyPage=yes
LicenseFile=gpl-2.0.txt

; Cosmetic
SetupIconFile=etc\git.ico
WizardSmallImageFile=install.bmp

[Tasks]
Name: quicklaunchicon; Description: "Create a &Quick Launch icon"; GroupDescription: "Additional icons:"; Flags: checkedonce
Name: desktopicon; Description: "Create a &Desktop icon"; GroupDescription: "Additional icons:"; Flags: checkedonce
Name: shellextension; Description: "Add ""Git Shell Here"" "; GroupDescription: "Shell extensions:"; Flags: checkedonce
Name: guiextension; Description: "Add ""Git GUI Here"" "; GroupDescription: "Shell extensions:"; Flags: checkedonce

[Files]
Source: "*"; DestDir: "{app}"; Excludes: "\*.txt, \install.*, \tmp.*, \bin\*install*"; Flags: recursesubdirs

[Icons]
Name: "{group}\Git GUI"; Filename: "{app}\bin\wish.exe"; Parameters: "{app}\bin\git-gui"; WorkingDir: "%APPDATA%\Git"; IconFilename: "{app}\etc\git.ico"
Name: "{group}\Git Shell"; Filename: "{app}\bin\sh.exe"; Parameters: "--login -i"; WorkingDir: "%APPDATA%\Git"; IconFilename: "{app}\etc\git.ico"
Name: "{group}\Uninstall Git"; Filename: "{uninstallexe}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Git Shell"; Filename: "{app}\bin\sh.exe"; Parameters: "--login -i"; WorkingDir: "%APPDATA%\Git"; IconFilename: "{app}\etc\git.ico"; Tasks: quicklaunchicon
Name: "{userdesktop}\Git Shell"; Filename: "{app}\bin\sh.exe"; Parameters: "--login -i"; WorkingDir: "%APPDATA%\Git"; IconFilename: "{app}\etc\git.ico"; Tasks: desktopicon

[Messages]
BeveledLabel={#emit APP_URL}

[Registry]
Root: HKLM; Subkey: "SOFTWARE\Classes\Directory\shell\git_shell"; ValueType: string; ValueData: "Git &Shell Here"; Flags: uninsdeletevalue uninsdeletekeyifempty; Tasks: shellextension
Root: HKLM; Subkey: "SOFTWARE\Classes\Directory\shell\git_shell\command"; ValueType: string; ValueData: "cmd.exe /c ""pushd ""%1"" && ""{app}\bin\sh.exe"" --login -i"""; Flags: uninsdeletevalue uninsdeletekeyifempty; Tasks: shellextension
Root: HKLM; Subkey: "SOFTWARE\Classes\Directory\shell\git_gui"; ValueType: string; ValueData: "Git &GUI Here"; Flags: uninsdeletevalue uninsdeletekeyifempty; Tasks: guiextension
Root: HKLM; Subkey: "SOFTWARE\Classes\Directory\shell\git_gui\command"; ValueType: string; ValueData: """{app}\bin\wish.exe"" ""{app}\bin\git-gui"""; Flags: uninsdeletevalue uninsdeletekeyifempty; Tasks: guiextension

[UninstallDelete]
Type: files; Name: "{app}\bin\git-*.exe"
Type: dirifempty; Name: "{app}\home\{username}"
Type: dirifempty; Name: "{app}\home"

[Code]
procedure InitializeWizard;
begin
   // Use a mono spaced font in the license dialog. NOTE: This might be too small.
   WizardForm.LicenseMemo.Font.Name:='Lucida Console';
   WizardForm.LicenseMemo.Font.Size:=7;
end;

function CreateHardLink(lpFileName,lpExistingFileName:string;lpSecurityAttributes:Integer):Boolean;
external 'CreateHardLinkA@Kernel32.dll';

procedure CurStepChanged(CurStep:TSetupStep);
var
    ListFile,AppDir:string;
    BuiltIns:TArrayOfString;
    i:Longint;
    IsNTFS:Boolean;
begin
    if CurStep<>ssDone then begin
        Exit;
    end;

    // Load the built-ins from a text file.
    ListFile:=ExpandConstant('{app}\'+'{#emit APP_BUILTINS}');
    if not LoadStringsFromFile(ListFile,BuiltIns) then begin
        MsgBox('Unable to read file "{#emit APP_BUILTINS}".', mbError, MB_OK);
        Exit;
    end;

    AppDir:=ExpandConstant('{app}');

    // Check if we are running on NTFS.
    IsNTFS:=False;
    if SetNTFSCompression(AppDir+'\bin\git.exe',true) then begin
        IsNTFS:=SetNTFSCompression(AppDir+'\bin\git.exe',false);
    end;

    // Map the built-ins to git.exe.
    if IsNTFS then begin
        for i:=0 to GetArrayLength(BuiltIns)-1 do begin
            // On non-NTFS partitions, create hard links.
            CreateHardLink(AppDir+'\'+BuiltIns[i],AppDir+'\bin\git.exe',0);
        end;
    end else begin
        for i:=0 to GetArrayLength(BuiltIns)-1 do begin
            // On non-NTFS partitions, copy simply the files.
            FileCopy(AppDir+'\bin\git.exe',AppDir+'\'+BuiltIns[i],false);
        end;
    end;
end;


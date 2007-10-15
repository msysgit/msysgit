#define APP_NAME     'Git'
#define APP_VERSION  '%APPVERSION%'
#define APP_URL      'http://code.google.com/p/msysgit/'
#define APP_BUILTINS 'etc\fileList-builtins.txt'

[Setup]
; Compiler-related
InternalCompressLevel=max
OutputBaseFilename={#emit APP_NAME+'-'+APP_VERSION}
OutputDir=%OUTPUTDIR%
SolidCompression=yes

; Installer-related
AllowNoIcons=yes
AppName={#emit APP_NAME}
AppPublisherURL={#emit APP_URL}
AppVersion={#emit APP_VERSION}
AppVerName={#emit APP_NAME+' '+APP_VERSION}
ChangesEnvironment=yes
DefaultDirName={pf}\{#emit APP_NAME}
DefaultGroupName={#emit APP_NAME}
DisableReadyPage=yes
LicenseFile=gpl-2.0.txt
UninstallDisplayIcon=etc\git.ico

; Cosmetic
SetupIconFile=etc\git.ico
WizardSmallImageFile=install.bmp

[Tasks]
Name: modifypath; Description: "Modify &PATH environment variable"; Flags: checkedonce
Name: modifypath\git; Description: "Add &only Git"; Flags: exclusive
Name: modifypath\tools; Description: "Add Git and UNIX &tools"; Flags: exclusive unchecked

Name: shellextension; Description: "Add ""Git &Bash Here"" to Windows Explorer"; Flags: checkedonce
Name: guiextension; Description: "Add ""Git &GUI Here"" to Windows Explorer"; Flags: checkedonce

Name: quicklaunchicon; Description: "Create a &Quick Launch icon"; GroupDescription: "Additional icons:"; Flags: checkedonce
Name: desktopicon; Description: "Create a &Desktop icon"; GroupDescription: "Additional icons:"; Flags: checkedonce

[Files]
Source: "*"; DestDir: "{app}"; Excludes: "\*.txt, \install.*, \tmp.*, \bin\*install*"; Flags: recursesubdirs

[Icons]
Name: "{group}\Git GUI"; Filename: "{app}\bin\wish.exe"; Parameters: """{app}\bin\git-gui"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"
Name: "{group}\Git Bash"; Filename: "{app}\bin\sh.exe"; Parameters: "--login -i"; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"
Name: "{group}\Uninstall Git"; Filename: "{uninstallexe}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Git Bash"; Filename: "{app}\bin\sh.exe"; Parameters: "--login -i"; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"; Tasks: quicklaunchicon
Name: "{userdesktop}\Git Bash"; Filename: "{app}\bin\sh.exe"; Parameters: "--login -i"; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"; Tasks: desktopicon

[Messages]
BeveledLabel={#emit APP_URL}

[Registry]
Root: HKLM; Subkey: "SOFTWARE\Classes\Directory\shell\git_shell"; ValueType: string; ValueData: "Git &Shell Here"; Flags: uninsdeletevalue uninsdeletekeyifempty; Tasks: shellextension
Root: HKLM; Subkey: "SOFTWARE\Classes\Directory\shell\git_shell\command"; ValueType: string; ValueData: "cmd.exe /c ""pushd ""%1"" && ""{app}\bin\sh.exe"" --login -i"""; Flags: uninsdeletevalue uninsdeletekeyifempty; Tasks: shellextension
Root: HKLM; Subkey: "SOFTWARE\Classes\Directory\shell\git_gui"; ValueType: string; ValueData: "Git &GUI Here"; Flags: uninsdeletevalue uninsdeletekeyifempty; Tasks: guiextension
Root: HKLM; Subkey: "SOFTWARE\Classes\Directory\shell\git_gui\command"; ValueType: string; ValueData: """{app}\bin\wish.exe"" ""{app}\bin\git-gui"" ""--working-dir"" ""%1"""; Flags: uninsdeletevalue uninsdeletekeyifempty; Tasks: guiextension

[UninstallDelete]
Type: files; Name: "{app}\bin\git-*.exe"
Type: dirifempty; Name: "{app}\home\{username}"
Type: dirifempty; Name: "{app}\home"

[Code]
function ModPathDir:TArrayOfString;
var
    IsModifyPathGit,IsModifyPathTools:Boolean;
    SelectedTasks:String;
begin
    if IsUninstaller then begin
        if LoadStringFromFile(ExpandConstant('{app}')+'\uninsTasks.txt',SelectedTasks) then begin
            IsModifyPathGit:=Pos('modifypath\git',SelectedTasks)>0;
            IsModifyPathTools:=Pos('modifypath\tools',SelectedTasks)>0;
        end else begin
            IsModifyPathGit:=False;
            IsModifyPathTools:=False;
        end;
    end else begin
        IsModifyPathGit:=IsTaskSelected('modifypath\git');
        IsModifyPathTools:=IsTaskSelected('modifypath\tools');
    end;

    if IsModifyPathGit then begin
        setArrayLength(Result,1);
        Result[0]:=ExpandConstant('{app}\cmd');
    end else if IsModifyPathTools then begin
        setArrayLength(Result,2);
        Result[0]:=ExpandConstant('{app}\bin');
        Result[1]:=ExpandConstant('{app}\mingw\bin');
    end;
end;
#include "modpath.iss"

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
    if CurStep=ssPostInstall then begin
        if IsTaskSelected('modifypath') then begin
            ModPath();
        end;
    end else if CurStep=ssDone then begin
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
end;

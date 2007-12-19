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
InfoAfterFile=ReleaseNotes.rtf
LicenseFile=gpl-2.0.rtf
PrivilegesRequired=none
UninstallDisplayIcon=etc\git.ico

; Cosmetic
SetupIconFile=etc\git.ico
WizardSmallImageFile=git.bmp

[Tasks]
Name: quicklaunchicon; Description: "Create a &Quick Launch icon"; GroupDescription: "Additional icons:"; Flags: checkedonce
Name: desktopicon; Description: "Create a &Desktop icon"; GroupDescription: "Additional icons:"; Flags: checkedonce
Name: shellextension; Description: "Add ""Git Ba&sh Here"""; GroupDescription: "Windows Explorer integration:"; Flags: checkedonce
Name: guiextension; Description: "Add ""Git &GUI Here"""; GroupDescription: "Windows Explorer integration:"; Flags: checkedonce

[Files]
Source: "*"; DestDir: "{app}"; Excludes: "\*.bmp, gpl-2.0.rtf, \install.*, \tmp.*, \bin\*install*"; Flags: recursesubdirs

[Icons]
Name: "{group}\Git GUI"; Filename: "{app}\bin\wish.exe"; Parameters: """{app}\bin\git-gui"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"
Name: "{group}\Git Bash"; Filename: "{syswow64}\cmd.exe"; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"
Name: "{group}\Uninstall Git"; Filename: "{uninstallexe}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Git Bash"; Filename: "{syswow64}\cmd.exe"; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"; Tasks: quicklaunchicon
Name: "{code:GetShellFolder|desktop}\Git Bash"; Filename: "{syswow64}\cmd.exe"; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"; Tasks: desktopicon

[Messages]
BeveledLabel={#emit APP_URL}

[UninstallDelete]
Type: files; Name: "{app}\bin\git-*.exe"
Type: dirifempty; Name: "{app}\home\{username}"
Type: dirifempty; Name: "{app}\home"

[Code]
{
    Helper methods
}

function GetShellFolder(Param:string):string;
begin
    if IsAdminLoggedOn then begin
        Param:='{common'+Param+'}';
    end else begin
        Param:='{user'+Param+'}';
    end;
    Result:=ExpandConstant(Param);
end;

function CreateHardLink(lpFileName,lpExistingFileName:string;lpSecurityAttributes:Integer):Boolean;
external 'CreateHardLinkA@Kernel32.dll';

function GetEnvStrings(VarName:string;AllUsers:Boolean):TArrayOfString;
var
    Path:string;
    i:Longint;
    p:Integer;
begin
    Path:='';

    // See http://www.jrsoftware.org/isfaq.php#env
    if AllUsers then begin
        // We ignore errors here. The resulting array of strings will be empty.
        RegQueryStringValue(HKEY_LOCAL_MACHINE,'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',VarName,Path);
    end else begin
        // We ignore errors here. The resulting array of strings will be empty.
        RegQueryStringValue(HKEY_CURRENT_USER,'Environment',VarName,Path);
    end;

    // Make sure we have at least one semicolon.
    Path:=Path+';';

    // Split the directories in PATH into an array of strings.
    i:=0;
    SetArrayLength(Result,0);

    p:=Pos(';',Path);
    while p>0 do begin
        SetArrayLength(Result,i+1);
        if p>1 then begin
            Result[i]:=Copy(Path,1,p-1);
            i:=i+1;
        end;
        Path:=Copy(Path,p+1,Length(Path));
        p:=Pos(';',Path);
    end;
end;

function SetEnvStrings(VarName:string;AllUsers,DeleteIfEmpty:Boolean;DirStrings:TArrayOfString):Boolean;
var
    Path,KeyName:string;
    i:Longint;
begin
    // Merge all non-empty directory strings into a PATH variable.
    Path:='';
    for i:=0 to GetArrayLength(DirStrings)-1 do begin
        if Length(DirStrings[i])>0 then begin
            if Length(Path)>0 then begin
                Path:=Path+';'+DirStrings[i];
            end else begin
                Path:=DirStrings[i];
            end;
        end;
    end;

    // See http://www.jrsoftware.org/isfaq.php#env
    if AllUsers then begin
        KeyName:='SYSTEM\CurrentControlSet\Control\Session Manager\Environment';
        if DeleteIfEmpty and (Length(Path)=0) then begin
            Result:=(not RegValueExists(HKEY_LOCAL_MACHINE,KeyName,VarName))
                      or RegDeleteValue(HKEY_LOCAL_MACHINE,KeyName,VarName);
        end else begin
            Result:=RegWriteStringValue(HKEY_LOCAL_MACHINE,KeyName,VarName,Path);
        end;
    end else begin
        KeyName:='Environment';
        if DeleteIfEmpty and (Length(Path)=0) then begin
            Result:=(not RegValueExists(HKEY_CURRENT_USER,KeyName,VarName))
                      or RegDeleteValue(HKEY_CURRENT_USER,KeyName,VarName);
        end else begin
            Result:=RegWriteStringValue(HKEY_CURRENT_USER,KeyName,VarName,Path);
        end;
    end;
end;

{
    Installer code
}

var
    EnvPage:TWizardPage;
    RdbGitBash,RdbGitCmd,RdbGitCmdTools:TRadioButton;

procedure InitializeWizard;
var
    LblGitBash,LblGitCmd,LblGitCmdTools,LblGitCmdToolsWarn:TLabel;
begin
    // Create a custom page for modifying the environment.
    EnvPage:=CreateCustomPage(
        wpSelectTasks,
        'Adjusting your PATH environment',
        'How would you like to use Git from the command line?'
    );

    // 1st choice
    RdbGitBash:=TRadioButton.Create(EnvPage);
    with RdbGitBash do begin
      Parent:=EnvPage.Surface;
      Caption:='Use Git Bash only';
      Left:=ScaleX(4);
      Top:=ScaleY(8);
      Width:=ScaleX(129);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=0;
      Checked:=True;
    end;
    LblGitBash:=TLabel.Create(EnvPage);
    with LblGitBash do begin
        Parent:=EnvPage.Surface;
        Caption:=
            'This is the most conservative choice if you are concerned about the' + #13 +
            'stability of your system. Your PATH will not be modified.';
        Left:=ScaleX(28);
        Top:=ScaleY(32);
        Width:=ScaleX(324);
        Height:=ScaleY(26);
    end;

    // 2nd choice
    RdbGitCmd:=TRadioButton.Create(EnvPage);
    with RdbGitCmd do begin
      Parent:=EnvPage.Surface;
      Caption:='Run Git from the Windows Command Prompt';
      Left:=ScaleX(4);
      Top:=ScaleY(76);
      Width:=ScaleX(281);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=1;
    end;
    LblGitCmd:=TLabel.Create(EnvPage);
    with LblGitCmd do begin
        Parent:=EnvPage.Surface;
        Caption:=
            'This option is considered safe and no conflicts with other tools are' + #13 +
            'known. Only Git will be added to your PATH.';
        Left:=ScaleX(28);
        Top:=ScaleY(100);
        Width:=ScaleX(316);
        Height:=ScaleY(26);
    end;

    // 3rd choice
    RdbGitCmdTools:=TRadioButton.Create(EnvPage);
    with RdbGitCmdTools do begin
      Parent:=EnvPage.Surface;
      Caption:='Run Git and included Unix tools from the Windows Command Prompt';
      Left:=ScaleX(4);
      Top:=ScaleY(152);
      Width:=ScaleX(405);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=2;
    end;
    LblGitCmdTools:=TLabel.Create(EnvPage);
    with LblGitCmdTools do begin
        Parent:=EnvPage.Surface;
        Caption:='Both Git and the Unix tools will be added to your PATH.';
        Left:=ScaleX(28);
        Top:=ScaleY(176);
        Width:=ScaleX(280);
        Height:=ScaleY(13);
    end;
    LblGitCmdToolsWarn:=TLabel.Create(EnvPage);
    with LblGitCmdToolsWarn do begin
        Parent:=EnvPage.Surface;
        Caption:=
            'Warning: This will override Windows tools like find.exe and' + #13 +
            'sort.exe. Select this option only if you understand the implications.';
        Left:=ScaleX(28);
        Top:=ScaleY(192);
        Width:=ScaleX(376);
        Height:=ScaleY(26);
        Font.Color:=255;
        Font.Style:=[fsBold];
    end;
end;

procedure CurStepChanged(CurStep:TSetupStep);
var
    AppDir,FileName,Cmd,Msg:string;
    BuiltIns,EnvPath,EnvHome:TArrayOfString;
    Count,i:Longint;
    IsNTFS:Boolean;
    RootKey:Integer;
begin
    if CurStep<>ssPostInstall then begin
        Exit;
    end;

    AppDir:=ExpandConstant('{app}');

    {
        Create the built-ins
    }

    // Load the built-ins from a text file.
    FileName:=ExpandConstant('{app}\'+'{#emit APP_BUILTINS}');
    if LoadStringsFromFile(FileName,BuiltIns) then begin
        // Check if we are running on NTFS.
        IsNTFS:=False;
        if SetNTFSCompression(AppDir+'\bin\git.exe',true) then begin
            IsNTFS:=SetNTFSCompression(AppDir+'\bin\git.exe',false);
        end;

        Count:=GetArrayLength(BuiltIns)-1;

        // Map the built-ins to git.exe.
        if IsNTFS then begin
            Log('Line {#emit __LINE__}: Partition seems to be NTFS, trying to create built-in aliases as hard links.');

            for i:=0 to Count do begin
                FileName:=AppDir+'\'+BuiltIns[i];

                // On non-NTFS partitions, create hard links.
                if (FileExists(FileName) and (not DeleteFile(FileName)))
                or (not CreateHardLink(FileName,AppDir+'\bin\git.exe',0)) then begin
                    Log('Line {#emit __LINE__}: Unable to create hard link "'+FileName+'", will try to copy files.');
                    IsNTFS:=False;
                    Break;
                end;
            end;

            Log('Line {#emit __LINE__}: Successfully created built-in aliases as hard links.');
        end;

        // The fallback is to copy the files.
        if not IsNTFS then begin
            Log('Line {#emit __LINE__}: Trying to create built-in aliases as file copies.');

            for i:=0 to Count do begin
                FileName:=AppDir+'\'+BuiltIns[i];

                // On non-NTFS partitions, copy simply the files (overwriting existing ones).
                if not FileCopy(AppDir+'\bin\git.exe',FileName,false) then begin
                    Msg:='Line {#emit __LINE__}: Unable to create file copy "'+FileName+'".';
                    MsgBox(Msg,mbError,MB_OK);
                    Log(Msg);
                    // This is not a critical error, Git could basically be used without the
                    // aliases for built-ins, so we continue.
                end;
            end;

            Log('Line {#emit __LINE__}: Successfully created built-in aliases as file copies.');
        end;
    end else begin
        Msg:='Line {#emit __LINE__}: Unable to read file "{#emit APP_BUILTINS}".';
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
        // This is not a critical error, Git could basically be used without the
        // aliases for built-ins, so we continue.
    end;


    {
        Modify the environment

        This must happen no later than ssPostInstall to make
        "ChangesEnvironment=yes" not happend before the change!
    }

    // Get the current user's directories in PATH.
    EnvPath:=GetEnvStrings('PATH',IsAdminLoggedOn);

    // First, remove the installation directory from PATH in any case.
    for i:=0 to GetArrayLength(EnvPath)-1 do begin
        if Pos(AppDir,EnvPath[i])=1 then begin
            EnvPath[i]:='';
        end;
    end;

    // Delete HOME if a previous installation modified it.
    EnvHome:=GetEnvStrings('HOME',IsAdminLoggedOn);
    if (GetArrayLength(EnvHome)=1) and
       (CompareStr(EnvHome[0],GetIniString('Environment','HOME','',AppDir+'\setup.ini'))=0) then begin
        if not SetEnvStrings('HOME',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to reset HOME prior to install.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    // Modify the PATH variable as requested by the user.
    if RdbGitCmd.Checked or RdbGitCmdTools.Checked then begin
        i:=GetArrayLength(EnvPath);
        SetArrayLength(EnvPath,i+1);

        // List \cmd before \bin so \cmd has higher priority and programs in
        // there will be called in favor of those in \bin.
        EnvPath[i]:=ExpandConstant('{app}\cmd');

        if RdbGitCmdTools.Checked then begin
            SetArrayLength(EnvPath,i+2);
            EnvPath[i+1]:=ExpandConstant('{app}\bin');

            // Set HOME for the Windows Command Prompt.
            EnvHome:=GetEnvStrings('HOME',IsAdminLoggedOn);
            i:=GetArrayLength(EnvHome);
            if (i=0) or ((i=1) and (Length(EnvHome[0])=0)) then begin
                SetArrayLength(EnvHome,1);
                EnvHome[0]:=ExpandConstant('{%USERPROFILE}');
                if not SetEnvStrings('HOME',IsAdminLoggedOn,True,EnvHome) then begin
                    Msg:='Line {#emit __LINE__}: Unable to set the HOME environment variable.';
                    MsgBox(Msg,mbError,MB_OK);
                    Log(Msg);
                    // This is not a critical error, the user can probably fix it manually,
                    // so we continue.
                end;

                // Mark that we have changed HOME.
                FileName:=AppDir+'\setup.ini';
                if not SetIniString('Environment','HOME',EnvHome[0],FileName) then begin
                    Msg:='Line {#emit __LINE__}: Unable to write to file "'+FileName+'".';
                    MsgBox(Msg,mbError,MB_OK);
                    Log(Msg);
                    // This is not a critical error, though uninstall / reinstall will probably not run cleanly,
                    // so we continue.
                end;
            end;
        end;
    end;

    // Set the current user's PATH directories.
    if not SetEnvStrings('PATH',IsAdminLoggedOn,True,EnvPath) then begin
        Msg:='Line {#emit __LINE__}: Unable to set the PATH environment variable.';
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
        // This is not a critical error, the user can probably fix it manually,
        // so we continue.
    end;

    {
        Create the Windows Explorer shell extensions
    }

    if IsAdminLoggedOn then begin
        RootKey:=HKEY_LOCAL_MACHINE;
    end else begin
        RootKey:=HKEY_CURRENT_USER;
    end;

    if IsTaskSelected('shellextension') then begin
        Cmd:=ExpandConstant('"{syswow64}\cmd.exe"');
        if (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell','','Git Ba&sh Here'))
        or (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell\command','',Cmd+' /c "pushd "%1" && "'+AppDir+'\bin\sh.exe" --login -i"')) then begin
            Msg:='Line {#emit __LINE__}: Unable to create "Git Bash Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    if IsTaskSelected('guiextension') then begin
        if (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui','','Git &GUI Here'))
        or (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui\command','','"'+AppDir+'\bin\wish.exe" "'+AppDir+'\bin\git-gui" "--working-dir" "%1"')) then begin
            Msg:='Line {#emit __LINE__}: Unable to create "Git GUI Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;
end;

{
    Uninstaller code
}

function InitializeUninstall:Boolean;
var
    FileName,NewName,Msg:string;
begin
    FileName:=ExpandConstant('{app}')+'\bin\ssh-agent.exe';
    if FileExists(FileName) then begin
        // Create a temporary copy of the file we try to delete.
        NewName:=FileName+'.'+IntToStr(1000+Random(9000));
        Result:=FileCopy(FileName,NewName,True) and DeleteFile(FileName);

        if not Result then begin
            Msg:='Line {#emit __LINE__}: Please stop all ssh-agent processes and run uninstall again.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);

            // Clean-up the temporary copy (ignoring any errors).
            DeleteFile(NewName);
        end else begin
            // Clean-up the temporary copy (ignoring any errors).
            RenameFile(NewName,FileName);
        end;
    end else begin
        Result:=True;
    end;
end;

procedure CurUninstallStepChanged(CurUninstallStep:TUninstallStep);
var
    AppDir,Command,Msg:string;
    EnvPath,EnvHome:TArrayOfString;
    i:Longint;
    RootKey:Integer;
begin
    if CurUninstallStep<>usUninstall then begin
        Exit;
    end;

    {
        Modify the environment

        This must happen no later than usUninstall to make
        "ChangesEnvironment=yes" not happend before the change!
    }

    AppDir:=ExpandConstant('{app}');

    // Get the current user's directories in PATH.
    EnvPath:=GetEnvStrings('PATH',IsAdminLoggedOn);

    // Remove the installation directory from PATH in any case, even if it
    // was not added by the installer.
    for i:=0 to GetArrayLength(EnvPath)-1 do begin
        if Pos(AppDir,EnvPath[i])=1 then begin
            EnvPath[i]:='';
        end;
    end;

    // Reset the current user's directories in PATH.
    if not SetEnvStrings('PATH',IsAdminLoggedOn,True,EnvPath) then begin
        Msg:='Line {#emit __LINE__}: Unable to revert any possible changes to PATH.';
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
        // This is not a critical error, the user can probably fix it manually,
        // so we continue.
    end;

    // Reset the current user's HOME if we modified it.
    EnvHome:=GetEnvStrings('HOME',IsAdminLoggedOn);
    if (GetArrayLength(EnvHome)=1) and
       (CompareStr(EnvHome[0],GetIniString('Environment','HOME','',AppDir+'\setup.ini'))=0) then begin
        if not SetEnvStrings('HOME',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to revert any possible changes to HOME.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    Command:=AppDir+'\setup.ini';
    if not DeleteFile(Command) then begin
        Msg:='Line {#emit __LINE__}: Unable to delete file "'+Command+'".';
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
        // This is not a critical error, the user can probably fix it manually,
        // so we continue.
    end;

    {
        Delete the Windows Explorer shell extensions
    }

    if IsAdminLoggedOn then begin
        RootKey:=HKEY_LOCAL_MACHINE;
    end else begin
        RootKey:=HKEY_CURRENT_USER;
    end;

    Command:='';
    RegQueryStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell\command','',Command);
    if Pos(AppDir,Command)>0 then begin
        if not RegDeleteKeyIncludingSubkeys(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell') then begin
            Msg:='Line {#emit __LINE__}: Unable to remove "Git Bash Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    Command:='';
    RegQueryStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui\command','',Command);
    if Pos(AppDir,Command)>0 then begin
        if not RegDeleteKeyIncludingSubkeys(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui') then begin
            Msg:='Line {#emit __LINE__}: Unable to remove "Git GUI Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;
end;

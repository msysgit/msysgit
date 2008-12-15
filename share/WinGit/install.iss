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
InfoBeforeFile=gpl-2.0.rtf
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
Source: ReleaseNotes.rtf; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\Git GUI"; Filename: "{app}\bin\wish.exe"; Parameters: """{app}\libexec\git-core\git-gui"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"
Name: "{group}\Git Bash"; Filename: "{syswow64}\cmd.exe"; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"
Name: "{group}\Uninstall Git"; Filename: "{uninstallexe}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Git Bash"; Filename: "{syswow64}\cmd.exe"; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"; Tasks: quicklaunchicon
Name: "{code:GetShellFolder|desktop}\Git Bash"; Filename: "{syswow64}\cmd.exe"; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: "%USERPROFILE%"; IconFilename: "{app}\etc\git.ico"; Tasks: desktopicon

[Messages]
BeveledLabel={#emit APP_URL}
SetupAppTitle={#emit APP_NAME} Setup
SetupWindowTitle={#emit APP_NAME} Setup

[UninstallDelete]
Type: files; Name: "{app}\bin\git-*.exe"
Type: files; Name: "{app}\libexec\git-core\git-*.exe"
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

const
    PuTTYUninstallKey='SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\PuTTY_is1';
    PuTTYPrivateKeyAssoc='PuTTYPrivateKey\shell\open\command';

function GetPuTTYLocation:string;
begin
    if RegQueryStringValue(HKEY_LOCAL_MACHINE,PuTTYUninstallKey,'InstallLocation',Result) and DirExists(Result) then begin
        // C:\Program Files\PuTTY\
        Exit;
    end;
    if RegQueryStringValue(HKEY_CLASSES_ROOT,PuTTYPrivateKeyAssoc,'',Result) then begin
        // "C:\Program Files\PuTTY\pageant.exe" "%1"
        Result:=RemoveQuotes(Result);
        // C:\Program Files\PuTTY\pageant.exe" "%1
        Result:=ExtractFilePath(Result);
        // C:\Program Files\PuTTY\
        if DirExists(Result) then begin
            Exit;
        end;
    end;
    // Guess something.
    Result:='C:\Program Files\PuTTY\';
end;

const
    // Git Path options.
    GP_BashOnly       = 1;
    GP_Cmd            = 2;
    GP_CmdTools       = 3;

    // Git SSH options.
    GS_OpenSSH        = 1;
    GS_PLink          = 2;

    // Git CRLF options.
    GC_LFOnly         = 1;
    GC_CRLFAlways     = 2;
    GC_CRLFCommitAsIs = 3;

var
    // Wizard page and variables for the Path options.
    PathPage:TWizardPage;
    RdbPath:array[GP_BashOnly..GP_CmdTools] of TRadioButton;

    // Wizard page and variables for the SSH options.
    PuTTYPage:TWizardPage;
    RdbSSH:array[GS_OpenSSH..GS_PLink] of TRadioButton;
    EdtPLink:TEdit;

    // Wizard page and variables for the CR/LF options.
    CRLFPage:TWizardPage;
    RdbCRLF:array[GC_LFOnly..GC_CRLFCommitAsIs] of TRadioButton;

procedure BrowseForPuTTYFolder(Sender:TObject);
var
    Path:string;
begin
    Path:=ExtractFilePath(EdtPLink.Text);
    BrowseForFolder('Please select the PuTTY folder:',Path,False);
    Path:=Path+'\plink.exe';
    if FileExists(Path) then begin
        EdtPLink.Text:=Path;
        RdbSSH[GS_PLink].Checked:=True;
    end else begin
        MsgBox('Please enter a valid path to plink.exe.',mbError,MB_OK);
    end;
end;

{
    Installer code
}

procedure InitializeWizard;
var
    LblGitBash,LblGitCmd,LblGitCmdTools,LblGitCmdToolsWarn:TLabel;
    LblOpenSSH,LblPLink:TLabel;
    LblLFOnly,LblCRLFAlways,LblCRLFCommitAsIs:TLabel;
    BtnPLink:TButton;
    Data:String;
begin
    // Create a custom page for modifying the environment.
    PathPage:=CreateCustomPage(
        wpSelectTasks,
        'Adjusting your PATH environment',
        'How would you like to use Git from the command line?'
    );

    // 1st choice
    RdbPath[GP_BashOnly]:=TRadioButton.Create(PathPage);
    with RdbPath[GP_BashOnly] do begin
      Parent:=PathPage.Surface;
      Caption:='Use Git Bash only';
      Left:=ScaleX(4);
      Top:=ScaleY(8);
      Width:=ScaleX(129);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=0;
      Checked:=True;
    end;
    LblGitBash:=TLabel.Create(PathPage);
    with LblGitBash do begin
        Parent:=PathPage.Surface;
        Caption:=
            'This is the most conservative choice if you are concerned about the stability' + #13 +
            'of your system. Your PATH will not be modified.';
        Left:=ScaleX(28);
        Top:=ScaleY(32);
        Width:=ScaleX(405);
        Height:=ScaleY(26);
    end;

    // 2nd choice
    RdbPath[GP_Cmd]:=TRadioButton.Create(PathPage);
    with RdbPath[GP_Cmd] do begin
      Parent:=PathPage.Surface;
      Caption:='Run Git from the Windows Command Prompt';
      Left:=ScaleX(4);
      Top:=ScaleY(76);
      Width:=ScaleX(281);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=1;
    end;
    LblGitCmd:=TLabel.Create(PathPage);
    with LblGitCmd do begin
        Parent:=PathPage.Surface;
        Caption:=
            'This option is considered safe and no conflicts with other tools are known.' + #13 +
            'Only Git will be added to your PATH. Use this option if you want to use Git' + #13 +
            'from a Cygwin Prompt (make sure to not have Cygwin''s Git installed).';
        Left:=ScaleX(28);
        Top:=ScaleY(100);
        Width:=ScaleX(405);
        Height:=ScaleY(39);
    end;

    // 3rd choice
    RdbPath[GP_CmdTools]:=TRadioButton.Create(PathPage);
    with RdbPath[GP_CmdTools] do begin
      Parent:=PathPage.Surface;
      Caption:='Run Git and included Unix tools from the Windows Command Prompt';
      Left:=ScaleX(4);
      Top:=ScaleY(152);
      Width:=ScaleX(405);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=2;
    end;
    LblGitCmdTools:=TLabel.Create(PathPage);
    with LblGitCmdTools do begin
        Parent:=PathPage.Surface;
        Caption:='Both Git and its accompanying Unix tools will be added to your PATH.';
        Left:=ScaleX(28);
        Top:=ScaleY(176);
        Width:=ScaleX(405);
        Height:=ScaleY(13);
    end;
    LblGitCmdToolsWarn:=TLabel.Create(PathPage);
    with LblGitCmdToolsWarn do begin
        Parent:=PathPage.Surface;
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

    // Restore the setting chosen during a previous install.
    Data:=GetPreviousData('Path Option','BashOnly');
    if Data='BashOnly' then begin
        RdbPath[GP_BashOnly].Checked:=True;
    end else if Data='Cmd' then begin
        RdbPath[GP_Cmd].Checked:=True;
    end else if Data='CmdTools' then begin
        RdbPath[GP_CmdTools].Checked:=True;
    end;

    // Create a custom page for using PuTTY's plink instead of ssh.
    PuTTYPage:=CreateCustomPage(
        PathPage.ID,
        'Choosing the SSH executable',
        'Which Secure Shell client program would you like Git to use?'
    );

    // 1st choice
    RdbSSH[GS_OpenSSH]:=TRadioButton.Create(PuTTYPage);
    with RdbSSH[GS_OpenSSH] do begin
      Parent:=PuTTYPage.Surface;
      Caption:='Use OpenSSH';
      Left:=ScaleX(4);
      Top:=ScaleY(8);
      Width:=ScaleX(129);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=0;
      Checked:=True;
    end;
    LblOpenSSH:=TLabel.Create(PuTTYPage);
    with LblOpenSSH do begin
        Parent:=PuTTYPage.Surface;
        Caption:=
            'This uses ssh.exe that comes with Git. The GIT_SSH environment' + #13 +
            'variable will not be modified.';
        Left:=ScaleX(28);
        Top:=ScaleY(32);
        Width:=ScaleX(324);
        Height:=ScaleY(26);
    end;

    // 2nd choice
    RdbSSH[GS_PLink]:=TRadioButton.Create(PuTTYPage);
    with RdbSSH[GS_PLink] do begin
      Parent:=PuTTYPage.Surface;
      Caption:='Use PLink';
      Left:=ScaleX(4);
      Top:=ScaleY(76);
      Width:=ScaleX(281);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=1;
    end;
    LblPLink:=TLabel.Create(PuTTYPage);
    with LblPLink do begin
        Parent:=PuTTYPage.Surface;
        Caption:=
            'This uses plink.exe from the PuTTY package which needs to be' + #13 +
            'provided by the user. The GIT_SSH environment variable will be' + #13 +
            'set to the path to plink.exe as specified below.';
        Left:=ScaleX(28);
        Top:=ScaleY(100);
        Width:=ScaleX(316);
        Height:=ScaleY(39);
    end;
    EdtPLink:=TEdit.Create(PuTTYPage);
    with EdtPLink do begin
        Parent:=PuTTYPage.Surface;
        Text:=GetPuTTYLocation+'plink.exe';
        if not FileExists(Text) then begin
            Text:='';
        end;
        Left:=ScaleX(28);
        Top:=ScaleY(148);
        Width:=ScaleX(316);
        Height:=ScaleY(13);
    end;
    BtnPLink:=TButton.Create(PuTTYPage);
    with BtnPLink do begin
        Parent:=PuTTYPage.Surface;
        Caption:='...';
        OnClick:=@BrowseForPuTTYFolder;
        Left:=ScaleX(348);
        Top:=ScaleY(148);
        Width:=ScaleX(21);
        Height:=ScaleY(21);
    end;

    // Restore the setting chosen during a previous install.
    Data:=GetPreviousData('SSH Option','OpenSSH');
    if Data='OpenSSH' then begin
        RdbSSH[GS_OpenSSH].Checked:=True;
    end else if Data='PLink' then begin
        RdbSSH[GS_PLink].Checked:=True;
    end;

    // Create a custom page for the autoCRLF setting.
    CRLFPage:=CreateCustomPage(
        PuTTYPage.ID,
        'Choosing CR/LF behavior',
        'Which CR/LF behavior would you like Git to have?'
    );

    // 1st choice
    RdbCRLF[GC_LFOnly]:=TRadioButton.Create(CRLFPage);
    with RdbCRLF[GC_LFOnly] do begin
      Parent:=CRLFPage.Surface;
      Caption:='Use Unix style line endings';
      Left:=ScaleX(4);
      Top:=ScaleY(8);
      Width:=ScaleX(329);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=0;
      Checked:=False;
    end;
    LblLFOnly:=TLabel.Create(CRLFPage);
    with LblLFOnly do begin
        Parent:=CRLFPage.Surface;
        Caption:=
            'Choose this if a single Line Feed character ends your lines. Most Windows' + #13 +
            'programs can cope with these line endings. However, some editors, like' + #13 +
            'Notepad, will show everything in one line with this mode.';
        Left:=ScaleX(28);
        Top:=ScaleY(32);
        Width:=ScaleX(364);
        Height:=ScaleY(47);
    end;

    // 2nd choice
    RdbCRLF[GC_CRLFAlways]:=TRadioButton.Create(CRLFPage);
    with RdbCRLF[GC_CRLFAlways] do begin
      Parent:=CRLFPage.Surface;
      Caption:='Use Windows style line endings';
      Left:=ScaleX(4);
      Top:=ScaleY(76);
      Width:=ScaleX(329);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=1;
      Checked:=True;
    end;
    LblCRLFAlways:=TLabel.Create(CRLFPage);
    with LblCRLFAlways do begin
        Parent:=CRLFPage.Surface;
        Caption:=
            'Choose this if your source code uses a Carriage Return and a Line Feed' + #13 +
            'character to end lines. This is the DOS convention; your checked-out files' + #13 +
            'might not be handled gracefully by MSYS / Cygwin command line utilities.';
        Left:=ScaleX(28);
        Top:=ScaleY(100);
        Width:=ScaleX(364);
        Height:=ScaleY(47);
    end;

    // 3rd choice
    RdbCRLF[GC_CRLFCommitAsIs]:=TRadioButton.Create(CRLFPage);
    with RdbCRLF[GC_CRLFCommitAsIs] do begin
      Parent:=CRLFPage.Surface;
      Caption:='Commit line endings as they are';
      Left:=ScaleX(4);
      Top:=ScaleY(152);
      Width:=ScaleX(329);
      Height:=ScaleY(17);
      Font.Style:=[fsBold];
      TabOrder:=2;
      Checked:=False;
    end;
    LblCRLFCommitAsIs:=TLabel.Create(CRLFPage);
    with LblCRLFCommitAsIs do begin
        Parent:=CRLFPage.Surface;
        Caption:=
            'Choose this if you know what you are doing and want to track the files with' + #13 +
            'the line endings exactly as they appear in the files. This option might' + #13 +
            'cause your projects to be hard to use on other platforms.';
        Left:=ScaleX(28);
        Top:=ScaleY(176);
        Width:=ScaleX(364);
        Height:=ScaleY(47);
    end;

    // Restore the setting chosen during a previous install.
    Data:=GetPreviousData('CRLF Option','CRLFAlways');
    if Data='LFOnly' then begin
        RdbCRLF[GC_LFOnly].Checked:=True;
    end else if Data='CRLFAlways' then begin
        RdbCRLF[GC_CRLFAlways].Checked:=True;
    end else if Data='CRLFCommitAsIs' then begin
        RdbCRLF[GC_CRLFCommitAsIs].Checked:=True;
    end;
end;

function NextButtonClick(CurPageID:Integer):Boolean;
begin
    if CurPageID<>PuTTYPage.ID then begin
        Result:=True;
        Exit;
    end;

    Result:=RdbSSH[GS_OpenSSH].Checked
        or (RdbSSH[GS_PLink].Checked and FileExists(EdtPLink.Text));

    if not Result then begin
        MsgBox('Please enter a valid path to plink.exe.',mbError,MB_OK);
    end;
end;

procedure CurStepChanged(CurStep:TSetupStep);
var
    AppDir,FileName,Cmd,Msg:string;
    BuiltIns,EnvPath,EnvHome,EnvSSH:TArrayOfString;
    Count,i:Longint;
    IsNTFS:Boolean;
    FindRec:TFindRec;
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

        // Delete all scripts as they might have been replaced by built-ins by now.
        for i:=0 to Count do begin
            FileName:=ChangeFileExt(AppDir+'\'+BuiltIns[i],'');
            if (FileExists(FileName) and (not DeleteFile(FileName))) then begin
                Log('Line {#emit __LINE__}: Unable to delete script "'+FileName+'", ignoring.');
            end;
        end;

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

        // Delete any duplicate files in case we are updating from a non-libexec to a libexec directory layout.
        if FindFirst(AppDir+'\libexec\git-core\*',FindRec) then begin
            repeat
                if (FindRec.Attributes and FILE_ATTRIBUTE_DIRECTORY)=0 then begin
                    FileName:=AppDir+'\bin\'+FindRec.name;
                    if (FileExists(FileName) and (not DeleteFile(FileName))) then begin
                        Log('Line {#emit __LINE__}: Unable to delete dupe "'+FileName+'", ignoring.');
                    end;
                end;
            until not FindNext(FindRec);
            FindClose(FindRec);
        end;
    end else begin
        Msg:='Line {#emit __LINE__}: Unable to read file "{#emit APP_BUILTINS}".';
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
        // This is not a critical error, Git could basically be used without the
        // aliases for built-ins, so we continue.
    end;

    {
        Adapt core.autocrlf
    }

    if RdbCRLF[GC_LFOnly].checked then begin
        Cmd:='core.autoCRLF input';
    end else if RdbCRLF[GC_CRLFAlways].checked then begin
        Cmd:='core.autoCRLF true';
    end else begin
        Cmd:='core.autoCRLF false';
    end;
    if not Exec(AppDir + '\bin\git-config.exe', '-f gitconfig ' + Cmd,
            AppDir + '\etc', SW_HIDE, ewWaitUntilTerminated, i) then begin
        Msg:='Could not set CR/LF behavior: ' + Cmd;
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
    end;

    {
        Modify the environment

        This must happen no later than ssPostInstall to make
        "ChangesEnvironment=yes" not happend before the change!
    }

    FileName:=AppDir+'\setup.ini';

    // Delete GIT_SSH if a previous installation modified it.
    EnvSSH:=GetEnvStrings('GIT_SSH',IsAdminLoggedOn);
    if (GetArrayLength(EnvSSH)=1) and
       (CompareStr(EnvSSH[0],GetIniString('Environment','GIT_SSH','',FileName))=0) then begin
        if not SetEnvStrings('GIT_SSH',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to reset GIT_SSH prior to install.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    if RdbSSH[GS_PLink].Checked then begin
        SetArrayLength(EnvSSH,1);
        EnvSSH[0]:=EdtPLink.Text;
        if not SetEnvStrings('GIT_SSH',IsAdminLoggedOn,True,EnvSSH) then begin
            Msg:='Line {#emit __LINE__}: Unable to set the GIT_SSH environment variable.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;

        // Mark that we have changed GIT_SSH.
        if not SetIniString('Environment','GIT_SSH',EnvSSH[0],FileName) then begin
            Msg:='Line {#emit __LINE__}: Unable to write to file "'+FileName+'".';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, though uninstall / reinstall will probably not run cleanly,
            // so we continue.
        end;
    end;

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
       (CompareStr(EnvHome[0],GetIniString('Environment','HOME','',FileName))=0) then begin
        if not SetEnvStrings('HOME',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to reset HOME prior to install.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    // Modify the PATH variable as requested by the user.
    if RdbPath[GP_Cmd].Checked or RdbPath[GP_CmdTools].Checked then begin
        i:=GetArrayLength(EnvPath);
        SetArrayLength(EnvPath,i+1);

        // List \cmd before \bin so \cmd has higher priority and programs in
        // there will be called in favor of those in \bin.
        EnvPath[i]:=ExpandConstant('{app}\cmd');

        if RdbPath[GP_CmdTools].Checked then begin
            SetArrayLength(EnvPath,i+3);
            EnvPath[i+1]:=ExpandConstant('{app}\bin');
            EnvPath[i+2]:=ExpandConstant('{app}\libexec\git-core');

            // Set HOME for the Windows Command Prompt, but only if it has not been set manually before.
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
        or (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui\command','','"'+AppDir+'\bin\wish.exe" "'+AppDir+'\libexec\git-core\git-gui" "--working-dir" "%1"')) then begin
            Msg:='Line {#emit __LINE__}: Unable to create "Git GUI Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;
end;

procedure RegisterPreviousData(PreviousDataKey:Integer);
var
    Data:string;
begin
    // Git Path options.
    Data:='';
    if RdbPath[GP_BashOnly].Checked then begin
        Data:='BashOnly';
    end else if RdbPath[GP_Cmd].Checked then begin
        Data:='Cmd';
    end else if RdbPath[GP_CmdTools].Checked then begin
        Data:='CmdTools';
    end;
    SetPreviousData(PreviousDataKey,'Path Option',Data);

    // Git SSH options.
    Data:='';
    if RdbSSH[GS_OpenSSH].Checked then begin
        Data:='OpenSSH';
    end else if RdbSSH[GS_PLink].Checked then begin
        Data:='PLink';
    end;
    SetPreviousData(PreviousDataKey,'SSH Option',Data);

    // Git CR/LF options.
    Data:='';
    if RdbCRLF[GC_LFOnly].Checked then begin
        Data:='LFOnly';
    end else if RdbCRLF[GC_CRLFAlways].Checked then begin
        Data:='CRLFAlways';
    end else if RdbCRLF[GC_CRLFCommitAsIs].Checked then begin
        Data:='CRLFCommitAsIs';
    end;
    SetPreviousData(PreviousDataKey,'CRLF Option',Data);
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
    EnvPath,EnvHome,EnvSSH:TArrayOfString;
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
    Command:=AppDir+'\setup.ini';

    // Reset the current user's GIT_SSH if we modified it.
    EnvSSH:=GetEnvStrings('GIT_SSH',IsAdminLoggedOn);
    if (GetArrayLength(EnvSSH)=1) and
       (CompareStr(EnvSSH[0],GetIniString('Environment','GIT_SSH','',Command))=0) then begin
        if not SetEnvStrings('GIT_SSH',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to revert any possible changes to GIT_SSH.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

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
       (CompareStr(EnvHome[0],GetIniString('Environment','HOME','',Command))=0) then begin
        if not SetEnvStrings('HOME',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to revert any possible changes to HOME.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    if (FileExists(Command) and (not DeleteFile(Command))) then begin
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

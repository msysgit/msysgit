#define APP_NAME     'Git'
#define APP_VERSION  '%APPVERSION%'
#define APP_URL      'http://msysgit.googlecode.com/'
#define APP_BUILTINS 'etc\fileList-builtins.txt'

[Setup]
; Compiler-related
InternalCompressLevel=max
OutputBaseFilename={#emit APP_NAME+'-'+APP_VERSION}
OutputDir=%OUTPUTDIR%
SolidCompression=yes

; Uncomment the line below to be able to compile the script from within the IDE.
;SourceDir={#GetEnv('TEMP')}\WinGit

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
WizardImageBackColor=clWhite
WizardImageStretch=no
WizardImageFile=git.bmp
WizardSmallImageFile=gitsmall.bmp

[Types]
; Define a dummy type to avoid getting the default ones.
Name: custom; Description: Custom installation; Flags: iscustom

[Components]
Name: icons; Description: Additional icons; Types: custom
Name: icons\quicklaunch; Description: In the Quick Launch; Types: custom
Name: icons\desktop; Description: On the Desktop; Types: custom
Name: ext; Description: Windows Explorer integration; Types: custom
Name: ext\shellhere; Description: """Git Bash Here"" context menu entry"; Types: custom
Name: ext\guihere; Description: """Git GUI Here"" context menu entry"; Types: custom
Name: assoc; Description: Associate .git* configuration files with the default text editor; Types: custom
Name: consolefont; Description: Use a TrueType font in the console (required for proper character encoding); Types: custom

[Files]
Source: *; DestDir: {app}; Excludes: \*.bmp, gpl-2.0.rtf, \*.iss, \tmp.*, \bin\*install*; Flags: recursesubdirs replacesameversion
Source: ReleaseNotes.rtf; DestDir: {app}; Flags: isreadme replacesameversion

[Icons]
Name: {group}\Git GUI; Filename: {app}\bin\wish.exe; Parameters: """{app}\libexec\git-core\git-gui"""; WorkingDir: %HOMEDRIVE%%HOMEPATH%; IconFilename: {app}\etc\git.ico
Name: {group}\Git Bash; Filename: {syswow64}\cmd.exe; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: %HOMEDRIVE%%HOMEPATH%; IconFilename: {app}\etc\git.ico
Name: {group}\Uninstall Git; Filename: {uninstallexe}
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\Git Bash; Filename: {syswow64}\cmd.exe; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: %HOMEDRIVE%%HOMEPATH%; IconFilename: {app}\etc\git.ico; Components: icons\quicklaunch
Name: {code:GetShellFolder|desktop}\Git Bash; Filename: {syswow64}\cmd.exe; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: %HOMEDRIVE%%HOMEPATH%; IconFilename: {app}\etc\git.ico; Components: icons\desktop

; Create a special shortcut that does not set a working directory. This is used by "Git Bash.vbs", which in turn is run by the "Git Bash Here" shell extension.
Name: {app}\Git Bash; Filename: {syswow64}\cmd.exe; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; IconFilename: {app}\etc\git.ico

[Messages]
BeveledLabel={#emit APP_URL}
SetupAppTitle={#emit APP_NAME} Setup
SetupWindowTitle={#emit APP_NAME} Setup

[Registry]
; There is no "Console" key in HKLM.
Root: HKCU; Subkey: Console; ValueType: string; ValueName: FaceName; ValueData: Lucida Console; Components: consolefont
Root: HKCU; Subkey: Console; ValueType: dword; ValueName: FontFamily; ValueData: $00000036; Components: consolefont
Root: HKCU; Subkey: Console; ValueType: dword; ValueName: FontSize; ValueData: $000e0000; Components: consolefont
Root: HKCU; Subkey: Console; ValueType: dword; ValueName: FontWeight; ValueData: $00000190; Components: consolefont

Root: HKCU; Subkey: Console\Git Bash; ValueType: string; ValueName: FaceName; ValueData: Lucida Console; Flags: createvalueifdoesntexist
Root: HKCU; Subkey: Console\Git Bash; ValueType: dword; ValueName: FontFamily; ValueData: $00000036; Flags: createvalueifdoesntexist
Root: HKCU; Subkey: Console\Git Bash; ValueType: dword; ValueName: FontSize; ValueData: $000e0000; Flags: createvalueifdoesntexist
Root: HKCU; Subkey: Console\Git Bash; ValueType: dword; ValueName: FontWeight; ValueData: $00000190; Flags: createvalueifdoesntexist

; File associations for configuration files that may be contained in a repository (so this does not include ".gitconfig").
Root: HKLM; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc

Root: HKLM; Subkey: Software\Classes\.gitignore; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitignore; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitignore; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitignore; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitignore; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitignore; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc

Root: HKLM; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist; Check: IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist; Check: not IsAdminLoggedOn; Components: assoc

[UninstallDelete]
; Delete the built-ins.
Type: files; Name: {app}\bin\git-*.exe
Type: files; Name: {app}\libexec\git-core\git-*.exe
Type: files; Name: {app}\libexec\git-core\git.exe

; Delete a home directory inside the msysGit directory.
Type: dirifempty; Name: {app}\home\{username}
Type: dirifempty; Name: {app}\home

[Code]
#include "helpers.inc.iss"
#include "putty.inc.iss"

function CreateHardLink(lpFileName,lpExistingFileName:String;lpSecurityAttributes:Integer):Boolean;
#ifdef UNICODE
external 'CreateHardLinkW@Kernel32.dll stdcall delayload setuponly';
#else
external 'CreateHardLinkA@Kernel32.dll stdcall delayload setuponly';
#endif

function CreateSymbolicLink(lpSymlinkFileName,lpTargetFileName:String;dwFlags:DWORD):Boolean;
#ifdef UNICODE
external 'CreateSymbolicLinkW@Kernel32.dll stdcall delayload setuponly';
#else
external 'CreateSymbolicLinkA@Kernel32.dll stdcall delayload setuponly';
#endif

const
    // Git Path options.
    GP_BashOnly       = 1;
    GP_Cmd            = 2;
    GP_CmdTools       = 3;

    // Git SSH options.
    GS_OpenSSH        = 1;
    GS_Plink          = 2;

    // Git line ending conversion options.
    GC_LFOnly         = 1;
    GC_CRLFAlways     = 2;
    GC_CRLFCommitAsIs = 3;

var
    // Wizard page and variables for the Path options.
    PathPage:TWizardPage;
    RdbPath:array[GP_BashOnly..GP_CmdTools] of TRadioButton;

    // Wizard page and variables for the SSH options.
    PuTTYPage:TWizardPage;
    RdbSSH:array[GS_OpenSSH..GS_Plink] of TRadioButton;
    EdtPlink:TEdit;

    // Wizard page and variables for the line ending conversion options.
    CRLFPage:TWizardPage;
    RdbCRLF:array[GC_LFOnly..GC_CRLFCommitAsIs] of TRadioButton;

procedure BrowseForPuTTYFolder(Sender:TObject);
var
    Path:String;
begin
    Path:=ExtractFilePath(EdtPlink.Text);
    BrowseForFolder('Please select the PuTTY folder:',Path,False);
    if FileExists(Path+'\TortoisePlink.exe') then begin
        EdtPlink.Text:=Path+'\TortoisePlink.exe';
        RdbSSH[GS_Plink].Checked:=True;
    end else if FileExists(Path+'\plink.exe') then begin
        EdtPlink.Text:=Path+'\plink.exe';
        RdbSSH[GS_Plink].Checked:=True;
    end else begin
        MsgBox('Please enter a valid path to "TortoisePlink.exe" or "plink.exe".',mbError,MB_OK);
    end;
end;

{
    Installer code
}

procedure InitializeWizard;
var
    PrevPageID:Integer;
    LblGitBash,LblGitCmd,LblGitCmdTools,LblGitCmdToolsWarn:TLabel;
    LblOpenSSH,LblPlink:TLabel;
    PuTTYSessions:TArrayOfString;
    LblLFOnly,LblCRLFAlways,LblCRLFCommitAsIs:TLabel;
    BtnPlink:TButton;
    Data:String;
begin
    PrevPageID:=wpSelectProgramGroup;

    (*
     * Create a custom page for modifying the environment.
     *)

    PathPage:=CreateCustomPage(
        PrevPageID,
        'Adjusting your PATH environment',
        'How would you like to use Git from the command line?'
    );
    PrevPageID:=PathPage.ID;

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

    (*
     * Create a custom page for using (Tortoise)Plink instead of OpenSSH
     * if at least one PuTTY session is found in the Registry.
     *)

    if RegGetSubkeyNames(HKEY_CURRENT_USER,'Software\SimonTatham\PuTTY\Sessions',PuTTYSessions) and (GetArrayLength(PuTTYSessions)>0) then begin
        PuTTYPage:=CreateCustomPage(
            PrevPageID,
            'Choosing the SSH executable',
            'Which Secure Shell client program would you like Git to use?'
        );
        PrevPageID:=PuTTYPage.ID;

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
                'This uses ssh.exe that comes with Git. The GIT_SSH and SVN_SSH' + #13 +
                'environment variables will not be modified.';
            Left:=ScaleX(28);
            Top:=ScaleY(32);
            Width:=ScaleX(324);
            Height:=ScaleY(26);
        end;

        // 2nd choice
        RdbSSH[GS_Plink]:=TRadioButton.Create(PuTTYPage);
        with RdbSSH[GS_Plink] do begin
            Parent:=PuTTYPage.Surface;
            Caption:='Use (Tortoise)Plink';
            Left:=ScaleX(4);
            Top:=ScaleY(76);
            Width:=ScaleX(281);
            Height:=ScaleY(17);
            Font.Style:=[fsBold];
            TabOrder:=1;
        end;
        LblPlink:=TLabel.Create(PuTTYPage);
        with LblPlink do begin
            Parent:=PuTTYPage.Surface;
            Caption:=
                'PuTTY sessions were found in your Registry. You may specify the path' + #13 +
                'to an existing copy of (Tortoise)Plink.exe from the TortoiseSVN/CVS' + #13 +
                'or PuTTY applications. The GIT_SSH and SVN_SSH environment' + #13 +
                'variables will be adjusted to point to the following executable:';
            Left:=ScaleX(28);
            Top:=ScaleY(100);
            Width:=ScaleX(340);
            Height:=ScaleY(52);
        end;
        EdtPlink:=TEdit.Create(PuTTYPage);
        with EdtPlink do begin
            Parent:=PuTTYPage.Surface;
            Text:=GetPuTTYLocation;
            if not FileExists(Text) then begin
                Text:='';
            end;
            Left:=ScaleX(28);
            Top:=ScaleY(161);
            Width:=ScaleX(316);
            Height:=ScaleY(13);
        end;
        BtnPlink:=TButton.Create(PuTTYPage);
        with BtnPlink do begin
            Parent:=PuTTYPage.Surface;
            Caption:='...';
            OnClick:=@BrowseForPuTTYFolder;
            Left:=ScaleX(348);
            Top:=ScaleY(161);
            Width:=ScaleX(21);
            Height:=ScaleY(21);
        end;

        // Restore the setting chosen during a previous install.
        Data:=GetPreviousData('SSH Option','OpenSSH');
        if Data='OpenSSH' then begin
            RdbSSH[GS_OpenSSH].Checked:=True;
        end else if Data='Plink' then begin
            RdbSSH[GS_Plink].Checked:=True;
        end;
    end else begin
        PuTTYPage:=NIL;
    end;

    (*
     * Create a custom page for the core.autocrlf setting.
     *)

    CRLFPage:=CreateCustomPage(
        PrevPageID,
        'Configuring the line ending conversions',
        'How should Git treat line endings in text files?'
    );
    PrevPageID:=CRLFPage.ID;

    // 1st choice
    RdbCRLF[GC_CRLFAlways]:=TRadioButton.Create(CRLFPage);
    with RdbCRLF[GC_CRLFAlways] do begin
        Parent:=CRLFPage.Surface;
        Caption:='Checkout Windows-style, commit Unix-style line endings';
        Left:=ScaleX(4);
        Top:=ScaleY(8);
        Width:=ScaleX(340);
        Height:=ScaleY(17);
        Font.Style:=[fsBold];
        TabOrder:=0;
        Checked:=True;
    end;
    LblCRLFAlways:=TLabel.Create(CRLFPage);
    with LblCRLFAlways do begin
        Parent:=CRLFPage.Surface;
        Caption:=
            'Git will convert LF to CRLF when checking out text files. When committing' + #13 +
            'text files, CRLF will be converted to LF. For cross-platform projects,' + #13 +
            'this is the recommended setting on Windows ("core.autocrlf" is set to "true").';
        Left:=ScaleX(28);
        Top:=ScaleY(32);
        Width:=ScaleX(372);
        Height:=ScaleY(47);
    end;

    // 2nd choice
    RdbCRLF[GC_LFOnly]:=TRadioButton.Create(CRLFPage);
    with RdbCRLF[GC_LFOnly] do begin
        Parent:=CRLFPage.Surface;
        Caption:='Checkout as-is, commit Unix-style line endings';
        Left:=ScaleX(4);
        Top:=ScaleY(80);
        Width:=ScaleX(340);
        Height:=ScaleY(17);
        Font.Style:=[fsBold];
        TabOrder:=1;
        Checked:=False;
    end;
    LblLFOnly:=TLabel.Create(CRLFPage);
    with LblLFOnly do begin
        Parent:=CRLFPage.Surface;
        Caption:=
            'Git will not perform any conversion when checking out text files. When' + #13 +
            'committing text files, CRLF will be converted to LF. For cross-platform projects,' + #13 +
            'this is the recommended setting on Unix ("core.autocrlf" is set to "input").';
        Left:=ScaleX(28);
        Top:=ScaleY(104);
        Width:=ScaleX(372);
        Height:=ScaleY(47);
    end;

    // 3rd choice
    RdbCRLF[GC_CRLFCommitAsIs]:=TRadioButton.Create(CRLFPage);
    with RdbCRLF[GC_CRLFCommitAsIs] do begin
        Parent:=CRLFPage.Surface;
        Caption:='Checkout as-is, commit as-is';
        Left:=ScaleX(4);
        Top:=ScaleY(152);
        Width:=ScaleX(340);
        Height:=ScaleY(17);
        Font.Style:=[fsBold];
        TabOrder:=2;
        Checked:=False;
    end;
    LblCRLFCommitAsIs:=TLabel.Create(CRLFPage);
    with LblCRLFCommitAsIs do begin
        Parent:=CRLFPage.Surface;
        Caption:=
            'Git will not perform any conversions when checking out or committing' + #13 +
            'text files. Choosing this option is not recommended for cross-platform' + #13 +
            'projects ("core.autocrlf" is set to "false").';
        Left:=ScaleX(28);
        Top:=ScaleY(176);
        Width:=ScaleX(372);
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
    if (PuTTYPage=NIL) or (CurPageID<>PuTTYPage.ID) then begin
        Result:=True;
        Exit;
    end;

    Result:=RdbSSH[GS_OpenSSH].Checked or
           (RdbSSH[GS_Plink].Checked and FileExists(EdtPlink.Text));

    if not Result then begin
        MsgBox('Please enter a valid path to (Tortoise)Plink.exe.',mbError,MB_OK);
    end;
end;

// AfterInstall
//
// Even though the name of this procedure suggests otherwise most of the
// code below is only executed once after the regular installation code
// is finished. This happens because of the if-guard right in the
// beginning of this procedure.
procedure CurStepChanged(CurStep:TSetupStep);
var
    AppDir,FileName,Cmd,Msg:String;
    BuiltIns,EnvPath,EnvHome,EnvSSH:TArrayOfString;
    Count,i:Longint;
    LinkCreated:Boolean;
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
    FileName:=ExpandConstant('{app}\{#emit APP_BUILTINS}');
    if LoadStringsFromFile(FileName,BuiltIns) then begin
        Count:=GetArrayLength(BuiltIns)-1;

        // Delete those scripts from "bin" which have been replaced by built-ins in "libexec\git-core".
        for i:=0 to Count do begin
            FileName:=AppDir+'\bin\'+ChangeFileExt(ExtractFileName(BuiltIns[i]),'');
            if FileExists(FileName) and (not DeleteFile(FileName)) then begin
                Log('Line {#emit __LINE__}: Unable to delete script "'+FileName+'", ignoring.');
            end;
        end;

        // Create built-ins as aliases for git.exe.
        for i:=0 to Count do begin
            FileName:=AppDir+'\'+BuiltIns[i];

            // Delete any existing built-in.
            if FileExists(FileName) and (not DeleteFile(FileName)) then begin
                Log('Line {#emit __LINE__}: Unable to delete existing built-in "'+FileName+'", skipping.');
                continue;
            end;

            try
                // This will throw an exception on pre-WinVista systems.
                LinkCreated:=CreateSymbolicLink(FileName,AppDir+'\bin\git.exe',0);
            except
                LinkCreated:=False;
                Log('Line {#emit __LINE__}: Creating symbolic link "'+FileName+'" failed, will try a hard link.');
            end;
            
            if not LinkCreated then begin
                try
                    // This will throw an exception on pre-Win2k systems.
                    LinkCreated:=CreateHardLink(FileName,AppDir+'\bin\git.exe',0);
                except
                    LinkCreated:=False;
                    Log('Line {#emit __LINE__}: Creating hardlink "'+FileName+'" failed, will try a copy.');
                end;
            end;

            if not LinkCreated then begin
                if not FileCopy(AppDir+'\bin\git.exe',FileName,False) then begin
                    Log('Line {#emit __LINE__}: Creating copy "'+FileName+'" failed, giving up.');
                    // This is not a critical error, Git could basically be used without the
                    // aliases for built-ins, so we continue.
                end;
            end;
        end;

        // Delete any duplicate files in case we are updating from a non-libexec to a libexec directory layout.
        if FindFirst(AppDir+'\libexec\git-core\*',FindRec) then begin
            repeat
                if (FindRec.Attributes and FILE_ATTRIBUTE_DIRECTORY)=0 then begin
                    FileName:=AppDir+'\bin\'+FindRec.name;
                    if (Pos(FindRec.name,'git.exe')<>1) and FileExists(FileName) and (not DeleteFile(FileName)) then begin
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
        Cmd:='core.autocrlf input';
    end else if RdbCRLF[GC_CRLFAlways].checked then begin
        Cmd:='core.autocrlf true';
    end else begin
        Cmd:='core.autocrlf false';
    end;
    if not Exec(AppDir + '\bin\git.exe', 'config -f gitconfig ' + Cmd,
            AppDir + '\etc', SW_HIDE, ewWaitUntilTerminated, i) then begin
        Msg:='Unable to configure the line ending conversion: ' + Cmd;
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
    end;

    {
        Modify the environment

        This must happen no later than ssPostInstall to make
        "ChangesEnvironment=yes" not happend before the change!
    }

    FileName:=AppDir+'\setup.ini';

    // Delete GIT_SSH and SVN_SSH if a previous installation set them (this is required for the GS_OpenSSH case).
    EnvSSH:=GetEnvStrings('GIT_SSH',IsAdminLoggedOn);
    if (GetArrayLength(EnvSSH)=1) and
       (CompareStr(RemoveQuotes(EnvSSH[0]),GetIniString('Environment','GIT_SSH','',FileName))=0) then begin
        if not SetEnvStrings('GIT_SSH',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to reset GIT_SSH prior to install.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    EnvSSH:=GetEnvStrings('SVN_SSH',IsAdminLoggedOn);
    if (GetArrayLength(EnvSSH)=1) and
       (CompareStr(RemoveQuotes(EnvSSH[0]),GetIniString('Environment','SVN_SSH','',FileName))=0) then begin
        if not SetEnvStrings('SVN_SSH',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to reset SVN_SSH prior to install.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    if (PuTTYPage<>NIL) and RdbSSH[GS_Plink].Checked then begin
        SetArrayLength(EnvSSH,1);
        EnvSSH[0]:=EdtPlink.Text;

        // Set GIT_SSH as specified by the user.
        if not SetEnvStrings('GIT_SSH',IsAdminLoggedOn,True,EnvSSH) then begin
            Msg:='Line {#emit __LINE__}: Unable to set the GIT_SSH environment variable.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;

        // Mark that we have changed GIT_SSH by writing its value to a file.
        if not SetIniString('Environment','GIT_SSH',EnvSSH[0],FileName) then begin
            Msg:='Line {#emit __LINE__}: Unable to write to file "'+FileName+'".';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, though uninstall / reinstall will probably not run cleanly,
            // so we continue.
        end;

        // Set SVN_SSH as specified by the user, but with escaped backslashes and quotes.
        StringChangeEx(EnvSSH[0],'\','\\',True);
        EnvSSH[0]:=AddQuotes(EnvSSH[0]);

        if not SetEnvStrings('SVN_SSH',IsAdminLoggedOn,True,EnvSSH) then begin
            Msg:='Line {#emit __LINE__}: Unable to set the SVN_SSH environment variable.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;

        // Mark that we have changed SVN_SSH by writing its value to a file.
        if not SetIniString('Environment','SVN_SSH',EnvSSH[0],FileName) then begin
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
        if Pos(AppDir+'\',EnvPath[i]+'\')=1 then begin
            EnvPath[i]:='';
        end;
    end;

    // Delete HOME if a previous installation modified it.
    EnvHome:=GetEnvStrings('HOME',IsAdminLoggedOn);
    if (GetArrayLength(EnvHome)=1) and
       (CompareStr(RemoveQuotes(EnvHome[0]),GetIniString('Environment','HOME','',FileName))=0) then begin
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
            SetArrayLength(EnvPath,i+2);
            EnvPath[i+1]:=ExpandConstant('{app}\bin');

            // Set HOME for the Windows Command Prompt, but only if it has not been set manually before.
            EnvHome:=GetEnvStrings('HOME',IsAdminLoggedOn);
            i:=GetArrayLength(EnvHome);
            if (i=0) or ((i=1) and (Length(EnvHome[0])=0)) then begin
                SetArrayLength(EnvHome,1);
                EnvHome[0]:=ExpandConstant('{%HOMEDRIVE}{%HOMEPATH}');
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

    if IsComponentSelected('ext\shellhere') then begin
        if (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell','','Git Ba&sh Here')) or
           (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell\command','','wscript "'+AppDir+'\Git Bash.vbs" "%1"')) then begin
            Msg:='Line {#emit __LINE__}: Unable to create "Git Bash Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    if IsComponentSelected('ext\guihere') then begin
        if (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui','','Git &GUI Here')) or
           (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui\command','','"'+AppDir+'\bin\wish.exe" "'+AppDir+'\libexec\git-core\git-gui" "--working-dir" "%1"')) then begin
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
    Data:String;
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
    if (PuTTYPage=NIL) or RdbSSH[GS_OpenSSH].Checked then begin
        Data:='OpenSSH';
    end else if RdbSSH[GS_Plink].Checked then begin
        Data:='Plink';
    end;
    SetPreviousData(PreviousDataKey,'SSH Option',Data);

    // Line ending conversion options.
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
    FileName,NewName,Msg:String;
begin
    FileName:=ExpandConstant('{app}\bin\ssh-agent.exe');
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

// PreUninstall
//
// Even though the name of this function suggests otherwise most of the
// code below is only executed right before the actual uninstallation.
// This happens because of the if-guard right in the beginning of this
// function.
procedure CurUninstallStepChanged(CurUninstallStep:TUninstallStep);
var
    AppDir,Command,Msg:String;
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

    // Delete the current user's GIT_SSH and SVN_SSH if we set it.
    EnvSSH:=GetEnvStrings('GIT_SSH',IsAdminLoggedOn);
    if (GetArrayLength(EnvSSH)=1) and
       (CompareStr(RemoveQuotes(EnvSSH[0]),GetIniString('Environment','GIT_SSH','',Command))=0) then begin
        if not SetEnvStrings('GIT_SSH',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to revert any possible changes to GIT_SSH.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    EnvSSH:=GetEnvStrings('SVN_SSH',IsAdminLoggedOn);
    if (GetArrayLength(EnvSSH)=1) and
       (CompareStr(RemoveQuotes(EnvSSH[0]),GetIniString('Environment','SVN_SSH','',Command))=0) then begin
        if not SetEnvStrings('SVN_SSH',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to revert any possible changes to SVN_SSH.';
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
        if Pos(AppDir+'\',EnvPath[i]+'\')=1 then begin
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
       (CompareStr(RemoveQuotes(EnvHome[0]),GetIniString('Environment','HOME','',Command))=0) then begin
        if not SetEnvStrings('HOME',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#emit __LINE__}: Unable to revert any possible changes to HOME.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    if FileExists(Command) and (not DeleteFile(Command)) then begin
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

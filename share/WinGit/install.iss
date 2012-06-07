#define APP_NAME      'Git'
#define APP_VERSION   '%APPVERSION%'
#define APP_URL       'http://msysgit.googlecode.com/'
#define APP_BUILTINS  'etc\fileList-builtins.txt'
#define APP_BINDIMAGE 'etc\fileList-bindimage.txt'

#define COMP_CONSOLE_FONT 'Use a TrueType font in all console windows (not only for Git Bash)'

#define DROP_HANDLER_GUID '{{86C86720-42A0-1069-A2E8-08002B30309D}}'

[Setup]
; Compiler-related
Compression=lzma2/ultra
LZMAUseSeparateProcess=yes
OutputBaseFilename={#APP_NAME+'-'+APP_VERSION}
OutputDir={#GetEnv('USERPROFILE')}
SolidCompression=yes

; Uncomment the line below to be able to compile the script from within the IDE.
;SourceDir={#GetEnv('TEMP')}\WinGit

; Installer-related
AllowNoIcons=yes
AppName={#APP_NAME}
AppPublisherURL={#APP_URL}
AppVersion={#APP_VERSION}
ChangesEnvironment=yes
DefaultDirName={pf}\{#APP_NAME}
DefaultGroupName={#APP_NAME}
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
Name: ext\reg; Description: Simple context menu (Registry based); Flags: exclusive; Types: custom
Name: ext\reg\shellhere; Description: Git Bash Here; Types: custom
Name: ext\reg\guihere; Description: Git GUI Here; Types: custom
Name: ext\cheetah; Description: Advanced context menu (git-cheetah plugin); Flags: exclusive; Types: custom
Name: assoc; Description: Associate .git* configuration files with the default text editor; Types: custom
Name: assoc_sh; Description: Associate .sh files to be run with Bash; Types: custom
Name: consolefont; Description: {#COMP_CONSOLE_FONT}; Types: custom

[Files]
; Install files that might be in use during setup under a different name.
Source: git-cheetah\git_shell_ext.dll; DestDir: {app}\git-cheetah; DestName: git_shell_ext.dll.new; Flags: replacesameversion; Components: ext\cheetah
Source: git-cheetah\git_shell_ext64.dll; DestDir: {app}\git-cheetah; DestName: git_shell_ext64.dll.new; Flags: replacesameversion; Components: ext\cheetah

Source: *; DestDir: {app}; Excludes: \*.bmp, gpl-2.0.rtf, \*.iss, \tmp.*, \bin\*install*, \git-cheetah\git_shell_ext.dll, \git-cheetah\git_shell_ext64.dll; Flags: recursesubdirs replacesameversion
Source: ReleaseNotes.rtf; DestDir: {app}; Flags: isreadme replacesameversion

[Icons]
Name: {group}\Git GUI; Filename: {app}\bin\wish.exe; Parameters: """{app}\libexec\git-core\git-gui"""; WorkingDir: %HOMEDRIVE%%HOMEPATH%; IconFilename: {app}\etc\git.ico
Name: {group}\Git Bash; Filename: {syswow64}\cmd.exe; Parameters: "/c """"{app}\bin\sh.exe"" --login -i"""; WorkingDir: %HOMEDRIVE%%HOMEPATH%; IconFilename: {app}\etc\git.ico

[Messages]
BeveledLabel={#APP_URL}
SetupAppTitle={#APP_NAME} Setup
SetupWindowTitle={#APP_NAME} Setup

[Registry]
; There is no "Console" key in HKLM.
Root: HKCU; Subkey: Console; ValueType: string; ValueName: FaceName; ValueData: Lucida Console; Flags: uninsclearvalue; Components: consolefont
Root: HKCU; Subkey: Console; ValueType: dword; ValueName: FontFamily; ValueData: $00000036; Components: consolefont
Root: HKCU; Subkey: Console; ValueType: dword; ValueName: FontSize; ValueData: $000e0000; Components: consolefont
Root: HKCU; Subkey: Console; ValueType: dword; ValueName: FontWeight; ValueData: $00000190; Components: consolefont

Root: HKCU; Subkey: Console\Git Bash; ValueType: string; ValueName: FaceName; ValueData: Lucida Console; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty
Root: HKCU; Subkey: Console\Git Bash; ValueType: dword; ValueName: FontFamily; ValueData: $00000036; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty
Root: HKCU; Subkey: Console\Git Bash; ValueType: dword; ValueName: FontSize; ValueData: $000e0000; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty
Root: HKCU; Subkey: Console\Git Bash; ValueType: dword; ValueName: FontWeight; ValueData: $00000190; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty

; Note that we write the Registry values below either to HKLM or to HKCU depending on whether the user running the installer
; is a member of the local Administrators group or not (see the "Check" argument).

; File associations for configuration files that may be contained in a repository (so this does not include ".gitconfig").
Root: HKLM; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitattributes; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc

Root: HKLM; Subkey: Software\Classes\.gitignore; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitignore; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitignore; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitignore; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitignore; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitignore; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc

Root: HKLM; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKLM; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueData: txtfile; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueName: Content Type; ValueData: text/plain; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc
Root: HKCU; Subkey: Software\Classes\.gitmodules; ValueType: string; ValueName: PerceivedType; ValueData: text; Flags: createvalueifdoesntexist uninsdeletevalue uninsdeletekeyifempty; Check: not IsAdminLoggedOn; Components: assoc

; Associate .sh extension with sh.exe so those files are double-clickable,
; startable from cmd.exe, and when files are dropped on them they are passed
; as arguments to the script.

; Install under HKEY_LOCAL_MACHINE if an administrator is installing.
Root: HKLM; Subkey: Software\Classes\.sh; ValueType: string; ValueData: sh_auto_file; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: IsAdminLoggedOn; Components: assoc_sh
Root: HKLM; Subkey: Software\Classes\sh_auto_file; ValueType: string; ValueData: "Shell Script"; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: IsAdminLoggedOn; Components: assoc_sh
Root: HKLM; Subkey: Software\Classes\sh_auto_file\shell\open\command; ValueType: string; ValueData: "{syswow64}\cmd.exe /C """"{app}\bin\sh.exe"" ""--login"" ""%1"" %*"""; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: IsAdminLoggedOn; Components: assoc_sh
Root: HKLM; Subkey: Software\Classes\sh_auto_file\DefaultIcon; ValueType: string; ValueData: "%SystemRoot%\System32\shell32.dll,-153"; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: IsAdminLoggedOn; Components: assoc_sh
Root: HKLM; Subkey: Software\Classes\sh_auto_file\ShellEx\DropHandler; ValueType: string; ValueData: {#DROP_HANDLER_GUID}; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: IsAdminLoggedOn; Components: assoc_sh

; Install under HKEY_CURRENT_USER if a non-administrator is installing.
Root: HKCU; Subkey: Software\Classes\.sh; ValueType: string; ValueData: sh_auto_file; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: not IsAdminLoggedOn; Components: assoc_sh
Root: HKCU; Subkey: Software\Classes\sh_auto_file; ValueType: string; ValueData: "Shell Script"; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: not IsAdminLoggedOn; Components: assoc_sh
Root: HKCU; Subkey: Software\Classes\sh_auto_file\shell\open\command; ValueType: string; ValueData: "{syswow64}\cmd.exe /C """"{app}\bin\sh.exe"" ""--login"" ""%1"" %*"""; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: not IsAdminLoggedOn; Components: assoc_sh
Root: HKCU; Subkey: Software\Classes\sh_auto_file\DefaultIcon; ValueType: string; ValueData: "%SystemRoot%\System32\shell32.dll,-153"; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: not IsAdminLoggedOn; Components: assoc_sh
Root: HKCU; Subkey: Software\Classes\sh_auto_file\ShellEx\DropHandler; ValueType: string; ValueData: {#DROP_HANDLER_GUID}; Flags: createvalueifdoesntexist uninsdeletekeyifempty uninsdeletevalue; Check: not IsAdminLoggedOn; Components: assoc_sh

[UninstallDelete]
; Delete the built-ins.
Type: files; Name: {app}\bin\git-*.exe
Type: files; Name: {app}\libexec\git-core\git-*.exe
Type: files; Name: {app}\libexec\git-core\git.exe

; Delete any (temporary) git-cheetah files.
Type: files; Name: {app}\git-cheetah\*.*

; Delete any manually created shortcuts.
Type: files; Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\Git Bash.lnk
Type: files; Name: {code:GetShellFolder|desktop}\Git Bash.lnk
Type: files; Name: {app}\Git Bash.lnk

; Delete a home directory inside the msysGit directory.
Type: dirifempty; Name: {app}\home\{username}
Type: dirifempty; Name: {app}\home

[Code]
#include "helpers.inc.iss"
#include "environment.inc.iss"
#include "putty.inc.iss"
#include "modules.inc.iss"

function CreateHardLink(lpFileName,lpExistingFileName:String;lpSecurityAttributes:Integer):Boolean;
#ifdef UNICODE
external 'CreateHardLinkW@Kernel32.dll stdcall delayload setuponly';
#else
external 'CreateHardLinkA@Kernel32.dll stdcall delayload setuponly';
#endif

function BindImageEx(Flags:DWORD;ImageName,DllPath,SymbolPath:AnsiString;StatusRoutine:Integer):Boolean;
external 'BindImageEx@Imagehlp.dll stdcall delayload setuponly';

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

    // BindImageEx API constants.
    BIND_NO_BOUND_IMPORTS  = $00000001;
    BIND_NO_UPDATE         = $00000002;
    BIND_ALL_IMAGES        = $00000004;
    BIND_CACHE_IMPORT_DLLS = $00000008;

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

    // Wizard page and variables for the processes page.
    SessionHandle:DWORD;
    Processes:ProcessList;
    ProcessesPage:TWizardPage;
    ProcessesListBox:TListBox;
    ProcessesRefresh,ContinueButton:TButton;

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

procedure DeleteContextMenuEntries;
var
    AppDir,Command,Msg:String;
    RootKey:Integer;
begin
    AppDir:=ExpandConstant('{app}');

    if IsAdminLoggedOn then begin
        RootKey:=HKEY_LOCAL_MACHINE;
    end else begin
        RootKey:=HKEY_CURRENT_USER;
    end;

    Command:='';
    RegQueryStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell\command','',Command);
    if Pos(AppDir,Command)>0 then begin
        if not RegDeleteKeyIncludingSubkeys(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell') then begin
            Msg:='Line {#__LINE__}: Unable to remove "Git Bash Here" shell extension.';
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
            Msg:='Line {#__LINE__}: Unable to remove "Git GUI Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;
end;

procedure RefreshProcessList(Sender:TObject);
var
    Version:TWindowsVersion;
    Modules:TArrayOfString;
    ProcsCloseRequired,ProcsCloseOptional:ProcessList;
    i:Longint;
    Caption:String;
    ManualClosingRequired:Boolean;
begin
    GetWindowsVersionEx(Version);

    // Use the Restart Manager API when installing the shell extension on Windows Vista and above.
    if Version.Major>=6 then begin
        SetArrayLength(Modules,5);
        Modules[0]:=ExpandConstant('{app}\bin\msys-1.0.dll');
        Modules[1]:=ExpandConstant('{app}\bin\tcl85.dll');
        Modules[2]:=ExpandConstant('{app}\bin\tk85.dll');
        Modules[3]:=ExpandConstant('{app}\git-cheetah\git_shell_ext.dll');
        Modules[4]:=ExpandConstant('{app}\git-cheetah\git_shell_ext64.dll');
        SessionHandle:=FindProcessesUsingModules(Modules,Processes);
    end else begin
        SetArrayLength(Modules,3);
        Modules[0]:=ExpandConstant('{app}\bin\msys-1.0.dll');
        Modules[1]:=ExpandConstant('{app}\bin\tcl85.dll');
        Modules[2]:=ExpandConstant('{app}\bin\tk85.dll');
        SessionHandle:=FindProcessesUsingModules(Modules,ProcsCloseRequired);

        SetArrayLength(Modules,2);
        Modules[0]:=ExpandConstant('{app}\git-cheetah\git_shell_ext.dll');
        Modules[1]:=ExpandConstant('{app}\git-cheetah\git_shell_ext64.dll');
        SessionHandle:=FindProcessesUsingModules(Modules,ProcsCloseOptional) or SessionHandle;

        // Misuse the "Restartable" flag to indicate which processes are required
        // to be closed before setup can continue, and which just should be closed
        // in order to make changes take effect immediately.
        SetArrayLength(Processes,GetArrayLength(ProcsCloseRequired)+GetArrayLength(ProcsCloseOptional));
        for i:=0 to GetArrayLength(ProcsCloseRequired)-1 do begin
            Processes[i]:=ProcsCloseRequired[i];
            Processes[i].Restartable:=False;
        end;
        for i:=0 to GetArrayLength(ProcsCloseOptional)-1 do begin
            Processes[GetArrayLength(ProcsCloseRequired)+i]:=ProcsCloseOptional[i];
            Processes[GetArrayLength(ProcsCloseRequired)+i].Restartable:=True;
        end;
    end;

    ManualClosingRequired:=False;

    ProcessesListBox.Items.Clear;
    if (Sender=NIL) or (SessionHandle>0) then begin
        for i:=0 to GetArrayLength(Processes)-1 do begin
            Caption:=Processes[i].Name+' (PID '+IntToStr(Processes[i].ID);
            if Processes[i].Restartable then begin
                Caption:=Caption+', closing is optional';
            end else begin
                Caption:=Caption+', closing is required';
                ManualClosingRequired:=True;
            end;
            Caption:=Caption+')';
            ProcessesListBox.Items.Append(Caption);
        end;
    end;

    if ContinueButton<>NIL then begin
        ContinueButton.Enabled:=not ManualClosingRequired;
    end;
end;

{
    Installer code
}

procedure InitializeWizard;
var
    i,PrevPageID:Integer;
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
        Width:=ScaleX(380);
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
        Width:=ScaleX(380);
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
        Width:=ScaleX(380);
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

    (*
     * Create a custom page for finding the processes that lock a module.
     *)

    ProcessesPage:=CreateCustomPage(
        wpPreparing,
        'Replacing in-use files',
        'The following applications use files that need to be replaced, please close them.'
    );

    ProcessesListBox:=TListBox.Create(ProcessesPage);
    with ProcessesListBox do begin
        Parent:=ProcessesPage.Surface;
        Width:=ProcessesPage.SurfaceWidth;
        Height:=ProcessesPage.SurfaceHeight-ScaleY(8);
    end;

    ProcessesRefresh:=TNewButton.Create(WizardForm);
    with ProcessesRefresh do begin
        Parent:=WizardForm;
        Width:=WizardForm.CancelButton.Width;
        Height:=WizardForm.CancelButton.Height;
        Top:=WizardForm.CancelButton.Top;
        Left:=WizardForm.ClientWidth-(WizardForm.CancelButton.Left+WizardForm.CancelButton.Width);
        Caption:='&Refresh';
        OnClick:=@RefreshProcessList;
    end;

    // This button is only used by the uninstaller.
    ContinueButton:=NIL;

    // Initially hide the Refresh button, show it when the process page becomes current.
    ProcessesRefresh.Hide;
end;

function ShouldSkipPage(PageID:Integer):Boolean;
begin
    if (ProcessesPage<>NIL) and (PageID=ProcessesPage.ID) then begin
        // This page is only reached forward (by pressing "Next", never by pressing "Back").
        RefreshProcessList(NIL);
        Result:=(GetArrayLength(Processes)=0);
    end else begin
        Result:=False;
    end;
end;

procedure CurPageChanged(CurPageID:Integer);
var
    i:Integer;
begin
    // Uncheck the console font option by default.
    if CurPageID=wpSelectComponents then begin
        for i:=0 to WizardForm.ComponentsList.Items.Count-1 do begin
            if WizardForm.ComponentsList.ItemCaption[i]='{#COMP_CONSOLE_FONT}' then begin
                WizardForm.ComponentsList.Checked[i]:=False;
                Break;
            end;
        end;
    end;

    // Show the "Refresh" button only on the processes page.
    if (ProcessesPage<>NIL) and (CurPageID=ProcessesPage.ID) then begin
        ProcessesRefresh.Show;
    end else begin
        ProcessesRefresh.Hide;
    end;
end;

function NextButtonClick(CurPageID:Integer):Boolean;
var
    i:Integer;
    Version:TWindowsVersion;
begin
    Result:=True;

    if (PuTTYPage<>NIL) and (CurPageID=PuTTYPage.ID) then begin
        Result:=RdbSSH[GS_OpenSSH].Checked or
            (RdbSSH[GS_Plink].Checked and FileExists(EdtPlink.Text));
        if not Result then begin
            MsgBox('Please enter a valid path to (Tortoise)Plink.exe.',mbError,MB_OK);
        end;
    end else if (ProcessesPage<>NIL) and (CurPageID=ProcessesPage.ID) then begin
        // It would have been nicer to just disable the "Next" button, but the
        // WizardForm exports the button just read-only.
        for i:=0 to GetArrayLength(Processes)-1 do begin
            if not Processes[i].Restartable then begin
                MsgBox('Setup cannot continue until you close at least those applications in the list that are marked as "closing is required".',mbCriticalError,MB_OK);
                Result:=False;
                Exit;
            end;
        end;

        Result:=(GetArrayLength(Processes)=0);

        if not Result then begin
            GetWindowsVersionEx(Version);
            if Version.Major>=6 then begin
                Result:=(MsgBox(
                    'If you continue without closing the listed applications they will be closed and restarted automatically.' + #13 + #13 +
                    'Are you sure you want to continue?',
                    mbConfirmation,
                    MB_YESNO
                )=IDYES);
            end else begin
                Result:=(MsgBox(
                    'If you continue without closing the listed applications you will need to log off and on again before changes take effect.' + #13 + #13 +
                    'Are you sure you want to continue anyway?',
                    mbConfirmation,
                    MB_YESNO
                )=IDYES);
            end;
        end;
    end;
end;

procedure CurStepChanged(CurStep:TSetupStep);
var
    AppDir,DllPath,FileName,TempName,Cmd,Msg:String;
    BuiltIns,ImageNames,EnvPath,EnvHome,EnvSSH:TArrayOfString;
    Count,i:Longint;
    LinkCreated:Boolean;
    FindRec:TFindRec;
    RootKey:Integer;
begin
    if CurStep=ssInstall then begin
        // Shutdown locking processes just before the actual installation starts.
        if SessionHandle>0 then try
            RmShutdown(SessionHandle,RmShutdownOnlyRegistered,0);
        except
            Log('Line {#__LINE__}: RmShutdown not supported.');
        end;

        Exit;
    end;

    // Make sure the code below is only executed just after the actual installation finishes.
    if CurStep<>ssPostInstall then begin
        Exit;
    end;

    AppDir:=ExpandConstant('{app}');

    {
        Bind the imported function addresses
    }

    try
        DllPath:=ExpandConstant('{app}\bin;{sys}');

        // Load the list of images from a text file.
        FileName:=AppDir+'\{#APP_BINDIMAGE}';
        if LoadStringsFromFile(FileName,ImageNames) then begin
            Count:=GetArrayLength(ImageNames)-1;
            for i:=0 to Count do begin
                FileName:=AppDir+'\'+ImageNames[i];
                if not BindImageEx(BIND_NO_BOUND_IMPORTS or BIND_CACHE_IMPORT_DLLS,FileName,DllPath,'',0) then begin
                    Log('Line {#__LINE__}: Error calling BindImageEx for "'+FileName+'".');
                end;
            end;
        end;
    except
        Log('Line {#__LINE__}: An exception occurred while calling BindImageEx.');
    end;

    {
        Create the built-ins
    }

    // Load the built-ins from a text file.
    FileName:=AppDir+'\{#APP_BUILTINS}';
    if LoadStringsFromFile(FileName,BuiltIns) then begin
        Count:=GetArrayLength(BuiltIns)-1;

        // Delete those scripts from "bin" which have been replaced by built-ins in "libexec\git-core".
        for i:=0 to Count do begin
            FileName:=AppDir+'\bin\'+ChangeFileExt(ExtractFileName(BuiltIns[i]),'');
            if FileExists(FileName) and (not DeleteFile(FileName)) then begin
                Log('Line {#__LINE__}: Unable to delete script "'+FileName+'", ignoring.');
            end;
        end;

        // Create built-ins as aliases for git.exe.
        for i:=0 to Count do begin
            FileName:=AppDir+'\'+BuiltIns[i];

            // Delete any existing built-in.
            if FileExists(FileName) and (not DeleteFile(FileName)) then begin
                Log('Line {#__LINE__}: Unable to delete existing built-in "'+FileName+'", skipping.');
                continue;
            end;

            try
                // This will throw an exception on pre-Win2k systems.
                LinkCreated:=CreateHardLink(FileName,AppDir+'\bin\git.exe',0);
            except
                LinkCreated:=False;
                Log('Line {#__LINE__}: Creating hardlink "'+FileName+'" failed, will try a copy.');
            end;

            if not LinkCreated then begin
                if not FileCopy(AppDir+'\bin\git.exe',FileName,False) then begin
                    Log('Line {#__LINE__}: Creating copy "'+FileName+'" failed, giving up.');
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
                        Log('Line {#__LINE__}: Unable to delete dupe "'+FileName+'", ignoring.');
                    end;
                end;
            until not FindNext(FindRec);
            FindClose(FindRec);
        end;
    end else begin
        Msg:='Line {#__LINE__}: Unable to read file "{#APP_BUILTINS}".';
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
        // This is not a critical error, the user can probably fix it manually,
        // so we continue.
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
            Msg:='Line {#__LINE__}: Unable to reset GIT_SSH prior to install.';
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
            Msg:='Line {#__LINE__}: Unable to reset SVN_SSH prior to install.';
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
            Msg:='Line {#__LINE__}: Unable to set the GIT_SSH environment variable.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;

        // Mark that we have changed GIT_SSH by writing its value to a file.
        if not SetIniString('Environment','GIT_SSH',EnvSSH[0],FileName) then begin
            Msg:='Line {#__LINE__}: Unable to write to file "'+FileName+'".';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, though uninstall / reinstall will probably not run cleanly,
            // so we continue.
        end;

        if not SetEnvStrings('SVN_SSH',IsAdminLoggedOn,True,EnvSSH) then begin
            Msg:='Line {#__LINE__}: Unable to set the SVN_SSH environment variable.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;

        // Mark that we have changed SVN_SSH by writing its value to a file.
        if not SetIniString('Environment','SVN_SSH',EnvSSH[0],FileName) then begin
            Msg:='Line {#__LINE__}: Unable to write to file "'+FileName+'".';
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
            Msg:='Line {#__LINE__}: Unable to reset HOME prior to install.';
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
        EnvPath[i]:=AppDir+'\cmd';

        if RdbPath[GP_CmdTools].Checked then begin
            SetArrayLength(EnvPath,i+2);
            EnvPath[i+1]:=AppDir+'\bin';

            // Set HOME for the Windows Command Prompt, but only if it has not been set manually before.
            EnvHome:=GetEnvStrings('HOME',IsAdminLoggedOn);
            i:=GetArrayLength(EnvHome);
            if (i=0) or ((i=1) and (Length(EnvHome[0])=0)) then begin
                SetArrayLength(EnvHome,1);
                EnvHome[0]:=ExpandConstant('{%HOMEDRIVE}{%HOMEPATH}');
                if not SetEnvStrings('HOME',IsAdminLoggedOn,True,EnvHome) then begin
                    Msg:='Line {#__LINE__}: Unable to set the HOME environment variable.';
                    MsgBox(Msg,mbError,MB_OK);
                    Log(Msg);
                    // This is not a critical error, the user can probably fix it manually,
                    // so we continue.
                end;

                // Mark that we have changed HOME.
                if not SetIniString('Environment','HOME',EnvHome[0],FileName) then begin
                    Msg:='Line {#__LINE__}: Unable to write to file "'+FileName+'".';
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
        Msg:='Line {#__LINE__}: Unable to set the PATH environment variable.';
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
        // This is not a critical error, the user can probably fix it manually,
        // so we continue.
    end;

    {
        Create shortcuts that need to be created regardless of the "Don't create a Start Menu folder" toggle
    }

    Cmd:=ExpandConstant('{syswow64}\cmd.exe');
    TempName:='/c ""'+AppDir+'\bin\sh.exe" --login -i"';
    FileName:=AppDir+'\etc\git.ico';

    if IsComponentSelected('icons\quicklaunch') then begin
        CreateShellLink(
            ExpandConstant('{userappdata}\Microsoft\Internet Explorer\Quick Launch\Git Bash.lnk')
        ,   'Git Bash'
        ,   Cmd
        ,   TempName
        ,   '%HOMEDRIVE%%HOMEPATH%'
        ,   FileName
        ,   0
        ,   SW_SHOWNORMAL
        );
    end;
    if IsComponentSelected('icons\desktop') then begin
        CreateShellLink(
            GetShellFolder('desktop')+'\Git Bash.lnk'
        ,   'Git Bash'
        ,   Cmd
        ,   TempName
        ,   '%HOMEDRIVE%%HOMEPATH%'
        ,   FileName
        ,   0
        ,   SW_SHOWNORMAL
        );
    end;

    // Create a special shortcut that does not set a working directory (Note: Since Inno Setup 5.3.11,
    // passing an empty WorkingDir gets replaced with {sys}, so use '.' instead).
    // This shortcut is used by "Git Bash.vbs", which in turn is run by the "Git Bash Here" shell extension.
    CreateShellLink(
        AppDir+'\Git Bash.lnk'
    ,   'Git Bash'
    ,   Cmd
    ,   TempName
    ,   '.'
    ,   FileName
    ,   0
    ,   SW_SHOWNORMAL
    );

    {
        Create the Windows Explorer integrations
    }

    if IsAdminLoggedOn then begin
        RootKey:=HKEY_LOCAL_MACHINE;
    end else begin
        RootKey:=HKEY_CURRENT_USER;
    end;

    if IsComponentSelected('ext\reg\shellhere') then begin
        if (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell','','Git Ba&sh Here')) or
           (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_shell\command','','"'+ExpandConstant('{syswow64}')+'\wscript" "'+AppDir+'\Git Bash.vbs" "%1"')) then begin
            Msg:='Line {#__LINE__}: Unable to create "Git Bash Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    if IsComponentSelected('ext\reg\guihere') then begin
        if (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui','','Git &GUI Here')) or
           (not RegWriteStringValue(RootKey,'SOFTWARE\Classes\Directory\shell\git_gui\command','','"'+AppDir+'\bin\wish.exe" "'+AppDir+'\libexec\git-core\git-gui" "--working-dir" "%1"')) then begin
            Msg:='Line {#__LINE__}: Unable to create "Git GUI Here" shell extension.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    // It is either the Registry-based context menu entries, or the shell extension.
    if IsComponentSelected('ext\cheetah') then begin
        DeleteContextMenuEntries;

        if isWin64 then begin
            FileName:=AppDir+'\git-cheetah\git_shell_ext64.dll';
        end else begin
            FileName:=AppDir+'\git-cheetah\git_shell_ext.dll';
        end;
        if not ReplaceInUseFile(FileName,FileName+'.new',True) then begin
            Log('Line {#__LINE__}: Replacing file "'+FileName+'" failed.');
        end;
    end;

    {
        Restart any processes that were shut down via the Restart Manager
    }

    if SessionHandle>0 then try
        RmRestart(SessionHandle,0,0);
        RmEndSession(SessionHandle);
    except
        Log('Line {#__LINE__}: RmRestart not supported.');
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
    Form:TSetupForm;
    Info:TLabel;
    ExitButton,RefreshButton:TButton;
begin
    Result:=True;

    Form:=CreateCustomForm;
    try
        Form.Caption:='Git Uninstall: Removing in-use files';
        Form.ClientWidth:=ScaleX(500);
        Form.ClientHeight:=ScaleY(256);
        Form.Center;

        Info:=TLabel.Create(Form);
        with Info do begin
            Parent:=Form;
            Left:=ScaleX(11);
            Top:=ScaleY(11);
            AutoSize:=True;
            Caption:='The following applications use files that need to be removed, please close them.';
        end;

        ContinueButton:=TButton.Create(Form);
        with ContinueButton do begin
            Parent:=Form;
            Left:=Form.ClientWidth-ScaleX(75+10);
            Top:=Form.ClientHeight-ScaleY(23+10);
            Width:=ScaleX(75);
            Height:=ScaleY(23);
            Caption:='Continue';
            ModalResult:=mrOk;
        end;

        ExitButton:=TButton.Create(Form);
        with ExitButton do begin
            Parent:=Form;
            Left:=ContinueButton.Left-ScaleX(75+6);
            Top:=ContinueButton.Top;
            Width:=ScaleX(75);
            Height:=ScaleY(23);
            Caption:='Exit';
            ModalResult:=mrCancel;
            Cancel:=True;
        end;

        RefreshButton:=TButton.Create(Form);
        with RefreshButton do begin
            Parent:=Form;
            Left:=ScaleX(10);
            Top:=ExitButton.Top;
            Width:=ScaleX(75);
            Height:=ScaleY(23);
            Caption:='Refresh';
            OnClick:=@RefreshProcessList;
        end;

        ProcessesListBox:=TListBox.Create(Form);
        with ProcessesListBox do begin
            Parent:=Form;
            Left:=ScaleX(11);
            Top:=Info.Top+Info.Height+11;
            Width:=Form.ClientWidth-ScaleX(11*2);
            Height:=ContinueButton.Top-ScaleY(11*4);
        end;

        Form.ActiveControl:=ContinueButton;

        RefreshProcessList(NIL);
        if GetArrayLength(Processes)>0 then begin
            // Now that these dialogs are going to be shown, we should probably
            // disable the "Are you sure to remove Git?" confirmation dialog, but
            // unfortunately that is not possible with Inno Setup currently.
            Result:=(Form.ShowModal()=mrOk);

            // Note: The number of processes might have changed during a refresh.
            if Result and (GetArrayLength(Processes)>0) then begin
                Result:=(MsgBox(
                    'If you continue without closing the listed applications, you will need to log off and on again to remove some files manually.' + #13 + #13 +
                    'Are you sure you want to continue anyway?',
                    mbConfirmation,
                    MB_YESNO
                )=IDYES);
            end;
        end;
    finally
        Form.free;
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
    AppDir,FileName,Msg:String;
    EnvPath,EnvHome,EnvSSH:TArrayOfString;
    i:Longint;
begin
    if CurUninstallStep<>usUninstall then begin
        Exit;
    end;

    // Reset the console font (the FontType is reset in the Registry section).
    if IsComponentInstalled('consolefont') then begin
        if MsgBox('Do you want to revert the TrueType font setting for all console windows?',mbConfirmation,MB_YESNO)=IDYES then begin
            RegWriteDWordValue(HKEY_CURRENT_USER,'Console','FontFamily',0);
            RegWriteDWordValue(HKEY_CURRENT_USER,'Console','FontSize',0);
            RegWriteDWordValue(HKEY_CURRENT_USER,'Console','FontWeight',0);
        end;
    end;

    {
        Modify the environment

        This must happen no later than usUninstall to make
        "ChangesEnvironment=yes" not happend before the change!
    }

    AppDir:=ExpandConstant('{app}');
    FileName:=AppDir+'\setup.ini';

    // Delete the current user's GIT_SSH and SVN_SSH if we set it.
    EnvSSH:=GetEnvStrings('GIT_SSH',IsAdminLoggedOn);
    if (GetArrayLength(EnvSSH)=1) and
       (CompareStr(RemoveQuotes(EnvSSH[0]),GetIniString('Environment','GIT_SSH','',FileName))=0) then begin
        if not SetEnvStrings('GIT_SSH',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#__LINE__}: Unable to revert any possible changes to GIT_SSH.';
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
            Msg:='Line {#__LINE__}: Unable to revert any possible changes to SVN_SSH.';
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
        Msg:='Line {#__LINE__}: Unable to revert any possible changes to PATH.';
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
        // This is not a critical error, the user can probably fix it manually,
        // so we continue.
    end;

    // Reset the current user's HOME if we modified it.
    EnvHome:=GetEnvStrings('HOME',IsAdminLoggedOn);
    if (GetArrayLength(EnvHome)=1) and
       (CompareStr(RemoveQuotes(EnvHome[0]),GetIniString('Environment','HOME','',FileName))=0) then begin
        if not SetEnvStrings('HOME',IsAdminLoggedOn,True,[]) then begin
            Msg:='Line {#__LINE__}: Unable to revert any possible changes to HOME.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
            // This is not a critical error, the user can probably fix it manually,
            // so we continue.
        end;
    end;

    if FileExists(FileName) and (not DeleteFile(FileName)) then begin
        Msg:='Line {#__LINE__}: Unable to delete file "'+FileName+'".';
        MsgBox(Msg,mbError,MB_OK);
        Log(Msg);
        // This is not a critical error, the user can probably fix it manually,
        // so we continue.
    end;

    {
        Delete the Windows Explorer integrations
    }

    DeleteContextMenuEntries;

    if isWin64 then begin
        FileName:=AppDir+'\git-cheetah\git_shell_ext64.dll';
    end else begin
        FileName:=AppDir+'\git-cheetah\git_shell_ext.dll';
    end;
    if FileExists(FileName) then begin
        if not UnregisterServer(Is64BitInstallMode,FileName,False) then begin
            Msg:='Line {#__LINE__}: Unable to unregister file "'+FileName+'". Please do it manually by running "regsvr32 /u '+ExtractFileName(FileName)+'".';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
        end;

        if not DeleteFile(FileName) then begin
            Msg:='Line {#__LINE__}: Unable to delete file "'+FileName+'". Please do it manually after logging off and on again.';
            MsgBox(Msg,mbError,MB_OK);
            Log(Msg);
        end;
    end;
end;

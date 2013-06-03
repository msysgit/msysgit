[Code]

const
    TortoiseGitInstallKey='SOFTWARE\TortoiseGit';
    TortoiseSVNInstallKey='SOFTWARE\TortoiseSVN';
    TortoiseCVSUninstallKey='SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\TortoiseCVS_is1';
    PuTTYUninstallKey='SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\PuTTY_is1';
    PuTTYPrivateKeyAssoc='PuTTYPrivateKey\shell\open\command';

// Tries to detect the path to a PuTTY installation / an application that comes
// with an improved version of Plink. TortoisePlink from TortoiseGit/SVN features a
// GUI dialog to accept new host keys, for example.
function GuessPlinkExecutable:string;
begin
    // Prefer TortoisePlink over vanilla Plink for its GUI dialog to accept host keys.
    if (IsWin64 and RegQueryStringValue(HKEY_LOCAL_MACHINE_64,TortoiseGitInstallKey,'Directory',Result)) or
                    RegQueryStringValue(HKEY_LOCAL_MACHINE_32,TortoiseGitInstallKey,'Directory',Result) then begin
        // C:\Program Files\TortoiseGit\
        Result:=Result+'bin\';
        // C:\Program Files\TortoiseGit\bin\
    end else if (IsWin64 and RegQueryStringValue(HKEY_LOCAL_MACHINE_64,TortoiseSVNInstallKey,'Directory',Result)) or
                             RegQueryStringValue(HKEY_LOCAL_MACHINE_32,TortoiseSVNInstallKey,'Directory',Result) then begin
            // C:\Program Files\TortoiseSVN\
            Result:=Result+'bin\';
            // C:\Program Files\TortoiseSVN\bin\
    end else begin
        if not (IsWin64 and RegQueryStringValue(HKEY_LOCAL_MACHINE_64,TortoiseCVSUninstallKey,'InstallLocation',Result)) then begin
            RegQueryStringValue(HKEY_LOCAL_MACHINE_32,TortoiseCVSUninstallKey,'InstallLocation',Result);
        end;
        // C:\Program Files\TortoiseCVS\
    end;

    if DirExists(Result) then begin
        Result:=Result+'TortoisePlink.exe'
        Exit;
    end;

    if not RegQueryStringValue(HKEY_LOCAL_MACHINE,PuTTYUninstallKey,'InstallLocation',Result) then begin
        if RegQueryStringValue(HKEY_CLASSES_ROOT,PuTTYPrivateKeyAssoc,'',Result) then begin
            // "C:\Program Files\PuTTY\pageant.exe" "%1"
            Result:=RemoveQuotes(Result);
            // C:\Program Files\PuTTY\pageant.exe" "%1
            Result:=ExtractFilePath(Result);
        end;
    end;
    // C:\Program Files\PuTTY\

    if not DirExists(Result) then begin
        // Guess something.
        Result:=ExpandConstant('{pf}\PuTTY\');
    end;

    Result:=Result+'plink.exe'
end;

function IsPlinkExecutable(Path:String):Boolean;
begin
    Result:=(Pos('plink',LowerCase(ExtractFileName(Path)))>0);
end;

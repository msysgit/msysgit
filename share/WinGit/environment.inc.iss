[Code]

// Returns the value(s) of the environment variable "VarName", which is tokenized
// by ";" into an array of strings. This makes it easy query PATH-like variables
// in addition to normal variables. If "AllUsers" is true, the common variables
// are searched, else the user-specific ones.
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

    // Fallback for built-in variables which are not stored in the Registry.
    if Length(Path)=0 then begin
        Path:=ExpandConstant('{%'+VarName+'}');
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

// Sets the contents of the specified environment variable for the current process.
function SetEnvironmentVariable(lpName,lpValue:String):Boolean;
#ifdef UNICODE
external 'SetEnvironmentVariableW@Kernel32.dll stdcall delayload';
#else
external 'SetEnvironmentVariableA@Kernel32.dll stdcall delayload';
#endif

// Sets the environment variable "VarName" to the concatenation of "DirStrings"
// using ";" as the delimiter. If "AllUsers" is true, a common variable is set,
// else a user-specific one. If "DeleteIfEmpty" is true and "DirStrings" is
// empty, "VarName" is deleted instead of set if it exists.
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
            Result:=(not RegValueExists(HKEY_LOCAL_MACHINE,KeyName,VarName)) or
                         RegDeleteValue(HKEY_LOCAL_MACHINE,KeyName,VarName);
        end else begin
            Result:=RegWriteStringValue(HKEY_LOCAL_MACHINE,KeyName,VarName,Path);
        end;
    end else begin
        KeyName:='Environment';
        if DeleteIfEmpty and (Length(Path)=0) then begin
            Result:=(not RegValueExists(HKEY_CURRENT_USER,KeyName,VarName)) or
                         RegDeleteValue(HKEY_CURRENT_USER,KeyName,VarName);
        end else begin
            Result:=RegWriteStringValue(HKEY_CURRENT_USER,KeyName,VarName,Path);
        end;
    end;

    // Also update the environment of the current process.
    SetEnvironmentVariable(VarName,Path);
end;

// Copies a NULL-terminated array of characters to a string.
function ArrayToString(Chars:array of Char):String;
var
    Len,i:Longint;
begin
    Len:=GetArrayLength(Chars);
    SetLength(Result,Len);

    i:=0;
    while (i<Len) and (Chars[i]<>#0) do begin
        Result[i+1]:=Chars[i];
        Inc(i);
    end;

    SetLength(Result,i);
end;

// Copies a string to a NULL-terminated array of characters.
function StringToArray(Str:String):array of Char;
var
    Len,i:Longint;
begin
    Len:=Length(Str);
    SetArrayLength(Result,Len+1);

    i:=0;
    while i<Len do begin
        Result[i]:=Str[i+1];
        Inc(i);
    end;

    Result[i]:=#0;
end;

// Returns the path to the common or user shell folder as specified in "Param".
function GetShellFolder(Param:string):string;
begin
    if IsAdminLoggedOn then begin
        Param:='{common'+Param+'}';
    end else begin
        Param:='{user'+Param+'}';
    end;
    Result:=ExpandConstant(Param);
end;

// As IsComponentSelected() is not supported during uninstall, this work-around
// simply checks the Registry. This is unreliable if the user runs the installer
// twice, the first time selecting the component, the second deselecting it.
function IsComponentInstalled(Component:String):Boolean;
var
    UninstallKey,UninstallValue:String;
    Value:String;
begin
    Result:=False;

    UninstallKey:='SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{#APP_NAME}_is1';
    UninstallValue:='Inno Setup: Selected Components';

    if RegQueryStringValue(HKEY_LOCAL_MACHINE,UninstallKey,UninstallValue,Value) then begin
        Result:=(Pos(Component,Value)>0);
    end;
end;

// Checks whether the specified directory can be created and written to.
// Note that the created dummy file is not explicitly deleted here, so that
// needs to be done as part of the uninstall process.
function IsDirWritable(DirName:String):Boolean;
var
    FileName:String;
begin
    Result:=False;

    if not ForceDirectories(DirName) then begin
        Exit;
    end;

    FileName:=DirName+'\setup.ini';

    if not SetIniBool('Dummy','Writable',true,FileName) then begin
        Exit;
    end;

    Result:=GetIniBool('Dummy','Writable',false,FileName);
end;

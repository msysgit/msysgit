' If there is an argument, use it as the directory to change to.
If WScript.Arguments.Length=1 Then
    Set WshObj = CreateObject("WScript.Shell")
    WshObj.CurrentDirectory = WScript.Arguments(0)
End If

' Launch the shortcut in the current directory which has the same
' base name as this script.
Set AppObj = CreateObject("Shell.Application")
AppObj.ShellExecute(Replace(WScript.ScriptFullName, ".vbs", ".lnk"))

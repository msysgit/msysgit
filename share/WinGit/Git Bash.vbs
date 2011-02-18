Option Explicit

Dim shell : Set shell = CreateObject("WScript.Shell")
Dim fso : Set fso = CreateObject("Scripting.FileSystemObject")
Dim gitdir : gitdir = Left(WScript.ScriptFullName,InStrRev(WScript.ScriptFullName,"\"))
Dim bash : bash = fso.BuildPath(gitdir, "bin\sh.exe")
Dim temp : temp = fso.GetSpecialFolder(2) ' Temporary folder
Dim linkfile : linkfile = fso.BuildPath(temp, fso.GetTempName() & ".lnk")

Dim link : Set link = shell.CreateShortCut(linkfile)
link.TargetPath = bash
link.Arguments = "--login -i"
link.WindowStyle = 1
If WScript.Arguments.Length > 0 Then link.WorkingDirectory = WScript.Arguments(0)
link.Save

Dim app : Set app = CreateObject("Shell.Application")
app.ShellExecute linkfile
WScript.Sleep 500
fso.DeleteFile linkfile

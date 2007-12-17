#!/mingw/bin/tclsh

switch -regexp [lindex $argv 0] {
"^(|quicklaunch|QuickLaunch|q)$" {
	set targetDirectory \
		"$env(APPDATA)/Microsoft/Internet Explorer/Quick Launch"
}
"^(Desktop|desktop|d)$" {
	set targetDirectory "$env(USERPROFILE)/Desktop"
}
"^(StartMenu|startmenu|start|s)$" {
	package require registry 1.0
	set key "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows"
	set key "$key\\CurrentVersion\\Explorer\\Shell Folders"
	set targetDirectory [registry get $key "Start Menu"]
}
"^(StartMenu2|startmenu2|start2|s2)$" {
	set startMenuName "msysGit"
	package require registry 1.0
	set key "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows"
	set key "$key\\CurrentVersion\\Explorer\\Shell Folders"
	set programs [registry get $key "Programs"]
	file mkdir $programs/$startMenuName
	set targetDirectory $programs/$startMenuName
}
"^(AllUsersStartMenu|allusersstartmenu|allusers|a)$" {
	package require registry 1.0
	set key "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows"
	set key "$key\\CurrentVersion\\Explorer\\Shell Folders"
	set targetDirectory [registry get $key "Common Start Menu"]
}
"^(AllUsersStartMenu2|allusersstartmenu2|allusers2|a2)$" {
	set startMenuName "msysGit"
	package require registry 1.0
	set key "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows"
	set key "$key\\CurrentVersion\\Explorer\\Shell Folders"
	set programs [registry get $key "Common Programs"]
	file mkdir $programs/$startMenuName
	set targetDirectory $programs/$startMenuName
}
default {
	puts "Unknown argument: [lindex $argv 0]"
	exit 1
}
}

cd [file dirname $argv0]

regsub "^(.*)/mingw/bin/tclsh" $env(_) "\\1" msysRoot2
regsub "^(.*)/share/msysGit/add-msysGit-shortcut.tcl" $msysRoot2 "\\1" msysRoot
append env(PATH) ":$msysRoot/bin:$msysRoot/mingw/bin"
exec make

set binDirectory "$msysRoot/bin"
set resDirectory "$msysRoot/share/resources"

exec ./create-shortcut.exe --work-dir "$binDirectory" \
	--icon-file "$resDirectory/msysgitlogo.ico" \
	--arguments "--login -i" \
	"$binDirectory/sh.exe" \
	"$targetDirectory/msysGit.lnk"

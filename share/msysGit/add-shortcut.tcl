#!/mingw/bin/tclsh

cd [file dirname $argv0]
set msysRoot [file dirname [file dirname [pwd]]]

switch -regexp [lindex $argv 0] {
"^(|help|-h|-help|--help)$" {
	puts "Usage: $argv0 \[option\]"
	puts "Options:"
	puts ""
	puts "	QuickLaunch	create a QuickLaunch icon"
	puts "	Desktop		create an icon on the Desktop"
	puts "	StartMenu	create an icon in your start menu"
	puts "	StartMenu2	create an icon in start menu's Programs>msysGit"
	puts "	AllUsersStartMenu	create an icon in All Users' start menu"
	puts "	AllUsersStartMenu2	create an icon in All Users'"
	puts "					start menu's Programs>msysGit"
	puts "	EnableQuickEdit	enable the QuickEdit mode in the console"
	puts ""
	puts "Short options are q, d, s, s2, a and a2."
	exit 1
}
"^(quicklaunch|QuickLaunch|q)$" {
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
"^(EnableQuickEdit|quickedit)$" {
	package require registry 1.0
	set sh [string map { "\\" "_" "/" "_" } $msysRoot/bin/sh.exe]
	set key "HKEY_CURRENT_USER\\Console"
	registry set $key "QuickEdit" 1 dword
	registry set $key "HistoryBufferSize" 999 dword
	registry broadcast $key
	registry broadcast "Console"
	exit 0
}
default {
	puts "Unknown argument: [lindex $argv 0]"
	exit 1
}
}

exec make

set binDirectory "$msysRoot/bin"
set resDirectory "$msysRoot/share/resources"

set command "$binDirectory/sh.exe"
set arguments "--login -i"
if {[info exists env(COMMONPROGRAMW6432)] && $env(COMMONPROGRAMW6432) != ""} {
	set command "%WINDIR%\\SysWOW64\\cmd.exe"
	set arguments "/c \"$binDirectory/sh.exe\" --login -i"
}
exec ./create-shortcut.exe --work-dir "%HOMEDRIVE%%HOMEPATH%" \
	--icon-file "$resDirectory/msysgitlogo.ico" \
	--arguments $arguments \
	$command \
	"$targetDirectory/msysGit.lnk"

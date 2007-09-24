#!/bin/sh
# Tcl ignores the next line -*- tcl -*- \
exec wish "$0" -- "$@"

# Copyright (C) 2007 Johannes E. Schindelin.  All rights reserved.
# This program is free software; it may be used, copied, modified
# and distributed under the terms of the GNU General Public Licence,
# either version 2, or (at your option) any later version.

package require registry 1.0

proc installGit {} {
	global currentDirectory answer env

	set uninstallPath "$env(TMP)/uninstall.Git"
	if {[file exists $uninstallPath]} {
		for {set i 1} {[file exists "$uninstallPath.$i"]} {incr i} {
			# do nothing
		}
		set uninstallPath "$uninstallPath.$i"
	}
	file mkdir $uninstallPath
	file copy "$currentDirectory/bin/uninstaller.exe" $uninstallPath
	set out [open "$uninstallPath/installLocation.txt" "w"]
	puts $out $currentDirectory
	close $out
	set uninstallList [open "$uninstallPath/fileList.txt" "w"]
	set in [open "$currentDirectory/etc/fileList.txt" "r"]
	while {[gets $in line] >= 0} {
		puts $uninstallList "$currentDirectory/$line"
	}

	toplevel .listbox
	text .listbox.list -yscrollcommand ".listbox.scroll set"
	scrollbar .listbox.scroll -command ".listbox.list yview"
	pack .listbox.scroll -side right -fill y
	pack .listbox.list -expand yes -fill both
	raise .listbox

	set list [open "$currentDirectory/etc/fileList-builtins.txt" r]
	while {[gets $list line] >= 0} {
		.listbox.list insert end "copying builtin: $line\n"
		.listbox.list yview moveto 1
		update
		file copy -force $currentDirectory/bin/git.exe \
			$currentDirectory/$line
		puts $uninstallList "$currentDirectory/$line"
	}
	close $list

	#destroy .listbox

	# Create shortcuts

	set destinations [list]
	set answer [tk_dialog .question "Desktop Icon" \
		"Would you like to add a Git icon to the Desktop?" \
		question 0 Yes No]
	if {$answer == 0} {
		lappend destinations $env(USERPROFILE)/Desktop
	}

	set answer [tk_dialog .question "Quick Launch" \
		"Would you like to add a Quick Launch icon?" \
		question 0 Yes No]
	if {$answer == 0} {
		set appdata [regsub -all "\\\\" $env(APPDATA) "/"]
		lappend destinations \
			"$appdata/Microsoft/Internet Explorer/Quick Launch"
	}
	toplevel .question
	wm title .question "Start Menu item"
	# center it
	set maxsize [wm maxsize .question]
	set question_width 320
	set question_height 80
	set question_x [expr ([lindex $maxsize 0] - $question_width) / 2]
	set question_y [expr ([lindex $maxsize 1] - $question_height) / 2]
	wm geometry .question [format "%dx%d+%d+%d" \
		$question_width $question_height $question_x $question_y]
	label .question.label -text \
		"Would you like to add a start menu item?"
	frame .question.name
	label .question.name.name -text "Name:"
	global startMenuName
	set startMenuName "Git"
	entry .question.name.entry -textvariable startMenuName
	pack .question.name.name .question.name.entry \
		-fill x -expand true -side left
	frame .question.buttons
	set answer -1
	button .question.buttons.yes -text Yes -default active \
		-command {
			set answer 1
			destroy .question
		}
	bind .question <KeyPress> {
		if {[string equal %K "Return"]} {
			set answer 1
			destroy .question
		}
		if {[string equal %K "Escape"]} {
			set answer 0
			destroy .question
		}
	}
	button .question.buttons.no -text No -command {
		set answer 0
		destroy .question
	}
	pack .question.buttons.yes .question.buttons.no \
		-fill x -expand true -side left
	pack .question.label .question.name .question.buttons \
		-fill y -expand true
	focus -force .question
	tkwait window .question
	if {$answer == 1} {
		set key "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows"
		set key "$key\\CurrentVersion\\Explorer\\Shell Folders"
		set programs [registry get $key "Common Programs"]
		file mkdir $programs/$startMenuName
		lappend destinations $programs/$startMenuName
	}

	# TODO: add git-gui
	# TODO: incorporate git-cheetah

	foreach location $destinations {
		exec bin/create-shortcut.exe --work-dir $currentDirectory \
			--icon-file $currentDirectory/etc/git.ico \
			--arguments "--login -i" \
			$currentDirectory/bin/sh.exe $location/Git\ Shell.lnk
		puts $uninstallList $location/Git\ Shell.lnk
	}
	close $uninstallList

	# Enter information for the Deinstallation
	set key "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows"
	set key "$key\\CurrentVersion\\Uninstall\\WinGit"
	set out [open "$uninstallPath/registryKeys.txt" "w"]
	puts $out $key
	close $out
	registry set $key DisplayName Git
	registry set $key DisplayVersion "@@WINGITVERSION@@"
	registry set $key DisplayIcon "\"$currentDirectory/etc/git.ico\""
	registry set $key UninstallString "\"$uninstallPath\\uninstaller.exe\""
	registry set $key InstallLocation "\"$currentDirectory\""
	registry set $key Publisher "\"The msysGit team\""
	registry set $key HelpLink "\"http://msysgit.googlecode.com\""

	# set PATH
	set key "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control"
	append key "\\Session Manager\\Environment"
	set path [registry get $key "PATH"]
	set git_path "[regsub -all "/" "$currentDirectory/cmd" "\\"];"
	set path "$git_path$path"
	registry set $key "PATH" $path expand_sz

	# remember what you did
	set out [open "$uninstallPath/pathRegistryKey.txt" "w"]
	puts $out $key
	puts $out $git_path
	close $out

	# broadcast "Environment changed!"
	exec bin/broadcast-environment-change.exe

	tk_dialog .info "WinGit installed" \
			"WinGit was successfully installed" info 0 OK

	destroy .
	exit
}

set currentDirectory [lindex $argv 0]

wm withdraw .
installGit

#!/bin/sh
# Tcl ignores the next line -*- tcl -*- \
exec wish "$0" -- "$@"

# Copyright (C) 2007 Johannes E. Schindelin.  All rights reserved.
# This program is free software; it may be used, copied, modified
# and distributed under the terms of the GNU General Public Licence,
# either version 2, or (at your option) any later version.

proc installGit {} {
	global currentDirectory answer env

	toplevel .listbox
	text .listbox.list -yscrollcommand ".listbox.scroll set"
	scrollbar .listbox.scroll -command ".listbox.list yview"
	pack .listbox.scroll -side right -fill y
	pack .listbox.list -expand yes -fill both
	raise .listbox

	set list [open "$currentDirectory/fileList-builtins.txt" r]
	while {[gets $list line] >= 0} {
		.listbox.list insert end "copying builtin: $line\n"
		.listbox.list yview moveto 1
		update
		file copy -force $currentDirectory/bin/git.exe \
			$currentDirectory/$line
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
		package require registry 1.0
		set key "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows"
		set key "$key\\CurrentVersion\\Explorer\\Shell Folders"
		set programs [registry get $key "Programs"]
		file mkdir $programs/$startMenuName
		lappend destinations $programs/$startMenuName
	}

	# TODO: add git-gui
	# TODO: incorporate git-cheetah

	foreach location $destinations {
		exec bin/create-shortcut.exe --work-dir $currentDirectory \
			--icon-file $currentDirectory/git.ico \
			--arguments "--login -i" \
			--description "Git for MSys" \
			$currentDirectory/bin/sh.exe $location/Git.lnk
	}

	tk_dialog .info "WinGit installed" \
			"WinGit was successfully installed" info 0 OK

	destroy .
	exit
}

set currentDirectory [lindex $argv 0]

wm withdraw .
installGit

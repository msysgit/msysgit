#!/bin/sh
# Tcl ignores the next line -*- tcl -*- \
exec wish "$0" -- "$@"

# Copyright (C) 2007 Johannes E. Schindelin.  All rights reserved.
# This program is free software; it may be used, copied, modified
# and distributed under the terms of the GNU General Public Licence,
# either version 2, or (at your option) any later version.

proc browseForTarget {} {
	global targetDirectory
	set targetDirectory [tk_chooseDirectory \
		-initialdir $targetDirectory -mustexist false \
		-title "Target directory (will be created if necessary)"]
}

proc installGit {} {
	global currentDirectory targetDirectory

	if {[file exists $targetDirectory]} {
		set answer [tk_dialog .question "Target directory exists!" \
			"The directory $targetDirectory exists already!\nShould I overwrite it?" \
			error 1 Yes No]
		if {$answer == 1} {
			return
		}
		file delete -force $targetDirectory
	}

	file mkdir $targetDirectory

	toplevel .listbox
	text .listbox.list -yscrollcommand ".listbox.scroll set"
	scrollbar .listbox.scroll -command ".listbox.list yview"
	pack .listbox.scroll -side right -fill y
	pack .listbox.list -expand yes -fill both
	raise .listbox

	# copy files
	set list [open "$currentDirectory/fileList.txt" r]
	while {[gets $list line] >= 0} {
		if {$line == "fileList.txt" || $line == "install.tcl" ||
				$line == "fileList-builtins.txt"} {
			continue
		}
		.listbox.list insert end "copying file: $line\n"
		.listbox.list yview moveto 1
		update

		set dir [file dirname "$targetDirectory/$line"]
		if {![file isdirectory $dir]} {
			file mkdir $dir
		}
		# NEEDSWORK: may fail gracelessly
		file copy "$currentDirectory/$line" "$targetDirectory/$line"
	}
	close $list

	set list [open "$currentDirectory/fileList-builtins.txt" r]
	while {[gets $list line] >= 0} {
		.listbox.list nisert end "copying builtin: $line\n"
		.listbox.list yview moveto 1
		update
		file copy "$currentDirectory/bin/git.exe $targetDirectory/$line"
	}
	close $list

	#destroy .listbox

	tk_dialog .info "WinGit installed" \
			"WinGit was successfully installed" info 0 OK

	destroy .
	exit
}

set currentDirectory [lindex $argv 0]
set targetDirectory "$env(PROGRAMFILES)\\Git2"

wm title . "WinGit installer - Git for Windows"

labelframe .licenseframe -text "License:"
label .licenseframe.license -text "This software is licensed under the GPLv2.\nIf you do not know what that is, you do not have the permission to use this software.\nThis legal warning is necessary, because there are too many lawyers out there.\n" -anchor w
pack .licenseframe.license -side top

labelframe .install -text "Installation:"

label .install.label -text "Where do you want to install Git?"

frame .install.targetFrame
entry .install.targetFrame.target -textvariable targetDirectory
focus .install.targetFrame.target
button .install.targetFrame.browse -text Browse -command browseForTarget
pack .install.targetFrame.target .install.targetFrame.browse -side left -fill x
pack configure .install.targetFrame.target -expand 1

frame .install.buttonFrame
button .install.buttonFrame.ok -text OK -borderwidth 4 -command installGit
button .install.buttonFrame.cancel -text Cancel -command exit
pack .install.buttonFrame.ok .install.buttonFrame.cancel -side left

pack .install.label .install.targetFrame .install.buttonFrame \
	-side top -fill both

pack .licenseframe .install -side top -fill both

raise .

bind . <Key-Escape> exit
bind . <Key-Return> installGit

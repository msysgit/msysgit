# filebox.tcl --
#
# This demonstration script prompts the user to select a file.
#
# RCS: @(#) $Id: filebox.tcl,v 1.3.4.1 2004/09/10 20:48:41 dkf Exp $

if {![info exists widgetDemo]} {
    error "This script should be run from the \"widget\" demo."
}

set w .filebox
catch {destroy $w}
toplevel $w
wm title $w "File Selection Dialogs"
wm iconname $w "filebox"
positionWindow $w

label $w.msg -font $font -wraplength 4i -justify left -text "Enter a file name in the entry box or click on the \"Browse\" buttons to select a file name using the file selection dialog."
pack $w.msg -side top

frame $w.buttons
pack $w.buttons -side bottom -fill x -pady 2m
button $w.buttons.dismiss -text Dismiss -command "destroy $w"
button $w.buttons.code -text "See Code" -command "showCode $w"
pack $w.buttons.dismiss $w.buttons.code -side left -expand 1

foreach i {open save} {
    set f [frame $w.$i]
    label $f.lab -text "Select a file to $i: " -anchor e
    entry $f.ent -width 20
    button $f.but -text "Browse ..." -command "fileDialog $w $f.ent $i"
    pack $f.lab -side left
    pack $f.ent -side left -expand yes -fill x
    pack $f.but -side left
    pack $f -fill x -padx 1c -pady 3
}

if {![string compare $tcl_platform(platform) unix]} {
    checkbutton $w.strict -text "Use Motif Style Dialog" \
	-variable tk_strictMotif -onvalue 1 -offvalue 0
    pack $w.strict -anchor c

    # This binding ensures that we don't run the rest of the demos
    # with motif style interactions
    bind $w.strict <Destroy> {set tk_strictMotif 0}
}

proc fileDialog {w ent operation} {
    #   Type names		Extension(s)	Mac File Type(s)
    #
    #---------------------------------------------------------
    set types {
	{"Text files"		{.txt .doc}	}
	{"Text files"		{}		TEXT}
	{"Tcl Scripts"		{.tcl}		TEXT}
	{"C Source Files"	{.c .h}		}
	{"All Source Files"	{.tcl .c .h}	}
	{"Image Files"		{.gif}		}
	{"Image Files"		{.jpeg .jpg}	}
	{"Image Files"		""		{GIFF JPEG}}
	{"All files"		*}
    }
    if {$operation == "open"} {
	set file [tk_getOpenFile -filetypes $types -parent $w]
    } else {
	set file [tk_getSaveFile -filetypes $types -parent $w \
	    -initialfile Untitled -defaultextension .txt]
    }
    if {[string compare $file ""]} {
	$ent delete 0 end
	$ent insert 0 $file
	$ent xview end
    }
}

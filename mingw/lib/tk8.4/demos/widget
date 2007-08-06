#!/bin/sh
# the next line restarts using wish \
exec wish "$0" "$@"

# widget --
# This script demonstrates the various widgets provided by Tk,
# along with many of the features of the Tk toolkit.  This file
# only contains code to generate the main window for the
# application, which invokes individual demonstrations.  The
# code for the actual demonstrations is contained in separate
# ".tcl" files is this directory, which are sourced by this script
# as needed.
#
# RCS: @(#) $Id: widget,v 1.9.2.2 2006/09/11 14:41:16 das Exp $

eval destroy [winfo child .]
wm title . "Widget Demonstration"
if {[tk windowingsystem] eq "x11"} {
    # This won't work everywhere, but there's no other way in core Tk
    # at the moment to display a coloured icon.
    image create photo TclPowered \
	    -file [file join $tk_library images logo64.gif]
    wm iconwindow . [toplevel ._iconWindow]
    pack [label ._iconWindow.i -image TclPowered]
    wm iconname . "tkWidgetDemo"
}

array set widgetFont {
    main   {Helvetica 12}
    bold   {Helvetica 12 bold}
    title  {Helvetica 18 bold}
    status {Helvetica 10}
    vars   {Helvetica 14}
}

set widgetDemo 1
set font $widgetFont(main)

#----------------------------------------------------------------
# The code below create the main window, consisting of a menu bar
# and a text widget that explains how to use the program, plus lists
# all of the demos as hypertext items.
#----------------------------------------------------------------

menu .menuBar -tearoff 0

# On the Mac use the special .apple menu for the about item
if {[tk windowingsystem] eq "classic" || [tk windowingsystem] eq "aqua"} {
    .menuBar add cascade -menu .menuBar.apple
    menu .menuBar.apple -tearoff 0
    .menuBar.apple add command -label "About..." -command "aboutBox"
} else {
    .menuBar add cascade -menu .menuBar.file -label "File" -underline 0
    menu .menuBar.file -tearoff 0
    .menuBar.file add command -label "About..." -command "aboutBox" \
	-underline 0 -accelerator "<F1>"
    .menuBar.file add sep
    .menuBar.file add command -label "Quit" -command "exit" -underline 0 \
	-accelerator "Meta-Q"
    bind . <F1> aboutBox
}

. configure -menu .menuBar

frame .statusBar
label .statusBar.lab -text "   " -relief sunken -bd 1 \
	-font $widgetFont(status) -anchor w
label .statusBar.foo -width 8 -relief sunken -bd 1 \
	-font $widgetFont(status) -anchor w
pack .statusBar.lab -side left -padx 2 -expand yes -fill both
pack .statusBar.foo -side left -padx 2
pack .statusBar -side bottom -fill x -pady 2

frame .textFrame
scrollbar .s -orient vertical -command {.t yview} -highlightthickness 0 \
    -takefocus 1
pack .s -in .textFrame -side right -fill y
text .t -yscrollcommand {.s set}  -wrap word  -width 70  -height 30 \
	-font $widgetFont(main)  -setgrid 1  -highlightthickness 0 \
	-padx 4  -pady 2  -takefocus 0
pack .t -in .textFrame -expand y -fill both -padx 1
pack  .textFrame -expand yes -fill both

# Create a bunch of tags to use in the text widget, such as those for
# section titles and demo descriptions.  Also define the bindings for
# tags.

.t tag configure title -font $widgetFont(title)
.t tag configure bold  -font $widgetFont(bold)

# We put some "space" characters to the left and right of each demo description
# so that the descriptions are highlighted only when the mouse cursor
# is right over them (but not when the cursor is to their left or right)
#
.t tag configure demospace -lmargin1 1c -lmargin2 1c


if {[winfo depth .] == 1} {
    .t tag configure demo -lmargin1 1c -lmargin2 1c \
	-underline 1
    .t tag configure visited -lmargin1 1c -lmargin2 1c \
	-underline 1
    .t tag configure hot -background black -foreground white
} else {
    .t tag configure demo -lmargin1 1c -lmargin2 1c \
	-foreground blue -underline 1
    .t tag configure visited -lmargin1 1c -lmargin2 1c \
	-foreground #303080 -underline 1
    .t tag configure hot -foreground red -underline 1
}
.t tag bind demo <ButtonRelease-1> {
    invoke [.t index {@%x,%y}]
}
set lastLine ""
.t tag bind demo <Enter> {
    set lastLine [.t index {@%x,%y linestart}]
    .t tag add hot "$lastLine +1 chars" "$lastLine lineend -1 chars"
    .t config -cursor hand2
    showStatus [.t index {@%x,%y}]
}
.t tag bind demo <Leave> {
    .t tag remove hot 1.0 end
    .t config -cursor xterm
    .statusBar.lab config -text ""
}
.t tag bind demo <Motion> {
    set newLine [.t index {@%x,%y linestart}]
    if {[string compare $newLine $lastLine] != 0} {
	.t tag remove hot 1.0 end
	set lastLine $newLine

	set tags [.t tag names {@%x,%y}]
	set i [lsearch -glob $tags demo-*]
	if {$i >= 0} {
	    .t tag add hot "$lastLine +1 chars" "$lastLine lineend -1 chars"
	}
    }
    showStatus [.t index {@%x,%y}]
}

# Create the text for the text widget.

proc addDemoSection {title demos} {
    .t insert end "\n" {} $title title " \n " demospace
    set num 0
    foreach {name description} $demos {
	.t insert end "[incr num]. $description." [list demo demo-$name]
	.t insert end " \n " demospace
    }
}

.t insert end "Tk Widget Demonstrations\n" title
.t insert end "\nThis application provides a front end for several short\
	scripts that demonstrate what you can do with Tk widgets.  Each of\
	the numbered lines below describes a demonstration;  you can click\
	on it to invoke the demonstration.  Once the demonstration window\
	appears, you can click the " {} "See Code" bold " button to see the\
	Tcl/Tk code that created the demonstration.  If you wish, you can\
	edit the code and click the " {} "Rerun Demo" bold " button in the\
	code window to reinvoke the demonstration with the modified code.\n"

addDemoSection "Labels, buttons, checkbuttons, and radiobuttons" {
    label	"Labels (text and bitmaps)"
    unicodeout	"Labels and UNICODE text"
    button	"Buttons"
    check	"Check-buttons (select any of a group)"
    radio	"Radio-buttons (select one of a group)"
    puzzle	"A 15-puzzle game made out of buttons"
    icon	"Iconic buttons that use bitmaps"
    image1	"Two labels displaying images"
    image2	"A simple user interface for viewing images"
    labelframe	"Labelled frames"
}
addDemoSection "Listboxes" {
    states	"The 50 states"
    colors	"Colors: change the color scheme for the application"
    sayings	"A collection of famous and infamous sayings"
}
addDemoSection "Entries and Spin-boxes" {
    entry1	"Entries without scrollbars"
    entry2	"Entries with scrollbars"
    entry3	"Validated entries and password fields"
    spin	"Spin-boxes"
    form	"Simple Rolodex-like form"
}
addDemoSection "Text" {
    text	"Basic editable text"
    style	"Text display styles"
    bind	"Hypertext (tag bindings)"
    twind	"A text widget with embedded windows"
    search	"A search tool built with a text widget"
}
addDemoSection "Canvases" {
    items	"The canvas item types"
    plot	"A simple 2-D plot"
    ctext	"Text items in canvases"
    arrow	"An editor for arrowheads on canvas lines"
    ruler	"A ruler with adjustable tab stops"
    floor	"A building floor plan"
    cscroll	"A simple scrollable canvas"
}
addDemoSection "Scales" {
    hscale	"Horizontal scale"
    vscale	"Vertical scale"
}
addDemoSection "Paned Windows" {
    paned1	"Horizontal paned window"
    paned2	"Vertical paned window"
}
addDemoSection "Menus" {
    menu	"Menus and cascades (sub-menus)"
    menubu	"Menu-buttons"
}
addDemoSection "Common Dialogs" {
    msgbox	"Message boxes"
    filebox	"File selection dialog"
    clrpick	"Color picker"
}
addDemoSection "Miscellaneous" {
    bitmap	"The built-in bitmaps"
    dialog1	"A dialog box with a local grab"
    dialog2	"A dialog box with a global grab"
}

.t configure -state disabled
focus .s

# positionWindow --
# This procedure is invoked by most of the demos to position a
# new demo window.
#
# Arguments:
# w -		The name of the window to position.

proc positionWindow w {
    wm geometry $w +300+300
}

# showVars --
# Displays the values of one or more variables in a window, and
# updates the display whenever any of the variables changes.
#
# Arguments:
# w -		Name of new window to create for display.
# args -	Any number of names of variables.

proc showVars {w args} {
    global widgetFont
    catch {destroy $w}
    toplevel $w
    wm title $w "Variable values"
    label $w.title -text "Variable values:" -width 20 -anchor center \
	    -font $widgetFont(vars)
    pack $w.title -side top -fill x
    set len 1
    foreach i $args {
	if {[string length $i] > $len} {
	    set len [string length $i]
	}
    }
    foreach i $args {
	frame $w.$i
	label $w.$i.name -text "$i: " -width [expr $len + 2] -anchor w
	label $w.$i.value -textvar $i -anchor w
	pack $w.$i.name -side left
	pack $w.$i.value -side left -expand 1 -fill x
	pack $w.$i -side top -anchor w -fill x
    }
    button $w.ok -text OK -command "destroy $w" -default active
    bind $w <Return> "tkButtonInvoke $w.ok"
    pack $w.ok -side bottom -pady 2
}

# invoke --
# This procedure is called when the user clicks on a demo description.
# It is responsible for invoking the demonstration.
#
# Arguments:
# index -	The index of the character that the user clicked on.

proc invoke index {
    global tk_library
    set tags [.t tag names $index]
    set i [lsearch -glob $tags demo-*]
    if {$i < 0} {
	return
    }
    set cursor [.t cget -cursor]
    .t configure -cursor watch
    update
    set demo [string range [lindex $tags $i] 5 end]
    uplevel [list source [file join $tk_library demos $demo.tcl]]
    update
    .t configure -cursor $cursor

    .t tag add visited "$index linestart +1 chars" "$index lineend -1 chars"
}

# showStatus --
#
#	Show the name of the demo program in the status bar. This procedure
#	is called when the user moves the cursor over a demo description.
#
proc showStatus index {
    global tk_library
    set tags [.t tag names $index]
    set i [lsearch -glob $tags demo-*]
    set cursor [.t cget -cursor]
    if {$i < 0} {
	.statusBar.lab config -text " "
	set newcursor xterm
    } else {
	set demo [string range [lindex $tags $i] 5 end]
	.statusBar.lab config -text "Run the \"$demo\" sample program"
	set newcursor hand2
    }
    if [string compare $cursor $newcursor] {
	.t config -cursor $newcursor
    }
}


# showCode --
# This procedure creates a toplevel window that displays the code for
# a demonstration and allows it to be edited and reinvoked.
#
# Arguments:
# w -		The name of the demonstration's window, which can be
#		used to derive the name of the file containing its code.

proc showCode w {
    global tk_library
    set file [string range $w 1 end].tcl
    if ![winfo exists .code] {
	toplevel .code
	frame .code.buttons
	pack .code.buttons -side bottom -fill x
	button .code.buttons.dismiss -text Dismiss \
            -default active -command "destroy .code"
	button .code.buttons.rerun -text "Rerun Demo" -command {
	    eval [.code.text get 1.0 end]
	}
	pack .code.buttons.dismiss .code.buttons.rerun -side left \
	    -expand 1 -pady 2
	frame .code.frame
	pack  .code.frame -expand yes -fill both -padx 1 -pady 1
	text .code.text -height 40 -wrap word\
	    -xscrollcommand ".code.xscroll set" \
	    -yscrollcommand ".code.yscroll set" \
	    -setgrid 1 -highlightthickness 0 -pady 2 -padx 3
	scrollbar .code.xscroll -command ".code.text xview" \
	    -highlightthickness 0 -orient horizontal
	scrollbar .code.yscroll -command ".code.text yview" \
	    -highlightthickness 0 -orient vertical

	grid .code.text -in .code.frame -padx 1 -pady 1 \
	    -row 0 -column 0 -rowspan 1 -columnspan 1 -sticky news
	grid .code.yscroll -in .code.frame -padx 1 -pady 1 \
	    -row 0 -column 1 -rowspan 1 -columnspan 1 -sticky news
#	grid .code.xscroll -in .code.frame -padx 1 -pady 1 \
#	    -row 1 -column 0 -rowspan 1 -columnspan 1 -sticky news
	grid rowconfig    .code.frame 0 -weight 1 -minsize 0
	grid columnconfig .code.frame 0 -weight 1 -minsize 0
    } else {
	wm deiconify .code
	raise .code
    }
    wm title .code "Demo code: [file join $tk_library demos $file]"
    wm iconname .code $file
    set id [open [file join $tk_library demos $file]]
    .code.text delete 1.0 end
    .code.text insert 1.0 [read $id]
    .code.text mark set insert 1.0
    close $id
}

# aboutBox --
#
#	Pops up a message box with an "about" message
#
proc aboutBox {} {
    tk_messageBox -icon info -type ok -title "About Widget Demo" -message \
"Tk widget demonstration

Copyright (c) 1996-1997 Sun Microsystems, Inc.

Copyright (c) 1997-2000 Ajuba Solutions, Inc.

Copyright (c) 2001-2002 Donal K. Fellows"
}

# Local Variables:
# mode: tcl
# End:

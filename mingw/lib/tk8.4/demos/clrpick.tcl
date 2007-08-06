# clrpick.tcl --
#
# This demonstration script prompts the user to select a color.
#
# RCS: @(#) $Id: clrpick.tcl,v 1.3 2001/06/14 10:56:58 dkf Exp $

if {![info exists widgetDemo]} {
    error "This script should be run from the \"widget\" demo."
}

set w .clrpick
catch {destroy $w}
toplevel $w
wm title $w "Color Selection Dialog"
wm iconname $w "colors"
positionWindow $w

label $w.msg -font $font -wraplength 4i -justify left -text "Press the buttons below to choose the foreground and background colors for the widgets in this window."
pack $w.msg -side top

frame $w.buttons
pack $w.buttons -side bottom -fill x -pady 2m
button $w.buttons.dismiss -text Dismiss -command "destroy $w"
button $w.buttons.code -text "See Code" -command "showCode $w"
pack $w.buttons.dismiss $w.buttons.code -side left -expand 1

button $w.back -text "Set background color ..." \
    -command \
    "setColor $w $w.back background {-background -highlightbackground}"
button $w.fore -text "Set foreground color ..." \
    -command \
    "setColor $w $w.back foreground -foreground"

pack $w.back $w.fore -side top -anchor c -pady 2m

proc setColor {w button name options} {
    grab $w
    set initialColor [$button cget -$name]
    set color [tk_chooseColor -title "Choose a $name color" -parent $w \
	-initialcolor $initialColor]
    if {[string compare $color ""]} {
	setColor_helper $w $options $color
    }
    grab release $w
}

proc setColor_helper {w options color} {
    foreach option $options {
	catch {
	    $w config $option $color
	}
    }
    foreach child [winfo children $w] {
	setColor_helper $child $options $color
    }
}

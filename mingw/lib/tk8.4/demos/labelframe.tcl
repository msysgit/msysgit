# labelframe.tcl --
#
# This demonstration script creates a toplevel window containing
# several labelframe widgets.
#
# RCS: @(#) $Id: labelframe.tcl,v 1.2 2001/10/30 11:21:50 dkf Exp $

if {![info exists widgetDemo]} {
    error "This script should be run from the \"widget\" demo."
}

set w .labelframe
catch {destroy $w}
toplevel $w
wm title $w "Labelframe Demonstration"
wm iconname $w "labelframe"
positionWindow $w

# Some information

label $w.msg -font $font -wraplength 4i -justify left -text "Labelframes are\
	used to group related widgets together.  The label may be either \
	plain text or another widget."
pack $w.msg -side top

# The bottom buttons

frame $w.buttons
pack $w.buttons -side bottom -fill x -pady 2m
button $w.buttons.dismiss -text Dismiss -command "destroy $w" -width 15
button $w.buttons.code -text "See Code" -command "showCode $w" -width 15
pack $w.buttons.dismiss $w.buttons.code -side left -expand 1

# Demo area

frame $w.f
pack $w.f -side bottom -fill both -expand 1
set w $w.f

# A group of radiobuttons in a labelframe

labelframe $w.f -text "Value" -padx 2 -pady 2
grid $w.f -row 0 -column 0 -pady 2m -padx 2m

foreach value {1 2 3 4} {
    radiobutton $w.f.b$value -text "This is value $value" \
            -variable lfdummy -value $value
    pack $w.f.b$value -side top -fill x -pady 2
}


# Using a label window to control a group of options.

proc lfEnableButtons {w} {
    foreach child [winfo children $w] {
        if {$child == "$w.cb"} continue
        if {$::lfdummy2} {
            $child configure -state normal
        } else {
            $child configure -state disabled
        }
    }
}

labelframe $w.f2 -pady 2 -padx 2
checkbutton $w.f2.cb -text "Use this option." -variable lfdummy2 \
        -command "lfEnableButtons $w.f2" -padx 0
$w.f2 configure -labelwidget $w.f2.cb
grid $w.f2 -row 0 -column 1 -pady 2m -padx 2m

set t 0
foreach str {Option1 Option2 Option3} {
    checkbutton $w.f2.b$t -text $str
    pack $w.f2.b$t -side top -fill x -pady 2
    incr t
}
lfEnableButtons $w.f2


grid columnconfigure $w {0 1} -weight 1

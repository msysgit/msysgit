# radio.tcl --
#
# This demonstration script creates a toplevel window containing
# several radiobutton widgets.
#
# RCS: @(#) $Id: radio.tcl,v 1.4 2001/11/12 14:32:50 dkf Exp $

if {![info exists widgetDemo]} {
    error "This script should be run from the \"widget\" demo."
}

set w .radio
catch {destroy $w}
toplevel $w
wm title $w "Radiobutton Demonstration"
wm iconname $w "radio"
positionWindow $w
label $w.msg -font $font -wraplength 5i -justify left -text "Three groups of radiobuttons are displayed below.  If you click on a button then the button will become selected exclusively among all the buttons in its group.  A Tcl variable is associated with each group to indicate which of the group's buttons is selected.  Click the \"See Variables\" button to see the current values of the variables."
pack $w.msg -side top

frame $w.buttons
pack $w.buttons -side bottom -fill x -pady 2m
button $w.buttons.dismiss -text Dismiss -command "destroy $w"
button $w.buttons.code -text "See Code" -command "showCode $w"
button $w.buttons.vars -text "See Variables" \
	-command "showVars $w.dialog size color align"
pack $w.buttons.dismiss $w.buttons.code $w.buttons.vars -side left -expand 1

labelframe $w.left -pady 2 -text "Point Size" -padx 2
labelframe $w.mid -pady 2 -text "Color" -padx 2
labelframe $w.right -pady 2 -text "Alignment" -padx 2
pack $w.left $w.mid $w.right -side left -expand yes  -pady .5c -padx .5c

foreach i {10 12 14 18 24} {
    radiobutton $w.left.b$i -text "Point Size $i" -variable size \
	    -relief flat -value $i
    pack $w.left.b$i  -side top -pady 2 -anchor w -fill x
}

foreach c {Red Green Blue Yellow Orange Purple} {
    set lower [string tolower $c]
    radiobutton $w.mid.$lower -text $c -variable color \
	    -relief flat -value $lower -anchor w \
	    -command "$w.mid configure -fg \$color"
    pack $w.mid.$lower -side top -pady 2 -fill x
}

label $w.right.l -text "Label" -bitmap questhead -compound left
$w.right.l configure -width [winfo reqwidth $w.right.l] -compound top
$w.right.l configure -height [winfo reqheight $w.right.l]
foreach a {Top Left Right Bottom} {
    set lower [string tolower $a]
    radiobutton $w.right.$lower -text $a -variable align \
	    -relief flat -value $lower -indicatoron 0 -width 7 \
	    -command "$w.right.l configure -compound \$align"
}
grid x $w.right.top
grid $w.right.left $w.right.l $w.right.right
grid x $w.right.bottom

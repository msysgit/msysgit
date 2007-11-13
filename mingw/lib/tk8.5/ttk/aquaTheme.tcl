#
# $Id: aquaTheme.tcl,v 1.5 2007/10/22 03:35:13 jenglish Exp $
#
# Aqua theme (OSX native look and feel)
#

namespace eval ttk::theme::aqua {
    ttk::style theme settings aqua {

	ttk::style configure . \
	    -font System \
	    -background White \
	    -foreground Black \
	    -selectbackground SystemHighlight \
	    -selectforeground SystemHighlightText \
	    -selectborderwidth 0 \
	    -insertwidth 1 \
	    ;
	ttk::style map . \
	    -foreground [list  disabled "#a3a3a3"  background "#a3a3a3"] \
	    -selectbackground [list background "#c3c3c3"  !focus "#c3c3c3"] \
	    -selectforeground [list background "#a3a3a3"  !focus "#000000"] \
	    ;

	# Workaround for #1100117:
	# Actually, on Aqua we probably shouldn't stipple images in
	# disabled buttons even if it did work...
	#
	ttk::style configure . -stipple {}

	ttk::style configure TButton -padding {0 2} -width -6
	ttk::style configure TMenubutton -anchor w
	ttk::style configure Toolbutton -padding 4
	# See Apple HIG figs 14-63, 14-65
	ttk::style configure TNotebook -tabposition n -padding {20 12}
	ttk::style configure TNotebook.Tab -padding {10 2 10 2}


	# Adjust combobox post position to ensure the box is
	# directly under 'entry square'
	#
	ttk::style configure TCombobox -postoffset {3 -2 -6 0}

	# Treeview:
	ttk::style configure Treeview -rowheight 18
	ttk::style configure Heading -font TkHeadingFont
	ttk::style map Row -background [list \
		{selected background} "#c3c3c3" selected SystemHighlight] ;
	ttk::style map Cell -foreground [list \
		{selected background} "#000000" selected SystemHighlightText] ;
	ttk::style map Item -foreground [list \
		{selected background} "#000000" selected SystemHighlightText] ;

	# Enable animation for ttk::progressbar widget:
	ttk::style configure TProgressbar -period 100 -maxphase 255

	# Modify the the default Labelframe layout to use generic text element
	# instead of Labelframe.text; the latter erases the window background
	# (@@@ this still isn't right... want to fill with background pattern)

	ttk::style layout TLabelframe {
	    Labelframe.border
	    text
	}
	#
	# For Aqua, labelframe labels should appear outside the border,
	# with a 14 pixel inset and 4 pixels spacing between border and label
	# (ref: Apple Human Interface Guidelines / Controls / Grouping Controls)
	#
    	ttk::style configure TLabelframe \
	    -labeloutside true -labelmargins {14 0 14 4}

	# TODO: panedwindow sashes should be 9 pixels (HIG:Controls:Split Views)
    }
}

#
# $Id: altTheme.tcl,v 1.3 2006/12/18 19:33:14 jenglish Exp $
#
# Ttk widget set: Alternate theme
#

namespace eval ttk::theme::alt {

    variable colors
    array set colors {
	-frame 		"#d9d9d9"
	-window		"#ffffff"
	-darker 	"#c3c3c3"
	-activebg 	"#ececec"
	-disabledfg	"#a3a3a3"
	-selectbg	"#4a6984"
	-selectfg	"#ffffff"
    }

    namespace import -force ::ttk::style
    style theme settings alt {

	style configure "." \
	    -background 	$colors(-frame) \
	    -foreground 	black \
	    -troughcolor	$colors(-darker) \
	    -selectbackground 	$colors(-selectbg) \
	    -selectforeground 	$colors(-selectfg) \
	    -font 		TkDefaultFont \
	    ;

	style map "." -background \
	    [list disabled $colors(-frame)  active $colors(-activebg)] ;
	style map "." -foreground [list disabled $colors(-disabledfg)] ;
        style map "." -embossed [list disabled 1] ;

	style configure TButton \
	    -width -11 -padding "1 1" -relief raised -shiftrelief 1 \
	    -highlightthickness 1 -highlightcolor $colors(-frame)

	style map TButton -relief {
	    {pressed !disabled} 	sunken
	    {active !disabled} 	raised
	} -highlightcolor {alternate black}

	style configure TCheckbutton -indicatorcolor "#ffffff" -padding 2
	style configure TRadiobutton -indicatorcolor "#ffffff" -padding 2
	style map TCheckbutton -indicatorcolor \
	    [list  disabled $colors(-frame)  pressed $colors(-frame)]
	style map TRadiobutton -indicatorcolor \
	    [list  disabled $colors(-frame)  pressed $colors(-frame)]

	style configure TMenubutton \
	    -width -11 -padding "3 3" -relief raised -anchor w

	style configure TEntry -padding 1
	style map TEntry -fieldbackground \
		[list readonly $colors(-frame) disabled $colors(-frame)]
	style configure TCombobox -padding 1
	style map TCombobox -fieldbackground \
		[list readonly $colors(-frame) disabled $colors(-frame)]

	style configure Toolbutton -relief flat -padding 2
	style map Toolbutton -relief \
	    {disabled flat selected sunken pressed sunken active raised}
	style map Toolbutton -background \
	    [list pressed $colors(-darker)  active $colors(-activebg)]

	style configure TScrollbar -relief raised

	style configure TLabelframe -relief groove -borderwidth 2

	style configure TNotebook -tabmargins {2 2 1 0}
	style configure TNotebook.Tab \
	    -padding {4 2} -background $colors(-darker)
	style map TNotebook.Tab \
	    -background [list selected $colors(-frame)] \
	    -expand [list selected {2 2 1 0}] \
	    ;

	# Treeview:
	style configure Heading -font TkHeadingFont -relief raised
	style configure Row -background $colors(-window)
	style configure Cell -background $colors(-window)
	style map Row \
	    -background [list selected $colors(-selectbg)] \
	    -foreground [list selected $colors(-selectfg)] ;
	style map Cell \
	    -background [list selected $colors(-selectbg)] \
	    -foreground [list selected $colors(-selectfg)] ;
	style map Item \
	    -background [list selected $colors(-selectbg)] \
	    -foreground [list selected $colors(-selectfg)] ;

	style configure TScale \
	    -groovewidth 4 -troughrelief sunken \
	    -sliderwidth raised -borderwidth 2
	style configure TProgressbar \
	    -background $colors(-selectbg) -borderwidth 0
    }
}

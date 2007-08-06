# safetk.tcl --
#
# Support procs to use Tk in safe interpreters.
#
# RCS: @(#) $Id: safetk.tcl,v 1.8.8.1 2006/01/25 18:21:41 dgp Exp $
#
# Copyright (c) 1997 Sun Microsystems, Inc.
#
# See the file "license.terms" for information on usage and redistribution
# of this file, and for a DISCLAIMER OF ALL WARRANTIES.

# see safetk.n for documentation

#
#
# Note: It is now ok to let untrusted code being executed
#       between the creation of the interp and the actual loading
#       of Tk in that interp because the C side Tk_Init will
#       now look up the master interp and ask its safe::TkInit
#       for the actual parameters to use for it's initialization (if allowed),
#       not relying on the slave state.
#

# We use opt (optional arguments parsing)
package require opt 0.4.1;

namespace eval ::safe {

    # counter for safe toplevels
    variable tkSafeId 0;

    #
    # tkInterpInit : prepare the slave interpreter for tk loading
    #                most of the real job is done by loadTk
    # returns the slave name (tkInterpInit does)
    #
    proc ::safe::tkInterpInit {slave argv} {
	global env tk_library

	# We have to make sure that the tk_library variable uses a file
	# pathname that works better in Tk (of the style returned by
	# [file join], ie C:/path/to/tk/lib, not C:\path\to\tk\lib
	set tk_library [file join $tk_library]

	# Clear Tk's access for that interp (path).
	allowTk $slave $argv

	# there seems to be an obscure case where the tk_library
	# variable value is changed to point to a sym link destination
	# dir instead of the sym link itself, and thus where the $tk_library
	# would then not be anymore one of the auto_path dir, so we use
	# the addToAccessPath which adds if it's not already in instead
	# of the more conventional findInAccessPath.
	# Might be usefull for masters without Tk really loaded too.
	::interp eval $slave [list set tk_library [::safe::interpAddToAccessPath $slave $tk_library]]
	return $slave
    }


# tkInterpLoadTk : 
# Do additional configuration as needed (calling tkInterpInit) 
# and actually load Tk into the slave.
# 
# Either contained in the specified windowId (-use) or
# creating a decorated toplevel for it.

# empty definition for auto_mkIndex
proc ::safe::loadTk {} {}
   
::tcl::OptProc loadTk {
    {slave -interp "name of the slave interpreter"}
    {-use  -windowId {} "window Id to use (new toplevel otherwise)"}
    {-display -displayName {} "display name to use (current one otherwise)"}
} {
    set displayGiven [::tcl::OptProcArgGiven "-display"]
    if {!$displayGiven} {
	
	# Try to get the current display from "."
	# (which might not exist if the master is tk-less)
	
	if {[catch {set display [winfo screen .]}]} {
	    if {[info exists ::env(DISPLAY)]} {
		set display $::env(DISPLAY)
	    } else {
		Log $slave "no winfo screen . nor env(DISPLAY)" WARNING
		set display ":0.0"
	    }
	}
    }
    if {![::tcl::OptProcArgGiven "-use"]} {
	
	# create a decorated toplevel
	
	::tcl::Lassign [tkTopLevel $slave $display] w use

	# set our delete hook (slave arg is added by interpDelete)
	# to clean up both window related code and tkInit(slave)
	Set [DeleteHookName $slave] [list tkDelete {} $w]

    } else {

	# set our delete hook (slave arg is added by interpDelete)
	# to clean up tkInit(slave)
	    
	Set [DeleteHookName $slave] [list disallowTk]

	# Let's be nice and also accept tk window names instead of ids
	
	if {[string match ".*" $use]} {
	    set windowName $use
	    set use [winfo id $windowName]
	    set nDisplay [winfo screen $windowName]
	} else {

	    # Check for a better -display value
	    # (works only for multi screens on single host, but not
	    #  cross hosts, for that a tk window name would be better
	    #  but embeding is also usefull for non tk names)
	    
	    if {![catch {winfo pathname $use} name]} {
		set nDisplay [winfo screen $name]
	    } else {

		# Can't have a better one
		
		set nDisplay $display
	    }
	}
	if {$nDisplay ne $display} {
	    if {$displayGiven} {
		error "conflicting -display $display and -use\
			$use -> $nDisplay"
	    } else {
		set display $nDisplay
	    }
	}
    }

    # Prepares the slave for tk with those parameters
    
    tkInterpInit $slave [list "-use" $use "-display" $display]
    
    load {} Tk $slave

    return $slave
}

proc ::safe::TkInit {interpPath} {
    variable tkInit
    if {[info exists tkInit($interpPath)]} {
	set value $tkInit($interpPath)
	Log $interpPath "TkInit called, returning \"$value\"" NOTICE
	return $value
    } else {
	Log $interpPath "TkInit called for interp with clearance:\
		preventing Tk init" ERROR
	error "not allowed"
    }
}

# safe::allowTk --
#
#	Set tkInit(interpPath) to allow Tk to be initialized in
#	safe::TkInit.
#
# Arguments:
#	interpPath	slave interpreter handle
#	argv		arguments passed to safe::TkInterpInit
#
# Results:
#	none.

proc ::safe::allowTk {interpPath argv} {
    variable tkInit
    set tkInit($interpPath) $argv
    return
}


# safe::disallowTk --
#
#	Unset tkInit(interpPath) to disallow Tk from getting initialized
#	in safe::TkInit.
#
# Arguments:
#	interpPath	slave interpreter handle
#
# Results:
#	none.

proc ::safe::disallowTk {interpPath} {
    variable tkInit
    # This can already be deleted by the DeleteHook of the interp
    if {[info exists tkInit($interpPath)]} {
	unset tkInit($interpPath)
    }
    return
}


# safe::tkDelete --
#
#	Clean up the window associated with the interp being deleted.
#
# Arguments:
#	interpPath	slave interpreter handle
#
# Results:
#	none.

proc ::safe::tkDelete {W window slave} {

    # we are going to be called for each widget... skip untill it's
    # top level

    Log $slave "Called tkDelete $W $window" NOTICE
    if {[::interp exists $slave]} {
	if {[catch {::safe::interpDelete $slave} msg]} {
	    Log $slave "Deletion error : $msg"
	}
    }
    if {[winfo exists $window]} {
	Log $slave "Destroy toplevel $window" NOTICE
	destroy $window
    }
    
    # clean up tkInit(slave)
    disallowTk $slave
    return
}

proc ::safe::tkTopLevel {slave display} {
    variable tkSafeId
    incr tkSafeId
    set w ".safe$tkSafeId"
    if {[catch {toplevel $w -screen $display -class SafeTk} msg]} {
	return -code error "Unable to create toplevel for\
		safe slave \"$slave\" ($msg)"
    }
    Log $slave "New toplevel $w" NOTICE

    set msg "Untrusted Tcl applet ($slave)"
    wm title $w $msg

    # Control frame
    set wc $w.fc
    frame $wc -bg red -borderwidth 3 -relief ridge

    # We will destroy the interp when the window is destroyed
    bindtags $wc [concat Safe$wc [bindtags $wc]]
    bind Safe$wc <Destroy> [list ::safe::tkDelete %W $w $slave]

    label $wc.l -text $msg -padx 2 -pady 0 -anchor w

    # We want the button to be the last visible item
    # (so be packed first) and at the right and not resizing horizontally

    # frame the button so it does not expand horizontally
    # but still have the default background instead of red one from the parent
    frame  $wc.fb -bd 0
    button $wc.fb.b -text "Delete" \
	    -bd 1  -padx 2 -pady 0 -highlightthickness 0 \
	    -command [list ::safe::tkDelete $w $w $slave]
    pack $wc.fb.b -side right -fill both
    pack $wc.fb -side right -fill both -expand 1
    pack $wc.l -side left  -fill both -expand 1
    pack $wc -side bottom -fill x

    # Container frame
    frame $w.c -container 1
    pack $w.c -fill both -expand 1
    
    # return both the toplevel window name and the id to use for embedding
    list $w [winfo id $w.c]
}

}

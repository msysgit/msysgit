if {![package vsatisfies [package provide Tcl] 8]} {return}
if {[string compare $::tcl_platform(platform) windows]} {return}
if {[info exists ::tcl_platform(debug)]} {
    package ifneeded registry 1.1.3 \
            [list load [file join $dir tclreg11g.dll] registry]
} else {
    package ifneeded registry 1.1.3 \
            [list load [file join $dir tclreg11.dll] registry]
}

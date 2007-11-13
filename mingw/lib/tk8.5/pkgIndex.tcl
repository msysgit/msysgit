if {[catch {package present Tcl 8.5b2}]} { return }
package ifneeded Tk 8.5b2 [list load [file join $dir .. .. bin tk85.dll] Tk]

# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/19 00:28:55 andreas_kupries Exp $

package ifneeded zlibtcl 1.2.1 [list load [file join $dir zlibtcl121.dll]]

# distinguish static and dyn variants, later.
if {0} {
package ifneeded zlibtcl 1.2.1 [string map [list @dir@ $dir] \
"if {[catch {load [file join @dir@ zlibtcl121.dll]}]} {
    load [file join @dir@ zlibtcl121.dll]
}"]
}
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/19 00:28:55 andreas_kupries Exp $

package ifneeded zlibtcl 1.2.1 [list load [file join $dir zlibtcl121.dll]]

# distinguish static and dyn variants, later.
if {0} {
package ifneeded zlibtcl 1.2.1 [string map [list @dir@ $dir] \
"if {[catch {load [file join @dir@ zlibtcl121.dll]}]} {
    load [file join @dir@ zlibtcl121.dll]
}"]
}
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/19 00:28:54 andreas_kupries Exp $

package ifneeded tifftcl 3.6.1 [list load [file join $dir tifftcl361.dll]]

# distinguish static and dyn variants, later.
if {0} {
package ifneeded tifftcl 3.6.1 [string map [list @dir@ $dir] \
"if {[catch {load [file join @dir@ tifftcl361.dll]}]} {
    load [file join @dir@ tifftcl361.dll]
}"]
}
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/19 00:28:54 andreas_kupries Exp $

package ifneeded jpegtcl 1.0 [list load [file join $dir jpegtcl10.dll]]

# distinguish static and dyn variants, later.
if {0} {
package ifneeded jpegtcl 1.0 [string map [list @dir@ $dir] \
"if {[catch {load [file join @dir@ jpegtcl10.dll]}]} {
    load [file join @dir@ jpegtcl10.dll]
}"]
}
# -*- tcl -*- Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.5 2003/03/09 17:13:07 obermeier Exp $

package ifneeded img::base 1.3 [list load [file join $dir tkimg13.dll]]

package ifneeded Img   1.3 {
    # Compatibility hack. When asking for the old name of the package
    # then load all format handlers and base libraries provided by tkImg.
    # Actually we ask only for the format handlers, the required base
    # packages will be loaded automatically through the usual package
    # mechanism.

    # When reading images without specifying it's format (option -format),
    # the available formats are tried in reversed order as listed here.
    # Therefore file formats with some "magic" identifier, which can be
    # recognized safely, should be added at the end of this list.

    package require img::window
    package require img::tga
    package require img::ico
    package require img::pcx
    package require img::sgi
    package require img::sun
    package require img::xbm
    package require img::xpm
    package require img::ps
    package require jpegtcl
    package require tifftcl
    package require img::bmp
    package require img::ppm
    package require img::gif
    package require img::pixmap

    package provide Img 1.3
}
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/21 07:20:23 andreas_kupries Exp $

package ifneeded "img::bmp" 1.3 [list load [file join $dir tkimgbmp13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/21 07:20:23 andreas_kupries Exp $

package ifneeded "img::gif" 1.3 [list load [file join $dir tkimggif13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:07 andreas_kupries Exp $

package ifneeded "img::ico" 1.3 [list load [file join $dir tkimgico13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:07 andreas_kupries Exp $

package ifneeded "img::ico" 1.3 [list load [file join $dir tkimgico13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:07 andreas_kupries Exp $

package ifneeded "img::pcx" 1.3 [list load [file join $dir tkimgpcx13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/12/05 07:08:42 andreas_kupries Exp $

package ifneeded "img::pixmap" 1.3 [list load [file join $dir tkimgpixmap13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/12/05 07:08:42 andreas_kupries Exp $

package ifneeded "img::pixmap" 1.3 [list load [file join $dir tkimgpixmap13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:07 andreas_kupries Exp $

package ifneeded "img::ppm" 1.3 [list load [file join $dir tkimgppm13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:07 andreas_kupries Exp $

package ifneeded "img::ps" 1.3 [list load [file join $dir tkimgps13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:08 andreas_kupries Exp $

package ifneeded "img::sgi" 1.3 [list load [file join $dir tkimgsgi13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:08 andreas_kupries Exp $

package ifneeded "img::sun" 1.3 [list load [file join $dir tkimgsun13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:08 andreas_kupries Exp $

package ifneeded "img::tga" 1.3 [list load [file join $dir tkimgtga13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:08 andreas_kupries Exp $

package ifneeded "img::tga" 1.3 [list load [file join $dir tkimgtga13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 08:57:56 andreas_kupries Exp $

package ifneeded "img::window" 1.3 [list load [file join $dir tkimgwindow13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:08 andreas_kupries Exp $

package ifneeded "img::xbm" 1.3 [list load [file join $dir tkimgxbm13.dll]]
# Tcl package index file - handcrafted
#
# $Id: pkgIndex.tcl.in,v 1.1 2002/11/29 05:46:08 andreas_kupries Exp $

package ifneeded "img::xpm" 1.3 [list load [file join $dir tkimgxpm13.dll]]

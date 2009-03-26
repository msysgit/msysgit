# tifftclConfig.sh --
# 
# This shell script (for sh) is generated automatically by tifftcl's
# configure script.  It will create shell variables for most of
# the configuration options discovered by the configure script.
# This script is intended to be included by the configure scripts
# for tifftcl extensions so that they don't have to figure this all
# out for themselves.  This file does not duplicate information
# already provided by tclConfig.sh, so you may need to use that
# file in addition to this one.
#
# The information in this file is specific to a single platform.

# tifftcl's version number.
tifftcl_VERSION='3.6.1'
tifftcl_MAJOR_VERSION='3'
tifftcl_MINOR_VERSION='6'
tifftcl_RELEASE_LEVEL='1'

# The name of the tifftcl library (may be either a .a file or a shared library):
tifftcl_LIB_FILE=tifftcl361.dll

# String to pass to linker to pick up the tifftcl library from its
# build directory.
tifftcl_BUILD_LIB_SPEC='-L/src/tcltk/tkimg1.3/libtiff/tcl -ltifftcl361'

# String to pass to linker to pick up the tifftcl library from its
# installed directory.
tifftcl_LIB_SPEC='-L/mingw/lib/tifftcl3.6.1 -ltifftcl361'

# The name of the tifftcl stub library (a .a file):
tifftcl_STUB_LIB_FILE=tifftclstub361.a

# String to pass to linker to pick up the tifftcl stub library from its
# build directory.
tifftcl_BUILD_STUB_LIB_SPEC='-L/src/tcltk/tkimg1.3/libtiff/tcl -ltifftclstub361'

# String to pass to linker to pick up the tifftcl stub library from its
# installed directory.
tifftcl_STUB_LIB_SPEC='-L/mingw/lib/tifftcl3.6.1 -ltifftclstub361'

# String to pass to linker to pick up the tifftcl stub library from its
# build directory.
tifftcl_BUILD_STUB_LIB_PATH='/src/tcltk/tkimg1.3/libtiff/tcl/tifftclstub361.a'

# String to pass to linker to pick up the tifftcl stub library from its
# installed directory.
tifftcl_STUB_LIB_PATH='/mingw/lib/tifftcl3.6.1/tifftclstub361.a'

# Location of the top-level source directories from which tifftcl
# was built.  This is the directory that contains generic, unix, etc.
# If tifftcl was compiled in a different place than the directory
# containing the source files, this points to the location of the
# sources, not the location where tifftcl was compiled. This can
# be relative to the build directory.

tifftcl_SRC_DIR='/src/tcltk/tkimg1.3/libtiff/tcl'

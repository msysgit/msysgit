===== TDM's Experimental GCC/MinGW32 Builds =====

NOTICE:
TDM-GCC is an unofficial replacement for the official GCC binaries distributed
by the MinGW project; please note the following caveats:
 * TDM-GCC is not formally affiliated with or endorsed by the MinGW project
    (although several MinGW team members make use of it)
 * No level of support for TDM-GCC is in any way guaranteed (although a best
    effor is made to fix bugs as they are found or forward them to GCC Bugzilla)

BUGS:
If you encounter a problem while using a TDM-GCC build that isn't present in a
previous MinGW or TDM release, you are encouraged to submit a helpful bug
report. Please see <http://www.tdragon.net/recentgcc/bugs.php> for further
instructions.


>>>>> INSTALLATION

*** TDM/MinGW Installer ***

Using the TDM/MinGW installer is highly recommended; it can automatically
install TDM-GCC (or the official MinGW GCC) as well as all supplementary MinGW
base system packages. The installer uses a standard wizard interface with
reasonable defaults.

*** Manual Installation ***

These binary packages are designed as drop-in replacements for the MinGW
project's official gcc packages. When using these packages, you are encouraged
to start with a clean slate and install only the MinGW packages which are
necessary to you. You'll need the following packages for basic Windows
development:
 * binutils (binutils-2.19.1-mingw32-bin.tar.gz)
 * mingw-runtime (mingwrt-3.15.2-mingw32-dev.tar.gz)
 * w32api (w32api-3.13-mingw32-dev.tar.gz)
You might also want to install:
 * mingw-utils (mingw-utils-0.3.tar.gz)
 * mingw32-make (mingw32-make-3.81-20080326-3.tar.gz)
 * gdb (gdb-6.8-mingw-3.tar.bz2)
You'll need GDB particularly if you want to use an IDE with debugging support.

Decide whether to use the SJLJ or DW2 (Dwarf-2) exception model. Then, for the
exception model of your choice, download at least the "core" TDM-GCC package,
which includes the required base files as well as support for the C language.
You can also download any or all of the other TDM-GCC packages, depending on
which of GCC's supported languages you'd like to use.

Extract the MinGW packages to an empty directory -- typically C:\MinGW. Then,
extract the TDM-GCC package(s) and choose to overwrite any duplicate files that
may exist. Finally, consider adding the bin directory to your Windows PATH
environment variable.


>>>>> USAGE NOTES

*** "Graphite" Loop Transformations ***

The TDM release of GCC 4.4.0 includes support for GCC 4.4's Graphite loop
transformation infrastructure. Because support for these optimizations is
currently optional, they are not enabled at any of the -O optimization levels.
If you are interested in using them, the relevant options are
"-floop-interchange", "-floop-strip-mine", and "-floop-block", and they are
documented at
<http://gcc.gnu.org/onlinedocs/gcc-4.4.0/gcc/Optimize-Options.html>

*** Dwarf-2 vs. SJLJ unwinding ***

GCC supports two methods of stack frame unwinding: Dwarf-2 (DW2) or SJLJ
(setjmp/longjmp). Until recently, only SJLJ has been available for the Windows
platform. This affects you, the end user, primarily in programs that throw and
catch exceptions. Programs which utilize the DW2 unwind method handle exceptions
much more quickly than programs which utilize the SJLJ method. However, the DW2
method increases code size by a noticeable amount, and additionally cannot yet
unwind (pass exceptions) through "foreign" stack frames: stack frames compiled
by another non-DW2-enabled compiler, such as OS DLLs in a Windows callback.

This means that you should in general choose the SJLJ version of the TDM-GCC
builds unless you know you need faster exception handling and can be certain you
will never throw an exception through a foreign stack area.

As distributed, the SJLJ and DW2 packages of TDM-GCC can coexist peacefully
extracted to the same directory (e.g. any files in common are for all intents
and purposes identical), because the driver executables (the ones in the "bin"
directory) are suffixed with "-dw2" for the DW2 build, and the libraries and
other executables hide in another "-dw2" directory in "lib(exec)/gcc/mingw32".
This allows you to use the same single addition to your PATH, and use DW2
exceptions only when you need them by calling "gcc-dw2", etc. If you truly want
DW2 exceptions as the default when calling "gcc" (from Makefiles or configury
systems, for example), you can rename or copy the suffixed executables to their
original names.

*** Exceptions and DLLs ***

The mingw32 port of GCC is gradually moving toward the generally accepted method
the rest of the world uses in allowing exceptions to propagate out of shared
libraries (DLLs) -- that is, reliance on a third DLL to contain state data
for the exception handling system. For any GCC language that supports exceptions
(and DLLs), this actually involves two extra DLLs: (1) libgcc_s*.dll, which
contains common core data, and (2) a language-specific DLL. You will note that
the first phase of this move (libgcc_s*.dll) finally builds correctly
out-of-the-box, but NOT THE SECOND PHASE (the language-specific DLLs).

Until such time as the language-specific DLLs build correctly, therefore,
TDM-GCC will continue to rely on a versioned shared memory region. You do not
need any additional command-line options to throw exceptions out of DLLs.

If you'd like to try out the new libgcc DLL for other reasons, add
"-shared-libgcc" to the command line, but be warned -- it may *break* inter-DLL
exceptions.

*** OpenMP and pthreads-w32 ***

The core binary package has been built to allow the use of GCC's "-fopenmp"
option for generating parallel code as specified by the OpenMP API. (See
<http://gcc.gnu.org/onlinedocs/gcc-4.4.0/libgomp/> for details.)

The OpenMP support in the TDM-GCC builds has received very little testing; if
you find build or packaging problems, please send a bug report (see BUGS above).

LibGOMP, GCC's implementation of OpenMP, currently only supports the use of the
POSIX Threads (pthreads) api for implementing its threading model. Because the
MinGW project itself doesn't distribute a pthreads implementation, the
"pthreads-win32" library, available from http://sourceware.org/pthreads-win32/,
is included in this distribution. If you aren't familiar with pthreads-win32,
please read the file "pthreads-win32-README" for more information, or the
documentation available at the website referenced above. pthreads-win32 is
distributed under the terms of the LGPL; see "COPYING.lib-gcc-tdm.txt" for
details.

In order to correctly compile code that utilizes OpenMP/libGOMP, you need to add
the "-fopenmp" option at compile time AND link time, and link to libgomp.a and
libpthread.a at link time ("-lgomp -lpthread"). By default, libpthread.a links
the standard C-cleanup DLL version of pthreads-win32 to your program, which
means that you will need to ensure that the file "pthreadGC2.dll" (included in
the "bin" subdirectory of this package) can be found by your program. If you
plan to distribute a program that relies on pthreads-win32, be sure to
understand and comply with the terms of the LGPL (see COPYING.lib-gcc-tdm.txt).

"libpthread.a" is included in the "lib/gcc/mingw32/4.4.0[-dw2]" subdirectory of
this package along with two other pthreads library files:
 - "libpthreadGC2-static.a" provides a static version of the pthreads-win32
     library, but it requires some additional non-POSIX-compliant startup code
     to be included in your program. See "pthreads-win32-README" for
     details.
 - "libpthreadGCE2.a" provides a version of the pthreads-win32 library with
     a somewhat safer response in the face of unexpected C++ exceptions.
     The creators of the pthreads-win32 library recommend, however, that this
     version not be used, because code written to rely on this is less portable.

*** Warnings and errors ***

GCC 4 represents a significant step forward in optimization capabilities, error
detection, and standards compliance, and this is more true than ever with the
most recent GCC releases. For you, the end user, this will mean that code which
compiled and ran without problems on previous GCC releases will almost certainly
exhibit some warnings and maybe even a few errors.

These meaningful warnings and errors are a very good thing, as they help the
programmer to write safer and more correct code. Unfortunately, there's also a
chance you might encounter incorrect warnings or errors, ICE's (internal
compiler errors, where the compiler makes a mistake and has to bail out), or
even miscompilations (where your code is incorrectly compiled and produces the
wrong result).

If you encounter an ICE while using a TDM-GCC build, feel free to file a bug
report (see BUGS above). With any other unexpected problem, you are urged to
work from the assumption that it stems from user error, and ensure that your
code is correct and standards-compliant. 


>>>>> BUGS AND KNOWN ISSUES

 * Under rare and as-yet-unidentified circumstances, inclusion of a precompiled
     header will cause compilation to fail with an error like "error: calling
     fdopen: bad file descriptor or file name". It seems only to happen when the
     PCH is double-included by both an #include directive and the -include
     command-line switch, but this in itself will not trigger the bug.

As these builds are provided on the same basis as the source releases, and the
mingw32 target in GCC tends to receive somewhat less-than-average attention,
some bugs are expected. If you encounter a bug that you are certain is in the
GCC sources (such as an ICE), or that is due to an issue in the building or
packaging process, you are encouraged to report it. Please visit the TDM-GCC
Bugs Page at <http://www.tdragon.net/recentgcc/bugs.php> for bug reporting
instructions.


>>>>> LOCAL FIXES AND CHANGES

 - Includes a patch ported from the official MinGW 3.4.5 release to propagate
     exceptions out of DLLs without the need for shared versions of libgcc and
     libstdc++.
 - Includes a patch which corrects backslash usage in header paths and fixes
      path problems when debugging. (See
      http://sourceforge.net/tracker2/?func=detail&aid=2145427&group_id=200665&atid=974439)
 - Includes a patch to keep GCC from erroneously using the CWD as the
     installation directory.
 - Configured with "--enable-fully-dynamic-string", which fixes a bug when
     passing empty std::string objects between DLLs and EXEs.

[The following patches are only necessary for the 4.3 series and have been
applied in the 4.4 sources]

 - Includes a patch to fix a crash when all temporary directory environment
     variables are empty.


>>>>> SOURCE CODE

The source code for the TDM-GCC binary releases is available from the TDM-GCC
download page on SourceForge:
<http://sourceforge.net/project/showfiles.php?group_id=200665>
(The most up-to-date link to the download site will always be available at
<http://www.tdragon.net/recentgcc/>.

The source is distributed in the form of the original ("vanilla") separate
source packages as downloaded, plus an additional "TDM Sources" package. The TDM
Sources package includes unified diffs of any changes made to the vanilla
sources, as well as the set of scripts used to build the binary releases.


>>>>> LICENSE

The TDM-GCC packages contain binary distributions constituting a work based on
GCC, CLooG, and PPL, all of which are licensed under the GPL. For further
details, refer to the file "COPYING-gcc-tdm.txt" within the downloaded package.
Additionally, TDM-GCC contains binary files constituting works based on
libiconv, GMP, MPFR, and pthreads-w32, all of which are licensed under the LGPL;
COPYING.lib-gcc-tdm.txt contains a copy of the LGPL.

The TDM-GCC distribution is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your option) any
later version.

TDM-GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

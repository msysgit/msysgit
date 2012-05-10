# Build environment for Git for Windows

This is the build environment -- also known as msysGit -- for [Git for Windows](http://msysgit.googlecode.com/).

The easiest way is to install it via the [net installer](http://code.google.com/p/msysgit/downloads/list?q=netinstall). This installer will clone our [two](http://github.com/msysgit/msysgit) [repositories](http://github.com/msysgit/git), including all the necessary components to build Git for Windows, and perform an initial build.

# The build environment

msysGit brings a few components that are required to build Git:

- Bash, a Unix-type command-line shell. Quite a few components of Git itself are still shell scripts. Therefore, Bash is required to execute Git commands (see the output of `cd /git && git ls-files \*.sh` for a full list).
- the GNU C Compiler. Since we try to rely only on free software (apart from the Operating System, of course), we think it makes more sense to rely on GCC than on Visual Studio express. Also, it makes the maintenance burden lighter, as [upstream Git](http://github.com/gitster/git) also targets mainly GCC.
- GNU Make.
- Perl. Still required for a couple of Git components (see the output of `cd /git && git ls-files \*.perl`), most notably `git svn`.
- Tcl/Tk, a scripting language making it easy to implement cross-platform graphical user interfaces. We need this for `gitk` and `git gui`.
- [cURL](http://curl.haxx.se), a library implementing HTTP and FTP transport.
- many more libraries.
- some Unix programs required by the shell scripts in Git.

# The relationship between _msysGit_ and _Git for Windows_

[Git for Windows](http://code.google.com/p/msysgit/downloads/list?q=full+installer+for+official+git) is the software package that installs a minimal environment to run Git on Windows. It comes with a Bash (a Unix-type shell), with a Perl interpreter and with the Git executable and its dependencies.

On the other hand, msysGit is the software package installing the _build environment_ that can build Git for Windows.  The easiest way is to install it via the [net installer](http://code.google.com/p/msysgit/downloads/list?q=netinstall).

# The difference between MSys and MinGW

The [MinGW project](http://mingw.org/)'s goal is to provide a way to compile native Windows binaries with no POSIX layer using the GNU C Compiler.

However, at least the Bash needs a POSIX layer (most notably due to the absence of the `fork()` call on Windows). Therefore, MSys (the _minimal system_) is thrown in, offering the minimal system necessary to offer Bash (and Perl) functionality on Windows.

Consequently, MSys ships with a POSIX layer (based on an old version of Cygwin) that is only used by the Bash and Perl, but not by anything compiled within that environment.

# Further information

For more information and documentation, please have a look and enhance our [Wiki](https://github.com/msysgit/msysgit/wiki).

For code contributions and discussions, please see our [mailing list](http://groups.google.com/group/msysgit).

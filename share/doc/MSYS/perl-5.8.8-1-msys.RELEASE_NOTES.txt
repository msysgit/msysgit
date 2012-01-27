msys perl
========================================================================
Perl is a general-purpose programming language originally developed for
text manipulation and now used for a wide range of tasks including
system administration, web development, network programming, GUI
development, and more.  This is port to the msys platform.

Note that msys-perl does NOT include the tools needed for the perlrebase
script in its list of automatically-installed dependencies.  Therefore,
mingw-get will NOT automatically install all of those tools.  If you
need perlrebase, manually ensure the following packages are installed:
	mingw-get install msys-findutils-bin \
                          msys-grep-bin \
                          msys-sed-bin \
                          msys-rebase-bin
and EITHER of the following:
	mingw-get install msys-binutils-bin
	mingw-get install mingw32-binutils-bin

Runtime requirements:
  msysCORE-1.0.17-1-msys-1.0.17-bin
  zlib-1.2.3-2-msys-1.0.13-dll
  libbz2-1.0.5-2-msys-1.0.13-dll-1
  libgdbm-1.8.3-3-msys-1.0.13-dll-3
  libcrypt-1.1_1-3-msys-1.0.13-dll-0
  libexpat-2.0.1-1-mingw32-dll-1
  libxml2-2.7.6-1-msys-1.0.13-dll-2
  findutils-4.4.2-2-msys-1.0.13-bin # for perlrebase
  grep-2.5.4-2-msys-1.0.13-bin      # for perlrebase
  sed-4.2.1-2-msys-1.0.13-bin       # for perlrebase
  binutils-*-msys-*-bin             # for perlrebase
  rebase-3.0.1_1-2-msys-1.0.15-bin  # for perlrebase

Build requirements:
  binutils-*-msys-*-bin
  gcc-*-msys-*-bin
  w32api-*-msys-*-dev

  Devel Tools and Dependent Libraries
    zlib-*-msys-*-dev
    libbz2-*-msys-*-dev
    libgdbm-*-msys-*-dev 
    libcrypt-*-msys-*-dev
    libiconv-*-msys-*-dev
    libiconv-*-msys-*-bin
    libexpat-*-msys-*-dev
    libxml2-*-msys-*-dev
    libtermcap-*-msys-*-dev
    groff-*-msys-*-bin
    rebase-*-msys-*-bin

  MSYS Environment
    msysCORE-1.0.17-1-msys-1.0.17-dev
    coreutils-5.97-3-msys-1.0.13-bin
    findutils-4.4.2-2-msys-1.0.13-bin
    grep-2.5.4-2-msys-1.0.13-bin
    sed-4.2.1-2-msys-1.0.13-bin
    bash-3.1.17-4-msys-1.0.16-bin
    make-3.81-3-msys-1.0.13-bin
    tar-1.23-1-msys-1.0.13-bin
    xz-4.999.9beta_20100409-1-msys-1.0.13-bin
    gzip-1.3.12-2-msys-1.0.13-bin
    liblzma-4.999.9beta_20100409-1-msys-1.0.13-dll-1
    zlib-1.2.3-2-msys-1.0.13-dll

Canonical homepage:
  http://www.perl.org/
  http://search.cpan.org/dist/perl-5.8.8/


Canonical download:
  Official perl-5.8.8:
  http://www.cpan.org/src/perl-5.8.8.tar.gz 

License:
  Artistic, GPL

Language:
  C, perl

========================================================================

Build instructions:
  unpack perl-5.8.8-1-msys-1.0.17-src.tar.lzma
  ./msys-build-perl

This will create:
  perl-5.8.8-1-msys-1.0.17-src.tar.lzma
  perl-5.8.8-1-msys-1.0.17-bin.tar.lzma
  perl-5.8.8-1-msys-1.0.17-doc.tar.lzma
  perl-5.8.8-1-msys-1.0.17-html.tar.lzma
  perl-5.8.8-1-msys-1.0.17-lic.tar.lzma

========================================================================

Test suite results

To reproduce these results, you need to use /bin/perl instead of ./perl
for the whole testsuite and remove the t/for_find directory, and rerun
 lib/filefind-taint.t and lib/filefind.t:

cd t
rm -rf for_find
PERL=/bin/perl /bin/perl harness lib/File/Find/t/find.t
rm -rf for_find
PERL=/bin/perl /bin/perl harness lib/filefind-taint.t

Failed Test                     Stat Wstat Total Fail  Failed  List of Failed
-------------------------------------------------------------------------------
../ext/Cwd/t/cwd.t                 2   512    29    2   6.90%  22-23
../ext/Cwd/t/taint.t               8  2048    17    8  47.06%  2 4 6 8 10 12 14
                                                               16
../lib/File/Copy.t                 4  1024    60    4   6.67%  28-29 55-56
../lib/File/Find/t/find.t                    199   62  31.16%  26-28 38-40 51-53 62-
                                                               64 80-82 109-113 170
                                                               184 186 188 200-227
../lib/File/Find/t/taint.t         8  2048    45   11  24.44%  3 5 10 26-28 32
                                                               46-48
../lib/File/Spec/t/Spec.t                    472    1   0.21%  468
../lib/Net/Ping/t/450_service.t               26    2   7.69%  9 18
../lib/Test/t/multiline.t                      2    1  50.00%  2
lib/filefind-taint.t                          45    6  13.33%  26-28 46-48
op/stat.t                                     86    3   3.49%  9 32 86
op/taint.t                       255 65280   238  420 176.47%  1-3 5 31-238
58 tests and 295 subtests skipped.
Failed 11/993 test scripts, 98.89% okay. 300/117046 subtests failed, 99.74% okay.

Note, if we remove all the "taint" tests, we end up with:
Failed 7/989 test scripts, 99.29% okay. 75/116701 subtests failed, 99.94% okay.

Of the remainder:

ext/Cwd/t/cwd.t                  - symlinks
../lib/File/Copy.t               - symlinks
../lib/File/Find/t/find.t        - symlinks
../lib/File/Spec/t/Spec.t        - test expects to collapse ///x to /x, but
                                   this is explicitly disabled on msys (UNC)
../lib/Net/Ping/t/450_service.t  - wonky firewall issues on Vista?
../lib/Test/t/multiline.t        - test is xfail; bug is we only xfail #1, and
                                   "count" #2.
op/stat.t                        -  9: hardlink ctime != mtime
                                   32: symlinks
                                   86: miscount. There really are only 85. 


Test results for bundled extensions:

All of the bundled extensions, except five, pass all of their tests. The
four extensions with some failures are:

========== log-ext-CPAN-1.9102.txt ===========
Failed 1/13 test scripts, 92.31% okay. 3/203 subtests failed, 98.52% okay.

========== log-ext-Math-BigInt-FastCalc-0.15.txt ===========
Failed 4/9 test scripts, 55.56% okay. 810/6892 subtests failed, 88.25% okay.

========== log-ext-Module-Build-0.2808.txt ===========
Failed 1/26 test scripts, 96.15% okay. 1/787 subtests failed, 99.87% okay.

========== log-ext-Win32API-File-0.1001.txt ===========
Failed 1/2 test scripts, 50.00% okay. 2/277 subtests failed, 99.28% okay.

========== log-ext-XML-LibXML-1.63.txt ===========
Failed 1/32 test scripts, 96.88% okay. 2/1790 subtests failed, 99.89% okay.

========================================================================

Port Notes:

Bundled Extensions
------------------
Algorithm-Diff-1.1902      HTML-Tagset-3.10           Probe-Perl-0.01
Alias-2.32                 IO-CaptureOutput-1.03      Proc-ProcessTable-0.41
Archive-Tar-1.32           IO-Compress-Base-2.005     Regexp-Common-2.120
Archive-Zip-1.20           IO-Compress-Bzip2-2.005    Tee-0.13
B-Generate-1.09            IO-Compress-Zlib-2.005     TermReadKey-2.30
Compress-Bzip2-2.09        IO-String-1.08             Term-ReadLine-Gnu-1.16
Compress-Raw-Bzip2-2.005   IO-Zlib-1.05               Term-ReadLine-Perl-1.0302
Compress-Raw-Zlib-2.005    IPC-Run3-0.037             Test-Pod-1.26
Compress-Zlib-2.005        libwww-perl-5.805          Test-Pod-Coverage-1.08
Config-Tiny-2.10           Math-BigInt-FastCalc-0.15  Test-Reporter-1.27
CPAN-1.9102                MD5-2.03                   Text-Diff-0.35
CPAN-Reporter-0.44         Module-Build-0.2808        URI-1.35
Devel-Symdump-2.07         Module-ScanDeps-0.75       version-0.7203
Digest-SHA-5.45            Module-Signature-0.55      Win32API-File-0.1001
ExtUtils-CBuilder-0.19     Net-Telnet-3.03            XML-LibXML-1.63
ExtUtils-ParseXS-2.18      PadWalker-1.5              XML-LibXML-Common-0.13
File-Copy-Recursive-0.33   PAR-Dist-0.23              XML-NamespaceSupport-1.09
File-HomeDir-0.65          Pod-Coverage-0.18          XML-Parser-2.34
File-pushd-0.99            Pod-Escapes-1.04           XML-SAX-0.15
File-Temp-0.18             podlators-2.0.5            YAML-0.62
Getopt-Long-2.36           Pod-Readme-0.09            YAML-Syck-0.88
HTML-Parser-3.56           Pod-Simple-3.05

Special configuration settings
------------------------------
-DDEBUGGING -- Not to be confused with -g, this macro causes perl to be built
               with a slight amount of runtime overhead, but enables the use
               of the -D* commandline options. See `perldoc perlrun'
64bitint    -- Perl will support 64bit wide scalar values (e.g. long longs).



----------  perl-5.8.8-1 -- 2011 Apr 25 -----------
* Use the patches from msysgit and cygwin, some trunk code and lots
  of testsuite adjustments to shape up 5.8.8. Thanks to the msysgit
  team and LRN for the bulk of these adaptations.
* Add perlrebase script
* Include expanded set of bundled extensions (derived from the list
  shipped with cygwin's perl-5.8.8-4 package) so that end users may
  have a fully operational CPAN shell out-of-the-box.

----------  perl-5.6.1_2-2 -- 2010 Jan 30 -----------
* Rebuild against msys-1.0.16, using (msys)gcc-3.4.4
  and (msys)binutils-2.19.51.
* Link against new (separate) gdbm and gdbm-compat libraries
* Link against (static) libiconv
* Build with -DDEBUGGING -- but symbols are stripped; this allows
  printing internal state within perl itself, but doesn't allow
  using gdb. This is a compromise for size (besides, gdb-based
  debugging at -O2 is not very useful).
* Use -O2 -fno-unit-at-a-time to avoid optimization bug
  in latest msys-gcc. Also, don't use -mms-bitfields.

----------  perl-5.6.1_2-1 -- 2009 Jul 30 -----------
* First release of perl for msys using new packaging standard.


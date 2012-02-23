Checking if your kit is complete...
Looks good
Writing Makefile for Pod::Readme
cp lib/Pod/Readme.pm blib/lib/Pod/Readme.pm
cp bin/pod2readme blib/script/pod2readme
/bin/perl.exe "-MExtUtils::MY" -e "MY->fixin(shift)" blib/script/pod2readme
/bin/perl.exe "-MExtUtils::Command::MM" "-e" "test_harness(0, 'blib/lib', 'blib/arch')" t/*.t
t/10-basic.......ok
t/90-fileport....skipped
        all skipped: Enable DEVEL_TESTS environent variable
t/90-pod.........skipped
        all skipped: Enable DEVEL_TESTS environent variable
t/90-podcover....skipped
        all skipped: Enable DEVEL_TESTS environent variable
All tests successful, 3 tests skipped.
Files=4, Tests=163,  2 wallclock secs ( 0.52 cusr +  0.91 csys =  1.44 CPU)
Installing /usr/lib/perl5/vendor_perl/5.8/Pod/Readme.pm
Installing /usr/bin/pod2readme
Writing /usr/lib/perl5/vendor_perl/5.8/msys/auto/Pod/Readme/.packlist
Appending installation info to /usr/lib/perl5/5.8/msys/perllocal.pod

#!/bin/sh

# in its infinite wisdom, Microsoft decided that Vista should treat _all_
# programs _containing_ the substring "setup", "install" or "update" as
# administrative programs.
#
# And now we have to say _explicitely_ that they are not.  Great.

cd /

for program in $(ls bin/*.exe | grep -ie setup -e install -e update -e patch)
do
	test -f $program.manifest || {
		base=$(basename $program)
		sed "s/patch.exe/$base/" \
			< /bin/patch.exe.manifest > $program.manifest
		git update-index --add $program.manifest
	}
done


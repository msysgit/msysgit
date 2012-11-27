#!/bin/sh

# This is the Tcl/Tk updating script for msysGit


cd "$(dirname "$0")"
srcdir=$(pwd)

mirror=http://kent.dl.sourceforge.net/project/tcl/Tcl/
version=8.5.13

for p in tcl tk
do
	# get the package
	u=$mirror$version/$p$version-src.tar.gz
	b=$(basename $u)
	test -f $b || curl $u > $b || exit

	# unpack it
	d=$p$version
	test -d $d || tar xzvf $b || exit

	# compile it
	shortversion=$(echo $version |
		sed -n "s/^[^0-9]*\([0-9][0-9]*\)\.\([0-9][0-9]*\).*/\1\2/p")
	case $p in
	tcl) prog=tclsh$shortversion.exe;;
	tk) prog=wish$shortversion.exe;;
	esac
	test -f $d/win/$prog || (
		cd $d/win &&
		./configure --prefix=/mingw &&
		make ||
		exit
	)

	# install it
	test -f /mingw/bin/$prog && test /mingw/bin/$prog -nt $d/win/$prog || (
		cd $d/win &&

		# Record pre-install state
		index=$(/share/msysGit/pre-install.sh) &&

		# Remove old Tcl/Tk files stored in fileList.txt
		list=$srcdir/fileList-$p.txt
		cat "$list" | grep -v 'release\.sh$' | (cd / && xargs git rm) &&

		make install &&

		shortprog=$(echo $prog | tr -d '0-9') &&
		if test ! -f /mingw/bin/$shortprog
		then
			ln /mingw/bin/$prog /mingw/bin/$shortprog
		fi &&

		/share/msysGit/post-install.sh $index \
			"Update $p to version $version" &&

		git diff --diff-filter=AM --name-only HEAD^! |
			sed -e "s/^/\//" > "$list" &&
		(cd / && git commit -C HEAD --amend -- "$list") ||

		exit
)
done

echo "Successfully built and installed Tcl/Tk $version"
echo


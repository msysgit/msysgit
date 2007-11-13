#!/bin/sh

# This is the Tcl/Tk updating script for msysGit


# Make sure that the working directory is clean and does not have untracked
# files; otherwise our semi-automatic finding the new files will not work!

(cd / &&
	git diff-files --quiet &&
	git diff-index --cached --quiet HEAD &&
	test -z "$(git ls-files --exclude-from=.gitignore \
		--exclude-per-directory=.gitignore --others)") || {
	echo "State not pristine enough for successful Tcl/Tk update"
	exit 1
}

cd "$(dirname "$0")"

# Remove old Tcl/Tk files stored in fileList.txt

cat fileList.txt | (cd / && xargs git rm) || exit

mirror=http://kent.dl.sourceforge.net/sourceforge/tcl/
version=8.5b2

for p in tcl tk
do
	# get the package
	u=$mirror$p$version-src.tar.gz
	b=$(basename $u)
	test -f $b || curl $u > $b || exit

	# unpack it
	d=$p$version
	test -d $d || tar xzvf $b || exit

	# compile it
	shortversion=$(echo $version |
		sed -e "s/[ab][0-9][0-9]*$//" -e "s/[^0-9]//g")
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
	test -f /mingw/bin/$prog || (
		cd $d/win &&
		make install ||
		exit
	)
done

# update index
(cd / && git add .) || exit

git diff --cached --diff-filter=AM --name-only |
	sed -e "s/^/\//" > fileList.txt ||
	exit

git add fileList.txt || exit

echo "Successfully built and installed Tcl/Tk $version"
echo "After checking the result, please commit (possibly with --amend)"
echo

#!/bin/sh

# This is a package updating script for msysGit

cd "$(dirname "$0")" || {
	echo "Could not switch to $(dirname "$0")"
	exit 1
}

package=TkImg
list=fileList-tkImg.txt
version=1.3
dir=tkimg$version
tar=tkimg$version.tar.bz2
taropt=-j
url=http://kent.dl.sourceforge.net/sourceforge/tkimg/$tar

patch_tkImg () {
	init_git &&
	git rev-parse --verify HEAD^ || {
		perl -i.bak -pe "s/(MP-RAS.*relid)\'/\\1/" \
			$(find -name configure) &&
		perl -i.bak -pe "s/EXTERN (int TkimgInitUtilities)/\\1/" \
			base/tkimg.c &&
		git commit -m "fix configure" -a
	}
}

patch=patch_tkImg

configure_extra=--srcdir=$(pwd)/$dir

premake_tkImg () {
	perl -i.bak -pe "s/-L(\\S+) -l(tkimgstub\S+)/\\1\/\\2.a/" \
		$(find -name Makefile)
}

premake=premake_tkImg

# The functions (overridable by setting $fetch, $unpack, $compile or $install)

fetch_it () {
	test -f $tar || curl $url > $tar
}

test -z "$fetch" && fetch=fetch_it

unpack_it () {
	test -d $dir || tar -xv $taropt -f $tar
}

test -z "$unpack" && unpack=unpack_it

test -z "$premake" && premake=true

compile_it () {
	test -f Makefile || {
		./configure --prefix=/mingw $configure_extra &&
		$premake &&
		make
	}
}

test -z "$compile" && compile=compile_it

install_it () {
	make install
}

test -z "$install" && install=install_it

init_git () {
	test -d .git || {
		git init &&
		git add . &&
		git commit -m "imported $package $version"
	}
}

# Do the real work

$fetch &&

$unpack &&

(cd $dir &&

	$patch &&

	$compile
) &&

# Install

index=$(/share/msysGit/pre-install.sh) &&

# Remove old files stored in the file list
cat $list | (cd / && xargs -r git rm) &&

(cd $dir && $install) &&

/share/msysGit/post-install.sh $index "Install $package $version" &&

git diff --diff-filter=AM --name-only HEAD^! |
sed -e "s/^/\//" > $list &&
git commit -C HEAD --amend $list ||
exit

echo "Successfully built and installed $package $version"
echo "After checking the result, please commit (possibly with --amend)"
echo

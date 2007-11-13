#!/bin/sh

# This is a package updating script for msysGit


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

# Make sure that the working directory is clean and does not have untracked
# files; otherwise our semi-automatic finding the new files will not work!

(cd / &&
	git diff-files --quiet &&
	git diff-index --cached --quiet HEAD &&
	test -z "$(git ls-files --exclude-from=.gitignore \
		--exclude-per-directory=.gitignore --others)") || {
	echo "State not pristine enough for successful TkImg update"
	exit 1
}

cd "$(dirname "$0")"

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

$fetch || exit

$unpack || exit

(cd $dir &&

 $patch &&

 $compile &&

# Remove old files stored in the file list

 (cd .. && cat $list | (cd / && xargs git rm)) &&

# Install

 $install
) || exit

# Update the index

(cd / && git add .) || exit

git diff-index --cached --diff-filter=AM --name-only HEAD |
	sed -e "s/^/\//" > $list ||
	exit

git add $list || exit

echo "Successfully built and installed $package $version"
echo "After checking the result, please commit (possibly with --amend)"
echo

#!/bin/sh

cd "$(dirname "$0")"

REPO=http://ccache-win32.googlecode.com/svn/trunk/ccache-win32
DIR=ccache-svn
REV=2

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR ||
git svn clone $REPO -r$REV $DIR ||
die "Could not clone $REPO"

test $(cd $DIR && git rev-list HEAD | wc -l) -gt 1 ||
(cd $DIR && git am ../patches/*) ||
die "Could not apply patches"

(cd $DIR &&
make &&
index=$(/share/msysGit/pre-install.sh) &&
cp ccache.exe /bin/ &&
/share/msysGit/post-install.sh $index "Install ccache-win32 (SVN revision $REV)"
) || die "Could not install ccache"

#!/bin/sh

cd "$(dirname "$0")"

REPO=git://repo.or.cz/antiword.git
DIR=antiword-git
HEAD=0680e7ee62e430e0905085e5b4cfb01d31db5936   # antiword 0.37

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR ||
( git clone -n $REPO $DIR && cd $DIR && git checkout $HEAD ) ||
die "Could not clone $REPO"

(cd $DIR && git am ../patches/*) ||
die "Could not apply patches"

(cd $DIR &&
make -f Makefile.Linux antiword.exe &&
index=$(/share/msysGit/pre-install.sh) &&
make -f Makefile.Linux global_install &&
/share/msysGit/post-install.sh $index "Install antiword (Git $HEAD)"
) || die "Could not install antiword"

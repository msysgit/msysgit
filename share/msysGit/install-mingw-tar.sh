#!/bin/sh

die () {
	echo "$*" >&2
	exit 1
}

test $# -ne 1 && die "Usage: $0 <TARFILE>"

cd /mingw || echo "/mingw does not exist?"

index=$(/share/msysGit/pre-install.sh) || die "Pre-install stage failed"

uncompress=
case "$1" in
*.lzma)
	(cd /tmp && /share/7-Zip/7za x "$1")
	set /tmp/"$(basename "$1" .lzma)"
	;;
*.bz2)
	uncompress=j
	;;
*.gz|*.tgz)
	uncompress=z
	;;
esac

tar x${uncompress}mf "$1" || die "Could not untar $1"

/share/msysGit/post-install.sh $index Install "$(basename "$1")" ||
die "Post-install stage failed"

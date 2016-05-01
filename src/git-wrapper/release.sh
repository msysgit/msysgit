#!/bin/sh

cd "$(dirname "$0")"

DEST=/cmd/git.exe

die () {
	echo "$*" >&2
	exit 1
}

rmscript () {
	test -f /cmd/git.cmd && rm /cmd/git.cmd || true
}

make &&
index=$(/share/msysGit/pre-install.sh) &&
rmscript &&
install -m 775 git-wrapper.exe $DEST &&
/share/msysGit/post-install.sh $index "Updated git wrapper exe" ||
die "Failed to update git wrapper executable"

#!/bin/sh

# This script tries to find out what made your repository so large.
# It sorts the loose and packed objects by size (for packed objects, we look
# at the size in the pack) and shows the largest ten.

die () {
	echo "$*" >&2
	exit 1
}

identify_object () {
	LINES="$(git log --root --raw --abbrev=40 --all --format="commit %H" |
		grep -e '^commit' -e "^:[^ ]* [^ ]* [^ ]* $1" |
		grep -m1 -B1 "^:[^ ]* [^ ]* [^ ]* $1")"
	if test -n "$LINES"
	then
		COMMIT="$(git name-rev $(echo "$LINES" |
				sed -n 's/commit //p') |
			sed 's/^[^ ]* //')"
		PATH="$(echo "$LINES" | sed -n 's/^.*	//p')"
		printf "'%s:%s'" $COMMIT "$PATH"
	fi
}

N=10
test $# -gt 0 && N=$1

GIT_DIR="$(git rev-parse --git-dir)" || die "No repository found"
OBJECT_LIST="$( (cd "$GIT_DIR" &&
	ls -l objects/??/* |
	sed 's/^\([^ ]* *\)\{4\}\([^ ]*\).* objects\/\(..\)\/\(.\{38\}\)$/\2 \3\4/' &&
	for pack in "$(ls objects/pack/*.pack 2> /dev/null)"
	do
		git verify-pack -v "$pack" 2>&1 |
		sed -n 's/^\([^ ]\{40\}\) *[^ ]* *[^ ]* *\([1-9][0-9]*\).*$/\2 \1/p'
	done) |
	sort -n -r |
	uniq |
	head -n "$N")"

echo "$OBJECT_LIST" |
while read size sha1
do
	echo $size $sha1 "$(identify_object $sha1)"
done

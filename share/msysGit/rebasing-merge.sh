#!/bin/sh

TO=junio/next

# Act as editor, to filter out commits with Junio as committer; This should
# work around the problems of junio/next rebasing every once in a while.

test $# -gt 0 && {
	case "$1" in
	*/git-rebase-todo)
		mv "$1" "$1".bup &&
		while read command sha1 oneline
		do
			case "$command" in
			\#*|'')
				echo "$command $sha1 $oneline"
				continue
				;;
			esac
			committer="$(git show -s --format=%cn $sha1)" &&
			case "$committer" in
			"Junio C Hamano"|"Junio Hamano"|"Shawn O. Pearce"|"Eric Wong"|"Thomas Rast"|"Jeff King"|"Paul Mackerras") ;; # skip
			*)	echo "$command $sha1 (committer: $committer) $oneline"
			esac || break
		done > "$1" < "$1".bup
		;;
	esac &&
	unset GIT_EDITOR &&
	"$(git var GIT_EDITOR)" "$@"
	exit
}

# Rebase 'devel' on top of 'junio/next', the merging the old state of
# 'devel' with the merge strategy 'ours' to enable a fast-forward.

this="$(cd "$(dirname "$0")" && pwd)/$(basename "$0")" &&
cd /git &&
case "$(git rev-parse --symbolic-full-name HEAD)" in
refs/heads/devel)
	test "$(git rev-parse HEAD)" = "$(git rev-parse origin/devel)" ||
	test "$(git rev-parse devel@{1})" = "$(git rev-parse origin/devel)" || {
		echo "Your 'devel' is not up-to-date!" >&2
		exit 1
	}
	;; # okay
HEAD) ;; # okay
*)
	echo "Not on 'devel'!" >&2
	exit 1
	;;
esac &&
git fetch junio &&
JUNIOS_HEAD=$(git rev-parse $TO) &&
if test $JUNIOS_HEAD != $(git merge-base HEAD $JUNIOS_HEAD)
then
	rebasing_merge="$(git rev-list --parents $TO..HEAD |
	while read commit parent1 parent2
	do
		test -n "$parent2" &&
		commit_tree="$(git rev-parse $commit:)" &&
		parent1_tree="$(git rev-parse $parent1:)" &&
		test "$commit_tree" = "$parent1_tree" ||
		continue
		echo "$commit"
		break
	done)" &&
	if test -z "$rebasing_merge"
	then
		GIT_EDITOR="$this" git rebase -i $TO
	else
		GIT_EDITOR="$this" \
		git rebase -i --onto $TO $rebasing_merge
	fi
fi &&
git merge -s ours -m "Rebasing merge to $TO" origin/devel

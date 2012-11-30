#!/bin/sh
#
# Rebase 'master' on top of an upstream branch (defaults to 'junio/next').
# This merges the old state of 'master' using the merge strategy 'ours'
# to enable a fast-forward.
#
# options:
#  --dry-run
#     do not perform the rebase but only display the revisions selected
#
#  --graph
#     as for dry-run but display the commits as a graph
#
#  --cherry
#     as for --dry-run but display the commits using cherry notation to mark
#     commits that are suitable for upstream consideration.

force=
dryrun=
graph=
cherry=
while test $# -gt 0
do
	case "$1" in
	-f|--force)
		force=t
		;;
	-s|--show|-d|--dry-run)
		dryrun=t
		;;
	-g|--graph)
		dryrun=t
		graph=--graph
		;;
	-c|--cherry)
		dryrun=t
		cherry=--cherry
		;;
	-*)
		echo "Unknown option: $1" >&2
		exit 1
		;;
	*)
		break
		;;
	esac
	shift
done

TO=${1:-junio/next}

if test -z "$force" && test -z "$(git rev-list .."$TO")"
then
	echo "Nothing new in $TO; To force a rebase, use the --force, Luke!" >&2
	exit 1
fi

TODO_EXTRA="$(git rev-parse --git-dir)/todo-extra"

case "$(git rev-parse --symbolic-full-name HEAD)" in
refs/heads/master)
	UPSTREAM=$(git rev-parse --symbolic-full-name HEAD@{u}) || {
		echo "Not tracking any remote branch!" >&2
		exit 1
	}
	test "$(git rev-parse HEAD)" = "$(git rev-parse $UPSTREAM)" ||
	test "$(git rev-parse master@{1})" = "$(git rev-parse $UPSTREAM)" || {
		echo "Your 'master' is not up-to-date!" >&2
		exit 1
	}
	;; # okay
HEAD) ;; # okay
*)
	echo "Not on 'master'!" >&2
	exit 1
	;;
esac

is_ours_merge () {
	test "$(git rev-parse $1:)" = "$(git rev-parse "$1^:")"
}

list_merges () {
	git rev-list --parents "$@" | sed -n 's/ .* .*//p'
}

# Find old rebasing merge, if any

PREVIOUS_REBASING=
for commit in $(list_merges $TO..)
do
	if is_ours_merge $commit
	then
		PREVIOUS_REBASING=$commit
		break
	fi
done

TO_SHA1=$(git rev-parse --short $TO)
MESSAGE="Rebasing merge to $TO ($TO_SHA1)"
RANGE=$TO.. &&
if test -n "$PREVIOUS_REBASING"
then
	MESSAGE="$(printf "%s\n\n%s" "$MESSAGE" \
		"Previous rebasing merge: $PREVIOUS_REBASING")"
	RANGE="$RANGE ^$PREVIOUS_REBASING^2"
	for commit in $(list_merges $RANGE)
	do
		test $commit != $PREVIOUS_REBASING &&
		is_ours_merge $commit &&
		RANGE="$RANGE ^$commit"
	done
fi

if test -n "$dryrun"
then
	git log --oneline $graph $cherry --boundary $RANGE
	exit
fi

ORIG_HEAD=$(git rev-parse HEAD)
# Get commits to rebase
git rev-list --format='pick %h %s (%an)' --reverse --no-merges $RANGE |
grep -v '^commit ' > "$TODO_EXTRA" &&
TMP_EDITOR="$(git rev-parse --git-dir)/rebasing-editor.sh" &&
cat > "$TMP_EDITOR" << EOF &&
#!/bin/sh
case "\$1" in
*/git-rebase-todo)
	sed -e '/^[^#]/d' < "\$1" >> "$TODO_EXTRA" &&
	mv "$TODO_EXTRA" "\$1"
esac &&
exec "$(git var GIT_EDITOR)" "\$@"
EOF
chmod a+x "$TMP_EDITOR" &&
if GIT_EDITOR="$TMP_EDITOR" git rebase --autosquash -i --onto $TO HEAD^
then
	git merge -s ours -m "$MESSAGE" $ORIG_HEAD
else
	FINISH="$(git rev-parse --git-dir)/finish-rebasing-merge.sh"
	cat > "$FINISH" << EOF
#!/bin/sh
git merge -s ours -m '$MESSAGE' $ORIG_HEAD
EOF
	chmod a+x "$FINISH"
	cat << EOF

After the rebase, call '$FINISH' manually
EOF
fi

#!/bin/sh
#
# Rebase 'master' on top of an upstream branch (defaults to 'junio/next'),
# retaining "fast-forwardability" by "merging" (with the "ours" strategy) the
# previous state on top of the current upstream state.
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
	-h|--help)
		cat >&2 << EOF
Usage: $0 [options] [<upstream>]

Options:
-s|--show	show which commits would be cherry-picked
-g|--graph	like --show, but with the commit graph
-c|--cherry	try to leave out commits that were applied upstream
EOF
		exit 1
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

HEAD_NAME="$(git rev-parse --symbolic-full-name HEAD)"
case "$HEAD_NAME" in
refs/heads/*)
	UPSTREAM=$(git rev-parse --symbolic-full-name HEAD@{u}) || {
		echo "Not tracking any remote branch!" >&2
		exit 1
	}
	test "$(git rev-parse HEAD)" = "$(git rev-parse $UPSTREAM)" ||
	test "$(git rev-parse $HEAD_NAME@{1})" = "$(git rev-parse $UPSTREAM)" || {
		echo "Your '$HEAD_NAME' is not up-to-date!" >&2
		exit 1
	}
	;; # okay
HEAD) ;; # okay
*)
	echo "Not on any branch!" >&2
	exit 1
	;;
esac
FROM_SHA1=$(git rev-parse --short HEAD)
TO_SHA1=$(git rev-parse --short $TO)

is_ours_merge () {
	test "$(git rev-parse $1:)" = "$(git rev-parse "$1^:")"
}

list_merges () {
	git rev-list --parents "$@" | sed -n 's/ .* .*//p'
}

# Find old merging rebase, if any

REBASING_BASE=
for commit in $(list_merges $TO..)
do
	if is_ours_merge $commit
	then
		REBASING_BASE=$commit
		break
	fi
done

BASE_MESSAGE=
if test -n "$REBASING_BASE"
then
	BASE_MESSAGE="using $REBASING_BASE as base."
	MESSAGE="$(git cat-file commit $REBASING_BASE |
		sed '1,/^$/d')"
	# old style rebasing merge?
	case "$MESSAGE" in
	"Rebasing merge to "*)
		BASE_MESSAGE="using the rebasing merge $REBASING_BASE."
		# Fake a commit such that 'git log <commit>..' shows all the
		# commits we want to rebase
		PREVIOUS_REBASING="$(git rev-parse $REBASING_BASE^2)"
		PREVIOUS_ONTO="$(echo "$MESSAGE" |
			sed -n '1s/Rebasing merge .*(\(.*\))/\1/p')"
		# To avoid checking out unneeded files/file versions, the
		# throw-away base points to the tree we want to rebase onto
		REBASING_BASE="$(echo Dummy |
			git commit-tree $TO_SHA1: \
				-p $PREVIOUS_ONTO -p $PREVIOUS_REBASING)"
		;;
	esac
fi

RANGE=$REBASING_BASE..
if test -n "$dryrun"
then
	git log --oneline $graph $cherry --boundary $RANGE
	exit
fi

# Fake our own editor to inject initial steps into the edit script
TODO_EXTRA="$(git rev-parse --git-dir)/.todo-extra"
printf "%s\n\n%s\n%s" "Start the merging-rebase to $TO" \
	"This commit starts the rebase of $FROM_SHA1 to $TO_SHA1" \
	"$BASE_MESSAGE" > "$TODO_EXTRA.msg"
cat > "$TODO_EXTRA" << EOF
# Start the merging rebase:
# Reset to $TO and ...
exec git reset --hard $TO
# ... fake-merge current $HEAD_NAME
exec git merge -s ours -m "\$(cat "$TODO_EXTRA.msg")" $FROM_SHA1

# Patches to rebase:
EOF
TMP_EDITOR="$(git rev-parse --git-dir)/.rebasing-editor.sh" &&
cat > "$TMP_EDITOR" << EOF &&
#!/bin/sh
case "\$1" in
*/git-rebase-todo)
	# prepend the initialising commands
	cat "\$1" >> "$TODO_EXTRA" &&
	mv "$TODO_EXTRA" "\$1"
esac &&
exec "$(git var GIT_EDITOR)" "\$@"
EOF
chmod a+x "$TMP_EDITOR"

# Rebase!
GIT_EDITOR="$TMP_EDITOR" git rebase --autosquash -i ${REBASING_BASE:-$TO}

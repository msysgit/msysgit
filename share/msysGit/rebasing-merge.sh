#!/bin/sh

TO=${1:-junio/next}

TODO_EXTRA="$(git rev-parse --git-dir)/todo-extra"

# Rebase 'devel' on top of 'junio/next', the merging the old state of
# 'devel' with the merge strategy 'ours' to enable a fast-forward.

case "$(git rev-parse --symbolic-full-name HEAD)" in
refs/heads/devel)
	UPSTREAM=$(git rev-parse --symbolic-full-name HEAD@{u}) || {
		echo "Not tracking any remote branch!" >&2
		exit 1
	}
	test "$(git rev-parse HEAD)" = "$(git rev-parse $UPSTREAM)" ||
	test "$(git rev-parse devel@{1})" = "$(git rev-parse $UPSTREAM)" || {
		echo "Your 'devel' is not up-to-date!" >&2
		exit 1
	}
	;; # okay
HEAD) ;; # okay
*)
	echo "Not on 'devel'!" >&2
	exit 1
	;;
esac

# Find old rebasing merge, if any

rm -f "$TODO_EXTRA"

MERGE=$(git rev-list --parents $TO.. | sed -n 's/ .* .*//p' | head -n 1)
if test "$(git rev-parse $MERGE:)" = "$(git rev-parse "$MERGE^:")"
then
	ORIG_HEAD=$(git rev-parse HEAD) &&
	# Find prior merges to $TO
	EXCLUDE=$(git rev-list --parents $TO..$MERGE^ |
		sed -n 's/^\([^ ]*\) .* .*/^\1/p') &&
	# Get commits from previous rebasing merge
	git rev-list --pretty=oneline --abbrev-commit --abbrev=7 --reverse \
		--no-merges $TO..$MERGE^ $EXCLUDE |
	sed 's/^/pick /' > "$TODO_EXTRA" &&
	TMP_EDITOR="$(git rev-parse --git-dir)/rebasing-editor.sh" &&
	cat > "$TMP_EDITOR" << EOF &&
#!/bin/sh
case "\$1" in
*/git-rebase-todo)
	cat "\$1" >> "$TODO_EXTRA" &&
	mv "$TODO_EXTRA" "\$1"
esac &&
exec "$(git var GIT_EDITOR)" "\$@"
EOF
	TO_SHA1=$(git rev-parse --short $TO) &&
	chmod a+x "$TMP_EDITOR" &&
	if GIT_EDITOR="$TMP_EDITOR" git rebase -i $MERGE --onto $TO
	then
		git merge -s ours -m "Rebasing merge to $TO ($TO_SHA1)" \
			$ORIG_HEAD
	else
		cat << EOF

After the rebase, call 'git merge -s ours $ORIG_HEAD' manually
EOF
	fi

else
	git rebase -i $TO
fi

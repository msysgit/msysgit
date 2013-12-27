#!/bin/sh
#
# Rebase the thicket of branches -- including their merge structure -- on top
# of the specified upstream branch (defaults to 'junio/next'), optionally
# retaining "fast-forwardability" by fake-merging (using the "ours" strategy)
# the previous state on top of the current upstream state ("merging rebase").
#
# options:
#  --merging
#     start the rebased branch by a fake merge of the previous state
#
# The idea is to generate our very own rebase script, then call rebase -i with
# our fake editor to put the rebase script into place and then let the user edit
# the script.
#
# To make things prettier, we rewrite the rebase script after letting the user
# edit it, to replace "new" rebase commands with calls to a temporary alias ".r"
# that is added to help with starting the merging rebase, merging things, and
# cleaning up afterwards.

die () {
	echo "$*" >&2
	exit 1
}

git_dir="$(git rev-parse --git-dir)" ||
die "Not in a Git directory"

help () {
	cat >&2 << EOF
Usage: $0 [options] <upstream>

Options:
-m|--merging[=<msg>]	allow fast-forwarding the current to the rebased branch
--onto=<commit>		rebase onto the given commit
--recreate=<merge>	recreate the branch merged in the specified commit
EOF
	exit 1
}

# Extra commands for use in the rebase script
extra_commands="edit bud finish mark rewind merge start_merging_rebase cleanup"

edit () {
	GIT_EDITOR="$1" &&
	GIT_SEQUENCE_EDITOR="$GIT_EDITOR" &&
	export GIT_EDITOR GIT_SEQUENCE_EDITOR &&
	shift &&
	case "$*" in
	*/git-rebase-todo)
		sed -e '/^noop/d' < "$1" >> "$git_dir"/SHEARS-SCRIPT &&
		mv "$git_dir"/SHEARS-SCRIPT "$1"
		"$GIT_EDITOR" "$@" &&
		mv "$1" "$git_dir"/SHEARS-SCRIPT &&
		exprs="$(for command in $extra_commands
			do
				printf " -e 's/^$command\$/exec git .r &/'"
				printf " -e 's/^$command /exec git .r &/'"
			done)" &&
		eval sed $exprs < "$git_dir"/SHEARS-SCRIPT > "$1"
		;;
	*)
		exec "$GIT_EDITOR" "$@"
	esac
}

mark () {
	git update-ref -m "Marking '$1' as rewritten" refs/rewritten/"$1" HEAD
}

rewind () {
	git reset --hard refs/rewritten/"$1"
}

bud () {
	shorthead="$(git rev-parse --short --verify HEAD)" &&
	git for-each-ref refs/rewritten/ |
	grep "^$shorthead" ||
	die "Refusing to leave unmarked revision $shorthead behind"
	git reset --hard refs/rewritten/onto
}

finish () {
	mark "$@" &&
	bud
}

merge () {
	# parse command-line arguments
	parents=
	while test $# -gt 0 && test "a$1" != a-C
	do
		parents="$parents $1" &&
		shift
	done &&
	if test "a$1" = "a-C"
	then
		shift &&
		orig="$1" &&
		shift &&
		# determine whether the merge needs to be redone
		p="$(git rev-parse HEAD)$parents" &&
		o="$(git rev-list -1 --parents $orig |
			sed "s/[^ ]*//")" &&
		while p=${p# }; o=${o# }; test -n "$p$o"
		do
			p1=${p%% *}; o1=${o%% *};
			test $o1 = "$(git rev-parse "$p1")" || break
			p=${p#$p1}; o=${o#$o1}
		done &&
		# either redo merge or fast-forward
		if test -z "$p$o"
		then
			git reset --hard $orig
			return
		fi &&
		msg="$(git cat-file commit $orig |
			sed "1,/^$/d")"
	else
		msg=
		p=
		for parent in $parents
		do
			test -z "$msg" ||
			msg="$msg and "
			msg="$msg'$parent'"
			p="$p $(git rev-parse --verify refs/rewritten/$parent \
					2> /dev/null ||
				echo $parent)"
		done &&
		msg="Merge $msg into HEAD"
	fi &&
	git merge -n --no-ff -m "$msg" $p
}

start_merging_rebase () {
	git merge -s ours -m "$(cat "$git_dir"/SHEARS-MERGING-MESSAGE)" "$1"
}

cleanup () {
	rm -f "$git_dir"/SHEARS-SCRIPT &&
	for rewritten
	do
		git update-ref -d refs/rewritten/$rewritten
	done &&
	for rewritten in $(git for-each-ref refs/rewritten/ |
		sed 's/^[^ ]* commit.refs\/rewritten\///')
	do
		test onto = "$rewritten" ||
		merge $rewritten
		git update-ref -d refs/rewritten/$rewritten
	done &&
	git config --unset alias..r
}

merging=
base_message=
onto=
recreate=
force=
while test $# -gt 0
do
	case "$1" in
	-m|--merging)
		merging=t
		base_message=
		;;
	--merging=*)
		merging=t
		base_message="${1#--merging=}"
		;;
	--onto)
		shift
		onto="$1"
		;;
	--onto=*)
		onto="${1#--onto=}"
		;;
	--recreate)
		shift
		recreate="$recreate $1"
		;;
	--recreate=*)
		recreate="$recreate ${1#--recreate=}"
		;;
	--force|-f)
		force=t
		;;
	-h|--help)
		help
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

case " $extra_commands " in
*" $1 "*)
	command="$1"
	shift
	"$command" "$@"
	exit
	;;
esac

string2regex () {
	echo "$*" |
	sed 's/[][\\\/*?]/\\&/g'
}

merge2branch_name () {
	git show -s --format=%s "$1" |
		sed -n -e "s/^Merge [^']*'\([^']*\).*/\1/p" \
		-e "s/^Merge pull request #[0-9]* from //p" |
	tr ' 	' '-'
}

commit_name_map=
name_commit () {
	name="$(echo "$commit_name_map" |
	sed -n "s/^$1 //p")"
	echo "${name:-$1}"
}

ensure_labeled () {
	for n in "$@"
	do
		case " $needslabel " in
		*" $n "*)
			;;
		*)
			needslabel="$needslabel $n"
			;;
		esac
	done
}

generate_script () {
	echo "Generating script..." >&2
	origtodo="$(git rev-list --no-merges --cherry-pick --pretty=oneline \
		--abbrev-commit --abbrev=7 --reverse --left-right --topo-order \
		$upstream..$head | \
		sed -n "s/^>/pick /p")"
	shorthead=$(git rev-parse --short $head)
	shortonto=$(git rev-parse --short $onto)

	# --topo-order has the bad habit of breaking first-parent chains over
	# merges, so we generate the topoligical order ourselves here

	list="$(git log --format='%h %p' --topo-order --reverse \
		$upstream..$head)"

	todo=
	if test -n "$merging"
	then
		from=$(git rev-parse --short "$upstream") &&
		to=$(git rev-parse --short "$onto") &&
		cat > "$git_dir"/SHEARS-MERGING-MESSAGE << EOF &&
Start the merging-rebase to $onto

This commit starts the rebase of $from to $to
$base_message
EOF
		todo="start_merging_rebase \"$shorthead\""
	fi
	todo="$(printf '%s\n%s\n' "$todo" \
		"mark onto")"

	toberebased=" $(echo "$list" | cut -f 1 -d ' ' | tr '\n' ' ')"
	handled=
	needslabel=

	# each tip is an end point of a commit->first parent chain
	branch_tips="$(echo "$list" |
		cut -f 3- -d ' ' |
		tr ' ' '\n' |
		grep -v '^$')"

	ensure_labeled $branch_tips

	branch_tips="$(printf '%s\n%s' "$branch_tips" "$shorthead")"

	# set up the map tip -> branch name
	for tip in $branch_tips
	do
		merged_by="$(echo "$list" |
			sed -n "s/^\([^ ]*\) [^ ]* $tip$/\1/p" |
			head -n 1)"
		if test -n "$merged_by"
		then
			branch_name="$(merge2branch_name "$merged_by")"
			test -z "$branch_name" ||
			commit_name_map="$(printf '%s\n%s' \
				"$tip $branch_name" "$commit_name_map")"
		fi
	done
	branch_name_dupes="$(echo "$commit_name_map" |
		sed 's/[^ ]* //' |
		sort |
		uniq -d)"
	if test -n "$branch_name_dupes"
	then
		exprs="$(echo "$branch_name_dupes" |
			while read branch_name
			do
				printf " -e '%s'" \
					"$(string2regex "$branch_name")"
			done)"
		commit_name_map="$(echo "$commit_name_map" |
			eval grep -v $exprs)"
	fi

	tip_total=$(printf '%s' "$branch_tips" | wc -l)
	tip_counter=0
	for tip in $branch_tips
	do
		printf '%d/%d...\r' $tip_counter $tip_total >&2
		tip_counter=$(($tip_counter+1))
		# if this is not a commit to be rebased, skip
		case "$toberebased" in *" $tip "*) ;; *) continue;; esac

		# if it is handled already, skip
		case "$handled " in *" $tip "*) continue;; esac

		# start sub-todo for this tip
		subtodo=
		commit=$tip
		while true
		do
			printf '\tcommit %s...\r' "$commit" >&2
			# if already handled, this is our branch point
			case "$handled " in
			*" $commit "*)
				ensure_labeled $commit
				subtodo="$(printf '\nrewind %s # %s\n%s' \
					"$(name_commit $commit)" \
					"$(git show -s --format=%s $commit)" \
					"$subtodo")"
				break
				;;
			esac

			line="$(echo "$list" | grep "^$commit ")"
			# if there is no line, branch from the 'onto' commit
			if test -z "$line"
			then
				subtodo="$(printf '\nbud\n%s' \
					"$subtodo")"
				break
			fi
			parents=${line#* }
			case "$parents" in
			*' '*)
				# merge
				parents2="`for parent in ${parents#* }
					do
						case "$toberebased" in
						*" $parent "*)
							printf refs/rewritten/
							;;
						esac
						echo "$(name_commit $parent) "
					done`"
				subtodo="$(printf '%s # %s\n%s' \
					"merge $parents2-C $commit" \
					"$(git show -s --format=%s $commit)" \
					"$subtodo")"
				;;
			*)
				# non-merge commit
				line="$(echo "$origtodo" |
					grep "^pick $commit")"
				if test -z "$line"
				then
					line="# skip $commit"
				fi
				subtodo="$(printf '%s\n%s' "$line" "$subtodo")"
				;;
			esac
			handled="$handled $commit"
			commit=${parents%% *}
		done

		branch_name="$(name_commit "$tip")"
		test -n "$branch_name" &&
		test "$branch_name" = "$tip" ||
		subtodo="$(echo "$subtodo" |
			sed -e "1a\\
# Branch: $branch_name")"

		todo="$(printf '%s\n\n%s' "$todo" "$subtodo")"
	done

	for commit in $needslabel
	do
		linenumber="$(echo "$todo" |
			grep -n -e "^\(pick\|# skip\) $commit" \
				-e "^merge [0-9a-f/ ]* -C $commit")"
		linenumber=${linenumber%%:*}
		test -n "$linenumber" ||
		die "Internal error: could not find $commit in $todo"
		todo="$(echo "$todo" |
			sed "${linenumber}a\\
mark $(name_commit $commit)\\
")"
	done

	lastline=9999
	while true
	do
		fixup="$(echo "$todo" |
			sed "$lastline,\$d" |
			grep -n -e '^pick [^ ]* \(fixup\|squash\)!' |
			tail -n 1)"
		test -n "$fixup" || break
		printf '%s...\r' "$fixup" >&2

		linenumber=${fixup%%:*}
		oneline="${fixup#* }"
		shortsha1="${oneline%% *}"
		oneline="${oneline#* }"
		command=${oneline%%!*}
		oneline="${oneline#*! }"
		oneline_regex="^pick [^ ]* $(string2regex "$oneline")\$"
		targetline="$(echo "$todo" |
			sed "$linenumber,\$d" |
			grep -n "$oneline_regex" |
			tail -n 1)"
		targetline=${targetline%%:*}
		if test -n "$targetline"
		then
			todo="$(echo "$todo" |
				sed -e "${linenumber}d" \
					-e "${targetline}a\\
$command $shortsha1 $oneline")"
			lastline=$(($linenumber+1))
		else
			echo "UNHANDLED: $oneline" >&2
			lastline=$(($linenumber))
		fi
	done

	while test -n "$recreate"
	do
		recreate="${recreate# }"
		merge="${recreate%% *}"
		recreate="${recreate#$merge}"
		printf 'Recreating %s...\r' "$merge" >&2

		mark="$(git rev-parse --short --verify "$merge^2")" ||
		die "Could not find merge commit: $merge^2"

		branch_name="$(merge2branch_name "$merge")"
		partfile="$git_dir/SHEARS-PART"
		printf '%s' "$(test -z "$branch_name" ||
			   echo "# Branch to recreate: $branch_name")" \
			> "$partfile"
		for sha1 in $(git rev-list --reverse $merge^..$merge^2)
		do
			msg="$(git show -s --format=%s $sha1)"
			msg_regex="^pick [^ ]* $(string2regex "$msg")\$"
			linenumber="$(echo "$todo" |
				grep -n "$msg_regex" |
				sed 's/:.*//')"
			test -n "$linenumber" ||
			die "Not a commit to rebase: $msg"
			test 1 = $(echo "$linenumber" | wc -l) ||
			die "More than one match for: $msg"
			echo "$todo" |
			sed -n "${linenumber}p" >> "$partfile"
			todo="$(echo "$todo" |
				sed "${linenumber}d")"
		done

		linenumber="$(echo "$todo" |
			grep -n "^bud\$" |
			tail -n 1 |
			sed 's/:.*//')"

		printf 'mark %s\n\nbud\n' \
			"$(name_commit $mark)" >> "$partfile"
		todo="$(echo "$todo" |
			sed -e "${linenumber}r$partfile" \
				-e "\$a\\
merge refs/rewritten/$mark -C $(name_commit $merge)")"
	done

	needslabel="$(for commit in $needslabel
		do
			printf ' %s' $(name_commit $commit)
		done)"
	todo="$(printf '%s\n\n%s' "$todo" "cleanup $needslabel")"
	echo "$todo" | uniq
}

this="$(cd "$(dirname "$0")" && pwd)/$(basename "$0")"
setup () {
	existing=$(git for-each-ref --format='%(refname)' refs/rewritten/)
	test -z "$existing" ||
	if test -n "$force"
	then
		for ref in $existing
		do
			git update-ref -d $ref
		done
	else
		die "$(printf '%s %s:\n%s\n' \
			'There are still rewritten revisions' \
			'(use --force to delete)' \
			"$existing")"
	fi

	alias="$(git config --get alias..r)"
	test -z "$alias" ||
	test "a$alias" = "a!sh \"$this\"" ||
	test -n "$force" ||
	die "There is already an '.r' alias!"

	git config alias..r "!sh \"$this\"" &&
	generate_script > "$git_dir"/SHEARS-SCRIPT &&
	GIT_EDITOR="$(cd "$git_dir" && pwd)/SHEARS-EDITOR" &&
	cat > "$GIT_EDITOR" << EOF &&
#!/bin/sh

exec "$this" edit "$(git var GIT_EDITOR)" "\$@"
EOF
	chmod +x "$GIT_EDITOR" &&
	GIT_EDITOR="\"$GIT_EDITOR\"" &&
	GIT_SEQUENCE_EDITOR="$GIT_EDITOR" &&
	export GIT_EDITOR GIT_SEQUENCE_EDITOR
}

test ! -d "$git_dir"/rebase-merge &&
test ! -d "$git_dir"/rebase-apply ||
die "Rebase already in progress"

test $# = 1 ||
help

head="$(git rev-parse HEAD)" &&
upstream="$1" &&
onto=${onto:-$upstream}||
die "Could not determine rebase parameters"

git update-index -q --ignore-submodules --refresh &&
git diff-files --quiet --ignore-submodules &&
git diff-index --cached --quiet --ignore-submodules HEAD -- ||
die 'There are uncommitted changes!'

setup

# Rebase!
git rebase -i --onto "$onto" HEAD


#!/bin/sh
# reencode file names in git tree objects from Windows system encoding to UTF-8

usage()
{
	echo "WARNING this script is not intended as a full-fledged and fool-proof
migration utility, but rather as a proof of concept or collection of examples.
Use at your own risk.

In particular, the script doesn't check or fix any non-ascii names in config
files (such as .git/config, .gitignore or .gitmodules). For specific migration
tasks, some of the commands in this script may require tweaking.

Usage: recodetree <command>
recodetree check    Checks git repository for non-ascii file names.
recodetree preview  Same as 'check', but prints file names as if converted
                    from cp$(getcp) to UTF-8.
recodetree head     Converts the current HEAD from cp$(getcp) to UTF-8.
                    Does not commit, use git status to check results first.
recodetree history  Converts entire repository history from cp$(getcp) to UTF-8.
                    WARNING: this rewrites the history of the repository.
                    - Make a BACKUP copy of the repository before using this!
                    - Read 'git help filter-branch' for implications of
                      rewriting history."
}

check()
{
	# use fast-export to dump all file names in the history
	git fast-export --no-data --signed-tags=strip --tag-of-filtered-object=drop --all |
	# use awk to filter for non-ascii names
	awk --posix '/^M [0-9]{6} [0-9a-f]{40} .*[\200-\377]/{print substr($0,51);}'
}

recode()
{
	# convert from system encoding to UTF-8
	iconv -c -f cp$(getcp) -t utf-8
}

recode_tree()
{
	# clear the index
	git rm -f -r -q --cached --ignore-unmatch \*
	# list specified commit, reencode and add to index
	git ls-tree -z -r $1 | recode | git update-index -z --index-info
}

case $1 in
	check)
		check
		;;

	preview)
		check | recode
		;;

	head)
		recode_tree HEAD
		;;

	history)
		git filter-branch --index-filter 'recodetree filter' -- --all
		;;

	filter)
		# used internally by recodetree history
		recode_tree $GIT_COMMIT
		;;

	*)
		usage
		;;
esac

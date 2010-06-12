#!/bin/sh

# This script will check for files that were literal copies in the
# parents of the given commits, but are no literal copies currently
# (ignoring those files that do no longer exist).

# Use it like this:
#
#	$0 $(git rev-list HEAD -- mingw/bin/gcc.exe)
#
# This would check that literal copies were maintained in all the commits
# in the current branch that touched mingw/bin/gcc.exe.

for rev in "$@"
do
	# Ignore initial commit
	git rev-parse -q --verify $rev^ > /dev/null || continue

	for f in $(git diff --name-only --diff-filter=RDM $rev^!)
	do
		test -f $f || continue
		sha1=$(git rev-parse $rev^:$f)
		matches="$(git ls-tree -r $rev^ | grep $sha1)"
		test 1 -lt $(echo "$matches" | wc -l) && {
			for f2 in $(echo "$matches" | sed "s/.*	//")
			do
				test -f $f2 || continue
				cmp $f $f2 || echo "$f != $f2"
			done
		}
	done
done

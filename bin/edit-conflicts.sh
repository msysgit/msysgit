#!/bin/sh
#
# Copyright (c) 2007 Johannes E. Schindelin
#
# Cleanup unreachable files and optimize the repository.

USAGE='my-edit-conflicts'
SUBDIRECTORY_OK=Yes
. "$(git --exec-path)"/git-sh-setup
cd_to_toplevel

test -z "$(git ls-files --unmerged)" && echo "Nothing to do" && exit

git ls-files --unmerged | cut -b51- | grep ' ' >/dev/null &&
die "filenames contain spaces"

opt=
test vi = "${VISUAL:-${EDITOR:-vi}}" && opt="+/<<<<<<<"
"${VISUAL:-${EDITOR:-vi}}" $opt $(git ls-files --unmerged | cut -b51- | uniq)
git add $(git ls-files --unmerged | cut -b51- | uniq)

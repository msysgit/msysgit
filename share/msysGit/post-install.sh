#!/bin/sh

test $# -lt 2 && {
	echo "Usage: $0 <GIT_INDEX_FILE> <MESSAGE...>"
	exit 1
}

# bashism
set -o pipefail

cd / &&
(export GIT_INDEX_FILE=$1 &&
 git diff-files --name-only --ignore-submodules -z &&
 git ls-files --exclude-standard --others -z) |
git update-index -z --add --remove --stdin &&
shift &&
git commit -s -m "$*"


#!/bin/sh

# This script records the current state of the msysGit root tree in a
# temporary Git index

cd / &&
export GIT_INDEX_FILE=/.git/install-index.$$ &&
cp .git/index $GIT_INDEX_FILE &&
git add . &&
echo $GIT_INDEX_FILE

#!/bin/sh

error () {
    echo "* error: $*"
    echo INSTALLATION ABORTED
    read -e IGNORED_INPUT
    trap - exit
    exit 1
}

# We're already in the install directory
INSTALL_PATH=`pwd`
export PATH=$INSTALL_PATH/installer-tmp/bin

cd $INSTALL_PATH/installer-tmp

echo -------------------------------------------------------
echo Fetching installation files
echo -------------------------------------------------------

repo=repo.or.cz
repoPath=msysgit.git
filesToFetch=master:share/GitMe/Installer

git archive --remote=git://$repo/$repoPath $filesToFetch | tar -x ||
 git archive --remote=http://$repo/r/$repoPath $filesToFetch | tar -x ||
  error "Cannot fetch installation files"

echo Done
echo

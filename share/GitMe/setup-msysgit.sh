#!/bin/sh

# We're already in the install directory
INSTALL_PATH=`pwd`
export PATH=$INSTALL_PATH/installer-tmp/bin:$PATH

error () {
    echo "* error: $*"
    echo INSTALLATION ABORTED
    read -e IGNORED_INPUT
    trap - exit
    exit 1
}

echo -------------------------------------------------------
echo Checking environment
echo -------------------------------------------------------
type cygpath >/dev/null 2>/dev/null && {
    echo "Cygwin seems to be in your system path. This was detected"
    echo "by trying to run cygpath, which was found by this shell."
    echo ""
    echo "Cygwin may cause severe problems, like crashes, if used in"
    echo "combination with msysgit. Please remove Cygwin from you system"
    echo "PATH environment variable."
    echo ""
    echo "For assistance on how to control your environment variables"
    echo "you should consult Microsoft's knowlege base:"
    echo "   Windows XP: http://support.microsoft.com/kb/310519"
    echo "   Windows NT: http://support.microsoft.com/kb/100843"
    echo ""
    error "Can not install msysgit when Cygwin is in PATH."
}
echo "Environment is clean. Can install msysgit."

echo
echo -------------------------------------------------------
echo Fetching the latest MSys environment
echo -------------------------------------------------------
MSYSGIT_REPO_GIT=repo.or.cz/msysgit.git
MSYSGIT_REPO_HTTP=repo.or.cz/r/msysgit.git

# Multiply git.exe

cp $INSTALL_PATH/installer-tmp/bin/git.exe $INSTALL_PATH/installer-tmp/bin/git-init.exe
cp $INSTALL_PATH/installer-tmp/bin/git.exe $INSTALL_PATH/installer-tmp/bin/git-unpack-objects.exe
cp $INSTALL_PATH/installer-tmp/bin/git.exe $INSTALL_PATH/installer-tmp/bin/git-update-ref.exe

git init &&
git config remote.origin.url git://$MSYSGIT_REPO_GIT &&
git config remote.origin.fetch '+refs/heads/*:refs/remotes/origin/*' &&
git config remote.mob.url \
        ssh://mob@$MSYSGIT_REPO_GIT &&
git config remote.mob.fetch +refs/remote/mob:refs/remotes/origin/mob &&
git config remote.mob.push master:mob &&

(git fetch ||
        (git config remote.origin.url \
                http://$MSYSGIT_REPO_HTTP &&
         git fetch))

# This following works, but would not fall back on curl if git:// protocol couldn't be used
#git-clone -n $MSYSGIT_REPO /msysgit-tmp ||
#mv /msysgit-tmp/.git $INSTALL_PATH/.git
#rm -rf /msysgit-tmp ||
#    error Couldn\'t clone $MSYSGIT_REPO!


echo
echo -------------------------------------------------------
echo Checking out the master branch
echo -------------------------------------------------------
git-checkout -l -f -b master origin/master ||
    error Couldn\'t checkout the master branch!


# TEMP: Remove pre-existing git directory
rm -rf git


echo
echo -------------------------------------------------------
echo Fetching the latest MinGW Git sources
echo -------------------------------------------------------
MINGW_REPO_GIT=git://repo.or.cz/git/mingw/4msysgit.git
MINGW_REPO_HTTP=http://repo.or.cz/r/git/mingw/4msysgit.git

git-submodule init &&
(git-submodule update ||
    (git config submodule.git.url $MINGW_REPO_HTTP &&
    rm -rf $INSTALL_PATH/git &&  # Need to clean up after the previous failed submodule update
    git-submodule update)) ||
    error Couldn\'t update submodules!

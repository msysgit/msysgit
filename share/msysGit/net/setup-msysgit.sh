#!/bin/sh

# We're already in the install directory
INSTALL_PATH="$(pwd)"
export PATH="$INSTALL_PATH/installer-tmp/bin:$PATH"

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
echo Fetching the latest msysgit environment
echo -------------------------------------------------------
MSYSGIT_REPO_GIT=git://github.com/msysgit/msysgit
MSYSGIT_REPO_HTTP=https://github.com/msysgit/msysgit.git

# Multiply git.exe

for builtin in init unpack-objects update-ref fetch ls-remote clone checkout
do
	ln "$INSTALL_PATH/installer-tmp/bin/git.exe" \
		"$INSTALL_PATH/installer-tmp/bin/git-$builtin.exe"
done

git config --system http.sslCAinfo /bin/curl-ca-bundle.crt
git init &&
git config core.autocrlf false &&
git config remote.origin.url $MSYSGIT_REPO_GIT &&
git config remote.origin.fetch \
	+refs/heads/@@MSYSGITBRANCH@@:refs/remotes/origin/@@MSYSGITBRANCH@@ &&
git config branch.@@MSYSGITBRANCH@@.remote origin &&
git config branch.@@MSYSGITBRANCH@@.merge refs/heads/@@MSYSGITBRANCH@@ &&

USE_HTTP=
git fetch || {
	USE_HTTP=t &&
        git config remote.origin.url $MSYSGIT_REPO_HTTP &&
        git fetch || {
		echo -n "Please enter a HTTP proxy: " &&
		read proxy &&
		test ! -z "$proxy" &&
		export http_proxy="$proxy" &&
		git fetch
	} ||
	error "Could not get msysgit.git"
}

git config remote.origin.fetch '+refs/heads/*:refs/remotes/origin/*'

echo
echo -------------------------------------------------------
echo Checking out the msysgit @@MSYSGITBRANCH@@ branch
echo -------------------------------------------------------
git-checkout -l -f -q -b @@MSYSGITBRANCH@@ origin/@@MSYSGITBRANCH@@ ||
	error Couldn\'t checkout the @@MSYSGITBRANCH@@ branch!
mkdir -p .git/hooks &&
cp share/msysGit/post-checkout-hook .git/hooks/post-checkout ||
	error Could not install post-checkout hook

# TEMP: Remove pre-existing git directory
rm -rf git


echo
echo -------------------------------------------------------
echo Fetching the latest Git sources
echo -------------------------------------------------------

case "$USE_HTTP" in
t)
	GIT_REPO_URL=https://github.com/git/git.git
	HTMLDOCS_REPO_URL=https://github.com/gitster/git-htmldocs.git
	MINGW_REPO_URL=http://repo.or.cz/r/git/mingw.git/
	MINGW4MSYSGIT_REPO_URL=https://github.com/msysgit/git.git
	GITCHEETAH_REPO_URL=https://github.com/msysgit/Git-Cheetah.git
;;
'')
	GIT_REPO_URL=git://github.com/git/git
	HTMLDOCS_REPO_URL=git://github.com/gitster/git-htmldocs.git
	MINGW_REPO_URL=git://repo.or.cz/git/mingw.git
	MINGW4MSYSGIT_REPO_URL=git://github.com/msysgit/git
	GITCHEETAH_REPO_URL=git://github.com/msysgit/Git-Cheetah
;;
esac

git config submodule.git.url $MINGW4MSYSGIT_REPO_URL &&
mkdir -p git &&
cd git &&
git init &&
git config core.autocrlf input &&
git config remote.junio.url $GIT_REPO_URL &&
git config remote.junio.fetch '+refs/heads/*:refs/remotes/junio/*' &&
git fetch --tags junio &&
git config remote.mingw.url $MINGW_REPO_URL &&
git config remote.mingw.fetch '+refs/heads/*:refs/remotes/mingw/*' &&
git fetch --tags mingw &&
git config remote.origin.url $MINGW4MSYSGIT_REPO_URL &&
git config remote.origin.fetch '+refs/heads/*:refs/remotes/origin/*' &&
git fetch --tags origin &&
if test -z "@@FOURMSYSGITBRANCH@@"
then
	FOURMSYS=origin/master
else
	FOURMSYS=origin/@@FOURMSYSGITBRANCH@@
fi &&
git config branch.${FOURMSYS#origin/}.remote origin &&
git config branch.${FOURMSYS#origin/}.merge refs/heads/${FOURMSYS#origin/} &&
git fetch origin &&
git checkout -l -f -q -b ${FOURMSYS#origin/} $FOURMSYS ||
error Couldn\'t update submodule git!

echo
echo -------------------------------------------------------
echo Fetching Git html help submodule
echo -------------------------------------------------------

cd .. &&
rm -rf /doc/git/html &&
git config submodule.html.url $HTMLDOCS_REPO_URL &&
mkdir -p doc/git/html &&
cd doc/git/html &&
git init &&
git config remote.origin.url $HTMLDOCS_REPO_URL &&
git config remote.origin.fetch '+refs/heads/master:refs/remotes/origin/master' &&
git fetch origin &&
git checkout -l -f -q $(cd ../../.. && git ls-tree HEAD doc/git/html |
	sed -n "s/^160000 commit \(.*\).doc\/git\/html$/\1/p") ||
error "Couldn't update submodule doc/git/html (HTML help will not work)."

echo
echo -------------------------------------------------------
echo Fetching git-cheetah submodule
echo -------------------------------------------------------

cd ../../.. &&
rm -rf /src/git-cheetah &&
git config submodule.git-cheetah.url $GITCHEETAH_REPO_URL &&
mkdir -p src/git-cheetah &&
cd src/git-cheetah &&
git init &&
git config remote.origin.url $GITCHEETAH_REPO_URL &&
git config remote.origin.fetch '+refs/heads/*:refs/remotes/origin/*' &&
git fetch origin &&
git-checkout -l -f -q -b master origin/master ||
	error "Could not update the submodule src/git-cheetah!"

# Copy profile.d/*.sh if there is any

cd ../.. &&
if test -d "$INSTALL_PATH"/installer-tmp/profile.d
then
	mkdir -p etc/profile.d &&
	for file in "$INSTALL_PATH"/installer-tmp/profile.d/*.sh
	do
		cp "$file" etc/profile.d/
	done
fi

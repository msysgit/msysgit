#!/bin/bash

force=
do_compile=t
while test $# -gt 0
do
	case "$1" in
	-f|--force)
		force=t
		shift
		;;
	-n|--no-compile)
		do_compile=
		shift
		;;
	*)
		break
	esac
done

test -z "$1" && {
	echo "Usage: $0 [-f] [-n] <version>" >&2
	exit 1
}

version=$1

# change directory to msysGit root
SCRIPTDIR="$(cd "$(dirname "$0")" && pwd)"
MSYSGITROOT="$(cd $SCRIPTDIR/../../ && pwd | sed 's/\/$//')/."
cd $MSYSGITROOT || {
	echo "Could not change directory to msysGit root" >&2
	exit 1
}

test -z "$force" && {
	die () {
		echo "$*" >&2
		echo "If that is okay, please call '$0 -f $version'" >&2
		exit 1
	}

	(cd git &&
	 git update-index --refresh &&
	 git diff-files --quiet &&
	 git diff-index --cached HEAD --) ||
	die "Git submodule has dirty files"
	(git update-index --refresh &&
	 git diff-files --quiet &&
	 git diff-index --cached HEAD --) ||
	die "msysGit super project not up-to-date"
}

create_msysgit_tag () {
	if tag=$(git describe --exact-match --match "*.msysgit.*" HEAD 2> /dev/null)
	then
		echo "Using existing tag $tag"
	else
		i=0 &&
		tag=$(git describe HEAD | cut -d- -f1) &&
		tag=${tag%.msysgit.*} &&
		while ! git tag -a -m "Git for Windows $1" $tag.msysgit.$i 2> /dev/null
		do
			i=$(($i+1))
		done &&
		echo "Created tag $tag.msysgit.$i"
	fi
}

# compile everything needed for standard setup
test "$do_compile" && {
	wordpad share/WinGit/ReleaseNotes.rtf && {
		( # create a commit if ReleaseNotes changed
		 if test ! -z "$(git diff share/WinGit/ReleaseNotes.rtf)"
		 then
			git add share/WinGit/ReleaseNotes.rtf &&
			git commit -m "Git for Windows $version"
		 fi) &&
		(cd git &&
		 create_msysgit_tag $version &&
		 make install) &&
		(cd git/contrib/subtree &&
			make install INSTALL=/bin/install prefix=) &&
		(cd git/contrib/credential/wincred &&
			make install INSTALL=/bin/install prefix=) &&
		/src/mingw-w64/release-easy.sh &&
		/src/mingw-w64/release-zlib.sh &&
		(cd src/git-cheetah/explorer/ &&
		 make objects-clean && make &&
		 make objects-clean && make W64=1)
	} || exit 1
}

test -z "$force" && {
	die () {
		echo "$*" >&2
		echo "If that is okay, please call '$0 -f $version'" >&2
		exit 1
	}

	(cd git &&
	 git update-index --refresh &&
	 git diff-files --quiet &&
	 git diff-index --cached HEAD --) ||
	die "Git submodule has dirty files"
	(cd git &&
	 test git.exe = $((printf 'git.exe\0'; git ls-files -z) | xargs --null ls -t 2>/dev/null| head -1)) ||
	die "Git's git.exe is not up-to-date (run 'cd /git && make' to fix)"
	for f in bin/git* libexec/git-core/git*
	do
		case "$f" in
		*.manifest)
			continue
			;;
		*/gitk)
			basename=gitk-git/gitk
			;;
		*/git-citool|*/git-gui)
			basename=git-gui/git-gui
			;;
		*/git-gui--askpass|*/git-gui--askyesno|*/git-gui.tcl)
			basename=git-gui/$(basename "$f")
			;;
		*/git-subtree)
			basename=contrib/subtree/$(basename "$f")
			;;
		*/git-credential-wincred.exe)
			basename=contrib/credential/wincred/$(basename "$f")
			;;
		*)
			basename=$(basename "$f")
			;;
		esac
		cmp "$f" "git/$basename" ||
		die "Installed Git disagrees with contents of /git/ ($f)"
	done
	(git update-index --refresh &&
	 git diff-files --quiet &&
	 git diff-index --cached HEAD --) ||
	die "msysGit super project not up-to-date"
	(cd git &&
	 test ! -z "$(git tag --contains HEAD)") ||
	die "Git's HEAD is untagged"
}

TMPDIR=/tmp/WinGit
unset DONT_REMOVE_BUILTINS

$MSYSGITROOT/share/WinGit/copy-files.sh $TMPDIR &&
sed -e '/share\/msysGit/d' -e "s/msysGit/Git (version $version)/" \
	< etc/motd > $TMPDIR/etc/motd &&
cp share/resources/gpl-2.0.rtf share/resources/git.bmp share/resources/gitsmall.bmp $TMPDIR &&
sed -e "s/%APPVERSION%/$version/" \
	< share/WinGit/install.iss > $TMPDIR/install.iss &&
cp share/WinGit/*.inc.iss $TMPDIR &&
echo "Launching Inno Setup compiler ..." &&
(cd $TMPDIR &&
 if test -x $MSYSGITROOT/share/InnoSetup/ISCC.exe
 then
	 $MSYSGITROOT/share/InnoSetup/ISCC.exe install.iss
 else
	 case $(wine --version) in
	 wine-0*|wine-1.[012]*|wine-1.3.[0-9]|wine-1.3.[0-9]-*|wine-1.3.1[0-4]|wine-1.3.1[0-4]-*)
		echo "You need at least WINE version 1.3.15" >&2 &&
		exit 1
	 esac &&
	 wine $MSYSGITROOT/share/InnoSetup/ISCC.exe install.iss
 fi > /tmp/install.out &&
 echo $? > /tmp/install.status) &&
(test 0 = "$(cat /tmp/install.status)") &&
git tag -a -m "Git for Windows $1" Git-$1 &&
echo "Installer is available as $(tail -n 1 /tmp/install.out)"

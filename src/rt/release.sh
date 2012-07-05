#!/bin/sh

die () {
	echo "$*" >&2
	exit 1
}

cd "$(dirname "$0")"

target=
debug=

# see what to build
case "$1" in
	msys|bash)
		target=$1
		;;
	*)
		die "$0 (msys|bash) [options]"
		;;
esac

shift

test "a$1" = "a--debug" && debug=t
debug_clean=
test "$debug" = "$(cat debug.txt 2>/dev/null)" || debug_clean=t
echo "$debug" > debug.txt

test -d ../msys/msys/rt ||
(
	cd ../.. &&
	git submodule update --init src/msys
) ||
die "Could not check out msys.git"

cd ../msys || {
  echo "Huh? ../msys does not exist."
  exit 1
}

current=$(git rev-list --no-merges origin/master.. | wc -l) &&
total=$(ls ../rt/patches/*.patch | wc -l) &&
i=1 &&
while test $i -le $total
do
	test $i -le $current ||
	git am ../rt/patches/$(printf "%04d" $i)*.patch ||
	die "Error: Applying patches failed."
	i=$(($i+1))
done


cd msys &&
release=MSYS-g$(git show -s --pretty=%h HEAD) ||
die "Could not detect MSYS release"

test -f /bin/cc.exe || ln gcc.exe /bin/cc.exe ||
die "Could not make sure that MSys cc is found instead of MinGW one"

# build msys.dll
release_msys() {
	(export MSYSTEM=MSYS &&
	 export PATH=/bin:$PATH &&
	 cd rt &&
	 (test -d bld || mkdir bld) &&
	 cd bld &&
	 DLL=i686-pc-msys/winsup/cygwin/new-msys-1.0.dll &&
	 (test -f Makefile && test -z "$debug_clean" ||
	  ../src/configure --prefix=/usr --enable-newlib-mb) &&
	 (test -z "$debug" || perl -i.bak -pe 's/-O2//g' $(find -name Makefile)) &&
	 (test -z "$debug_clean" || make clean) &&
	 (make || test -f $DLL) &&
	 (test ! -z "$debug" || strip $DLL) &&
	 rebase -b 0x68000000 $DLL &&
	 mv $DLL /bin/) &&
	cd / &&
	hash=$(git hash-object -w bin/new-msys-1.0.dll) &&
	git update-index --cacheinfo 100755 $hash bin/msys-1.0.dll &&
	git commit -s -m "Updated msys-1.0.dll to $release" &&
	/share/msysGit/post-checkout-hook HEAD^ HEAD 1
}

# build bash.exe
release_bash() {
	(export MSYSTEM=MSYS &&
	 export PATH=/bin:$PATH &&
	 cd packages/bash &&
	 case "$(git config --get --bool core.autocrlf)" in
	 true)
		git config core.autocrlf false &&
		git read-tree HEAD &&
		git stash
		;;
	 esac &&
	 (test -d bld || mkdir bld) &&
	 cd bld &&
	 BASH=bash.exe &&
	 (test -f Makefile && test -z "$debug_clean" ||
	  ../3.1/configure \
		--prefix=/usr \
		--sysconfdir=/etc \
		--localstatedir=/var \
		--disable-nls \
		--disable-rpath \
		--without-curses) &&
	 (test -z "$debug" || perl -i.bak -pe 's/-O2//g' $(find -name Makefile)) &&
	 (test -z "$debug_clean" || make clean) &&
	 make &&
	 test -f $BASH &&
	 (test ! -z "$debug" || strip $BASH) &&
	 cp $BASH /bin/new-bash.exe) &&
	cd / &&
	hash=$(git hash-object -w bin/new-bash.exe) &&
	git update-index --cacheinfo 100755 $hash bin/bash.exe &&
	git update-index --cacheinfo 100755 $hash bin/sh.exe &&
	git commit -s -m "Updated bash.exe to $release" &&
	/share/msysGit/post-checkout-hook HEAD^ HEAD 1
}

release_$target

#!/bin/sh

cd "$(dirname "$0")"

VERSION=0.9.8x
DIR=openssl-$VERSION
URL=http://www.openssl.org/source/$DIR.tar.gz
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

replace_symlinks_with_copies () {
	BRANCH=$1
	SYMLINKS="$(git ls-tree -r $BRANCH: | sed -n 's/^120000.\{47\}//p')" &&
	if test -z "$SYMLINKS"
	then
		die "No symlinks found?  You need to update your /git/."
	else
		(export GIT_INDEX_FILE=.git/tmp &&
		 git read-tree $BRANCH &&
		 i=1 &&
		 total=$(echo "$SYMLINKS" | wc -l) &&
		 UPDATES="$(echo "$SYMLINKS" |
		 while read path
		 do
		 	printf "\rProcessing symlink ($i/$total)" >&2 &&
			i=$(($i+1)) &&
		 	BASEDIR="${path%/*}/" &&
		 	TARGET="$(git cat-file blob $BRANCH:$path)" &&
			while test "$TARGET" != "${TARGET#../}"
			do
				BASEDIR="$(echo "$BASEDIR" |
					sed 's|[^/]*/$||')" &&
				TARGET="${TARGET#../}"
			done &&
			git ls-files --stage "$BASEDIR$TARGET" |
			sed "s|	.*$|	$path|"
		 done)" &&
		 echo "$UPDATES" | git update-index --index-info &&
		 TREE=$(git write-tree) &&
		 COMMIT=$(echo "Replace symlinks with copies" |
		 	git commit-tree $TREE -p $BRANCH) &&
		 git update-ref refs/heads/$BRANCH $COMMIT)

	fi
}

apply_patches () {
	test $(ls ../patches/*.patch | wc -l) = \
		$(($(git rev-list HEAD | wc -l)-2)) && return
	git am ../patches/*.patch
}

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download OpenSSL"

	mkdir $DIR && (
		cd $DIR &&
		git init &&
		git config core.autocrlf false &&
		/git/contrib/fast-import/import-tars.perl ../$FILE
	)
} || die "Could not check out openssl"

test $(cat $DIR/apps/md4.c 2> /dev/null | wc -l) -gt 2 || (
	cd $DIR &&
	replace_symlinks_with_copies import-tars &&
	git checkout import-tars &&
	test $(wc -l < apps/md4.c) -gt 2
) || die "Could not replace symlinks with copies"

test grep INSTALLTOP=/mingw $DIR/Makefile > /dev/null 2>&1 || (
	cd $DIR &&
	apply_patches
) || die "Could not apply the patches"

test -f $DIR/openssl.dll || (
	cd $DIR &&
	cmd /c ms\\mingw32.bat &&
	cd out &&
	list=$(echo *.dll openssl.exe) &&
	cp $list /mingw/bin && (
		cd /mingw/bin &&
		git add $list &&
		git commit -s -m "Install OpenSSL $VERSION"
	) &&
	list=$(echo *.dll.a) &&
	cp $list /mingw/lib && (
		cd /mingw/lib &&
		git add $list &&
		git commit -s -m "Install OpenSSL $VERSION import libs"
	) &&
	cd ../outinc &&
	cp -r openssl /mingw/include &&
	(
		cd /mingw/include &&
		git add openssl &&
		git commit -s -m "Install OpenSSL $VERSION header files"
	)
) || die "Could not install $FILE"

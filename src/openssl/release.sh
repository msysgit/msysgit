#!/bin/sh

VERSION=0.9.8k
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
	index=$(/share/msysGit/pre-install.sh) &&
	cp -r outinc/* /mingw/include/ &&
	cp out/*.a /mingw/lib/ &&
	cp *.dll /mingw/bin/ &&
	/share/msysGit/post-install.sh $index "Install $FILE"
) || die "Could not install $FILE"

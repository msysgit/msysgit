#!/bin/sh

cd "$(dirname "$0")"

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
		die 'No symlinks found?  You need to update your /git/, 
remove '"$DIR"' and try again.'
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

reinstall_symlinks () {
	REF=import-tars^
	git ls-tree -r $REF: | sed -n 's/^120000.\{47\}//p' |
	while read name
	do
		DIR=${name%/*}
		TARGET=$DIR${DIR:+/}$(git show $REF:$name)
		cp $TARGET $name ||
		die "Could not fake symlink $name -> $TARGET"
	done
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
	git reset --hard import-tars &&
	test $(wc -l < apps/md4.c) -gt 2
) || die "Could not replace symlinks with copies"

test grep 'cyg\$' $DIR/Makefile.shared > /dev/null 2>&1 || (
	perl -pi.bak -e "s/([ \/])cyg/\\1msys-/g" $DIR/Makefile &&
	perl -pi.bak -e "s/=cyg/=msys-/" $DIR/Makefile.shared &&
	perl -pi.bak -e "s/cp cyg/cp msys-/" $DIR/engines/Makefile
) || die "Could not apply the patches"

test -f $DIR/.gitignore ||
cat << EOF > $DIR/.gitignore
*.o
*.s
*.a
*.dll
*.exe
*.pc
lib
EOF

test -f $DIR/openssl.dll || (
	cd $DIR &&
	if test ! -f Makefile.bak
	then
		./Configure --prefix=/usr --shared Cygwin &&
		echo "Reinstalling 'symlinked' files" &&
		reinstall_symlinks
	fi &&
	make &&
	index=$(/share/msysGit/pre-install.sh) &&
	make install &&
	/share/msysGit/post-install.sh $index "Install OpenSSL $VERSION"
) || die "Could not install $FILE"

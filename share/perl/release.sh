#!/bin/sh

# Make sure that the working directory is clean and does not have untracked
# files; otherwise our semi-automatic finding the new files will not work!

(cd / &&
	 git diff-files --quiet &&
	 git diff-index --cached --quiet HEAD &&
	 test -z "$(git ls-files --exclude-from=.gitignore --others)") || {
		echo "State not pristine enough for successful Perl update"
		exit 1
	}

cd "$(dirname "$0")"

# Remove old Perl files stored in fileList.txt

cat fileList.txt | (cd / && xargs git rm) || exit

url=ftp://ftp.funet.fi/pub/CPAN/src/
version=5.6.1

p=perl-$version
tar=$p.tar.gz
for ext in "" .md5
do
	f=$tar$ext
	test -f $f && continue
	echo "Downloading $f ..." 
	curl $url/$f -o $f || exit
done

echo "Verifying md5 sum ..." 
md5sum -c --status $tar.md5 || exit

test -d $p || {
	echo "Unpacking $tar ..."
	tar -xzf $tar || exit
}

cd $p || {
	echo "Could not cd to $p"
	exit 1
}

test -d .git || {
	git init &&
	git add . &&
	git commit -m "Perl $version from $tar" > /dev/null ||
	exit
}

git rev-parse --verify HEAD^ 2>/dev/null ||
	git am ../patches/* ||
	exit

MSYSTEM=MSYS

test -f config.sh || ./Configure -de || exit

LIB= make install || exit

# update index
(cd / && git add .) || exit

git diff --cached --diff-filter=AM --name-only |
	sed -e "s/^/\//" > fileList.txt ||
	exit
		
git add fileList.txt || exit
		
echo "Successfully built and installed Perl $version"
echo "After checking the result, please commit (possibly with --amend)"
echo

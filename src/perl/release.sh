#!/bin/sh

cd "$(dirname "$0")"

url=ftp://ftp.funet.fi/pub/CPAN/src/
version=5.8.8
md5='b8c118d4360846829beb30b02a6b91a7'

#dmakeurl=http://mirrors.zerg.biz/cpan/authors/id/S/SH/SHAY/
#dmaketar=dmake-4.11-20080107-SHAY.zip
dmakeurl=http://tools.openoffice.org/dmake/
dmaketar=dmake_4.11.zip
dmakedir=dmake

if test ! -f $dmaketar
then
	curl $dmakeurl$dmaketar > $dmaketar
fi &&
if test ! -d $dmakedir
then
	unzip $dmaketar
fi &&
if test ! -f $dmakedir/Makefile
then
	perl -i.bak -pe 's/^_os=.*$/_os=MINGW/' $dmakedir/configure &&
	(cd $dmakedir && ./configure)
fi &&
if test ! -f $dmakedir/dmake.exe
then
	(cd $dmakedir && make)
fi || {
	echo "Could not build dmake"
	exit 1
}

p=perl-$version
tar=$p.tar.gz
test -f $tar || {
	echo "Downloading $tar ..." 
	curl $url/$tar -o $tar || exit
}

echo "Verifying md5 sum ..." 
echo "$md5 *$tar" > $tar.md5
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

#git rev-parse --verify HEAD^ 2>/dev/null ||
#	git am ../patches/* ||
#	exit

export TMP="$(echo "$TMP" | tr '/' '\\')"
DMAKE="../../dmake INST_TOP=\"$(cd /mingw; pwd -W)\""

test -f perl.exe || {
	(cd win32 && $DMAKE) ||
	exit
}

index=$(/share/msysGit/pre-install.sh) &&
(cd win32 && $DMAKE install) &&
/share/msysGit/post-install.sh $index "Install Perl $version" ||
exit

echo "Successfully built and installed Perl $version"
echo "After checking the result, please commit (possibly with --amend)"
echo

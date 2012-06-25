#!/bin/sh

cd "$(dirname "$0")"

URL=ftp://ftp.info-zip.org/pub/infozip/src/
TAR=unzip60.tgz
DIR=unzip60

if test ! -f $TAR
then
	curl $URL/$TAR > $TAR
fi &&
if test ! -d $DIR
then
	tar xzvf $TAR
fi &&
(cd $DIR && make -f win32/Makefile.gcc) &&
FILES="funzip.exe unzip.exe unzipsfx.exe" &&
(cd $DIR && cp $FILES /bin/) &&
(cd /bin && git add $FILES && git commit -s -m "Install $DIR" $FILES) || {
	echo "Failed to install unzip"
	exit 1
}

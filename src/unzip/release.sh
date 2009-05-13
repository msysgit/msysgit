#!/bin/sh

cd "$(dirname "$0")"

URL=http://ftp.uni-koeln.de/util/arc/
TAR=unzip60.tar.gz
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

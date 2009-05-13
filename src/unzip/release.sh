#!/bin/sh

cd "$(dirname "$0")"

URL=ftp://tug.ctan.org/tex-archive/tools/zip/info-zip/src/
TAR=unzip552.tar.gz
DIR=unzip-5.52

if test ! -f $TAR
then
	curl $URL$TAR > $TAR
fi &&
if test ! -d $DIR
then
	tar xzvf $TAR
fi &&
(cd $DIR && make -f win32/Makefile.gcc) &&
FILES="funzip.exe unzip.exe unzipsfx.exe" &&
(cd $DIR && cp $FILES /bin/) &&
(cd /bin && git add $FILES && git commit -s -m "Install unzip 5.52" $FILES) || {
	echo "Failed to install unzip"
	exit 1
}

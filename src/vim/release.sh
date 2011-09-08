#!/bin/sh

cd "$(dirname "$0")"

VERSION=7.3
DIR=vim73
URL=ftp://ftp.vim.org/pub/vim/unix/vim-7.3.tar.bz2
MD5='5b9510a17074e2b37d8bb38ae09edbf2'
FILE=${URL##*/}

die () {
	echo "$*" >&2
	exit 1
}

test -d $DIR || {
	test -f $FILE ||
	curl -O $URL ||
	die "Could not download vim"

	echo "$MD5 *$FILE" > $FILE.md5
	md5sum -c --status $FILE.md5 || (echo "invalid checksum $FILE";exit 1)

	tar xjvf $FILE && (
		cd $DIR &&
		git init &&
		git config core.autocrlf false &&
		git add . &&
		git commit -m "Import of $FILE"
	)
} || die "Could not check out vim"

cd $DIR/src &&
make -f Make_ming.mak clean &&
make -f Make_ming.mak GUI=no vim.exe &&
make -f Make_ming.mak GUI=yes gvim.exe &&
INDEX=$(/share/msysGit/pre-install.sh) &&
rm -rf /share/vim/vim[0-9]* &&
VIM_VERSION=$(sed -n 's/.*VIM_VERSION_NODOT	"\(.*\)".*/\1/p' < version.h) &&
SHARE=/share/vim/$VIM_VERSION &&
cp -R ../runtime $SHARE &&
cp gvim.exe vim.exe $SHARE/ &&
cat > /bin/vi << EOF &&
#!/bin/sh

exec $SHARE/vim "\$@"
EOF
rm -f /bin/vim.exe &&
cp /bin/vi /bin/vim &&
cat > /bin/gvim << EOF &&
#!/bin/sh

exec $SHARE/gvim "\$@"
EOF
/share/msysGit/post-install.sh $INDEX Install $VIM_VERSION || {
	echo "Failed to install vi"
	exit 1
}

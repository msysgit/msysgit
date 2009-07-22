#!/bin/sh

cd "$(dirname "$0")"

URL=git://github.com/cmichon/vim.git

if test -d vim
then
	cd vim &&
	git pull
else
	git clone $URL &&
	cd vim
fi &&
cd src &&
make -f Make_ming.mak vim.exe &&
INDEX=$(/share/msysGit/pre-install.sh) &&
rm -rf /share/vim/vim[0-9]* &&
VIM_VERSION=$(sed -n 's/.*VIM_VERSION_NODOT	"\(.*\)".*/\1/p' < version.h) &&
SHARE=/share/vim/$VIM_VERSION &&
cp -R ../runtime $SHARE &&
cp vim.exe $SHARE/ &&
cat > /bin/vi << EOF &&
#!/bin/sh

exec $SHARE/vim "\$@"
EOF
rm -f /bin/vim.exe &&
cp /bin/vi /bin/vim &&
/share/msysGit/post-install.sh $INDEX Install $VIM_VERSION || {
	echo "Failed to install vi"
	exit 1
}

#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <version>"
	exit 1
}

TARGET="$HOME"/WinGit-$1.exe
OPTS7="-m0=lzma -mx=9 -md=64M"
TARGET7=tmp.7z
LIST7=fileList.txt
TMPDIR=/tmp/WinGit

(test ! -d "$TMPDIR" || echo "Removing $TMPDIR" && rm -rf "$TMPDIR") &&
mkdir "$TMPDIR" &&
(cd "$(dirname "$0")" &&
 make &&
 mkdir "$TMPDIR"/bin &&
 cp create-shortcut.exe "$TMPDIR"/bin) &&
cp /share/resources/git.ico "$TMPDIR" &&
cd "$TMPDIR" &&
echo "Copying files" &&
(cd / && tar cf - bin/ lib/perl5/) |
tar xvf - &&
gitmd5=$(md5sum bin/git.exe | cut -c 1-32) &&
md5sum bin/git-*.exe | sed -n "s/^$gitmd5 \\*//p" > fileList-builtins.txt &&
rm $(cat fileList-builtins.txt) &&
(cd /mingw && tar cf - bin/*{tcl,tk,wish,gpg,curl.exe}* \
	lib/*{tcl,tk}* libexec/gnupg/) |
tar xvf - &&
strip bin/{[a-fh-z],g[a-oq-z],gp[a-fh-z]}*.exe &&
mkdir etc &&
cp /git/contrib/completion/git-completion.bash etc/ &&
sed 's/^\. .*\(git-completion.bash\)/. \/etc\/\1/' \
	< /etc/profile > etc/profile &&
cp /share/WinGit/install.tcl ./ &&
: > "$LIST7" &&
find * -type f | sed "s|^\./||" > "$LIST7" &&
7z a $OPTS7 $TARGET7 @"$LIST7" ||
exit

(cat /share/7-Zip/7zSD.sfx &&
 echo ';!@Install@!UTF-8!' &&
 echo 'Progress="yes"' &&
 echo 'Title="WinGit: MinGW Git + minimal MSys installation"' &&
 echo 'BeginPrompt="This program installes a complete Git for MSys setup"' &&
 echo 'CancelPrompt="Do you want to cancel WinGit installation?"' &&
 echo 'ExtractDialogText="Please, wait..."' &&
 echo 'ExtractPathText="Where do you want to install WinGit?"' &&
 echo 'ExtractTitle="Extracting..."' &&
 echo 'GUIFlags="8+32+64+256+4096"' &&
 echo 'GUIMode="1"' &&
 echo 'InstallPath="%PROGRAMFILES%\\Git"' &&
 echo 'OverwriteMode="2"' &&
 echo 'RunProgram="\"%%T\\bin\\wish.exe\" \"%%T\install.tcl\" \"%%T\""' &&
 echo ';!@InstallEnd@!7z' &&
 cat $TARGET7) > "$TARGET"
exit


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
cd "$TMPDIR" &&
echo "Copying files" &&
(cd / && tar cf - bin/{git*,awk,basename.exe,bash.exe,bunzip2,bzip2.exe,cat.exe,chmod.exe,clear,cmp.exe,cp.exe,cpio,cut.exe,cvs.exe,date.exe,diff.exe,du.exe,echo,egrep,env.exe,expr.exe,false.exe,find.exe,gawk.exe,grep.exe,gunzip,gzip.exe,head.exe,id.exe,less.exe,libW11.dll,libperl.dll,ln.exe,ls.exe,md5sum.exe,mkdir.exe,msys-1.0.dll,msysltdl-3.dll,mv.exe,patch.exe,patch.exe.manifest,perl.exe,printf,ps.exe,pwd,rm.exe,rmdir.exe,rxvt.exe,scp.exe,sed.exe,sh.exe,sleep.exe,sort.exe,split.exe,ssh-agent.exe,ssh.exe,tail.exe,tar.exe,tee.exe,touch.exe,tr.exe,true.exe,uname.exe,uniq.exe,vi,vim.exe,wc.exe,which,xargs.exe} lib/perl5/) |
tar xvf - &&
mkdir lib/perl5/site_perl &&
cp /lib/{Error.pm,Git.pm} lib/perl5/site_perl/ &&
gitmd5=$(md5sum bin/git.exe | cut -c 1-32) &&
md5sum bin/git-*.exe | sed -n "s/^$gitmd5 \\*//p" > fileList-builtins.txt &&
rm $(cat fileList-builtins.txt) &&
(cd /mingw && tar cf - bin/*{tcl,tk,wish,gpg,curl.exe}* \
	lib/*{tcl,tk}* libexec/gnupg/) |
tar xvf - &&
strip bin/{[a-fh-z],g[a-oq-z]}*.exe &&
mkdir etc &&
cp /git/contrib/completion/git-completion.bash etc/ &&
cp /etc/termcap etc/ &&
sed 's/^\. .*\(git-completion.bash\)/. \/etc\/\1/' \
	< /etc/profile > etc/profile &&
cp /share/resources/git.ico etc/ &&
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


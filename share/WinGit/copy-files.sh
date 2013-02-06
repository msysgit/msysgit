#!/bin/bash

test -z "$1" && {
	echo "Usage: $0 <dir>"
	exit 1
}

test -d doc/git/html/.git ||
(git submodule update --init doc/git/html/) || {
	echo "Error: html pages in /doc/git/html/ missing"
	exit 1
}

if test "$( cd doc/git/html/ ; git config core.autocrlf )" != "true"
then
	echo "Error: documentation must be checked out with core.autocrlf=true."
	echo "If you have changes in the documentation, hit Ctrl-C NOW."
	sleep 3
	(cd doc/git/html &&
	 git config core.autocrlf true &&
	 rm -rf *.html *.txt howto &&
	 git checkout -f) || {
		echo "Could not fix documentation"
		exit 1
	}
fi

SCRIPTDIR="$(cd "$(dirname "$0")" && pwd)"
MSYSGITROOT="$(cd $SCRIPTDIR/../../ && pwd | sed 's/\/$//')/."
TMPDIR=$1

(test ! -d "$TMPDIR" || echo "Removing $TMPDIR" && rm -rf "$TMPDIR") &&
mkdir "$TMPDIR" &&
cd "$TMPDIR" &&
echo "Copying files" &&
(git --git-dir=$MSYSGITROOT/doc/git/html/.git log --pretty=format:%s -1 HEAD &&
 mkdir -p doc/git/html && cd doc/git/html &&
 git --git-dir=$MSYSGITROOT/doc/git/html/.git archive HEAD | tar xf -) &&
(cd $MSYSGITROOT && tar cf - \
$(ls {bin,libexec/git-core}/git* | grep -v 'cvs\|shell\|archimport\|instaweb') \
bin/{antiword.exe,docx2txt,astextplain,awk,basename.exe,bash.exe,bison.exe,yacc,\
bunzip2,bzip2.exe,c_rehash,\
cat.exe,chmod.exe,clear,cmp.exe,cp.exe,cut.exe,cvs.exe,date.exe,diff.exe,\
dirname.exe,\
du.exe,echo,egrep,env.exe,expr.exe,false.exe,find.exe,flex.exe,gawk.exe,grep.exe,\
head.exe,id.exe,kill.exe,less.exe,libW11.dll,ln.exe,\
ls.exe,m4.exe,md5sum.exe,mkdir.exe,msys-1.0.dll,msysltdl-3.dll,mv.exe,patch.exe,\
patch.exe.manifest,perl.exe,printf,ps.exe,pwd,recodetree,rm.exe,rmdir.exe,rxvt.exe,\
scp.exe,sed.exe,sh.exe,sleep.exe,sort.exe,split.exe,\
ssh-agent.exe,ssh.exe,ssh-add.exe,ssh-keygen.exe,ssh-keyscan.exe,\
tail.exe,tar.exe,tee.exe,touch.exe,tr.exe,true.exe,uname.exe,uniq.exe,\
unzip.exe,vi,\
msys-perl5_8.dll,lib{apr,aprutil,expat,neon,z,svn}*.dll,pthreadGC2.dll,\
msys-crypto-0.9.8.dll,msys-regex-1.dll,msys-ssl-0.9.8.dll,msys-minires.dll,msys-z.dll,\
openssl.exe,vim,wc.exe,which,xargs.exe,start} lib/engines/ \
ssl/ cmd/ lib/perl5/ libexec/git-core/mergetools share/antiword/ share/bison/ share/git* \
share/vim/vimrc share/vim/vim73/{filetype.vim,ftoff.vim,menu.vim,optwin.vim,\
scripts.vim,\
autoload/netrw.vim,autoload/netrwFileHandlers.vim,autoload/netrwSettings.vim,\
plugin/netrwPlugin.vim,\
syntax/c.vim,syntax/conf.vim,syntax/cpp.vim,syntax/diff.vim,\
syntax/gitcommit.vim,syntax/gitconfig.vim,syntax/gitrebase.vim,syntax/git.vim,\
syntax/nosyntax.vim,syntax/syncolor.vim,syntax/synload.vim,syntax/syntax.vim,\
vim.exe}) |
tar xf - &&
rm -rf bin/cvs.exe &&
(test ! -f $MSYSGITROOT/lib/Git.pm || cp -u $MSYSGITROOT/lib/Git.pm lib/perl5/site_perl/Git.pm) &&
(test ! -d $MSYSGITROOT/lib/Git || cp -uR $MSYSGITROOT/lib/Git lib/perl5/site_perl/Git) &&
test -f lib/perl5/site_perl/Git.pm &&
gitmd5=$(md5sum bin/git.exe | cut -c 1-32) &&
mkdir etc &&
if test -z "$DONT_REMOVE_BUILTINS"
then
	md5sum {bin,libexec/git-core}/git-*.exe libexec/git-core/git.exe |
	sed -n -r "s/^$gitmd5\s+\*?(.*)/\1/p" > etc/fileList-builtins.txt &&
	rm $(cat etc/fileList-builtins.txt)
fi &&
(cd $MSYSGITROOT/mingw && tar cf - \
	bin/*{tcl,tk,wish,gpg,msmtp,curl.exe,*.crt}* bin/connect.exe \
	bin/*{libcurl,libcrypto,libssl,libgsasl,libiconv}* \
	bin/getcp.exe bin/rebase.exe \
	bin/gzip.exe bin/gunzip.exe \
	bin/{libpoppler-7.dll,pdfinfo.exe,pdftotext.exe} \
	lib/{tcl,tk,dde,reg}* ) |
tar xf - &&
cp $MSYSGITROOT/mingw/bin/hd2u.exe bin/dos2unix.exe &&
strip bin/{[a-fh-z],g[a-oq-z]}*.exe libexec/git-core/*.exe &&
cp $MSYSGITROOT/git/contrib/completion/git-completion.bash etc/ &&
cp $MSYSGITROOT/git/contrib/completion/git-prompt.sh etc/ &&
cp $MSYSGITROOT/etc/termcap etc/ &&
cp $MSYSGITROOT/etc/inputrc etc/ &&
sed 's/ = \/mingw\// = \//' < $MSYSGITROOT/etc/gitconfig > etc/gitconfig &&
cp $MSYSGITROOT/etc/gitattributes etc/ &&
cp $MSYSGITROOT/share/WinGit/Git\ Bash.vbs . &&
mkdir git-cheetah &&
cp $MSYSGITROOT/src/git-cheetah/explorer/git_shell_ext.dll git-cheetah/ &&
cp $MSYSGITROOT/src/git-cheetah/explorer/git_shell_ext64.dll git-cheetah/ &&
cp $MSYSGITROOT/share/WinGit/ReleaseNotes.rtf . &&
sed 's@/git/contrib/completion@/etc@g' \
	< $MSYSGITROOT/etc/profile > etc/profile &&
cp $MSYSGITROOT/share/resources/git.ico etc/ &&
cp $MSYSGITROOT/share/resources/git.ico share/git-gui/lib/git-gui.ico &&
find bin libexec -iname \*.exe -o -iname \*.dll | sort > etc/fileList-bindimage.txt ||
exit 1

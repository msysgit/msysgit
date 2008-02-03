#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <dir>"
	exit 1
}

test -d /doc/git/html/.git || { echo "Error: html pages in /doc/git/html/.git missing"; exit 1; }

if [ "$( cd /doc/git/html/ ; git config core.autocrlf )" != "true" ]
then
	echo "Error: documentation must be checked out with core.autocrlf=true."
	echo "Hint: fix this by"
	echo "   cd /doc/git/html"
	echo "   git config core.autocrlf true"
	echo "   rm *.html *.txt howto"
	echo "   git checkout -f"
	exit 1
fi

TMPDIR=$1

(test ! -d "$TMPDIR" || echo "Removing $TMPDIR" && rm -rf "$TMPDIR") &&
mkdir "$TMPDIR" &&
cd "$TMPDIR" &&
echo "Copying files" &&
(git --git-dir=/doc/git/html/.git log --pretty=format:%s -1 HEAD &&
 mkdir -p doc/git/html && cd doc/git/html &&
 git --git-dir=/doc/git/html/.git archive HEAD | tar xf -) &&
(cd / && tar cf - \
$(ls bin/git* | grep -v 'cvs\|send-email\|shell\|archimport\|instaweb\|filter-branch') \
bin/{awk,basename.exe,bash.exe,bunzip2,bzip2.exe,c_rehash,\
cat.exe,chmod.exe,clear,cmp.exe,cp.exe,cut.exe,cvs.exe,date.exe,diff.exe,\
du.exe,echo,egrep,env.exe,expr.exe,false.exe,find.exe,gawk.exe,grep.exe,\
gunzip,gzip.exe,head.exe,id.exe,less.exe,libW11.dll,ln.exe,\
ls.exe,md5sum.exe,mkdir.exe,msys-1.0.dll,msysltdl-3.dll,mv.exe,patch.exe,\
patch.exe.manifest,perl.exe,printf,ps.exe,pwd,rm.exe,rmdir.exe,rxvt.exe,\
scp.exe,sed.exe,sh.exe,sleep.exe,sort.exe,split.exe,ssh-agent.exe,ssh.exe,\
tail.exe,tar.exe,tee.exe,touch.exe,tr.exe,true.exe,uname.exe,uniq.exe,vi,\
msys-perl5_8.dll,lib{apr,aprutil,expat,neon,z,svn}*.dll,\
msys-crypto-0.9.8.dll,msys-ssl-0.9.8.dll,msys-minires.dll,msys-z.dll,\
openssl.exe,vim.exe,wc.exe,which,xargs.exe,ssh-add.exe,start} lib/engines/ \
ssl/ cmd/ lib/perl5/ share/git* share/vim) |
tar xf - &&
gitmd5=$(md5sum bin/git.exe | cut -c 1-32) &&
mkdir etc &&
md5sum bin/git-*.exe | sed -n "s/^$gitmd5 \\*//p" > etc/fileList-builtins.txt &&
rm $(cat etc/fileList-builtins.txt) &&
(cd /mingw && tar cf - bin/*{tcl,tk,wish,gpg,curl.exe,libcurl,libiconv}* \
	lib/*{tcl,tk}* libexec/gnupg/) |
tar xf - &&
strip bin/{[a-fh-z],g[a-oq-z]}*.exe &&
cp /git/contrib/completion/git-completion.bash etc/ &&
cp /etc/termcap etc/ &&
cp /etc/gitconfig etc/ &&
cp /share/WinGit/ReleaseNotes.rtf . &&
sed 's/^\. .*\(git-completion.bash\)/. \/etc\/\1/' \
	< /etc/profile > etc/profile &&
cp /share/resources/git.ico etc/ ||
exit 1

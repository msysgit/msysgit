#!/bin/sh

test -z "$1" && {
	echo "Usage: $0 <dir>"
	exit 1
}

test -d /doc/git/html/.git || { echo "Error: html pages in /doc/git/html/.git missing"; exit 1; }

TMPDIR=$1

(test ! -d "$TMPDIR" || echo "Removing $TMPDIR" && rm -rf "$TMPDIR") &&
mkdir "$TMPDIR" &&
cd "$TMPDIR" &&
echo "Copying files" &&
(git --git-dir=/doc/git/html/.git log --pretty=format:%s -1 HEAD &&
 mkdir -p doc/git/html && cd doc/git/html &&
 git --git-dir=/doc/git/html/.git archive HEAD | tar xf -) &&
(cd / && tar cf - bin/{git*,awk,basename.exe,bash.exe,bunzip2,bzip2.exe,\
cat.exe,chmod.exe,clear,cmp.exe,cp.exe,cpio,cut.exe,cvs.exe,date.exe,diff.exe,\
du.exe,echo,egrep,env.exe,expr.exe,false.exe,find.exe,gawk.exe,grep.exe,\
gunzip,gzip.exe,head.exe,id.exe,less.exe,libW11.dll,libperl.dll,ln.exe,\
ls.exe,md5sum.exe,mkdir.exe,msys-1.0.dll,msysltdl-3.dll,mv.exe,patch.exe,\
patch.exe.manifest,perl.exe,printf,ps.exe,pwd,rm.exe,rmdir.exe,rxvt.exe,\
scp.exe,sed.exe,sh.exe,sleep.exe,sort.exe,split.exe,ssh-agent.exe,ssh.exe,\
tail.exe,tar.exe,tee.exe,touch.exe,tr.exe,true.exe,uname.exe,uniq.exe,vi,\
vim.exe,wc.exe,which,xargs.exe,ssh-add.exe,start} cmd/ lib/perl5/ share/git* share/vim) |
tar xvf - &&
mkdir lib/perl5/site_perl &&
cp /lib/{Error.pm,Git.pm} lib/perl5/site_perl/ &&
gitmd5=$(md5sum bin/git.exe | cut -c 1-32) &&
mkdir etc &&
md5sum bin/git-*.exe | sed -n "s/^$gitmd5 \\*//p" > etc/fileList-builtins.txt &&
rm $(cat etc/fileList-builtins.txt) &&
(cd /mingw && tar cf - bin/*{tcl,tk,wish,gpg,curl.exe,libcurl}* \
	lib/*{tcl,tk}* libexec/gnupg/) |
tar xvf - &&
strip bin/{[a-fh-z],g[a-oq-z]}*.exe &&
cp /git/contrib/completion/git-completion.bash etc/ &&
cp /etc/termcap etc/ &&
cp /share/WinGit/ReleaseNotes.txt . &&
sed 's/^\. .*\(git-completion.bash\)/. \/etc\/\1/' \
	< /etc/profile > etc/profile &&
cp /share/resources/git.ico etc/ ||
exit 1

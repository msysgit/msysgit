This is a loose list of things to do.  Please remove the items with the commit
that implements it.

- feed the changes in 4msysgit.git to mingw.git or directly to git.git. This
  is a bit involved, as it means repackaging the whole diff between our master
  and Junio's master.  We might get away with rebasing step by step, i.e.
  replace each merge from upstream with a rebase.  Much work, no doubt.

- WinGit: force
  "git ls-files --other bin/git-* | xargs rm && cd /git && make install"
  to avoid installing stale files.

- rebase with binary patches says "corrupt patch" at some stage.

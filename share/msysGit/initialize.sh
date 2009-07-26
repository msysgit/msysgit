#!/bin/sh

# This script initializes /.git from msysgit.git on repo.or.cz

test -d /git/.git || {
	cd /git &&
	git init &&
	git config core.autocrlf false &&
	git remote add -f origin \
		mob@repo.or.cz:/srv/git/git/mingw/4msysgit.git &&
	if test ! -f /etc/full-git-sha1 ||
		! git reset $(cat /etc/full-git-sha1)
	then
		git add . &&
		git commit -m "Current revision"
	fi &&
	git gc
} ||
exit


test -d /.git || {
	cd / &&
	git init &&
	git config core.autocrlf false &&
	git remote add -f origin mob@repo.or.cz:/srv/git/msysgit.git &&
	if test ! -f /etc/full-msysgit-sha1 ||
		! git reset $(cat /etc/full-msysgit-sha1)
	then
		git ls-files --other --exclude-standard $(sed -n \
				-e 's/^path = /--exclude=/p' < .gitmodules) -z |
			git update-index --add -z --stdin &&
		git commit -m "Current revision"
	fi &&
	git gc
}

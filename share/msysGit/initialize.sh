#!/bin/sh

# This script initializes /.git from msysgit/msysgit on github.com

test -d /git/.git || {
	cd /git &&
	git init &&
	git config core.autocrlf false &&
	git remote add -f origin \
		https://github.com/msysgit/git &&
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
	git remote add -f origin https://github.com/msysgit/msysgit &&
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

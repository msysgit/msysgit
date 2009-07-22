#!/bin/sh

# This script initializes /.git from msysgit.git on repo.or.cz

test -d /git/.git || {
	cd /git &&
	git init &&
	git add . &&
	git commit -m "Current revision" &&
	git remote add -f origin mob@repo.or.cz:/srv/git/git/mingw/4msysgit.git
} ||
exit


test -d /.git || {
	cd / &&
	git init &&
	git ls-files --other --exclude-standard $(sed -n \
			-e 's/^path = /--exclude=/p' < .gitmodules) -z |
		git update-index --add --stdin -z &&
	git commit -m "Current revision" &&
	git remote add -f origin mob@repo.or.cz:/srv/git/4msysgit.git &&
	git gc
}

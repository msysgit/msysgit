#!/bin/sh

# This script initializes /.git from msysgit.git on repo.or.cz

test -d /.git || {
	cd / &&
	git init &&
	git add bin doc etc lib mingw msys* share .gitignore &&
	git add $( (cd git &&
			git ls-files | grep -v "^\"\?gitweb" &&
			echo gitweb) |
		sed "s|^|git/|" ) &&
	git update-index --add git/config.mak &&
	git remote add origin git://repo.or.cz/msysgit.git/ &&
	git fetch &&
	git gc &&
	git reset --soft origin/master &&
	git read-tree -m -u HEAD
}


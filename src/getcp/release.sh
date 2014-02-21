#!/bin/sh

DEST=/mingw/bin/getcp.exe
make && 
install -m 775 getcp.exe $DEST &&
git add $DEST &&
git commit -n -s -m "getcp: locale independent utility to read the current code page" $DEST

#!/bin/sh

DEST=/bin/xser32.dll
cd "$(dirname "$0")" &&
make &&
install -m 775 xser32.dll $DEST &&
git add $DEST &&
git commit -s -m "xser32.dll: Fake user32.dll like stub (for sh.exe not to load user32.dll)" $DEST

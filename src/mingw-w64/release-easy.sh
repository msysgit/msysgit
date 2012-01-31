#!/bin/sh

cd "$(dirname "$0")"
srcdir=$(pwd)

# Limit the number of RSS feed entries.
limit=500

link=$(curl -s http://sourceforge.net/api/file/index/project-id/202880/mtime/desc/limit/$limit/rss |
     sed -nr "s/<link>(.+(mingw-w64-bin_i686-mingw_[0-9]+.zip).+)<\/link>/\2\t\1/p" |
     head -1)

file=$(echo "$link" | cut -f 1)
url=$(echo "$link" | cut -f 2)

# Trim whitespaces.
file=$(echo $file)
url=$(echo $url)

dir=${file%.zip}

# download it
test -f $file || curl -L $url -o $file || exit

# unpack & install it
test -f sysroot/.root.init.marker &&
test sysroot/.root.init.marker -nt $file ||
(mkdir -p sysroot &&
 cd sysroot &&
 unzip ../$file &&
 touch .root.init.marker
)

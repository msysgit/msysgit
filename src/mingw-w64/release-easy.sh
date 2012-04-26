#!/bin/sh

cd "$(dirname "$0")"
srcdir=$(pwd)

# Limit the number of RSS feed entries.
limit=500

rss="$(curl -s http://sourceforge.net/api/file/index/project-id/202880/mtime/desc/limit/$limit/rss)"
if test $? -ne 0
then
	file="$(ls -1 mingw-w64-bin_i686-mingw_[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9].zip 2>/dev/null)"
	if test $? -ne 0
	then
		site=http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Automated%20Builds/

		echo "Could not download mingw-w64-bin_i686-mingw_\$date.zip"
		echo "If you do not have a direct network connection please go to"
		echo "	$site"
		echo "download the latest file, place it in $srcdir"
		echo "and restart this script"
		exit 1
	else
		file=$(echo "$file" | tail -n 1)
	fi
else
	link=$(echo "$rss" |
	     sed -nr "s/<link>(.+(mingw-w64-bin_i686-mingw_[0-9]+.zip).+)<\/link>/\2\t\1/p" |
	     head -1)
	file=$(echo "$link" | cut -f 1)
	url=$(echo "$link" | cut -f 2)

	# Trim whitespaces.
	file=$(echo $file)
	url=$(echo $url)

	# download it
	test -f $file || curl -L $url -o $file || exit
fi

# unpack & install it
test -f sysroot/.root.init.marker &&
test sysroot/.root.init.marker -nt $file ||
(mkdir -p sysroot &&
 cd sysroot &&
 unzip ../$file &&
 touch .root.init.marker
)

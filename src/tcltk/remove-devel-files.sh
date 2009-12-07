#!/bin/sh

cd "$(dirname "$0")"

index=$(/share/msysGit/pre-install.sh)

cat fileList-*.txt |
grep -e '\.\(h\|a\|sh\)$' -e '/demos/' > remove.txt &&
if test -s remove.txt
then
	# remove the files
	(cd / && xargs git rm -r) < remove.txt &&
	# update the file lists (for deinstallation/updating)
	for f in fileList-*.txt
	do
		# comm -23 $f remove.txt (but comm is not there)
		cat $f remove.txt remove.txt | sort | uniq -u > tmp.txt &&
		mv tmp.txt $f &&
		git add $f ||
		break
	done
fi &&
rm remove.txt ||
exit

/share/msysGit/post-install.sh $index 'Remove Tcl/Tk development files'

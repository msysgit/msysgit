#!/bin/sh

i=1
cd patches &&
ls *.patch |
while read patch
do
	ordered="$(printf "%04d-%s" $i "${patch#????-}")"
	test "$patch" = "$ordered" ||
	git mv "$patch" "$ordered" ||
	break
	i=$(($i+1))
done

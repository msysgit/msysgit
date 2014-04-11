#!/bin/sh

die () {
	echo "$*" >&2
	exit 1
}

test $# -ge 2 ||
die "Usage: $0 <tag-name> <path>..."

tagname="$1"
shift

url=https://api.github.com/repos/msysgit/msysgit/releases
id="$(curl --netrc -s $url |
	grep -B1 "\"tag_name\": \"$tagname\"" |
	sed -n 's/.*"id": *\([0-9]*\).*/\1/p')"
test -n "$id" || {
	out="$(curl --netrc -s -XPOST -d '{"tag_name":"'"$tagname"'"}' $url)" ||
	die "Error creating release: $out"
	id="$(echo "$out" |
		sed -n 's/.*"id": *\([0-9]*\).*/\1/p')"
	test -n "$id" ||
	die "Could not create release for tag $tagname"
}

url=https://uploads.${url#https://api.}

for path
do
	case "$path" in
	*.exe)
		contenttype=application/executable
		;;
	*.7z)
		contenttype=application/zip
		;;
	*)
		die "Unknown file type: $path"
		;;
	esac
	basename="$(basename "$path")"
	curl -i --netrc -XPOST -H "Content-Type: $contenttype" \
		--data-binary @"$path" "$url/$id/assets?name=$basename"
done

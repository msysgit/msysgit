#!/bin/sh

test $# = 2 || {
	echo "Usage: $0 <summary> <file>" >&2
	exit 1
}

python "$(dirname "$0")"/googlecode_upload.py -s "$1" -p msysgit \
	-u "$(cat "$(dirname "$0")"/.googlecode-user)" \
	-w "$(cat "$(dirname "$0")"/.googlecode-pwd)" "$2"

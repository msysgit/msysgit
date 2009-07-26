#!/bin/sh

die () {
	echo "$*" >&2
	exit 1
}

test $# = 0 &&
die "Usage: $0 <https hostname>"

cd "$(dirname "$0")" &&
host="$1"
host=${1#https://}
host=${host%%/*}

echo "Please press any key" >&2
out="$(openssl s_client -connect $host:443 </dev/null 2> /dev/null)" ||
die "Could not get certificate for $host"

mkdir -p certs &&
echo "$out" |
sed -n '/^-----BEGIN CERTIFICATE/,/^-----END CERTIFICATE/p' \
	> certs/$host.pem

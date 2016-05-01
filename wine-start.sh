#!/bin/sh

WINECONSOLE=wineconsole
REBASE=
while test $# -gt 0
do
	case "$1" in
	--no-console)
		WINECONSOLE=
		;;
	--rebase)
		REBASE=0x60000000
		;;
	--rebase=*)
		REBASE=${1#--rebase=}
		;;
	*)
		break
		;;
	esac
	shift
done

if test $# -gt 0
then
	echo "Unhandled options: $*" >&2
	exit 1
fi

cat << EOF
Please restart with --rebase if you see 'assertion "!inheap (s)" failed: ...'
EOF

die () {
	echo "$*" >&2
	exit 1
}

cd "$(dirname "$0")" &&
if test -n "$REBASE"
then
	(cd bin && wine ../mingw/bin/rebase.exe -b "$REBASE" msys-1.0.dll) ||
	die "Could not rebase msys-1.0.dll to $REBASE"
	git update-index --assume-unchanged bin/msys-1.0.dll ||
	cat << EOF
Did not find a (non-msysGit) git; please run

	git update-index --assume-unchanged /bin/msys-1.0.dll

when Git was compiled
EOF
fi &&
exec wine $WINECONSOLE bin/bash --login -i ||
echo "Failure to start Wine!"

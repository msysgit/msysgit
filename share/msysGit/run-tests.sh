#!/bin/sh

case "$1" in
-*)
	COUNT=$(echo "$1" | sed "s/-//")
	shift
;;
*)
	COUNT=9999
;;
esac

start_test="$1"

cd /git/t

: > /tmp/failed-tests.out

for test in t[0-9]*.sh
do
	case $test in
	$start_test*) start_test=;;
	*) continue;;
	esac

	printf '%70s ' $test
	if sh -x $test --no-symlinks -v > /tmp/test.out 2>&1
	then
		echo -e '\033[32mok\033[0m'
	else
		echo "*** $test" >> /tmp/failed-tests.out
		cat /tmp/test.out >> /tmp/failed-tests.out
		echo -e '\033[31mfailed\033[0m'
	fi
	COUNT=$(($COUNT-1))
	test $COUNT -gt 0 || break
done

test -s /tmp/failed-tests.out &&
echo "Do you want to see the output?" &&
read answer &&
case $answer in y*|Y*|j*|J*)
	less /tmp/failed-tests.out
esac


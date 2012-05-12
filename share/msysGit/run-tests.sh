#!/bin/sh

# This list was generated after a run of "make test" using generate_skip_list

export GIT_SKIP_TESTS='
'

#echo "$GIT_SKIP_TESTS" | tr '\n' ' '; exit
export NO_SVN_TESTS=t
case " $*" in
*' -j'*) ;;
*) PARALLEL_MAKE=-j15;;
esac

generate_skip_list () {
	cd /git/t
	for d in trash*
	do
		name=${d#trash directory.}
		short=${name%%-*}
		sh $name.sh |
		sed -n -e "s/.*FAIL \([0-9]*\).*/$short.\1/p" \
			-e "s/^not ok - \([0-9]*\).*/$short.\1/p"
	done
}

test generate_skip_list = "$1" && {
	generate_skip_list
	exit
}

get_test_name () {
	echo "$*" | sed 's/.* \(t[0-9].*\)\.sh .*/\1/'
}

get_finished_tests () {
	REMAINING_TESTS=
	for t in $CURRENT_TESTS
	do
		f=$(grep failed t/test-results/${t%.sh}-[1-9]* 2> /dev/null)
		if test ! -z "$f"
		then
			printf '%70s ' $(cd t && echo $t*.sh)
			if test "failed 0" = "$f"
			then
				echo -e '\033[32mok\033[0m'
			else
				FAILED_TESTS="$FAILED_TESTS $t"
				echo -e '\033[31mfailed\033[0m'
			fi
		else
			REMAINING_TESTS="$REMAINING_TESTS $t"
		fi
	done
	CURRENT_TESTS="$REMAINING_TESTS"
}

cd /usr/git &&
for file in *.exe
do
	dir=${file%.exe} &&
	test ! -d "$dir" ||
	rm -rf "$dir"
done &&
echo make $PARALLEL_MAKE &&
(cd t &&
 rm -rf test-results &&
 time make $PARALLEL_MAKE -k "$@" < /dev/null) 2>&1 |
(
 CURRENT_TESTS=
 FAILED_TESTS=
 while read line
 do
	case "$line" in
	"*** t"*)
		TEST_NAME=$(get_test_name "$line")
		CURRENT_TESTS="$CURRENT_TESTS $TEST_NAME"
		printf "$(echo "$CURRENT_TESTS" |
			sed 's/t\([0-9]*\)-[^ ]*/\1/g')\\r"
		;;
	'* passed'*|'# passed'*)
		get_finished_tests
		;;
	esac
 done
 test -z "$FAILED_TESTS" || echo "These tests failed: $FAILED_TESTS"
 test -z "$CURRENT_TESTS" || echo "Unfinished tests: $CURRENT_TESTS")

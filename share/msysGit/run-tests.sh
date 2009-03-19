#!/bin/sh

# This list was generated after a run of "make test" using generate_skip_list

export GIT_SKIP_TESTS='
t0060.2
t0060.5
t0060.6
t0060.7
t0060.9
t0060.10
t0060.11
t0060.12
t0060.13
t0060.14
t0060.15
t0060.16
t0060.17
t0060.18
t0060.19
t0060.21
t0060.22
t0060.23
t0060.24
t0060.25
t0060.32
t0060.42
t0060.43
t0060.44
t0060.46
t0060.49
t0060.50
t0060.52
t0060.53
t0060.58
t0060.59
t0060.60
t0060.61
t0060.62
t0060.63
t0060.64
t0060.65
t1301.2
t1301.3
t1504.23
t1504.24
t1504.25
t4252.7
t6031.1
t6031.2
t7502.18
t7502.19
'

#echo "$GIT_SKIP_TESTS" | tr '\n' ' '; exit
export NO_SVN_TESTS=t
case " $*" in
*' -j'*) ;;
*) PARALLEL_MAKE=-j5;;
esac

generate_skip_list () {
	cd /git/t
	for d in trash*
	do
		name=${d#trash directory.}
		short=${name%%-*}
		sh $name.sh |
		sed -n "s/.*FAIL \([0-9]*\).*/$short.\1/p"
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

cd /git &&
echo make $PARALLEL_MAKE &&
(cd t &&
 rm -rf test-results &&
 time make $PARALLEL_MAKE -k "$@") 2>&1 |
(
 CURRENT_TESTS=
 FAILED_TESTS=
 while read line
 do
	case "$line" in
	"*** t"*)
		TEST_NAME=$(get_test_name "$line")
		CURRENT_TESTS="$CURRENT_TESTS $TEST_NAME"
		printf "Currently running $(echo "$CURRENT_TESTS" |
			sed 's/-[^ ]*//g')\\r"
		;;
	'* passed'*)
		get_finished_tests
		;;
	esac
 done
 test -z "$FAILED_TESTS" || echo "These tests failed: $FAILED_TESTS"
 test -z "$CURRENT_TESTS" || echo "Unfinished tests: $CURRENT_TESTS")

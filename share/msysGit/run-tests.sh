#!/bin/sh

# This list was generated after a run of "make test" using generate_skip_list

export GIT_SKIP_TESTS='
t1300.70
t1300.71
t5000.12
t5530.6
t5560.2
t5560.3
t5560.4
t5560.5
t5560.6
t5560.7
t5560.8
t5560.9
t5560.10
t5560.11
t5560.12
t5560.13
t7602.3
t7602.4
t7602.5
t9001.8
t9001.10
t9001.12
t9500.1
t9500.2
t9500.3
t9500.4
t9500.5
t9500.6
t9500.7
t9500.8
t9500.10
t9500.11
t9500.12
t9500.13
t9500.14
t9500.15
t9500.16
t9500.17
t9500.18
t9500.19
t9500.20
t9500.21
t9500.22
t9500.23
t9500.24
t9500.25
t9500.26
t9500.27
t9500.28
t9500.29
t9500.30
t9500.32
t9500.33
t9500.34
t9500.35
t9500.36
t9500.38
t9500.39
t9500.40
t9500.41
t9500.42
t9500.43
t9500.44
t9500.45
t9500.47
t9500.48
t9500.50
t9500.51
t9500.52
t9500.53
t9500.54
t9500.55
t9500.56
t9500.57
t9500.58
t9500.59
t9500.60
t9500.61
t9500.62
t9500.63
t9500.64
t9500.65
t9500.66
t9500.67
t9500.68
t9500.69
t9500.70
t9500.71
t9500.72
t9500.73
t9500.74
t9500.75
t9500.76
t9500.77
t9500.78
t9500.79
t9500.80
t9500.81
t9500.82
t9500.83
t9500.84
t9500.85
t9500.86
t9500.87
t9501.1
t9501.2
t9501.3
t9501.4
t9501.5
t9501.6
t9501.7
t9501.8
t9501.9
t9501.10
t9502.2
t9502.3
t9502.4
t9502.5
t9502.6
t9502.7
t9502.8
t9502.9
t9502.10
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

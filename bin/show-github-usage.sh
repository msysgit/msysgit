#!/bin/sh

USAGE="$0"' <options>...

Get the amount of kB used by the msysGit organization

Options:
	--user		<github-account>	(required)
'

user=
repository=
while test $# -gt 0
do
	case "$1" in
	--user)
		test $# -gt 1 || {
			echo "Option '$1' needs a value" >&2
			exit 1
		}
		eval ${1#--}="$2"
		shift
		;;
	--user=*)
		pair="${1#--}"
		eval ${pair%%=*}="${pair#*=}"
		;;
	--help)
		echo "$USAGE"
		exit 1
		;;
	*)
		break;
	esac
	shift
done

test -z "$user" &&
user="$(grep -A2 -i '^machine  *api.github.com' < "$HOME/.netrc" 2> /dev/null |
	sed -n 's|login  *||pi')"

test -n "$user" || {
	echo "$USAGE"
	exit 1
}

get_password () { # args: user host
	# try $HOME/.netrc; ignore <user> parameter first
	password="$(grep -A2 -i "^machine  *$2" < $HOME/.netrc 2> /dev/null |
		sed -n 's|^password  *||p')"
	test -z "$password" &&
	password="$(git gui--askpass "Password for $1@$2")"
	echo "$password"
}

json_get () { # args: key json
	echo "$2" |
	sed -n -s \
		-e "s|^ *\"$1\" *: *\"\(.*\)\",\?$|\1|p" \
		-e "s|^ *\"$1\" *: *\([^\"]*[^\",]\),\?$|\1|p"
}

password="$(get_password "$user" "api.github.com")"
test -n "$password" || exit

# get disk usage
json="$(curl -s \
	-XPATCH \
	-i \
	-d '{}' \
	-u "$user:$password" \
	https://api.github.com/orgs/msysgit)"

echo "Disk usage: $(json_get disk_usage "$json")kB"

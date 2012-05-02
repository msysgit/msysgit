#!/bin/sh

# Written with a lot of assistance by Scott Chacon

USAGE="$0"' <options>... <filepath>
Options:
	--description	<download-description>	(required)
	--user		<github-account>	(required)
	--repository	<github-repository>	(required)
'

description=
user=
repository=
filepath=
filesize=
basename=
dryrun=
while test $# -gt 0
do
	case "$1" in
	--description|--user|--repository)
		test $# -gt 1 || {
			echo "Option '$1' needs a value" >&2
			exit 1
		}
		eval ${1#--}="\"$2\""
		shift
		;;
	--description=*|--user=*|--repository=*)
		pair="${1#--}"
		eval ${pair%%=*}="${pair#*=}"
		;;
	--dry-run)
		dryrun=YouGotThatRight
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

if test $# -ne 1 || ! test -f "$1"
then
	echo "$USAGE"
	exit 1
fi

filepath="$1"
filesize="$(stat -c %s "$filepath")"
basename="$(basename "$filepath")"

# extract 'for version <version>' from basename
for_version=${basename%-preview*}
for_version=${for_version##*Git-}
for_version=${for_version##*install-}
for_version="for official Git for Windows $for_version"

case "$basename" in
Git-*)
	description="${description:-Full installer $for_version}"
	repository=${repository:-msysgit/git}
	;;
PortableGit-*)
	description="${description:-Portable application $for_version}"
	repository=${repository:-msysgit/git}
	;;
msysGit-netinstall-*)
	description="${description:-Net installer if you want to hack on Git}"
	repository=${repository:-msysgit/git}
	;;
msysGit-fullinstall-*)
	description="${description:-Full installer (self-contained) if you want to hack on Git}"
	repository=${repository:-msysgit/git}
	;;
esac

test -z "$user" &&
user="$(grep -A2 -i '^machine  *api.github.com' < "$HOME/.netrc" 2> /dev/null |
	sed -n 's|login  *||pi')"

if test -z "$description" || test -z "$user" || test -z "$repository"
then
	echo "$USAGE"
	exit 1
fi

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
        sed -n -s "s|^ *\"$1\" *: *\"\(.*\)\",\?$|\1|p"
}

json_wrap () { # args: key1, value1, [key2, value2], ...
	printf '{'
	sep=
	while test $# -gt 1
	do
		printf '%s"%s":"%s"' "$sep" "$1" "$2"
		sep=,
		shift
		shift
	done
	printf '}'
}

windowsfilepath="$(cd "$(dirname "$filepath")" && pwd -W)\\$basename"

test -n "$dryrun" && {
	cat << EOF
basename:	$basename
size:		$filesize
description:	$description
user:		$user
repository:	$repository
EOF
	exit 0
}

password="$(get_password "$user" "api.github.com")"
test -n "$password" || exit

# get ticket
json="$(curl -XPOST \
	-d "$(json_wrap \
		name "$basename" \
		size "$filesize" \
		description "$description")" \
	-u "$user:$password" \
	https://api.github.com/repos/$repository/downloads)"

# upload for real, using S3
result="$(curl \
	-F key="$(json_get path "$json")" \
	-F acl="$(json_get acl "$json")" \
	-F success_action_status=201 \
	-F Filename="$(json_get name "$json")" \
	-F AWSAccessKeyId="$(json_get accesskeyid "$json")" \
	-F Policy="$(json_get policy "$json")" \
	-F Signature="$(json_get signature "$json")" \
	-F Content-Type="$(json_get mime_type "$json")" \
	-F file=@"$windowsfilepath" \
	"$(json_get s3_url "$json")")"

echo "$result"

# Verify that the upload was successful
case "$result" in
*"<Location>"*"</Location>"*)
	echo "Success!"
	;;
*)
	exit 1
	;;
esac

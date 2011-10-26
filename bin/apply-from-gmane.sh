#!/bin/sh

URL="$1"

case "$URL" in
http://thread.*) URL=http://article.${URL#http://thread.};;
http://*|article.gmane.org*) ;;
*@*)
	TMP=.git/apply.tmp
	curl -D $TMP http://mid.gmane.org/$1 > /dev/null
	URL=$(sed -n 's/^Location: //p' < $TMP);;
*) URL=http://article.gmane.org/gmane.comp.version-control.msysgit/$1;;
esac

case "$URL" in
*/raw) ;;
*) URL=${URL%/}/raw;;
esac

curl $URL | git am --whitespace=fix -s

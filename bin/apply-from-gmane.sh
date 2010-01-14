#!/bin/sh

URL="$1"

case "$URL" in
http://*|article.gmane.org*) ;;
*) URL=http://article.gmane.org/gmane.comp.version-control.msysgit/$1;;
esac

case "$URL" in
*/raw) ;;
*) URL=$URL/raw;;
esac

curl $URL | git am -s

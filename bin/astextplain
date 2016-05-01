#!/bin/sh -e
# minimalistic replacement for `run-mailcap --action=cat <file>`

if test "$#" != 1 ; then
	echo "Usage: astextplain <file>" 1>&2
	exit 1
fi

# XXX output encoding (UTF-8) hardcoded
case "$1" in
	*.doc | *.DOC | *.dot | *.DOT)
		antiword -m UTF-8 "$1" || cat "$1"
		;;
	*.docx | *.DOCX)
		docx2txt "$1" -
		;;
	*.pdf | *.PDF)
		pdftotext -layout "$1" -enc UTF-8 -
		;;
	# TODO add rtf support
	*.rtf | *.RTF)
		cat "$1"
		;;
	*)
		echo "E: unsupported filetype $1" 1>&2
		exit 1
		;;
esac

exit 0

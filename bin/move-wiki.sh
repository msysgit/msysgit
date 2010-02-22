#!/bin/sh

case $(uname -s) in
MINGW*)
	EDITOR=wordpad
	START=start
	;;
Linux)
	EDITOR=gedit
	START=xdg-open
	;;
esac

OLDWIKISVN=http://msysgit.googlecode.com/svn/wiki
NEWWIKI=http://git.wiki.kernel.org/index.php
NAMESPACE=MSysGit

transform () {
	perl -e 'while (<>) {
		if ($_ eq "{{{\n") {
			print "<code>\n";
			while (<>) {
				last if ($_ eq "}}}\n" || $_ eq "}}}");
				print $_;
			}
			print "</code>\n";
			next;
		}
		s/^#.*/<!-- $& -->/;
		s/{{{(.*?)}}}/<code>$1<\/code>/g;
		s/`(.*?)`/<code>$1<\/code>/g;
		s/_(.*?)_/'\'''\''$1'\'''\''/g;
		s/\*(.*?)\*/'\'''\'''\''$1'\'''\'''\''/g;
		s/(?<=\s)!([A-Z])/$1/g;
		s/(?<!\[)\[(?![a-z]*:)([^\] ]+) +([^\]]+)\]/[[MSysGit:$1|$2]]/g;
		s/(?<!\[)\[(?![a-z]*:)([^\] ]+)\]/[[MSysGit:$1|$1]]/g;
		s/^ \*/*/;
		s/(\s)_(\S[^_]*\S)_(\s)/$1<u>$2<\/u>$3/g;
		print $_;
	}
	print "\n[[Category:MSysGit]]\n";
	'
}

download () {
	curl $OLDWIKISVN/"$1".wiki
}

download_index () {
	curl $OLDWIKISVN/ |
	sed -n 's/.*>\([^<]*\)\.wiki<.*/\1/p'
}

action () {
	download "$1" > /tmp/"$1".old &&
	transform < /tmp/"$1".old > /tmp/"$1".wiki &&
	$START $NEWWIKI?title="$NAMESPACE:$1&action=edit" &&
	$EDITOR /tmp/"$1".wiki &&
	rm /tmp/"$1".old /tmp/"$1".wiki
}

test $# = 0 && set $(download_index)

for arg
do
	action $arg
done

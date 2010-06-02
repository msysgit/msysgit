#!/usr/bin/perl

if (@ARGV != 1) {
	print STDERR <<EOF;
Usage: <script> <date-or-commit>
EOF
	exit(1);
}

use Date::Parse;
use HTML::Entities;

my $since = `git show -s --format=%ct $ARGV[0]^0 2> /dev/null`;
chomp($since);
if ($since eq '') {
	$since = str2time($ARGV[0]);
}

$url = 'http://code.google.com/p/msysgit/updates/list?num=50&start=';

my ($offset, $date, $issue, $oneline);

sub get_fixes ($) {
	$offset = shift;

	open IN, 'curl -s "' . $url . $offset . '" |';
	while (<IN>) {
		if (/<span class="date below-more" title="([^"]+)"/) {
			$date = str2time($1);
			if ($date < $since) {
				close IN;
				return 0;
			}
		}
		elsif (/<a class="ot-issue-link" [^>]*>([^<]+)</) {
			$issue = $1;
			$_ = <IN>;
			if (/^\s*\((.+)\) Status changed/) {
				$oneline = decode_entities($1);
				while (<IN>) {
					if (/^<\/div>/) {
						last;
					}
					if (/<span class="ot-issue-field-value">Fixed<\/span>/) {
						print "Issue $issue ($oneline) was fixed\n";
					}
				}
			}
		}
	}
	close IN;
	return 1;
}

for (my $off = 0; $off < 250 && get_fixes($off); $off += 50) {
	# do nothing
}

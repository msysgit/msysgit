#!/usr/bin/perl

if (@ARGV != 1) {
	print STDERR <<EOF;
Usage: <script> <date-or-commit>
EOF
	exit(1);
}

# do not use Date::Parse; which is not installed on msysGit

sub str2time($) {
	my $date = shift;
	my $result = `date -d "$date" +%s`;
	chomp $result;
	return $result;
}

# do not use HTML::Entities; which is not installed on msysGit

sub decode_entities($) {
	my $html = shift;
	$html =~ s/&quot;/"/g;
	$html =~ s/&lt;/</g;
	$html =~ s/&gt;/>/g;
	# must be last one
	$html =~ s/&amp;/\&/g;
	return $html;
}

my $since = `git show -s --format=%ct $ARGV[0]^0 2> /dev/null`;
chomp($since);
if ($since eq '') {
	$since = str2time($ARGV[0]);
}

$url = 'http://code.google.com/p/msysgit/issues/list?can=1&num=10000&q=status:';
$issue_url = 'http://code.google.com/p/msysgit/issues/detail?id=';

sub test_issue ($$) {
	my $since = shift;
	my $id = shift;
	my $subject = '<no subject>';
	my $fix_count = 0;
	my $fix_date = 0;
	my $cur_date = 0;
	open ISSUE, 'curl -s "' . $issue_url . $id . '" |';
	while (<ISSUE>) {
		if (/<span class="h3" >([^<]+)<\/span>/) {
			$subject = decode_entities($1);
		}
		elsif (/<span class="date" title="([^"]+)">/) {
			$cur_date = str2time($1);
		}
		elsif (/<b>Status:<\/b> Fixed/) {
			$fix_count++;
			$fix_date = $cur_date;
		}
	}
	close ISSUE;
	if ($fix_date >= $since) {
		my $fixed = "fixed";
		if ($fix_count > 1) {
			$fixed = "fixed again";
		}
		print "Issue $id ($subject) was $fixed\n";
	}
}

sub get_issues ($$) {
	my $since = shift;
	my $status = shift;

	open IN, 'curl -s "' . $url . $status . '" |';
	while (<IN>) {
		if (/<td class="vt id col_0"><a href="detail\?id=(\d+)">\d+<\/a><\/td>/) {
			test_issue($since, $1);
		}
	}
	close IN;
	return 1;
}

get_issues($since, 'Fixed');

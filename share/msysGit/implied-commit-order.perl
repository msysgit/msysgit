#!/usr/bin/perl

# List the given commit range similar to "git log --graph" but instead of
# showing the branches as recorded in the commits, show the implicit commit
# hierarchy as far as merge conflicts are concerned: a commit is considered an
# "implicit ancestor" of a descendant commit if exchanging both in the commit
# history would cause merge conflicts, i.e. if their changes overlap.
#
# The idea originates from the Darcs SCM which -- while its underlying idea is
# cool, and replicated in this Perl script -- was doomed by the choice of
# programming language and by trying to describe the principle via quantum
# physics (when the proper scientific background would have been group theory,
# really, although that would have been even worse a vehicle to document the
# motivation and implementation).

# list of all commits, in order
my @commits = ();
# maps short commit names to long ones
my %short2long = ();
# maps commit -> parents
my %forward = ();
# maps commit -> children
my %backward = ();
# maps commit -> file_name -> hunk list
# where hunk list is a struct returned by hunks_data()
my %commit_changes = ();

sub ordered_set () {
	my @list = ();
	my %seen = ();
	my $add = sub ($) {
		if ($seen{$_[0]} eq undef) {
			push(@list, $_[0]);
			$seen{$_[0]} = $#list;
		}
	};
	return {
		'add' => $add,
		'remove' => sub ($) {
			my $index = $seen{$_[0]};
			return if $index eq undef;
			delete $seen{$_[0]};
			splice(@list, $index, 1);
			for (; $i <= $#list; $i++) {
				$seen{$list[$i]} = $i;
			}
		},
		'contains' => sub ($) {
			return $seen{$_[0]} ne undef;
		},
		'merge' => sub ($) {
			map { &$add($_) } @{$_[0]->{'list'}()};
		},
		'clone' => sub () {
			my $cloned = ordered_set();
			map { $cloned->{'add'}($_) } @list;
			return $cloned;
		},
		'list' => sub () {
			return \@list;
		}
	};
}

sub imply_parents ($$) {
	my $child = $_[0];
	my $parents = $_[1];

	foreach my $parent(@$parents) {
		next if $child eq $parent;

		$forward{$child} = ordered_set() if $forward{$child} eq undef;
		return if ($forward{$child}->{'contains'}($parent));
		$forward{$child}->{'add'}($parent);
		$backward{$parent} = ordered_set() if $backward{$parent} eq undef;
		$backward{$parent}->{'add'}($child);
	}
}

sub hunks_data () {
	my @begin = ();
	my @end = ();
	my @revisions = ();

	my $insert = sub ($$$$) {
		splice(@begin, $_[0], 0, $_[1]);
		splice(@end, $_[0], 0, $_[2]);
		splice(@revisions, $_[0], 0, $_[3]);
	};
	return {
		'size' => sub () {
			return $#end;
		},
		'begin' => \@begin,
		'end' => \@end,
		'revisions' => \@revisions,
		'add' => sub ($$$) {
			push(@begin, $_[0]);
			push(@end, $_[1]);
			if (ref($_[2]) ne 'HASH') {
				my $set = ordered_set();
				$set->{'add'}($_[2]);
				$_[2] = $set;
			}
			push(@revisions, $_[2]);
		},
		'merge' => sub ($) {
			my @begin2 = @{$_[0]->{'begin'}};
			my @end2 = @{$_[0]->{'end'}};
			my @revisions2 = @{$_[0]->{'revisions'}};
			my $i = 0;
			my $j = 0;
			while ($i <= $#end && $j <= $#end2) {
				if ($begin[$i] >= $end2[$j]) {
					&$insert($i, $begin2[$j], $end2[$j], $revisions2[$j]);
					$j++;
				} elsif ($end[$i] > $begin2[$j]) {
					if ($begin[$i] < $begin2[$j]) {
						&$insert($i, $begin[$i], $begin2[$j], $revisions[$i]->{'clone'}());
						$i++;
					} elsif ($begin1 > $begin2[$j]) {
						&$insert($i, $begin2[$j], $begin[$i], $revisions2[$j]->{'clone'}());
						$i++;
					}
					if ($end[$i] < $end2[$j]) {
						&$insert($i + 1, $end[$i], $end2[$j], $revisions2[$j]->{'clone'}());
						$revisions[$i]->{'merge'}($revisions2[$j]);
						$i++;
					} elsif ($end[$i] > $end2[$j]) {
						&$insert($i + 1, $end2[$j], $end[$i], $revisions[$i]->{'clone'}());
						$revisions[$i]->{'merge'}($revisions2[$j]);
						$i++;
					} else {
						$revisions[$i]->{'merge'}($revisions2[$j]);
					}
				}
				$i++;
			}
			while ($j <= $#end2) {
				push(@begin, $begin2[$j]);
				push(@end, $end2[$j]);
				push(@revisions, $revisions2[$j]);
				$j++;
			}
		},
		# merge-weakly merges only the specified hunks which do not overlap with the current ones.
		'merge-weakly' => sub ($) {
			my @begin2 = @{$_[0]->{'begin'}};
			my @end2 = @{$_[0]->{'end'}};
			my @revisions2 = @{$_[0]->{'revisions'}};
			my $i = 0;
			my $j = 0;
			while ($i <= $#end && $j <= $#end2) {
				if ($begin[$i] >= $end2[$j]) {
					&$insert($i, $begin2[$j], $end2[$j], $revisions2[$j]);
					$j++;
				} elsif ($end[$i] > $begin2[$j]) {
					if ($begin1 > $begin2[$j]) {
						&$insert($i, $begin2[$j], $begin[$i], $revisions2[$j]->{'clone'}());
						$i++;
					}
					if ($end[$i] < $end2[$j]) {
						&$insert($i + 1, $end[$i], $end2[$j], $revisions2[$j]->{'clone'}());
						$i++;
					}
				}
				$i++;
			}
			while ($j <= $#end2) {
				push(@begin, $begin2[$j]);
				push(@end, $end2[$j]);
				push(@revisions, $revisions2[$j]);
				$j++;
			}
		},
		'clone-for-hunk-adjustment' => sub () {
			my $clone = hunks_data();
			my @hunks = ();
			$clone->{'hunk'} = sub ($$$$) {
				push(@hunks, @_);
			};
			$clone->{'finish'} = sub () {
				my $i = 0, $offset = 0;
				while ($i <= $#end) {
					last if $#hunks < 0;
					if ($end[$i] < $hunks[0]) {
						$clone->{'add'}($offset + $begin[$i], $offset + $end[$i], $revisions[$i]);
					} elsif ($begin[$i] > $hunks[1]) {
						$offset = $hunks[3] - $hunks[1];
						splice(@hunks, 0, 4);
						next;
					} else {
						my $begin2 = $begin[$i] < $hunks[0] ? $begin[$i] + $offset : $hunks[2];
						$offset = $hunks[3] - $hunks[1];
						my $end2 = $end[$i] <= $hunks[1] ? $hunks[2] : $end[$i] + $offset;
						$clone->{'add'}($begin2, $end2, $revisions[$i]);
					}
					$i++;
				}
				while ($i <= $#end) {
					$clone->{'add'}($offset + $begin[$i], $offset + $end[$i], $revisions[$i]);
					$i++;
				}
				delete $clone->{'hunk'};
				delete $clone->{'finish'};
			};
			return $clone;
		},
		'implied-revisions' => sub ($) {
			my @begin2 = @{$_[0]->{'begin'}};
			my @end2 = @{$_[0]->{'end'}};
			my @revisions2 = @{$_[0]->{'revisions'}};
			my $i = 0;
			my $j = 0;
			my $result = ordered_set();
			while ($i <= $#end && $j <= $#end2) {
				if ($end[$i] < $begin2[$j]) {
					$i++;
				} elsif ($begin[$i] > $end2[$j]) {
					$j++;
				} else {
					$result->{'merge'}($revisions2[$j]);
					$j++;
				}
			}
			return $result->{'list'}();
		}
	};
}

sub handle_single_parent ($$$$$) {
	my $current_commit = $_[0];
	my $in = $_[1];
	my %original_parent_changes = %{$_[2]};
	my $changes = $_[3];
	my $parent_changes = $_[4];

	my $file_name;
	my $hunks = undef;
	my $parent_hunks = undef;
	my %handled_files = ();

	my $finish_file = sub () {
		if ($hunks ne undef) {
			if ($changes->{$file_name} eq undef) {
				$changes->{$file_name} = $hunks;
			} else {
				$changes->{$file_name}->{'merge'}($hunks);
			}
		}
		if ($parent_hunks ne undef) {
			$parent_hunks->{'finish'}();
			if ($parent_changes->{$file_name} eq undef) {
				$parent_changes->{$file_name} = $parent_hunks;
			} else {
				$parent_changes->{$file_name}->{'merge'}($parent_hunks);
			}
		}
		$handled_files{$file_name} = 1 if $file_name ne undef;
	};

	while (<$in>) {
		# TODO: handle spaces and even " b/" as part of a filename
		if (/^diff --git a\/.* b\/(.*)$/) {
			&$finish_file();
			$file_name = $1;
			$hunks = hunks_data();
			$parent_hunks = $original_parent_changes{$file_name};
			$parent_hunks = $parent_hunks->{'clone-for-hunk-adjustment'}() if $parent_hunks ne undef;
		} elsif (/^@@ -(\d+)(,(\d+))? \+(\d+)(,(\d+))? @@/) {
			my $length0 = $3 ne '' ? $3 : 1;
			my $begin0 = $1 + ($3 eq '0' ? 1 : 0);
			my $end0 = $begin0 + $length0;
			my $length1 = $6 ne '' ? $6 : 1;
			my $begin1 = $4 + ($6 eq '0' ? 1 : 0);
			my $end1 = $begin1 + $length1;

			$hunks->{'add'}($begin1, $end1, $current_commit);
			$parent_hunks->{'hunk'}($begin0, $end0, $begin1, $end1) if $parent_hunks ne undef;
		}
	}
	&$finish_file();

	foreach my $file_name (keys %original_parent_changes) {
		if ($handled_files{$file_name} eq undef) {
			my $hunks = $original_parent_changes{$file_name};
			if ($parent_changes->{$file_name} eq undef) {
				$parent_changes->{$file_name} = $hunks;
			} else {
				$parent_changes->{$file_name}->{'merge'}($hunks);
			}
		}
	}
}

# Reads the diff(s) associated with the (merge) commit into the global data
# structures. Takes previously read information about ancestors into account.
# After this method has been called on all the commits of interest,
# $commit_changes{$commit} will refer to a hash that maps all touched files to
# the respective hunk lists (that document what commits touched which parts,
# sort of a simultaneous `git blame`).

sub read_commit ($$) {
	my $current_commit = $_[0];
	my @parents = @{$_[1]};
	my %changes = ();
	my %parent_changes = ();
	$commit_changes{$current_commit} = \%changes;

	# use the empty tree to compare initial commits against
	@parents = ( '4b825dc642cb6eb9a060e54bf8d69288fbee4904' ) if $#parents < 0;
	foreach my $parent (@parents) {
		my $original_parent_changes = $commit_changes{$parent};

		my @command = ('git', 'diff', '-U0', # '-M',
			$parent, $current_commit);
		open(my $in, '-|', @command);
		handle_single_parent($current_commit, $in, $original_parent_changes, \%changes, \%parent_changes);
		close($in);
	}

	foreach my $file_name (keys %changes) {
		my $parent_hunks = $parent_changes{$file_name};
		next if $parent_hunks eq undef;
		my $hunks = $changes{$file_name};
		imply_parents($current_commit, $hunks->{'implied-revisions'}($parent_hunks));
		$hunks->{'merge-weakly'}($parent_hunks);
	}

	map { $changes{$_} = $parent_changes{$_} if $changes{$_} eq undef; } keys %parent_changes;

}

# Reads all necessary information for the commit range specified by the argument
# which is expected to be a reference to an array of command-line arguments
# appropriate for being called with `git log`.

sub read_commits ($) {
	my $commit_range = $_[0];
	my $current;
	my @parents;
	my %parent_changes;

	my $previous_file_name;
	my $current_file;
	my @current_file_changes;
	my @parent_file_changes;
	my $offset;

	my @command = ('git', 'log', '--reverse', '--topo-order',
		'--format=%H %h %p');
	# TODO: filter out --graph and stuff
	push(@command, @$commit_range);
	my $i = 1;
	open (my $in, '-|', @command);
	while (<$in>) {
		next if (/^$/);
		print $i++ . "...\r";
		chomp;
		if (/^([0-9a-f]+) ([0-9a-f]+) ([0-9a-f ]*)$/) {
			my $sha1 = $1;
			$current = $2;
			@parents = split(/ /, $3);

			push(@commits, $current);
			$short2long{$current} = $sha1;
			read_commit($current, \@parents);
		}
	}
	close($in);
}

my $use_gitk = 0;
my $simplify = 1;
my $dashdash = -1;
for (my $i = 0; $i <= $#ARGV; $i++) {
	if ($ARGV[$i] eq '--') {
		$dashdash = $i;
		last;
	}
	if ($ARGV[$i] eq '--gitk') {
		$use_gitk = 1;
	} elsif ($ARGV[$i] eq '--simplify') {
		$simplify = 1;
	} elsif ($ARGV[$i] eq '--no-simplify') {
		$simplify = 0;
	} else {
		next;
	}
	splice(@ARGV, $i, 1);
	$i--;
}

read_commits(\@ARGV);

sub get_parents ($) {
	my $parents = $forward{$_[0]};
	return [] if $parents eq undef;
	return $parents->{'list'}();
}

# We can simplify the implied history by skipping parents that are ancestors of
# other parents (e.g. if a commit is already an implied grandparent, it does
# not have to be an implied parent, too).

if ($simplify) {
	foreach my $current (@commits) {
		my @stack = ();
		my %seen = ();
		my %parents = ();
		foreach my $parent (@{get_parents($current)}) {
			$parents{$parent} = 1;
			foreach my $grampy (@{get_parents($parent)}) {
				push(@stack, $grampy);
			}
		}
		while ($#stack >= 0) {
			my $commit = pop(@stack);
			next if $seen{$commit} ne undef;
			if ($parents{$commit} ne undef) {
				$forward{$current}->{'remove'}($commit);
				delete $parents{$commit};
			}
			foreach my $parent (@{get_parents($commit)}) {
				push(@stack, $parent);
			}
			$seen{$commit} = 1;
		}
	}
}

# Unfortunately, there is no scriptable way to use the --graph support of `git
# log`.
#
# Fortunately, however, there is a way to circumvent that: by defining the
# commit order using temporary grafts, written into a temporary file and used
# via a temporary GIT_GRAFT_FILE env variable.

my $git_dir = `git rev-parse --git-dir`;
chomp $git_dir;

sub show () {
	my $grafts_file = $git_dir . '/TEMP-GRAFTS';
	my @args = ('log', '--graph', '--format=%h %s%n');
	open(my $grafts, '>', $grafts_file);
	foreach my $current (@commits) {
		push(@args, $current) if $backward{$current} eq undef;
		print $grafts $short2long{$current};
		if (ref($forward{$current}) eq 'HASH') {
			foreach my $parent (@{$forward{$current}->{'list'}()}) {
				my $sha1 = $short2long{$parent};
				if ($sha1 ne undef) {
					print $grafts ' ' . $sha1;
				}
			}
		}
		print $grafts "\n";
	}
	close($grafts);
	$ENV{'GIT_GRAFT_FILE'} = $grafts_file;
	push(@args, '--');
	# add file arguments from @ARGV
	for (my $i = 0; $i <= $#ARGV; $i++) {
		next if $ARGV[$i] ne '--';
		$i++;
		push(@args, @ARGV[$i..$#ARGV]) if $i <= $#ARGV;
		last;
	}
	if ($use_gitk) {
		splice(@args, 0, 3);
		exec('gitk', @args);
	}
	exec('git', @args);
}

show();

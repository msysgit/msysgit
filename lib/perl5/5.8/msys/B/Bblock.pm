package B::Bblock;

our $VERSION = '1.02_01';

use Exporter ();
@ISA = "Exporter";
@EXPORT_OK = qw(find_leaders);

use B qw(peekop walkoptree walkoptree_exec
	 main_root main_start svref_2object
         OPf_SPECIAL OPf_STACKED );

use B::Concise qw(concise_cv concise_main set_style_standard);
use strict;

my $bblock;
my @bblock_ends;

sub mark_leader {
    my $op = shift;
    if ($$op) {
	$bblock->{$$op} = $op;
    }
}

sub remove_sortblock{
    foreach (keys %$bblock){
        my $leader=$$bblock{$_};	
	delete $$bblock{$_} if( $leader == 0);   
    }
}
sub find_leaders {
    my ($root, $start) = @_;
    $bblock = {};
    mark_leader($start) if ( ref $start ne "B::NULL" );
    walkoptree($root, "mark_if_leader") if ((ref $root) ne "B::NULL") ;
    remove_sortblock();
    return $bblock;
}

# Debugging
sub walk_bblocks {
    my ($root, $start) = @_;
    my ($op, $lastop, $leader, $bb);
    $bblock = {};
    mark_leader($start);
    walkoptree($root, "mark_if_leader");
    my @leaders = values %$bblock;
    while ($leader = shift @leaders) {
	$lastop = $leader;
	$op = $leader->next;
	while ($$op && !exists($bblock->{$$op})) {
	    $bblock->{$$op} = $leader;
	    $lastop = $op;
	    $op = $op->next;
	}
	push(@bblock_ends, [$leader, $lastop]);
    }
    foreach $bb (@bblock_ends) {
	($leader, $lastop) = @$bb;
	printf "%s .. %s\n", peekop($leader), peekop($lastop);
	for ($op = $leader; $$op != $$lastop; $op = $op->next) {
	    printf "    %s\n", peekop($op);
	}
	printf "    %s\n", peekop($lastop);
    }
}

sub walk_bblocks_obj {
    my $cvref = shift;
    my $cv = svref_2object($cvref);
    walk_bblocks($cv->ROOT, $cv->START);
}

sub B::OP::mark_if_leader {}

sub B::COP::mark_if_leader {
    my $op = shift;
    if ($op->label) {
	mark_leader($op);
    }
}

sub B::LOOP::mark_if_leader {
    my $op = shift;
    mark_leader($op->next);
    mark_leader($op->nextop);
    mark_leader($op->redoop);
    mark_leader($op->lastop->next);
}

sub B::LOGOP::mark_if_leader {
    my $op = shift;
    my $opname = $op->name;
    mark_leader($op->next);
    if ($opname eq "entertry") {
	mark_leader($op->other->next);
    } else {
	mark_leader($op->other);
    }
}

sub B::LISTOP::mark_if_leader {
    my $op = shift;
    my $first=$op->first;
    $first=$first->next while ($first->name eq "null");
    mark_leader($op->first) unless (exists( $bblock->{$$first}));
    mark_leader($op->next);
    if ($op->name eq "sort" and $op->flags & OPf_SPECIAL
	and $op->flags & OPf_STACKED){
        my $root=$op->first->sibling->first;
        my $leader=$root->first;
        $bblock->{$$leader} = 0;
    }
}

sub B::PMOP::mark_if_leader {
    my $op = shift;
    if ($op->name ne "pushre") {
	my $replroot = $op->pmreplroot;
	if ($$replroot) {
	    mark_leader($replroot);
	    mark_leader($op->next);
	    mark_leader($op->pmreplstart);
	}
    }
}

# PMOP stuff omitted

sub compile {
    my @options = @_;
    B::clearsym();
    if (@options) {
	return sub {
	    my $objname;
	    foreach $objname (@options) {
		$objname = "main::$objname" unless $objname =~ /::/;
		eval "walk_bblocks_obj(\\&$objname)";
		die "walk_bblocks_obj(\\&$objname) failed: $@" if $@;
		print "-------\n";
		set_style_standard("terse");
		eval "concise_cv('exec', \\&$objname)";
		die "concise_cv('exec', \\&$objname) failed: $@" if $@;
	    }
	}
    } else {
	return sub {
	    walk_bblocks(main_root, main_start);
	    print "-------\n";
	    set_style_standard("terse");
	    concise_main("exec");
	};
    }
}

# Basic block leaders:
#     Any COP (pp_nextstate) with a non-NULL label
#     [The op after a pp_enter] Omit
#     [The op after a pp_entersub. Don't count this one.]
#     The ops pointed at by nextop, redoop and lastop->op_next of a LOOP
#     The ops pointed at by op_next and op_other of a LOGOP, except
#     for pp_entertry which has op_next and op_other->op_next
#     The op pointed at by op_pmreplstart of a PMOP
#     The op pointed at by op_other->op_pmreplstart of pp_substcont?
#     [The op after a pp_return] Omit

1;

__END__

=head1 NAME

B::Bblock - Walk basic blocks

=head1 SYNOPSIS

  # External interface
  perl -MO=Bblock[,OPTIONS] foo.pl

  # Programmatic API
  use B::Bblock qw(find_leaders);
  my $leaders = find_leaders($root_op, $start_op);

=head1 DESCRIPTION

This module is used by the B::CC back end.  It walks "basic blocks".
A basic block is a series of operations which is known to execute from
start to finish, with no possibility of branching or halting.

It can be used either stand alone or from inside another program.

=for _private
Somebody who understands the stand-alone options document them, please.

=head2 Functions

=over 4

=item B<find_leaders>

  my $leaders = find_leaders($root_op, $start_op);

Given the root of the op tree and an op from which to start
processing, it will return a hash ref representing all the ops which
start a block.

=for _private
The above description may be somewhat wrong.

The values of %$leaders are the op objects themselves.  Keys are $$op
addresses.

=for _private
Above cribbed from B::CC's comments.  What's a $$op address?

=back


=head1 AUTHOR

Malcolm Beattie, C<mbeattie@sable.ox.ac.uk>

=cut

package TAP::Parser::Scheduler::Spinner;

use strict;
use vars qw($VERSION);
use Carp;

=head1 NAME

TAP::Parser::Scheduler::Spinner - A no-op job.

=head1 VERSION

Version 3.23

=cut

$VERSION = '3.23';

=head1 SYNOPSIS

    use TAP::Parser::Scheduler::Spinner;

=head1 DESCRIPTION

A no-op job. Returned by C<TAP::Parser::Scheduler> as an instruction to
the harness to spin (keep executing tests) while the scheduler can't
return a real job.

=head1 METHODS

=head2 Class Methods

=head3 C<new>

    my $job = TAP::Parser::Scheduler::Spinner->new;

Returns a new C<TAP::Parser::Scheduler::Spinner> object.

=cut

sub new { bless {}, shift }

=head3 C<is_spinner>

Returns true indicating that is a 'spinner' job. Spinners are returned
when the scheduler still has pending jobs but can't (because of locking)
return one right now.

=cut

sub is_spinner {1}

1;

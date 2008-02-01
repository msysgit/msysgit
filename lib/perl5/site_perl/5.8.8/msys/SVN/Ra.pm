use strict;
use warnings;

package SVN::Ra;
use SVN::Base qw(Ra);
use File::Temp;

=head1 NAME

SVN::Ra - Subversion remote access functions

=head1 SYNOPSIS

    require SVN::Core;
    require SVN::Ra;
    my $ra = SVN::Ra->new ('file:///tmp/svmtest');
    print $ra->get_latest_revnum ();


=head1 DESCRIPTION

SVN::Ra wraps the object-oriented svn_ra_plugin_t functions.

=head1 SVN::Ra

=head2 CONSTRUCTOR - new (...)

The method creates an RA object and calls C<open> for it. It takes a
hash array as parameter. if there's only one argument supplied, it's
used as the url. valid keys are:

=over

=item url

=item auth

An auth_baton could be given to the SVN::RA object. Default to a
auth_provider with a username_provider. See L<SVN::Client> for how to
create auth_baton.

=item pool

The pool for the ra session to use, and also the member functions will
be called with this pool. Default to a newly created root pool.

=item config

The config hash that could be obtained by SVN::Core::config_get_config(undef).

=item callback

The ra_callback namespace to use. Default to SVN::Ra::Callback.

=back

=head2 METHODS

Please consult the svn_ra.h section in the Subversion API. Member
functions of svn_ra_plugin_t could be called as methods of SVN::Ra
objects, with the session_baton and pool omitted.

=cut

require SVN::Client;

my $ralib = SVN::_Ra::svn_ra_init_ra_libs($SVN::Core::gpool);

# Ra methods that returns reporter
my %reporter = map { $_ => 1 } qw(do_diff do_switch do_status do_update);
our $AUTOLOAD;

sub AUTOLOAD {
    my $class = ref($_[0]);
    my $method = $AUTOLOAD;
    $method =~ s/.*:://;
    return unless $method =~ m/[^A-Z]/;

    my $self = shift;
    no strict 'refs';

    my $func = $self->{session}->can ($method)
        or die "no such method $method";

    my @ret = $func->($self->{session}, @_);
    return bless [@ret], 'SVN::Ra::Reporter' if $reporter{$method};
    return $#ret == 0 ? $ret[0] : @ret;
}

sub new {
    my $class = shift;
    my $self = bless {}, $class;
    %$self = $#_ ? @_ : (url => $_[0]);

    if (defined($self->{auth})) {
        if (ref($self->{auth}) ne '_p_svn_auth_baton_t') {
            # If the auth is already set to a auth_baton ignore it
            # otherwise make an auth_baton and store the callbacks
            my ($auth_baton,$auth_callbacks) = 
                                SVN::Core::auth_open_helper($self->{auth});
            $self->{auth} = $auth_baton;
            $self->{auth_provider_callbacks} = $auth_callbacks;
        }
    } else {
        # no callback to worry about with a username provider so just call
        # auth_open directly
        $self->{auth} = SVN::Core::auth_open(
                             [SVN::Client::get_username_provider()]);
    }

    my $pool = $self->{pool} ||= SVN::Pool->new;
    my $callback = 'SVN::Ra::Callbacks';

    # custom callback namespace
    if ($self->{callback} && !ref($self->{callback})) {
	$callback = delete $self->{callback};
    }
    # instantiate callbacks
    $callback = (delete $self->{callback}) || $callback->new (auth => $self->{auth});

    $self->{session} = SVN::_Ra::svn_ra_open ($self->{url}, $callback, $self->{config} || {}, $pool);
    return $self;
}

sub DESTROY {

}

package _p_svn_ra_session_t;
use SVN::Base qw(Ra svn_ra_);

package SVN::Ra::Reporter;
use SVN::Base qw(Ra svn_ra_reporter2_);

=head1 SVN::Ra::Reporter

the SVN::Ra methods: do_diff, do_status, do_switch, do_update, returns
a SVN::Ra::Reporter object as a wrapper of svn_ra_reporter_t. You can
use the member functions of it as methods of SVN::Ra::Reporter, with
the reporter_baton omitted.

=cut

our $AUTOLOAD;
sub AUTOLOAD {
    my $class = ref($_[0]);
    $AUTOLOAD =~ s/^${class}::(SUPER::)?//;
    return if $AUTOLOAD =~ m/^[A-Z]/;

    my $self = shift;
    no strict 'refs';

    my $method = $self->can("invoke_$AUTOLOAD")
        or die "no such method $AUTOLOAD";

    no warnings 'uninitialized';
    $method->(@$self, @_);
}

package SVN::Ra::Callbacks;

=head1 SVN::Ra::Callbacks

This is the wrapper class for svn_ra_callback_t. To supply custom
callback to SVN::Ra, subclass this class and override the member
functions.

=cut

require SVN::Core;

sub new {
    my $class = shift;
    my $self = bless {}, $class;
    %$self = @_;
    return $self;
}

sub open_tmp_file {
    local $^W; # silence the warning for unopened temp file
    my ($self, $pool) = @_;
    my ($fd, $name) = SVN::Core::io_open_unique_file(
        ( File::Temp::tempfile(
            'XXXXXXXX', OPEN => 0, DIR => File::Spec->tmpdir
        ))[1], 'tmp', 1, $pool
    );
    return $fd;
}

sub get_wc_prop {
    return undef;
}

=head1 AUTHORS

Chia-liang Kao E<lt>clkao@clkao.orgE<gt>

=head1 COPYRIGHT

Copyright (c) 2003 CollabNet.  All rights reserved.

This software is licensed as described in the file COPYING, which you
should have received as part of this distribution.  The terms are also
available at http://subversion.tigris.org/license-1.html.  If newer
versions of this license are posted there, you may use a newer version
instead, at your option.

This software consists of voluntary contributions made by many
individuals.  For exact contribution history, see the revision history
and logs, available at http://subversion.tigris.org/.

=cut

1;

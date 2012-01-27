package CPAN::Nox;
use strict;
use vars qw($VERSION @EXPORT);

BEGIN{
  $CPAN::Suppress_readline=1 unless defined $CPAN::term;
}

use base 'Exporter';
use CPAN;

$VERSION = "1.03";
$CPAN::META->has_inst('Digest::MD5','no');
$CPAN::META->has_inst('LWP','no');
$CPAN::META->has_inst('Compress::Zlib','no');
@EXPORT = @CPAN::EXPORT;

*AUTOLOAD = \&CPAN::AUTOLOAD;

1;

__END__

=head1 NAME

CPAN::Nox - Wrapper around CPAN.pm without using any XS module

=head1 SYNOPSIS

Interactive mode:

  perl -MCPAN::Nox -e shell;

=head1 DESCRIPTION

This package has the same functionality as CPAN.pm, but tries to
prevent the usage of compiled extensions during its own
execution. Its primary purpose is a rescue in case you upgraded perl
and broke binary compatibility somehow.

=head1  SEE ALSO

CPAN(3)

=cut


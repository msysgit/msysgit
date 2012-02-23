package bignum;
require 5.005;

$VERSION = '0.17';
use Exporter;
@EXPORT_OK 	= qw( ); 
@EXPORT 	= qw( inf NaN ); 
@ISA 		= qw( Exporter );

use strict;

############################################################################## 

# These are all alike, and thus faked by AUTOLOAD

my @faked = qw/round_mode accuracy precision div_scale/;
use vars qw/$VERSION $AUTOLOAD $_lite/;		# _lite for testsuite

sub AUTOLOAD
  {
  my $name = $AUTOLOAD;

  $name =~ s/.*:://;    # split package
  no strict 'refs';
  foreach my $n (@faked)
    {
    if ($n eq $name)
      {
      *{"bignum::$name"} = sub 
        {
        my $self = shift;
        no strict 'refs';
        if (defined $_[0])
          {
          Math::BigInt->$name($_[0]);
          return Math::BigFloat->$name($_[0]);
          }
        return Math::BigInt->$name();
        };
      return &$name;
      }
    }
 
  # delayed load of Carp and avoid recursion
  require Carp;
  Carp::croak ("Can't call bignum\-\>$name, not a valid method");
  }

sub upgrade
  {
  my $self = shift;
  no strict 'refs';
#  if (defined $_[0])
#    {
#    $Math::BigInt::upgrade = $_[0];
#    $Math::BigFloat::upgrade = $_[0];
#    }
  return $Math::BigInt::upgrade;
  }

sub import 
  {
  my $self = shift;

  # some defaults
  my $lib = '';
  my $upgrade = 'Math::BigFloat';
  my $downgrade = 'Math::BigInt';

  my @import = ( ':constant' );				# drive it w/ constant
  my @a = @_; my $l = scalar @_; my $j = 0;
  my ($ver,$trace);					# version? trace?
  my ($a,$p);						# accuracy, precision
  for ( my $i = 0; $i < $l ; $i++,$j++ )
    {
    if ($_[$i] eq 'upgrade')
      {
      # this causes upgrading
      $upgrade = $_[$i+1];		# or undef to disable
      my $s = 2; $s = 1 if @a-$j < 2;	# avoid "can not modify non-existant..."
      splice @a, $j, $s; $j -= $s; $i++;
      }
    elsif ($_[$i] eq 'downgrade')
      {
      # this causes downgrading
      $downgrade = $_[$i+1];		# or undef to disable
      my $s = 2; $s = 1 if @a-$j < 2;	# avoid "can not modify non-existant..."
      splice @a, $j, $s; $j -= $s; $i++;
      }
    elsif ($_[$i] =~ /^(l|lib)$/)
      {
      # this causes a different low lib to take care...
      $lib = $_[$i+1] || '';
      my $s = 2; $s = 1 if @a-$j < 2;	# avoid "can not modify non-existant..."
      splice @a, $j, $s; $j -= $s; $i++;
      }
    elsif ($_[$i] =~ /^(a|accuracy)$/)
      {
      $a = $_[$i+1];
      my $s = 2; $s = 1 if @a-$j < 2;	# avoid "can not modify non-existant..."
      splice @a, $j, $s; $j -= $s; $i++;
      }
    elsif ($_[$i] =~ /^(p|precision)$/)
      {
      $p = $_[$i+1];
      my $s = 2; $s = 1 if @a-$j < 2;	# avoid "can not modify non-existant..."
      splice @a, $j, $s; $j -= $s; $i++;
      }
    elsif ($_[$i] =~ /^(v|version)$/)
      {
      $ver = 1;
      splice @a, $j, 1; $j --;
      }
    elsif ($_[$i] =~ /^(t|trace)$/)
      {
      $trace = 1;
      splice @a, $j, 1; $j --;
      }
    else { die "unknown option $_[$i]"; }
    }
  my $class;
  $_lite = 0;					# using M::BI::L ?
  if ($trace)
    {
    require Math::BigInt::Trace; $class = 'Math::BigInt::Trace';
    $upgrade = 'Math::BigFloat::Trace';	
    }
  else
    {
    # see if we can find Math::BigInt::Lite
    if (!defined $a && !defined $p)		# rounding won't work to well
      {
      eval 'require Math::BigInt::Lite;';
      if ($@ eq '')
        {
        @import = ( );				# :constant in Lite, not MBI
        Math::BigInt::Lite->import( ':constant' );
        $_lite= 1;				# signal okay
        }
      }
    require Math::BigInt if $_lite == 0;	# not already loaded?
    $class = 'Math::BigInt';			# regardless of MBIL or not
    }
  push @import, 'lib' => $lib if $lib ne ''; 
  # Math::BigInt::Trace or plain Math::BigInt
  $class->import(@import, upgrade => $upgrade);

  if ($trace)
    {
    require Math::BigFloat::Trace; $class = 'Math::BigFloat::Trace';
    $downgrade = 'Math::BigInt::Trace';	
    }
  else
    {
    require Math::BigFloat; $class = 'Math::BigFloat';
    }
  $class->import(':constant','downgrade',$downgrade);

  bignum->accuracy($a) if defined $a;
  bignum->precision($p) if defined $p;
  if ($ver)
    {
    print "bignum\t\t\t v$VERSION\n";
    print "Math::BigInt::Lite\t v$Math::BigInt::Lite::VERSION\n" if $_lite;
    print "Math::BigInt\t\t v$Math::BigInt::VERSION";
    my $config = Math::BigInt->config();
    print " lib => $config->{lib} v$config->{lib_version}\n";
    print "Math::BigFloat\t\t v$Math::BigFloat::VERSION\n";
    exit;
    }
  $self->export_to_level(1,$self,@a);		# export inf and NaN
  }

sub inf () { Math::BigInt->binf(); }
sub NaN () { Math::BigInt->bnan(); }

1;

__END__

=head1 NAME

bignum - Transparent BigNumber support for Perl

=head1 SYNOPSIS

  use bignum;

  $x = 2 + 4.5,"\n";			# BigFloat 6.5
  print 2 ** 512 * 0.1,"\n";		# really is what you think it is
  print inf * inf,"\n";			# prints inf
  print NaN * 3,"\n";			# prints NaN

=head1 DESCRIPTION

All operators (including basic math operations) are overloaded. Integer and
floating-point constants are created as proper BigInts or BigFloats,
respectively.

If you do 

        use bignum;

at the top of your script, Math::BigFloat and Math::BigInt will be loaded
and any constant number will be converted to an object (Math::BigFloat for
floats like 3.1415 and Math::BigInt for integers like 1234).

So, the following line:

        $x = 1234;

creates actually a Math::BigInt and stores a reference to in $x.
This happens transparently and behind your back, so to speak.

You can see this with the following:

        perl -Mbignum -le 'print ref(1234)'

Don't worry if it says Math::BigInt::Lite, bignum and friends will use Lite
if it is installed since it is faster for some operations. It will be
automatically upgraded to BigInt whenever neccessary:

        perl -Mbignum -le 'print ref(2**255)'

This also means it is a bad idea to check for some specific package, since
the actual contents of $x might be something unexpected. Due to the
transparent way of bignum C<ref()> should not be neccessary, anyway.

Since Math::BigInt and BigFloat also overload the normal math operations,
the following line will still work:

        perl -Mbignum -le 'print ref(1234+1234)'

Since numbers are actually objects, you can call all the usual methods from
BigInt/BigFloat on them. This even works to some extent on expressions:

        perl -Mbignum -le '$x = 1234; print $x->bdec()'
        perl -Mbignum -le 'print 1234->binc();'
        perl -Mbignum -le 'print 1234->binc->badd(6);'
        perl -Mbignum -le 'print +(1234)->binc()'

(Note that print doesn't do what you expect if the expression starts with
'(' hence the C<+>)

You can even chain the operations together as usual:

        perl -Mbignum -le 'print 1234->binc->badd(6);'
        1241

Under bignum (or bigint or bigrat), Perl will "upgrade" the numbers
appropriately. This means that:

        perl -Mbignum -le 'print 1234+4.5'
        1238.5

will work correctly. These mixed cases don't do always work when using
Math::BigInt or Math::BigFloat alone, or at least not in the way normal Perl
scalars work. 

If you do want to work with large integers like under C<use integer;>, try
C<use bigint;>:

        perl -Mbigint -le 'print 1234.5+4.5'
        1238

There is also C<use bigrat;> which gives you big rationals:

        perl -Mbigrat -le 'print 1234+4.1'
        12381/10

The entire upgrading/downgrading is still experimental and might not work
as you expect or may even have bugs.

You might get errors like this:

        Can't use an undefined value as an ARRAY reference at
        /usr/local/lib/perl5/5.8.0/Math/BigInt/Calc.pm line 864

This means somewhere a routine got a BigFloat/Lite but expected a BigInt (or
vice versa) and the upgrade/downgrad path was missing. This is a bug, please
report it so that we can fix it.

You might consider using just Math::BigInt or Math::BigFloat, since they
allow you finer control over what get's done in which module/space. For
instance, simple loop counters will be Math::BigInts under C<use bignum;> and
this is slower than keeping them as Perl scalars:

        perl -Mbignum -le 'for ($i = 0; $i < 10; $i++) { print ref($i); }'

Please note the following does not work as expected (prints nothing), since
overloading of '..' is not yet possible in Perl (as of v5.8.0):

        perl -Mbignum -le 'for (1..2) { print ref($_); }'

=head2 Options

bignum recognizes some options that can be passed while loading it via use.
The options can (currently) be either a single letter form, or the long form.
The following options exist:

=over 2

=item a or accuracy

This sets the accuracy for all math operations. The argument must be greater
than or equal to zero. See Math::BigInt's bround() function for details.

	perl -Mbignum=a,50 -le 'print sqrt(20)'

=item p or precision

This sets the precision for all math operations. The argument can be any
integer. Negative values mean a fixed number of digits after the dot, while
a positive value rounds to this digit left from the dot. 0 or 1 mean round to
integer. See Math::BigInt's bfround() function for details.

	perl -Mbignum=p,-50 -le 'print sqrt(20)'

=item t or trace

This enables a trace mode and is primarily for debugging bignum or
Math::BigInt/Math::BigFloat.

=item l or lib

Load a different math lib, see L<MATH LIBRARY>.

	perl -Mbignum=l,GMP -e 'print 2 ** 512'

Currently there is no way to specify more than one library on the command
line. This will be hopefully fixed soon ;)

=item v or version

This prints out the name and version of all modules used and then exits.

	perl -Mbignum=v

=head2 Methods

Beside import() and AUTOLOAD() there are only a few other methods.

Since all numbers are now objects, you can use all functions that are part of
the BigInt or BigFloat API. It is wise to use only the bxxx() notation, and not
the fxxx() notation, though. This makes it possible that the underlying object
might morph into a different class than BigFloat.

=head2 Caveat

But a warning is in order. When using the following to make a copy of a number,
only a shallow copy will be made.

        $x = 9; $y = $x;
        $x = $y = 7;

If you want to make a real copy, use the following:

        $y = $x->copy();

Using the copy or the original with overloaded math is okay, e.g. the
following work:

        $x = 9; $y = $x;
        print $x + 1, " ", $y,"\n";     # prints 10 9

but calling any method that modifies the number directly will result in
B<both> the original and the copy beeing destroyed:

        $x = 9; $y = $x;
        print $x->badd(1), " ", $y,"\n";        # prints 10 10

        $x = 9; $y = $x;
        print $x->binc(1), " ", $y,"\n";        # prints 10 10

        $x = 9; $y = $x;
        print $x->bmul(2), " ", $y,"\n";        # prints 18 18

Using methods that do not modify, but testthe contents works:

        $x = 9; $y = $x;
        $z = 9 if $x->is_zero();                # works fine

See the documentation about the copy constructor and C<=> in overload, as
well as the documentation in BigInt for further details.

=over 2

=item inf()

A shortcut to return Math::BigInt->binf(). Usefull because Perl does not always
handle bareword C<inf> properly.

=item NaN()

A shortcut to return Math::BigInt->bnan(). Usefull because Perl does not always
handle bareword C<NaN> properly.

=item upgrade()

Return the class that numbers are upgraded to, is in fact returning
C<$Math::BigInt::upgrade>.

=back

=head2 MATH LIBRARY

Math with the numbers is done (by default) by a module called
Math::BigInt::Calc. This is equivalent to saying:

	use bignum lib => 'Calc';

You can change this by using:

	use bignum lib => 'BitVect';

The following would first try to find Math::BigInt::Foo, then
Math::BigInt::Bar, and when this also fails, revert to Math::BigInt::Calc:

	use bignum lib => 'Foo,Math::BigInt::Bar';

Please see respective module documentation for further details.

=head2 INTERNAL FORMAT

The numbers are stored as objects, and their internals might change at anytime,
especially between math operations. The objects also might belong to different
classes, like Math::BigInt, or Math::BigFLoat. Mixing them together, even
with normal scalars is not extraordinary, but normal and expected.

You should not depend on the internal format, all accesses must go through
accessor methods. E.g. looking at $x->{sign} is not a bright idea since there
is no guaranty that the object in question has such a hashkey, nor is a hash
underneath at all.

=head2 SIGN

The sign is either '+', '-', 'NaN', '+inf' or '-inf' and stored seperately.
You can access it with the sign() method.

A sign of 'NaN' is used to represent the result when input arguments are not
numbers or as a result of 0/0. '+inf' and '-inf' represent plus respectively
minus infinity. You will get '+inf' when dividing a positive number by 0, and
'-inf' when dividing any negative number by 0.

=head1 MODULES USED

C<bignum> is just a thin wrapper around various modules of the Math::BigInt
family. Think of it as the head of the family, who runs the shop, and orders
the others to do the work.

The following modules are currently used by bignum:

	Math::BigInt::Lite	(for speed, and only if it is loadable)
	Math::BigInt
	Math::BigFloat

=head1 EXAMPLES

Some cool command line examples to impress the Python crowd ;)
 
	perl -Mbignum -le 'print sqrt(33)'
	perl -Mbignum -le 'print 2*255'
	perl -Mbignum -le 'print 4.5+2*255'
	perl -Mbignum -le 'print 3/7 + 5/7 + 8/3'
	perl -Mbignum -le 'print 123->is_odd()'
	perl -Mbignum -le 'print log(2)'
	perl -Mbignum -le 'print 2 ** 0.5'
	perl -Mbignum=a,65 -le 'print 2 ** 0.2'

=head1 LICENSE

This program is free software; you may redistribute it and/or modify it under
the same terms as Perl itself.

=head1 SEE ALSO

Especially L<bigrat> as in C<perl -Mbigrat -le 'print 1/3+1/4'>.

L<Math::BigFloat>, L<Math::BigInt>, L<Math::BigRat> and L<Math::Big> as well
as L<Math::BigInt::BitVect>, L<Math::BigInt::Pari> and  L<Math::BigInt::GMP>.

=head1 AUTHORS

(C) by Tels L<http://bloodgate.com/> in early 2002, 2003.

=cut

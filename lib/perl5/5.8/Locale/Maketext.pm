
# Time-stamp: "2004-03-30 16:33:31 AST"

require 5;
package Locale::Maketext;
use strict;
use vars qw( @ISA $VERSION $MATCH_SUPERS $USING_LANGUAGE_TAGS
             $USE_LITERALS $MATCH_SUPERS_TIGHTLY);
use Carp ();
use I18N::LangTags 0.30 ();

#--------------------------------------------------------------------------

BEGIN { unless(defined &DEBUG) { *DEBUG = sub () {0} } }
 # define the constant 'DEBUG' at compile-time

$VERSION = "1.09";
@ISA = ();

$MATCH_SUPERS = 1;
$MATCH_SUPERS_TIGHTLY = 1;
$USING_LANGUAGE_TAGS  = 1;
 # Turning this off is somewhat of a security risk in that little or no
 # checking will be done on the legality of tokens passed to the
 # eval("use $module_name") in _try_use.  If you turn this off, you have
 # to do your own taint checking.

$USE_LITERALS = 1 unless defined $USE_LITERALS;
 # a hint for compiling bracket-notation things.

my %isa_scan = ();

###########################################################################

sub quant {
  my($handle, $num, @forms) = @_;

  return $num if @forms == 0; # what should this mean?
  return $forms[2] if @forms > 2 and $num == 0; # special zeroth case

  # Normal case:
  # Note that the formatting of $num is preserved.
  return( $handle->numf($num) . ' ' . $handle->numerate($num, @forms) );
   # Most human languages put the number phrase before the qualified phrase.
}


sub numerate {
 # return this lexical item in a form appropriate to this number
  my($handle, $num, @forms) = @_;
  my $s = ($num == 1);

  return '' unless @forms;
  if(@forms == 1) { # only the headword form specified
    return $s ? $forms[0] : ($forms[0] . 's'); # very cheap hack.
  } else { # sing and plural were specified
    return $s ? $forms[0] : $forms[1];
  }
}

#--------------------------------------------------------------------------

sub numf {
  my($handle, $num) = @_[0,1];
  if($num < 10_000_000_000 and $num > -10_000_000_000 and $num == int($num)) {
    $num += 0;  # Just use normal integer stringification.
         # Specifically, don't let %G turn ten million into 1E+007
  } else {
    $num = CORE::sprintf("%G", $num);
     # "CORE::" is there to avoid confusion with the above sub sprintf.
  }
  while( $num =~ s/^([-+]?\d+)(\d{3})/$1,$2/s ) {1}  # right from perlfaq5
   # The initial \d+ gobbles as many digits as it can, and then we
   #  backtrack so it un-eats the rightmost three, and then we
   #  insert the comma there.

  $num =~ tr<.,><,.> if ref($handle) and $handle->{'numf_comma'};
   # This is just a lame hack instead of using Number::Format
  return $num;
}

sub sprintf {
  no integer;
  my($handle, $format, @params) = @_;
  return CORE::sprintf($format, @params);
    # "CORE::" is there to avoid confusion with myself!
}

#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#

use integer; # vroom vroom... applies to the whole rest of the module

sub language_tag {
  my $it = ref($_[0]) || $_[0];
  return undef unless $it =~ m/([^':]+)(?:::)?$/s;
  $it = lc($1);
  $it =~ tr<_><->;
  return $it;
}

sub encoding {
  my $it = $_[0];
  return(
   (ref($it) && $it->{'encoding'})
   || "iso-8859-1"   # Latin-1
  );
} 

#--------------------------------------------------------------------------

sub fallback_languages { return('i-default', 'en', 'en-US') }

sub fallback_language_classes { return () }

#--------------------------------------------------------------------------

sub fail_with { # an actual attribute method!
  my($handle, @params) = @_;
  return unless ref($handle);
  $handle->{'fail'} = $params[0] if @params;
  return $handle->{'fail'};
}

#--------------------------------------------------------------------------

sub failure_handler_auto {
  # Meant to be used like:
  #  $handle->fail_with('failure_handler_auto')

  my($handle, $phrase, @params) = @_;
  $handle->{'failure_lex'} ||= {};
  my $lex = $handle->{'failure_lex'};

  my $value;
  $lex->{$phrase} ||= ($value = $handle->_compile($phrase));

  # Dumbly copied from sub maketext:
  {
    local $SIG{'__DIE__'};
    eval { $value = &$value($handle, @_) };
  }
  # If we make it here, there was an exception thrown in the
  #  call to $value, and so scream:
  if($@) {
    my $err = $@;
    # pretty up the error message
    $err =~ s<\s+at\s+\(eval\s+\d+\)\s+line\s+(\d+)\.?\n?>
             <\n in bracket code [compiled line $1],>s;
    #$err =~ s/\n?$/\n/s;
    Carp::croak "Error in maketexting \"$phrase\":\n$err as used";
    # Rather unexpected, but suppose that the sub tried calling
    # a method that didn't exist.
  } else {
    return $value;
  }
}

#==========================================================================

sub new {
  # Nothing fancy!
  my $class = ref($_[0]) || $_[0];
  my $handle = bless {}, $class;
  $handle->init;
  return $handle;
}

sub init { return } # no-op

###########################################################################

sub maketext {
  # Remember, this can fail.  Failure is controllable many ways.
  Carp::croak "maketext requires at least one parameter" unless @_ > 1;

  my($handle, $phrase) = splice(@_,0,2);

  # Look up the value:

  my $value;
  foreach my $h_r (
    @{  $isa_scan{ref($handle) || $handle} || $handle->_lex_refs  }
  ) {
    print "* Looking up \"$phrase\" in $h_r\n" if DEBUG;
    if(exists $h_r->{$phrase}) {
      print "  Found \"$phrase\" in $h_r\n" if DEBUG;
      unless(ref($value = $h_r->{$phrase})) {
        # Nonref means it's not yet compiled.  Compile and replace.
        $value = $h_r->{$phrase} = $handle->_compile($value);
      }
      last;
    } elsif($phrase !~ m/^_/s and $h_r->{'_AUTO'}) {
      # it's an auto lex, and this is an autoable key!
      print "  Automaking \"$phrase\" into $h_r\n" if DEBUG;
      
      $value = $h_r->{$phrase} = $handle->_compile($phrase);
      last;
    }
    print "  Not found in $h_r, nor automakable\n" if DEBUG > 1;
    # else keep looking
  }

  unless(defined($value)) {
    print "! Lookup of \"$phrase\" in/under ", ref($handle) || $handle,
      " fails.\n" if DEBUG;
    if(ref($handle) and $handle->{'fail'}) {
      print "WARNING0: maketext fails looking for <$phrase>\n" if DEBUG;
      my $fail;
      if(ref($fail = $handle->{'fail'}) eq 'CODE') { # it's a sub reference
        return &{$fail}($handle, $phrase, @_);
         # If it ever returns, it should return a good value.
      } else { # It's a method name
        return $handle->$fail($phrase, @_);
         # If it ever returns, it should return a good value.
      }
    } else {
      # All we know how to do is this;
      Carp::croak("maketext doesn't know how to say:\n$phrase\nas needed");
    }
  }

  return $$value if ref($value) eq 'SCALAR';
  return $value unless ref($value) eq 'CODE';
  
  {
    local $SIG{'__DIE__'};
    eval { $value = &$value($handle, @_) };
  }
  # If we make it here, there was an exception thrown in the
  #  call to $value, and so scream:
  if($@) {
    my $err = $@;
    # pretty up the error message
    $err =~ s<\s+at\s+\(eval\s+\d+\)\s+line\s+(\d+)\.?\n?>
             <\n in bracket code [compiled line $1],>s;
    #$err =~ s/\n?$/\n/s;
    Carp::croak "Error in maketexting \"$phrase\":\n$err as used";
    # Rather unexpected, but suppose that the sub tried calling
    # a method that didn't exist.
  } else {
    return $value;
  }
}

###########################################################################

sub get_handle {  # This is a constructor and, yes, it CAN FAIL.
  # Its class argument has to be the base class for the current
  # application's l10n files.

  my($base_class, @languages) = @_;
  $base_class = ref($base_class) || $base_class;
   # Complain if they use __PACKAGE__ as a project base class?
  
  if( @languages ) {
    DEBUG and print "Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";
    if($USING_LANGUAGE_TAGS) {   # An explicit language-list was given!
      @languages =
       map {; $_, I18N::LangTags::alternate_language_tags($_) }
        # Catch alternation
       map I18N::LangTags::locale2language_tag($_),
        # If it's a lg tag, fine, pass thru (untainted)
        # If it's a locale ID, try converting to a lg tag (untainted),
        # otherwise nix it.
       @languages;
      DEBUG and print "Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";
    }
  } else {
    @languages = $base_class->_ambient_langprefs;
  }
 
  @languages = $base_class->_langtag_munging(@languages);

  my %seen;
  foreach my $module_name ( map { $base_class . "::" . $_ }  @languages ) {
    next unless length $module_name; # sanity
    next if $seen{$module_name}++        # Already been here, and it was no-go
            || !&_try_use($module_name); # Try to use() it, but can't it.
    return($module_name->new); # Make it!
  }

  return undef; # Fail!
}

###########################################################################

sub _langtag_munging {
  my($base_class, @languages) = @_;

  # We have all these DEBUG statements because otherwise it's hard as hell
  # to diagnose ifwhen something goes wrong.

  DEBUG and print "Lgs1: ", map("<$_>", @languages), "\n";

  if($USING_LANGUAGE_TAGS) {
    DEBUG and print "Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";
    @languages     = $base_class->_add_supers( @languages );

    push @languages, I18N::LangTags::panic_languages(@languages);
    DEBUG and print "After adding panic languages:\n", 
      " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";

    push @languages, $base_class->fallback_languages;
     # You are free to override fallback_languages to return empty-list!
    DEBUG and print "Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";

    @languages =  # final bit of processing to turn them into classname things
      map {
        my $it = $_;  # copy
        $it =~ tr<-A-Z><_a-z>; # lc, and turn - to _
        $it =~ tr<_a-z0-9><>cd;  # remove all but a-z0-9_
        $it;
      } @languages
    ;
    DEBUG and print "Nearing end of munging:\n", 
      " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";
  } else {
    DEBUG and print "Bypassing language-tags.\n", 
      " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";
  }

  DEBUG and print "Before adding fallback classes:\n", 
    " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";

  push @languages, $base_class->fallback_language_classes;
   # You are free to override that to return whatever.

  DEBUG and print "Finally:\n", 
    " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";

  return @languages;
}

###########################################################################

sub _ambient_langprefs {
  require I18N::LangTags::Detect;
  return  I18N::LangTags::Detect::detect();
}

###########################################################################

sub _add_supers {
  my($base_class, @languages) = @_;

  if(!$MATCH_SUPERS) {
    # Nothing
    DEBUG and print "Bypassing any super-matching.\n", 
      " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";

  } elsif( $MATCH_SUPERS_TIGHTLY ) {
    DEBUG and print "Before adding new supers tightly:\n", 
      " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";
    @languages = I18N::LangTags::implicate_supers( @languages );
    DEBUG and print "After adding new supers tightly:\n", 
      " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";

  } else {
    DEBUG and print "Before adding supers to end:\n", 
      " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";
    @languages = I18N::LangTags::implicate_supers_strictly( @languages );
    DEBUG and print "After adding supers to end:\n", 
      " Lgs\@", __LINE__, ": ", map("<$_>", @languages), "\n";
  }
  
  return @languages;
}

###########################################################################
#
# This is where most people should stop reading.
#
###########################################################################

use Locale::Maketext::GutsLoader;

###########################################################################

my %tried = ();
  # memoization of whether we've used this module, or found it unusable.

sub _try_use {   # Basically a wrapper around "require Modulename"
  # "Many men have tried..."  "They tried and failed?"  "They tried and died."
  return $tried{$_[0]} if exists $tried{$_[0]};  # memoization

  my $module = $_[0];   # ASSUME sane module name!
  { no strict 'refs';
    return($tried{$module} = 1)
     if defined(%{$module . "::Lexicon"}) or defined(@{$module . "::ISA"});
    # weird case: we never use'd it, but there it is!
  }

  print " About to use $module ...\n" if DEBUG;
  {
    local $SIG{'__DIE__'};
    eval "require $module"; # used to be "use $module", but no point in that.
  }
  if($@) {
    print "Error using $module \: $@\n" if DEBUG > 1;
    return $tried{$module} = 0;
  } else {
    print " OK, $module is used\n" if DEBUG;
    return $tried{$module} = 1;
  }
}

#--------------------------------------------------------------------------

sub _lex_refs {  # report the lexicon references for this handle's class
  # returns an arrayREF!
  no strict 'refs';
  my $class = ref($_[0]) || $_[0];
  print "Lex refs lookup on $class\n" if DEBUG > 1;
  return $isa_scan{$class} if exists $isa_scan{$class};  # memoization!

  my @lex_refs;
  my $seen_r = ref($_[1]) ? $_[1] : {};

  if( defined( *{$class . '::Lexicon'}{'HASH'} )) {
    push @lex_refs, *{$class . '::Lexicon'}{'HASH'};
    print "%" . $class . "::Lexicon contains ",
         scalar(keys %{$class . '::Lexicon'}), " entries\n" if DEBUG;
  }

  # Implements depth(height?)-first recursive searching of superclasses.
  # In hindsight, I suppose I could have just used Class::ISA!
  foreach my $superclass (@{$class . "::ISA"}) {
    print " Super-class search into $superclass\n" if DEBUG;
    next if $seen_r->{$superclass}++;
    push @lex_refs, @{&_lex_refs($superclass, $seen_r)};  # call myself
  }

  $isa_scan{$class} = \@lex_refs; # save for next time
  return \@lex_refs;
}

sub clear_isa_scan { %isa_scan = (); return; } # end on a note of simplicity!

###########################################################################
1;

__END__

HEY YOU!  You need some FOOD!


  ~~ Tangy Moroccan Carrot Salad ~~

* 6 to 8 medium carrots, peeled and then sliced in 1/4-inch rounds
* 1/4 teaspoon chile powder (cayenne, chipotle, ancho, or the like)
* 1 tablespoon ground cumin
* 1 tablespoon honey
* The juice of about a half a big lemon, or of a whole smaller one
* 1/3 cup olive oil
* 1 tablespoon of fresh dill, washed and chopped fine
* Pinch of salt, maybe a pinch of pepper

Cook the carrots in a pot of boiling water until just tender -- roughly
six minutes.  (Just don't let them get mushy!)  Drain the carrots.

In a largish bowl, combine the lemon juice, the cumin, the chile
powder, and the honey.  Mix well.
Add the olive oil and whisk it together well.  Add the dill and stir.

Add the warm carrots to the bowl and toss it all to coat the carrots
well.  Season with salt and pepper, to taste.

Serve warm or at room temperature.

The measurements here are very approximate, and you should feel free to
improvise and experiment.  It's a very forgiving recipe.  For example,
you could easily halve or double the amount of cumin, or use chopped mint
leaves instead of dill, or lime juice instead of lemon, et cetera.

[end]


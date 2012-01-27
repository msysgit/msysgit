# Pod::Text -- Convert POD data to formatted ASCII text.
# $Id: Text.pm,v 2.21 2002/08/04 03:34:58 eagle Exp $
#
# Copyright 1999, 2000, 2001, 2002 by Russ Allbery <rra@stanford.edu>
#
# This program is free software; you may redistribute it and/or modify it
# under the same terms as Perl itself.
#
# This module converts POD to formatted text.  It replaces the old Pod::Text
# module that came with versions of Perl prior to 5.6.0 and attempts to match
# its output except for some specific circumstances where other decisions
# seemed to produce better output.  It uses Pod::Parser and is designed to be
# very easy to subclass.
#
# Perl core hackers, please note that this module is also separately
# maintained outside of the Perl core as part of the podlators.  Please send
# me any patches at the address above in addition to sending them to the
# standard Perl mailing lists.

##############################################################################
# Modules and declarations
##############################################################################

package Pod::Text;

require 5.004;

use Carp qw(carp croak);
use Exporter ();
use Pod::ParseLink qw(parselink);
use Pod::Select ();

use strict;
use vars qw(@ISA @EXPORT %ESCAPES $VERSION);

# We inherit from Pod::Select instead of Pod::Parser so that we can be used by
# Pod::Usage.
@ISA = qw(Pod::Select Exporter);

# We have to export pod2text for backward compatibility.
@EXPORT = qw(pod2text);

# Don't use the CVS revision as the version, since this module is also in Perl
# core and too many things could munge CVS magic revision strings.  This
# number should ideally be the same as the CVS revision in podlators, however.
$VERSION = 2.21;


##############################################################################
# Table of supported E<> escapes
##############################################################################

# This table is taken near verbatim from Pod::PlainText in Pod::Parser, which
# got it near verbatim from the original Pod::Text.  It is therefore credited
# to Tom Christiansen, and I'm glad I didn't have to write it.  :)  "iexcl" to
# "divide" added by Tim Jenness.
%ESCAPES = (
    'amp'       =>    '&',      # ampersand
    'apos'      =>    "'",      # apostrophe
    'lt'        =>    '<',      # left chevron, less-than
    'gt'        =>    '>',      # right chevron, greater-than
    'quot'      =>    '"',      # double quote
    'sol'       =>    '/',      # solidus (forward slash)
    'verbar'    =>    '|',      # vertical bar

    "Aacute"    =>    "\xC1",   # capital A, acute accent
    "aacute"    =>    "\xE1",   # small a, acute accent
    "Acirc"     =>    "\xC2",   # capital A, circumflex accent
    "acirc"     =>    "\xE2",   # small a, circumflex accent
    "AElig"     =>    "\xC6",   # capital AE diphthong (ligature)
    "aelig"     =>    "\xE6",   # small ae diphthong (ligature)
    "Agrave"    =>    "\xC0",   # capital A, grave accent
    "agrave"    =>    "\xE0",   # small a, grave accent
    "Aring"     =>    "\xC5",   # capital A, ring
    "aring"     =>    "\xE5",   # small a, ring
    "Atilde"    =>    "\xC3",   # capital A, tilde
    "atilde"    =>    "\xE3",   # small a, tilde
    "Auml"      =>    "\xC4",   # capital A, dieresis or umlaut mark
    "auml"      =>    "\xE4",   # small a, dieresis or umlaut mark
    "Ccedil"    =>    "\xC7",   # capital C, cedilla
    "ccedil"    =>    "\xE7",   # small c, cedilla
    "Eacute"    =>    "\xC9",   # capital E, acute accent
    "eacute"    =>    "\xE9",   # small e, acute accent
    "Ecirc"     =>    "\xCA",   # capital E, circumflex accent
    "ecirc"     =>    "\xEA",   # small e, circumflex accent
    "Egrave"    =>    "\xC8",   # capital E, grave accent
    "egrave"    =>    "\xE8",   # small e, grave accent
    "ETH"       =>    "\xD0",   # capital Eth, Icelandic
    "eth"       =>    "\xF0",   # small eth, Icelandic
    "Euml"      =>    "\xCB",   # capital E, dieresis or umlaut mark
    "euml"      =>    "\xEB",   # small e, dieresis or umlaut mark
    "Iacute"    =>    "\xCD",   # capital I, acute accent
    "iacute"    =>    "\xED",   # small i, acute accent
    "Icirc"     =>    "\xCE",   # capital I, circumflex accent
    "icirc"     =>    "\xEE",   # small i, circumflex accent
    "Igrave"    =>    "\xCC",   # capital I, grave accent
    "igrave"    =>    "\xEC",   # small i, grave accent
    "Iuml"      =>    "\xCF",   # capital I, dieresis or umlaut mark
    "iuml"      =>    "\xEF",   # small i, dieresis or umlaut mark
    "Ntilde"    =>    "\xD1",   # capital N, tilde
    "ntilde"    =>    "\xF1",   # small n, tilde
    "Oacute"    =>    "\xD3",   # capital O, acute accent
    "oacute"    =>    "\xF3",   # small o, acute accent
    "Ocirc"     =>    "\xD4",   # capital O, circumflex accent
    "ocirc"     =>    "\xF4",   # small o, circumflex accent
    "Ograve"    =>    "\xD2",   # capital O, grave accent
    "ograve"    =>    "\xF2",   # small o, grave accent
    "Oslash"    =>    "\xD8",   # capital O, slash
    "oslash"    =>    "\xF8",   # small o, slash
    "Otilde"    =>    "\xD5",   # capital O, tilde
    "otilde"    =>    "\xF5",   # small o, tilde
    "Ouml"      =>    "\xD6",   # capital O, dieresis or umlaut mark
    "ouml"      =>    "\xF6",   # small o, dieresis or umlaut mark
    "szlig"     =>    "\xDF",   # small sharp s, German (sz ligature)
    "THORN"     =>    "\xDE",   # capital THORN, Icelandic
    "thorn"     =>    "\xFE",   # small thorn, Icelandic
    "Uacute"    =>    "\xDA",   # capital U, acute accent
    "uacute"    =>    "\xFA",   # small u, acute accent
    "Ucirc"     =>    "\xDB",   # capital U, circumflex accent
    "ucirc"     =>    "\xFB",   # small u, circumflex accent
    "Ugrave"    =>    "\xD9",   # capital U, grave accent
    "ugrave"    =>    "\xF9",   # small u, grave accent
    "Uuml"      =>    "\xDC",   # capital U, dieresis or umlaut mark
    "uuml"      =>    "\xFC",   # small u, dieresis or umlaut mark
    "Yacute"    =>    "\xDD",   # capital Y, acute accent
    "yacute"    =>    "\xFD",   # small y, acute accent
    "yuml"      =>    "\xFF",   # small y, dieresis or umlaut mark

    "laquo"     =>    "\xAB",   # left pointing double angle quotation mark
    "lchevron"  =>    "\xAB",   #  synonym (backwards compatibility)
    "raquo"     =>    "\xBB",   # right pointing double angle quotation mark
    "rchevron"  =>    "\xBB",   #  synonym (backwards compatibility)

    "iexcl"     =>    "\xA1",   # inverted exclamation mark
    "cent"      =>    "\xA2",   # cent sign
    "pound"     =>    "\xA3",   # (UK) pound sign
    "curren"    =>    "\xA4",   # currency sign
    "yen"       =>    "\xA5",   # yen sign
    "brvbar"    =>    "\xA6",   # broken vertical bar
    "sect"      =>    "\xA7",   # section sign
    "uml"       =>    "\xA8",   # diaresis
    "copy"      =>    "\xA9",   # Copyright symbol
    "ordf"      =>    "\xAA",   # feminine ordinal indicator
    "not"       =>    "\xAC",   # not sign
    "shy"       =>    '',       # soft (discretionary) hyphen
    "reg"       =>    "\xAE",   # registered trademark
    "macr"      =>    "\xAF",   # macron, overline
    "deg"       =>    "\xB0",   # degree sign
    "plusmn"    =>    "\xB1",   # plus-minus sign
    "sup2"      =>    "\xB2",   # superscript 2
    "sup3"      =>    "\xB3",   # superscript 3
    "acute"     =>    "\xB4",   # acute accent
    "micro"     =>    "\xB5",   # micro sign
    "para"      =>    "\xB6",   # pilcrow sign = paragraph sign
    "middot"    =>    "\xB7",   # middle dot = Georgian comma
    "cedil"     =>    "\xB8",   # cedilla
    "sup1"      =>    "\xB9",   # superscript 1
    "ordm"      =>    "\xBA",   # masculine ordinal indicator
    "frac14"    =>    "\xBC",   # vulgar fraction one quarter
    "frac12"    =>    "\xBD",   # vulgar fraction one half
    "frac34"    =>    "\xBE",   # vulgar fraction three quarters
    "iquest"    =>    "\xBF",   # inverted question mark
    "times"     =>    "\xD7",   # multiplication sign
    "divide"    =>    "\xF7",   # division sign

    "nbsp"      =>    "\x01",   # non-breaking space
);


##############################################################################
# Initialization
##############################################################################

# Initialize the object.  Must be sure to call our parent initializer.
sub initialize {
    my $self = shift;

    $$self{alt}      = 0  unless defined $$self{alt};
    $$self{indent}   = 4  unless defined $$self{indent};
    $$self{margin}   = 0  unless defined $$self{margin};
    $$self{loose}    = 0  unless defined $$self{loose};
    $$self{sentence} = 0  unless defined $$self{sentence};
    $$self{width}    = 76 unless defined $$self{width};

    # Figure out what quotes we'll be using for C<> text.
    $$self{quotes} ||= '"';
    if ($$self{quotes} eq 'none') {
        $$self{LQUOTE} = $$self{RQUOTE} = '';
    } elsif (length ($$self{quotes}) == 1) {
        $$self{LQUOTE} = $$self{RQUOTE} = $$self{quotes};
    } elsif ($$self{quotes} =~ /^(.)(.)$/
             || $$self{quotes} =~ /^(..)(..)$/) {
        $$self{LQUOTE} = $1;
        $$self{RQUOTE} = $2;
    } else {
        croak qq(Invalid quote specification "$$self{quotes}");
    }

    # Stack of indentations.
    $$self{INDENTS}  = [];

    # Current left margin.
    $$self{MARGIN} = $$self{indent} + $$self{margin};

    $self->SUPER::initialize;

    # Tell Pod::Parser that we want the non-POD stuff too if code was set.
    $self->parseopts ('-want_nonPODs' => 1) if $$self{code};
}


##############################################################################
# Core overrides
##############################################################################

# Called for each command paragraph.  Gets the command, the associated
# paragraph, the line number, and a Pod::Paragraph object.  Just dispatches
# the command to a method named the same as the command.  =cut is handled
# internally by Pod::Parser.
sub command {
    my $self = shift;
    my $command = shift;
    return if $command eq 'pod';
    return if ($$self{EXCLUDE} && $command ne 'end');
    if ($self->can ('cmd_' . $command)) {
        $command = 'cmd_' . $command;
        $self->$command (@_);
    } else {
        my ($text, $line, $paragraph) = @_;
        my $file;
        ($file, $line) = $paragraph->file_line;
        $text =~ s/\n+\z//;
        $text = " $text" if ($text =~ /^\S/);
        warn qq($file:$line: Unknown command paragraph: =$command$text\n);
        return;
    }
}

# Called for a verbatim paragraph.  Gets the paragraph, the line number, and a
# Pod::Paragraph object.  Just output it verbatim, but with tabs converted to
# spaces.
sub verbatim {
    my $self = shift;
    return if $$self{EXCLUDE};
    $self->item if defined $$self{ITEM};
    local $_ = shift;
    return if /^\s*$/;
    s/^(\s*\S+)/(' ' x $$self{MARGIN}) . $1/gme;
    $self->output ($_);
}

# Called for a regular text block.  Gets the paragraph, the line number, and a
# Pod::Paragraph object.  Perform interpolation and output the results.
sub textblock {
    my $self = shift;
    return if $$self{EXCLUDE};
    $self->output ($_[0]), return if $$self{VERBATIM};
    local $_ = shift;
    my $line = shift;

    # Interpolate and output the paragraph.
    $_ = $self->interpolate ($_, $line);
    s/\s+$/\n/;
    if (defined $$self{ITEM}) {
        $self->item ($_ . "\n");
    } else {
        $self->output ($self->reformat ($_ . "\n"));
    }
}

# Called for a formatting code.  Gets the command, argument, and a
# Pod::InteriorSequence object and is expected to return the resulting text.
# Calls methods for code, bold, italic, file, and link to handle those types
# of codes, and handles S<>, E<>, X<>, and Z<> directly.
sub interior_sequence {
    local $_;
    my ($self, $command, $seq);
    ($self, $command, $_, $seq) = @_;

    # We have to defer processing of the inside of an L<> formatting code.  If
    # this code is nested inside an L<> code, return the literal raw text of
    # it.
    my $parent = $seq->nested;
    while (defined $parent) {
        return $seq->raw_text if ($parent->cmd_name eq 'L');
        $parent = $parent->nested;
    }

    # Index entries are ignored in plain text.
    return '' if ($command eq 'X' || $command eq 'Z');

    # Expand escapes into the actual character now, warning if invalid.
    if ($command eq 'E') {
        if (/^\d+$/) {
            return chr;
        } else {
            return $ESCAPES{$_} if defined $ESCAPES{$_};
            my ($file, $line) = $seq->file_line;
            warn "$file:$line: Unknown escape: E<$_>\n";
            return "E<$_>";
        }
    }

    # For all the other formatting codes, empty content produces no output.
    return if $_ eq '';

    # For S<>, compress all internal whitespace and then map spaces to \01.
    # When we output the text, we'll map this back.
    if ($command eq 'S') {
        s/\s+/ /g;
        tr/ /\01/;
        return $_;
    }

    # Anything else needs to get dispatched to another method.
    if    ($command eq 'B') { return $self->seq_b ($_) }
    elsif ($command eq 'C') { return $self->seq_c ($_) }
    elsif ($command eq 'F') { return $self->seq_f ($_) }
    elsif ($command eq 'I') { return $self->seq_i ($_) }
    elsif ($command eq 'L') { return $self->seq_l ($_, $seq) }
    else {
        my ($file, $line) = $seq->file_line;
        warn "$file:$line: Unknown formatting code: $command<$_>\n";
    }
}

# Called for each paragraph that's actually part of the POD.  We take
# advantage of this opportunity to untabify the input.  Also, if given the
# code option, we may see paragraphs that aren't part of the POD and need to
# output them directly.
sub preprocess_paragraph {
    my $self = shift;
    local $_ = shift;
    1 while s/^(.*?)(\t+)/$1 . ' ' x (length ($2) * 8 - length ($1) % 8)/me;
    $self->output_code ($_) if $self->cutting;
    $_;
}


##############################################################################
# Command paragraphs
##############################################################################

# All command paragraphs take the paragraph and the line number.

# First level heading.
sub cmd_head1 {
    my ($self, $text, $line) = @_;
    $self->heading ($text, $line, 0, '====');
}

# Second level heading.
sub cmd_head2 {
    my ($self, $text, $line) = @_;
    $self->heading ($text, $line, $$self{indent} / 2, '==  ');
}

# Third level heading.
sub cmd_head3 {
    my ($self, $text, $line) = @_;
    $self->heading ($text, $line, $$self{indent} * 2 / 3 + 0.5, '=   ');
}

# Third level heading.
sub cmd_head4 {
    my ($self, $text, $line) = @_;
    $self->heading ($text, $line, $$self{indent} * 3 / 4 + 0.5, '-   ');
}

# Start a list.
sub cmd_over {
    my $self = shift;
    local $_ = shift;
    $self->item ("\n\n") if defined $$self{ITEM};
    unless (/^[-+]?\d+\s+$/) { $_ = $$self{indent} }
    push (@{ $$self{INDENTS} }, $$self{MARGIN});
    $$self{MARGIN} += ($_ + 0);
}

# End a list.
sub cmd_back {
    my ($self, $text, $line, $paragraph) = @_;
    $self->item ("\n\n") if defined $$self{ITEM};
    $$self{MARGIN} = pop @{ $$self{INDENTS} };
    unless (defined $$self{MARGIN}) {
        my $file;
        ($file, $line) = $paragraph->file_line;
        warn "$file:$line: Unmatched =back\n";
        $$self{MARGIN} = $$self{indent};
    }
}

# An individual list item.
sub cmd_item {
    my $self = shift;
    if (defined $$self{ITEM}) { $self->item }
    local $_ = shift;
    s/\s+$//;
    $$self{ITEM} = $_ ? $self->interpolate ($_) : '*';
}

# Begin a block for a particular translator.  Setting VERBATIM triggers
# special handling in textblock().
sub cmd_begin {
    my $self = shift;
    local $_ = shift;
    my ($kind) = /^(\S+)/ or return;
    if ($kind eq 'text') {
        $$self{VERBATIM} = 1;
    } else {
        $$self{EXCLUDE} = 1;
    }
}

# End a block for a particular translator.  We assume that all =begin/=end
# pairs are properly closed.
sub cmd_end {
    my $self = shift;
    $$self{EXCLUDE} = 0;
    $$self{VERBATIM} = 0;
}

# One paragraph for a particular translator.  Ignore it unless it's intended
# for text, in which case we treat it as a verbatim text block.
sub cmd_for {
    my $self = shift;
    local $_ = shift;
    my $line = shift;
    return unless s/^text\b[ \t]*\n?//;
    $self->verbatim ($_, $line);
}


##############################################################################
# Formatting codes
##############################################################################

# The simple ones.  These are here mostly so that subclasses can override them
# and do more complicated things.
sub seq_b { return $_[0]{alt} ? "``$_[1]''" : $_[1] }
sub seq_f { return $_[0]{alt} ? "\"$_[1]\"" : $_[1] }
sub seq_i { return '*' . $_[1] . '*' }

# Apply a whole bunch of messy heuristics to not quote things that don't
# benefit from being quoted.  These originally come from Barrie Slaymaker and
# largely duplicate code in Pod::Man.
sub seq_c {
    my $self = shift;
    local $_ = shift;

    # A regex that matches the portion of a variable reference that's the
    # array or hash index, separated out just because we want to use it in
    # several places in the following regex.
    my $index = '(?: \[.*\] | \{.*\} )?';

    # Check for things that we don't want to quote, and if we find any of
    # them, return the string with just a font change and no quoting.
    m{
      ^\s*
      (?:
         ( [\'\`\"] ) .* \1                             # already quoted
       | \` .* \'                                       # `quoted'
       | \$+ [\#^]? \S $index                           # special ($^Foo, $")
       | [\$\@%&*]+ \#? [:\'\w]+ $index                 # plain var or func
       | [\$\@%&*]* [:\'\w]+ (?: -> )? \(\s*[^\s,]\s*\) # 0/1-arg func call
       | [+-]? ( \d[\d.]* | \.\d+ ) (?: [eE][+-]?\d+ )? # a number
       | 0x [a-fA-F\d]+                                 # a hex constant
      )
      \s*\z
     }xo && return $_;

    # If we didn't return, go ahead and quote the text.
    return $$self{alt} ? "``$_''" : "$$self{LQUOTE}$_$$self{RQUOTE}";
}

# Handle links.  Since this is plain text, we can't actually make any real
# links, so this is all to figure out what text we print out.  Most of the
# work is done by Pod::ParseLink.
sub seq_l {
    my ($self, $link, $seq) = @_;
    my ($text, $type) = (parselink ($link))[1,4];
    my ($file, $line) = $seq->file_line;
    $text = $self->interpolate ($text, $line);
    $text = '<' . $text . '>' if $type eq 'url';
    return $text || '';
}


##############################################################################
# Header handling
##############################################################################

# The common code for handling all headers.  Takes the interpolated header
# text, the line number, the indentation, and the surrounding marker for the
# alt formatting method.
sub heading {
    my ($self, $text, $line, $indent, $marker) = @_;
    $self->item ("\n\n") if defined $$self{ITEM};
    $text =~ s/\s+$//;
    $text = $self->interpolate ($text, $line);
    if ($$self{alt}) {
        my $closemark = reverse (split (//, $marker));
        my $margin = ' ' x $$self{margin};
        $self->output ("\n" . "$margin$marker $text $closemark" . "\n\n");
    } else {
        $text .= "\n" if $$self{loose};
        my $margin = ' ' x ($$self{margin} + $indent);
        $self->output ($margin . $text . "\n");
    }
}


##############################################################################
# List handling
##############################################################################

# This method is called whenever an =item command is complete (in other words,
# we've seen its associated paragraph or know for certain that it doesn't have
# one).  It gets the paragraph associated with the item as an argument.  If
# that argument is empty, just output the item tag; if it contains a newline,
# output the item tag followed by the newline.  Otherwise, see if there's
# enough room for us to output the item tag in the margin of the text or if we
# have to put it on a separate line.
sub item {
    my $self = shift;
    local $_ = shift;
    my $tag = $$self{ITEM};
    unless (defined $tag) {
        carp "Item called without tag";
        return;
    }
    undef $$self{ITEM};
    my $indent = $$self{INDENTS}[-1];
    unless (defined $indent) { $indent = $$self{indent} }
    my $margin = ' ' x $$self{margin};
    if (!$_ || /^\s+$/ || ($$self{MARGIN} - $indent < length ($tag) + 1)) {
        my $realindent = $$self{MARGIN};
        $$self{MARGIN} = $indent;
        my $output = $self->reformat ($tag);
        $output =~ s/^$margin /$margin:/ if ($$self{alt} && $indent > 0);
        $output =~ s/\n*$/\n/;

        # If the text is just whitespace, we have an empty item paragraph;
        # this can result from =over/=item/=back without any intermixed
        # paragraphs.  Insert some whitespace to keep the =item from merging
        # into the next paragraph.
        $output .= "\n" if $_ && $_ =~ /^\s*$/;

        $self->output ($output);
        $$self{MARGIN} = $realindent;
        $self->output ($self->reformat ($_)) if $_ && /\S/;
    } else {
        my $space = ' ' x $indent;
        $space =~ s/^$margin /$margin:/ if $$self{alt};
        $_ = $self->reformat ($_);
        s/^$margin /$margin:/ if ($$self{alt} && $indent > 0);
        my $tagspace = ' ' x length $tag;
        s/^($space)$tagspace/$1$tag/ or warn "Bizarre space in item";
        $self->output ($_);
    }
}


##############################################################################
# Output formatting
##############################################################################

# Wrap a line, indenting by the current left margin.  We can't use Text::Wrap
# because it plays games with tabs.  We can't use formline, even though we'd
# really like to, because it screws up non-printing characters.  So we have to
# do the wrapping ourselves.
sub wrap {
    my $self = shift;
    local $_ = shift;
    my $output = '';
    my $spaces = ' ' x $$self{MARGIN};
    my $width = $$self{width} - $$self{MARGIN};
    while (length > $width) {
        if (s/^([^\n]{0,$width})\s+// || s/^([^\n]{$width})//) {
            $output .= $spaces . $1 . "\n";
        } else {
            last;
        }
    }
    $output .= $spaces . $_;
    $output =~ s/\s+$/\n\n/;
    $output;
}

# Reformat a paragraph of text for the current margin.  Takes the text to
# reformat and returns the formatted text.
sub reformat {
    my $self = shift;
    local $_ = shift;

    # If we're trying to preserve two spaces after sentences, do some munging
    # to support that.  Otherwise, smash all repeated whitespace.
    if ($$self{sentence}) {
        s/ +$//mg;
        s/\.\n/. \n/g;
        s/\n/ /g;
        s/   +/  /g;
    } else {
        s/\s+/ /g;
    }
    $self->wrap ($_);
}

# Output text to the output device.
sub output { $_[1] =~ tr/\01/ /; print { $_[0]->output_handle } $_[1] }

# Output a block of code (something that isn't part of the POD text).  Called
# by preprocess_paragraph only if we were given the code option.  Exists here
# only so that it can be overridden by subclasses.
sub output_code { $_[0]->output ($_[1]) }


##############################################################################
# Backwards compatibility
##############################################################################

# The old Pod::Text module did everything in a pod2text() function.  This
# tries to provide the same interface for legacy applications.
sub pod2text {
    my @args;

    # This is really ugly; I hate doing option parsing in the middle of a
    # module.  But the old Pod::Text module supported passing flags to its
    # entry function, so handle -a and -<number>.
    while ($_[0] =~ /^-/) {
        my $flag = shift;
        if    ($flag eq '-a')       { push (@args, alt => 1)    }
        elsif ($flag =~ /^-(\d+)$/) { push (@args, width => $1) }
        else {
            unshift (@_, $flag);
            last;
        }
    }

    # Now that we know what arguments we're using, create the parser.
    my $parser = Pod::Text->new (@args);

    # If two arguments were given, the second argument is going to be a file
    # handle.  That means we want to call parse_from_filehandle(), which means
    # we need to turn the first argument into a file handle.  Magic open will
    # handle the <&STDIN case automagically.
    if (defined $_[1]) {
        my @fhs = @_;
        local *IN;
        unless (open (IN, $fhs[0])) {
            croak ("Can't open $fhs[0] for reading: $!\n");
            return;
        }
        $fhs[0] = \*IN;
        return $parser->parse_from_filehandle (@fhs);
    } else {
        return $parser->parse_from_file (@_);
    }
}


##############################################################################
# Module return value and documentation
##############################################################################

1;
__END__

=head1 NAME

Pod::Text - Convert POD data to formatted ASCII text

=head1 SYNOPSIS

    use Pod::Text;
    my $parser = Pod::Text->new (sentence => 0, width => 78);

    # Read POD from STDIN and write to STDOUT.
    $parser->parse_from_filehandle;

    # Read POD from file.pod and write to file.txt.
    $parser->parse_from_file ('file.pod', 'file.txt');

=head1 DESCRIPTION

Pod::Text is a module that can convert documentation in the POD format (the
preferred language for documenting Perl) into formatted ASCII.  It uses no
special formatting controls or codes whatsoever, and its output is therefore
suitable for nearly any device.

As a derived class from Pod::Parser, Pod::Text supports the same methods and
interfaces.  See L<Pod::Parser> for all the details; briefly, one creates a
new parser with C<< Pod::Text->new() >> and then calls either
parse_from_filehandle() or parse_from_file().

new() can take options, in the form of key/value pairs, that control the
behavior of the parser.  The currently recognized options are:

=over 4

=item alt

If set to a true value, selects an alternate output format that, among other
things, uses a different heading style and marks C<=item> entries with a
colon in the left margin.  Defaults to false.

=item code

If set to a true value, the non-POD parts of the input file will be included
in the output.  Useful for viewing code documented with POD blocks with the
POD rendered and the code left intact.

=item indent

The number of spaces to indent regular text, and the default indentation for
C<=over> blocks.  Defaults to 4.

=item loose

If set to a true value, a blank line is printed after a C<=head1> heading.
If set to false (the default), no blank line is printed after C<=head1>,
although one is still printed after C<=head2>.  This is the default because
it's the expected formatting for manual pages; if you're formatting
arbitrary text documents, setting this to true may result in more pleasing
output.

=item margin

The width of the left margin in spaces.  Defaults to 0.  This is the margin
for all text, including headings, not the amount by which regular text is
indented; for the latter, see the I<indent> option.  To set the right
margin, see the I<width> option.

=item quotes

Sets the quote marks used to surround CE<lt>> text.  If the value is a
single character, it is used as both the left and right quote; if it is two
characters, the first character is used as the left quote and the second as
the right quoted; and if it is four characters, the first two are used as
the left quote and the second two as the right quote.

This may also be set to the special value C<none>, in which case no quote
marks are added around CE<lt>> text.

=item sentence

If set to a true value, Pod::Text will assume that each sentence ends in two
spaces, and will try to preserve that spacing.  If set to false, all
consecutive whitespace in non-verbatim paragraphs is compressed into a
single space.  Defaults to true.

=item width

The column at which to wrap text on the right-hand side.  Defaults to 76.

=back

The standard Pod::Parser method parse_from_filehandle() takes up to two
arguments, the first being the file handle to read POD from and the second
being the file handle to write the formatted output to.  The first defaults
to STDIN if not given, and the second defaults to STDOUT.  The method
parse_from_file() is almost identical, except that its two arguments are the
input and output disk files instead.  See L<Pod::Parser> for the specific
details.

=head1 DIAGNOSTICS

=over 4

=item Bizarre space in item

=item Item called without tag

(W) Something has gone wrong in internal C<=item> processing.  These
messages indicate a bug in Pod::Text; you should never see them.

=item Can't open %s for reading: %s

(F) Pod::Text was invoked via the compatibility mode pod2text() interface
and the input file it was given could not be opened.

=item Invalid quote specification "%s"

(F) The quote specification given (the quotes option to the constructor) was
invalid.  A quote specification must be one, two, or four characters long.

=item %s:%d: Unknown command paragraph: %s

(W) The POD source contained a non-standard command paragraph (something of
the form C<=command args>) that Pod::Man didn't know about.  It was ignored.

=item %s:%d: Unknown escape: %s

(W) The POD source contained an C<EE<lt>E<gt>> escape that Pod::Text didn't
know about.

=item %s:%d: Unknown formatting code: %s

(W) The POD source contained a non-standard formatting code (something of
the form C<XE<lt>E<gt>>) that Pod::Text didn't know about.

=item %s:%d: Unmatched =back

(W) Pod::Text encountered a C<=back> command that didn't correspond to an
C<=over> command.

=back

=head1 RESTRICTIONS

Embedded Ctrl-As (octal 001) in the input will be mapped to spaces on
output, due to an internal implementation detail.

=head1 NOTES

This is a replacement for an earlier Pod::Text module written by Tom
Christiansen.  It has a revamped interface, since it now uses Pod::Parser,
but an interface roughly compatible with the old Pod::Text::pod2text()
function is still available.  Please change to the new calling convention,
though.

The original Pod::Text contained code to do formatting via termcap
sequences, although it wasn't turned on by default and it was problematic to
get it to work at all.  This rewrite doesn't even try to do that, but a
subclass of it does.  Look for L<Pod::Text::Termcap>.

=head1 SEE ALSO

L<Pod::Parser>, L<Pod::Text::Termcap>, L<pod2text(1)>

The current version of this module is always available from its web site at
L<http://www.eyrie.org/~eagle/software/podlators/>.  It is also part of the
Perl core distribution as of 5.6.0.

=head1 AUTHOR

Russ Allbery <rra@stanford.edu>, based I<very> heavily on the original
Pod::Text by Tom Christiansen <tchrist@mox.perl.com> and its conversion to
Pod::Parser by Brad Appleton <bradapp@enteract.com>.

=head1 COPYRIGHT AND LICENSE

Copyright 1999, 2000, 2001, 2002 by Russ Allbery <rra@stanford.edu>.

This program is free software; you may redistribute it and/or modify it
under the same terms as Perl itself.

=cut

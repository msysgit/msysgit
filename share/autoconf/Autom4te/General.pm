# autoconf -- create `configure' using m4 macros
# Copyright (C) 2001, 2002 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

package Autom4te::General;

use 5.005_03;
use Exporter;
use File::Basename;
use File::Spec;
use File::stat;
use IO::File;
use Carp;
use strict;

use vars qw (@ISA @EXPORT);

@ISA = qw (Exporter);

# Variables we define and export.
my @export_vars =
  qw ($debug $force $help $me $tmp $verbose $version);

# Functions we define and export.
my @export_subs =
  qw (&backname &catfile &canonpath &debug &error
      &file_name_is_absolute &find_configure_ac &find_file
      &getopt &mktmpdir &mtime
      &uniq &update_file &up_to_date_p &verbose &xsystem &xqx);

# Functions we forward (coming from modules we use).
my @export_forward_subs =
  qw (&basename &dirname &fileparse);

@EXPORT = (@export_vars, @export_subs, @export_forward_subs);

# Variable we share with the main package.  Be sure to have a single
# copy of them: using `my' together with multiple inclusion of this
# package would introduce several copies.
use vars qw ($debug);
$debug = 0;

# Recreate all the files, or consider all the output files are obsolete.
use vars qw ($force);
$force = undef;

use vars qw ($help);
$help = undef;

use vars qw ($me);
$me = basename ($0);

# Our tmp dir.
use vars qw ($tmp);
$tmp = undef;

use vars qw ($verbose);
$verbose = 0;

use vars qw ($version);
$version = undef;


## ------------ ##
## Prototypes.  ##
## ------------ ##

sub verbose (@);


## ----- ##
## END.  ##
## ----- ##


# END
# ---
# Exit nonzero whenever closing STDOUT fails.
# Ideally we should `exit ($? >> 8)', unfortunately, for some reason
# I don't understand, whenever we `exit (1)' somewhere in the code,
# we arrive here with `$? = 29'.  I suspect some low level END routine
# might be responsible.  In this case, be sure to exit 1, not 29.
sub END
{
  my $exit_status = $? ? 1 : 0;

  use POSIX qw (_exit);

  if (!$debug && defined $tmp && -d $tmp)
    {
      if (<$tmp/*>)
	{
	  unlink <$tmp/*>
	    or carp ("$me: cannot empty $tmp: $!\n"), _exit (1);
	}
      rmdir $tmp
	or carp ("$me: cannot remove $tmp: $!\n"), _exit (1);
    }

  # This is required if the code might send any output to stdout
  # E.g., even --version or --help.  So it's best to do it unconditionally.
  close STDOUT
    or (carp "$me: closing standard output: $!\n"), _exit (1);

  _exit ($exit_status);
}


## ----------- ##
## Functions.  ##
## ----------- ##


# $BACKPATH
# &backname ($REL-DIR)
# --------------------
# If I `cd $REL-DIR', then to come back, I should `cd $BACKPATH'.
# For instance `src/foo' => `../..'.
# Works with non strictly increasing paths, i.e., `src/../lib' => `..'.
sub backname ($)
{
  my ($file) = @_;
  my $underscore = $_;
  my @res;

  foreach (split (/\//, $file))
    {
      next if $_ eq '.' || $_ eq '';
      if ($_ eq '..')
	{
	  pop @res;
	}
      else
	{
	  push (@res, '..');
	}
    }

  $_ = $underscore;
  return canonpath (catfile (@res))
}


# $FILE
# &catfile (@COMPONENT)
# ---------------------
sub catfile (@)
{
  my (@component) = @_;
  return File::Spec->catfile (@component);
}


# $FILE
# &canonpath ($FILE)
# ------------------
sub canonpath ($)
{
  my ($file) = @_;
  return File::Spec->canonpath ($file);
}


# &debug(@MESSAGE)
# ----------------
# Messages displayed only if $DEBUG and $VERBOSE.
sub debug (@)
{
  print STDERR "$me: ", @_, "\n"
    if $verbose && $debug;
}


# &error (@MESSAGE)
# -----------------
# Same as die or confess, depending on $debug.
sub error (@)
{
  if ($debug)
    {
      confess "$me: ", @_, "\n";
    }
  else
    {
      die "$me: ", @_, "\n";
    }
}


# $BOOLEAN
# &file_name_is_absolute ($FILE)
# ------------------------------
sub file_name_is_absolute ($)
{
  my ($file) = @_;
  return File::Spec->file_name_is_absolute ($file);
}


# $CONFIGURE_AC
# &find_configure_ac ([$DIRECTORY = `.'])
# ---------------------------------------
sub find_configure_ac (;$)
{
  my ($directory) = @_;
  $directory ||= '.';
  my $configure_ac = canonpath (catfile ($directory, 'configure.ac'));
  my $configure_in = canonpath (catfile ($directory, 'configure.in'));

  if (-f $configure_ac)
    {
      if (-f $configure_in)
	{
	  carp "$me: warning: `$configure_ac' and `$configure_in' both present.\n";
	  carp "$me: warning: proceeding with `$configure_ac'.\n";
	}
      return $configure_ac;
    }
  elsif (-f $configure_in)
    {
      return $configure_in;
    }
  return;
}


# $FILENAME
# find_file ($FILENAME, @INCLUDE)
# -------------------------------
# We match exactly the behavior of GNU M4: first look in the current
# directory (which includes the case of absolute file names), and, if
# the file is not absolute, just fail.  Otherwise, look in @INCLUDE.
#
# If the file is flagged as optional (ends with `?'), then return undef
# if absent.
sub find_file ($@)
{
  my ($filename, @include) = @_;
  my $optional = 0;

  $optional = 1
    if $filename =~ s/\?$//;

  return canonpath ($filename)
    if -e $filename;

  if (file_name_is_absolute ($filename))
    {
      error "no such file or directory: $filename"
	unless $optional;
      return undef;
    }

  foreach my $path (@include)
    {
      return canonpath (catfile ($path, $filename))
	if -e catfile ($path, $filename);
    }

  error "no such file or directory: $filename"
    unless $optional;

  return undef;
}


# getopt (%OPTION)
# ----------------
# Handle the %OPTION, plus all the common options.
# Work around Getopt bugs wrt `-'.
sub getopt (%)
{
  my (%option) = @_;
  use Getopt::Long;

  # F*k.  Getopt seems bogus and dies when given `-' with `bundling'.
  # If fixed some day, use this: '' => sub { push @ARGV, "-" }
  my $stdin = grep /^-$/, @ARGV;
  @ARGV = grep !/^-$/, @ARGV;
  %option = ("h|help"     => sub { print $help; exit 0 },
             "V|version"  => sub { print $version; exit 0 },

             "v|verbose"    => \$verbose,
             "d|debug"      => \$debug,
	     'f|force'      => \$force,

	     # User options last, so that they have precedence.
	     %option);
  Getopt::Long::Configure ("bundling", "pass_through");
  GetOptions (%option)
    or exit 1;

  foreach (grep { /^-./ } @ARGV)
    {
      print STDERR "$0: unrecognized option `$_'\n";
      print STDERR "Try `$0 --help' for more information.\n";
      exit (1);
    }

  push @ARGV, '-'
    if $stdin;
}


# mktmpdir ($SIGNATURE)
# ---------------------
# Create a temporary directory which name is based on $SIGNATURE.
sub mktmpdir ($)
{
  my ($signature) = @_;
  my $TMPDIR = $ENV{'TMPDIR'} || '/tmp';

  # If mktemp supports dirs, use it.
  $tmp = `(umask 077 &&
           mktemp -d -q "$TMPDIR/${signature}XXXXXX") 2>/dev/null`;
  chomp $tmp;

  if (!$tmp || ! -d $tmp)
    {
      $tmp = "$TMPDIR/$signature" . int (rand 10000) . ".$$";
      mkdir $tmp, 0700
	or croak "$me: cannot create $tmp: $!\n";
    }

  print STDERR "$me:$$: working in $tmp\n"
    if $debug;
}


# $MTIME
# MTIME ($FILE)
# -------------
# Return the mtime of $FILE.  Missing files, or `-' standing for STDIN
# or STDOUT are ``obsolete'', i.e., as old as possible.
sub mtime ($)
{
  my ($file) = @_;

  return 0
    if $file eq '-' || ! -f $file;

  my $stat = stat ($file)
    or croak "$me: cannot stat $file: $!\n";

  return $stat->mtime;
}


# @RES
# uniq (@LIST)
# ------------
# Return LIST with no duplicates.
sub uniq (@)
{
  my @res = ();
  my %seen = ();
  foreach my $item (@_)
    {
      if (! exists $seen{$item})
	{
	  $seen{$item} = 1;
	  push (@res, $item);
	}
    }
  return wantarray ? @res : "@res";
}


# $BOOLEAN
# &up_to_date_p ($FILE, @DEPS)
# ----------------------------
# Is $FILE more recent than @DEPS?
sub up_to_date_p ($@)
{
  my ($file, @dep) = @_;
  my $mtime = mtime ($file);

  foreach my $dep (@dep)
    {
      if ($mtime < mtime ($dep))
	{
	  debug "up_to_date ($file): outdated: $dep";
	  return 0;
	}
    }

  debug "up_to_date ($file): up to date";
  return 1;
}


# &update_file ($FROM, $TO)
# -------------------------
# Rename $FROM as $TO, preserving $TO timestamp if it has not changed.
# Recognize `$TO = -' standing for stdin.  $FROM is always removed/renamed.
sub update_file ($$)
{
  my ($from, $to) = @_;
  my $SIMPLE_BACKUP_SUFFIX = $ENV{'SIMPLE_BACKUP_SUFFIX'} || '~';
  use File::Compare;
  use File::Copy;

  if ($to eq '-')
    {
      my $in = new IO::File ("$from");
      my $out = new IO::File (">-");
      while ($_ = $in->getline)
	{
	  print $out $_;
	}
      $in->close;
      unlink ($from)
	or error "cannot not remove $from: $!";
      return;
    }

  if (-f "$to" && compare ("$from", "$to") == 0)
    {
      # File didn't change, so don't update its mod time.
      verbose "`$to' is unchanged";
      unlink ($from)
	or error "cannot not remove $from: $!";
      return
    }

  if (-f "$to")
    {
      # Back up and install the new one.
      move ("$to",  "$to$SIMPLE_BACKUP_SUFFIX")
	or error "cannot not backup $to: $!";
      move ("$from", "$to")
	or error "cannot not rename $from as $to: $!";
      verbose "`$to' is updated";
    }
  else
    {
      move ("$from", "$to")
	or error "cannot not rename $from as $to: $!";
      verbose "`$to' is created";
    }
}


# verbose(@MESSAGE)
# -----------------
sub verbose (@)
{
  print STDERR "$me: ", @_, "\n"
    if $verbose;
}


# xqx ($COMMAND)
# --------------
# Same as `qx' (but in scalar context), but fails on errors.
sub xqx ($)
{
  use POSIX qw (WIFEXITED WEXITSTATUS);

  my ($command) = @_;

  verbose "running: $command";
  my $res = `$command`;

  error ((split (' ', $command))[0]
	 . " failed with exit status: "
	 . WEXITSTATUS ($?))
    if WIFEXITED ($?) && WEXITSTATUS ($?) != 0;

  return $res;
}


# xsystem ($COMMAND)
# ------------------
sub xsystem ($)
{
  use POSIX qw (WEXITSTATUS);

  my ($command) = @_;

  verbose "running: $command";

  (system $command) == 0
    or error ((split (' ', $command))[0]
	      . " failed with exit status: "
	      . WEXITSTATUS ($?));
}


1; # for require

### Setup "GNU" style for perl-mode and cperl-mode.
## Local Variables:
## perl-indent-level: 2
## perl-continued-statement-offset: 2
## perl-continued-brace-offset: 0
## perl-brace-offset: 0
## perl-brace-imaginary-offset: 0
## perl-label-offset: -2
## cperl-indent-level: 2
## cperl-brace-offset: 0
## cperl-continued-brace-offset: 0
## cperl-label-offset: -2
## cperl-extra-newline-before-brace: t
## cperl-merge-trailing-else: nil
## cperl-continued-statement-offset: 2
## End:

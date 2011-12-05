#!/usr/bin/env perl

# docx2txt, a command-line utility to convert Docx documents to text format.
# Copyright (C) 2008-2009 Sandeep Kumar
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#
# This script extracts text from document.xml contained inside .docx file.
# Perl v5.8.2 was used for testing this script.
#
# Author : Sandeep Kumar (shimple0 -AT- Yahoo .DOT. COM)
#
# ChangeLog :
#
#    10/08/2008 - Initial version (v0.1)
#    15/08/2008 - Script takes two arguments [second optional] now and can be
#                 used independently to extract text from docx file. It accepts
#                 docx file directly, instead of xml file.
#    18/08/2008 - Added support for center and right justification of text that
#                 fits in a line 80 characters wide (adjustable).
#    03/09/2008 - Fixed the slip in usage message.
#    12/09/2008 - Slightly changed the script invocation and argument handling
#                 to incorporate some of the shell script functionality here.
#                 Added support to handle embedded urls in docx document.
#    23/09/2008 - Changed #! line to use /usr/bin/env - good suggestion from
#                 Rene Maroufi (info>AT<maroufi>DOT<net) to reduce user work
#                 during installation.
#    31/08/2009 - Added support for handling more escape characters.
#                 Using OS specific null device to redirect stderr.
#                 Saving text file in binary mode.
#    03/09/2009 - Updations based on feedback/suggestions from Sergei Kulakov
#                 (sergei>AT<dewia>DOT<com).
#                 - removal of non-document text in between TOC related tags.
#                 - display of hyperlink alongside linked text user controlled.
#                 - some character conversion updates
#    05/09/2009 - Merged cjustify and rjustify into single subroutine justify.
#                 Added more character conversions.
#                 Organised conversion mappings in tabular form for speedup and
#                 easy maintenance.
#                 Tweaked code to reduce number of passes over document content.
#    10/09/2009 - For leaner text experience, hyperlink is not displayed if
#                 hyperlink and hyperlinked text are same, even if user has
#                 enabled hyperlink display.
#                 Improved handling of short line justification. Many
#                 justification tag patterns were not captured earlier.
#    11/09/2009 - A directory holding the unzipped content of .docx file can
#                 also be specified as argument to the script, in place of file.
#    17/09/2009 - Removed trailing slashes from input directory name.
#                 Updated unzip command invocations to handle path names
#                 containing spaces.
#    01/10/2009 - Added support for configuration file.
#    02/10/2009 - Using single quotes to specify path for unzip command. 
#    04/10/2009 - Corrected configuration option name lineIndent to listIndent.
#


#
# The default settings below can be overridden via docx2txt.config - searched
# first in current directory and then in the same location as this script.
#

our $unzip = '/usr/bin/unzip';	# Windows path like 'C:/path/to/unzip.exe'
our $newLine = "\n";		# Alternative is "\r\n".
our $listIndent = "  ";		# Indent nested lists by "\t", " " etc.
our $lineWidth = 80;		# Line width, used for short line justification.
our $showHyperLink = "N";	# Show hyperlink alongside linked text.


# ToDo: Better list handling. Currently assumed 8 level nesting.
my @levchar = ('*', '+', 'o', '-', '**', '++', 'oo', '--');

#
# Character conversion tables
#

# Only amp, gt and lt are required for docx escapes, others are used for better
# text experience.
my %escChrs = (	amp => '&', gt => '>', lt => '<',
		acute => '\'', brvbar => '|', copy => '(C)', divide => '/',
		laquo => '<<', macr => '-', nbsp => ' ', raquo => '>>',
		reg => '(R)', shy => '-', times => 'x'
);

my %splchars = (
	"\xC2\xA0" => ' ',		# <nbsp>
	"\xC2\xA6" => '|',		# <brokenbar>
	"\xC2\xA9" => '(C)',		# <copyright>
	"\xC2\xAB" => '<<',		# <laquo>
	"\xC2\xAC" => '-',		# <negate>
	"\xC2\xAE" => '(R)',		# <regd>
	"\xC2\xB1" => '+-',		# <plusminus>
	"\xC2\xBB" => '>>',		# <raquo>

#	"\xC2\xA7" => '',		# <section>
#	"\xC2\xB6" => '',		# <para>

	"\xC3\x97" => 'x',		# <mul>
	"\xC3\xB7" => '/',		# <div>

	"\xE2\x80\x82" => '  ',		# <enspc>
	"\xE2\x80\x83" => '  ',		# <emspc>
	"\xE2\x80\x85" => ' ',		# <qemsp>
	"\xE2\x80\x93" => ' - ',	# <endash>
	"\xE2\x80\x94" => ' -- ',	# <emdash>
	"\xE2\x80\x98" => '`',		# <soq>
	"\xE2\x80\x99" => '\'',		# <scq>
	"\xE2\x80\x9C" => '"',		# <doq>
	"\xE2\x80\x9D" => '"',		# <dcq>
	"\xE2\x80\xA2" => '::',		# <diamond symbol>
	"\xE2\x80\xA6" => '...',	# <ellipsis>

	"\xE2\x84\xA2" => '(TM)',	# <trademark>

	"\xE2\x89\xA0" => '!=',		# <neq>
	"\xE2\x89\xA4" => '<=',		# <leq>
	"\xE2\x89\xA5" => '>=',		# <geq>

	#
	# Currency symbols
	#
	"\xC2\xA2" => 'cent',
	"\xC2\xA3" => 'Pound',
	"\xC2\xA5" => 'Yen',
	"\xE2\x82\xAC" => 'Euro'
);


#
# Check argument(s) sanity.
#

my $usage = <<USAGE;

Usage:	$0 <infile.docx> [outfile.txt|-]

	Use '-' as the outfile name to dump the text on STDOUT.
	Output is saved in infile.txt if second argument is omitted.

	infile.docx can also be a directory name holding the unzipped content
	of concerned .docx file.

USAGE

die $usage if (@ARGV == 0 || @ARGV > 2);


#
# Check for existence and readability of required file in specified directory,
# and whether it is a text file.
#

sub check_for_required_file_in_folder {
    stat("$_[1]/$_[0]");
    die "Can't read <$_[0]> in <$_[1]>!\n" if ! (-f _ && -r _);
    die "<$_[1]/$_[0]> does not seem to be a text file!\n" if ! -T _;
}

sub readFileInto
{
  local $/ = undef;
  open my $fh, "$_[0]" or die "Couldn't read file <$_[0]>!\n";
  binmode $fh;
  $_[1] = <$fh>;
  close $fh;
}


#
# Check whether first argument is specifying a directory holding extracted
# content of .docx file, or .docx file itself.
#

stat($ARGV[0]);

if (-d _) {
    check_for_required_file_in_folder("word/document.xml", $ARGV[0]);
    check_for_required_file_in_folder("word/_rels/document.xml.rels", $ARGV[0]);
    $inpIsDir = 'y';
}
else {
    die "Can't read docx file <$ARGV[0]>!\n" if ! (-f _ && -r _);
    die "<$ARGV[0]> does not seem to be docx file!\n" if -T _;
}


#
# Get user configuration, if any.
#

my %config;

if (-f "docx2txt.config") {
    %config = do 'docx2txt.config';
} elsif ($0 =~ m%^(.*[/\\])[^/\\]*?$%) {
    %config = do "$1docx2txt.config" if (-f "$1docx2txt.config");
}

if (%config) {
    foreach my $var (keys %config) {
        $$var = $config{$var};
    }
}


#
# Extract xml document content from argument docx file/directory.
#

if ($ENV{OS} =~ /^Windows/) {
    $nulldevice = "nul";
} else {
    $nulldevice = "/dev/null";
}

if ($inpIsDir eq 'y') {
    readFileInto("$ARGV[0]/word/document.xml", $content);
} else {
    $content = `"$unzip" -p "$ARGV[0]" word/document.xml 2>$nulldevice`;
}

die "Failed to extract required information from <$ARGV[0]>!\n" if ! $content;


#
# Be ready for outputting the extracted text contents.
#

if (@ARGV == 1) {
     $ARGV[1] = $ARGV[0];

     # Remove any trailing slashes to generate proper output filename, when
     # input is directory.
     $ARGV[1] =~ s%[/\\]+$%% if ($inpIsDir eq 'y');

     $ARGV[1] .= ".txt" if !($ARGV[1] =~ s/\.docx$/\.txt/);
}

my $txtfile;
open($txtfile, "> $ARGV[1]") || die "Can't create <$ARGV[1]> for output!\n";
binmode $txtfile;    # Ensure no auto-conversion of '\n' to '\r\n' on Windows.


#
# Gather information about header, footer, hyperlinks, images, footnotes etc.
#

if ($inpIsDir eq 'y') {
    readFileInto("$ARGV[0]/word/_rels/document.xml.rels", $_);
} else {
    $_ = `"$unzip" -p "$ARGV[0]" word/_rels/document.xml.rels 2>$nulldevice`;
}

my %docurels;
while (/<Relationship Id="(.*?)" Type=".*?\/([^\/]*?)" Target="(.*?)"( .*?)?\/>/g)
{
    $docurels{"$2:$1"} = $3;
}


#
# Subroutines for center and right justification of text in a line.
#

sub justify {
    my $len = length $_[1];

    if ($_[0] eq "center" && $len < ($lineWidth - 1)) {
        return ' ' x (($lineWidth - $len) / 2) . $_[1];
    } elsif ($_[0] eq "right" && $len < $lineWidth) {
        return ' ' x ($lineWidth - $len) . $_[1];
    } else {
        return $_[1];
    }
}

#
# Subroutines for dealing with embedded links and images
#

sub hyperlink {
    my $hlrid = $_[0];
    my $hltext = $_[1];
    my $hlink = $docurels{"hyperlink:$hlrid"};

    $hltext =~ s/<[^>]*?>//og;
    $hltext .= " [HYPERLINK: $hlink]" if ($showHyperLink eq "y" && $hltext ne $hlink);

    return $hltext;
}

#
# Subroutines for processing paragraph content.
#

sub processParagraph {
    my $para = $_[0] . "$newLine";
    my $align = $1 if ($_[0] =~ /<w:jc w:val="([^"]*?)"\/>/);

    $para =~ s/<.*?>//og;
    return justify($align,$para) if $align;

    return $para;
}


#
# Force configuration value to lowercase as expected by script.
#
$showHyperLink = lc $showHyperLink;


#
# Text extraction starts.
#

my %tag2chr = (tab => "\t", noBreakHyphen => "-", softHyphen => " - ");

$content =~ s/<?xml .*?\?>(\r)?\n//;

# Remove stuff between TOC related tags.
if ($content =~ m|<w:pStyle w:val="TOCHeading"/>|) {
    $content =~ s|<w:instrText[^>]*>.*?</w:instrText>||og;
}

$content =~ s{<w:(tab|noBreakHyphen|softHyphen)/>}|$tag2chr{$1}|og;

my $hr = '-' x $lineWidth . $newLine;
$content =~ s|<w:pBdr>.*?</w:pBdr>|$hr|og;

$content =~ s|<w:numPr><w:ilvl w:val="([0-9]+)"/>|$listIndent x $1 . "$levchar[$1] "|oge;

#
# Uncomment either of below two lines and comment above line, if dealing
# with more than 8 level nested lists.
#

# $content =~ s|<w:numPr><w:ilvl w:val="([0-9]+)"/>|$listIndent x $1 . '* '|oge;
# $content =~ s|<w:numPr><w:ilvl w:val="([0-9]+)"/>|'*' x ($1+1) . ' '|oge;

$content =~ s{<w:caps/>.*?(<w:t>|<w:t [^>]+>)(.*?)</w:t>}/uc $2/oge;

$content =~ s{<w:hyperlink r:id="(.*?)".*?>(.*?)</w:hyperlink>}/hyperlink($1,$2)/oge;

$content =~ s/<w:p [^>]+?>(.*?)<\/w:p>/processParagraph($1)/oge;

$content =~ s{<w:p [^/>]+?/>|</w:p>|<w:br/>}|$newLine|og;
$content =~ s/<.*?>//og;


#
# Convert non-ASCII characters/character sequences to ASCII characters.
#

$content =~ s/(\xE2..|\xC2.|\xC3.)/($splchars{$1} ? $splchars{$1} : $1)/oge;

#
# Convert docx specific escape chars first.
#
$content =~ s/(&)(amp|gt|lt)(;)/$escChrs{lc $2}/iog;

#
# Another pass for a better text experience, after sequences like "&amp;laquo;"
# are converted to "&laquo;".
#
$content =~ s/((&)([a-z]+)(;))/($escChrs{lc $3} ? $escChrs{lc $3} : $1)/ioge;


#
# Write the extracted and converted text contents to output.
#

print $txtfile $content;
close $txtfile;


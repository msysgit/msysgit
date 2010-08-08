package TAP::Harness::Archive;
use warnings;
use strict;
use base 'TAP::Harness';
use Cwd                     ();
use File::Basename          ();
use File::Temp              ();
use File::Spec              ();
use File::Path              ();
use File::Find              ();
use Archive::Tar            ();
use TAP::Parser             ();
use YAML::Tiny              ();
use TAP::Parser::Aggregator ();

=head1 NAME

TAP::Harness::Archive - Create an archive of TAP test results

=cut

our $VERSION = '0.14';

=head1 SYNOPSIS

    use TAP::Harness::Archive;
    my $harness = TAP::Harness::Archive->new(\%args);
    $harness->runtests(@tests);

=head1 DESCRIPTION

This module is a direct subclass of L<TAP::Harness> and behaves
in exactly the same way except for one detail. In addition to
outputting a running progress of the tests and an ending summary
it can also capture all of the raw TAP from the individual test
files or streams into an archive file (C<.tar> or C<.tar.gz>).

=head1 METHODS

All methods are exactly the same as our base L<TAP::Harness> except
for the following.

=head2 new

In addition to the options that L<TAP::Harness> allow to this method,
we also allow the following:

=over

=item archive

This is the name of the archive file to generate. We use L<Archive::Tar>
in the background so we only support C<.tar> and C<.tar.gz> archive file
formats. This can optionally be an existing directory that will have
the TAP archive's contents deposited therein without any file archiving
(no L<Archive::Tar> involved).

=item extra_files

This is an array reference to extra files that you want to include in the TAP
archive but which are not TAP files themselves. This is useful if you want to
include some log files that contain useful information about the test run.

=item extra_properties

This is a hash reference of extra properties that you've collected during your
test run. Some things you might want to include are the Perl version, the system's
architecture, the operating system, etc.

=back

=cut

my (%ARCHIVE_TYPES, @ARCHIVE_EXTENSIONS);
BEGIN {
    %ARCHIVE_TYPES = (
        'tar'    => 'tar',
        'tar.gz' => 'tar.gz',
        'tgz'    => 'tar.gz',
    );
    @ARCHIVE_EXTENSIONS = map { ".$_" } keys %ARCHIVE_TYPES;
}

sub new {
    my ($class, $args) = @_;
    $args ||= {};

    # these can't be passed on to Test::Harness
    my $archive     = delete $args->{archive};
    my $extra_files = delete $args->{extra_files};
    my $extra_props = delete $args->{extra_properties};

    $class->_croak("You must provide the name of the archive to create!")
      unless $archive;

    my $self = $class->SUPER::new($args);

    my $is_directory = -d $archive ? 1 : 0;
    if ($is_directory) {
        $self->{__archive_is_directory} = $is_directory;
        $self->{__archive_tempdir}      = $archive;
    } else {
        my $format = $class->_get_archive_format_from_filename($archive);

        # if it's not a format we understand, or it's not a directory
        $class->_croak("Archive is not a known format type!")
          unless $format && $ARCHIVE_TYPES{$format};

        $self->{__archive_file}    = $archive;
        $self->{__archive_format}  = $format;
        $self->{__archive_tempdir} = File::Temp::tempdir();
    }

    # handle any extra files
    if($extra_files) {
        ref $extra_files eq 'ARRAY' 
            or $class->_croak("extra_files must be an array reference!");
        foreach my $file (@$extra_files) {
            $class->_croak("extra_file $file does not exist!") unless -e $file;
            $class->_croak("extra_file $file is not readable!") unless -r $file;
        }
        $self->{__archive_extra_files} = $extra_files;
    }

    if($extra_props) {
        ref $extra_props eq 'HASH'
            or $class->_croak("extra_properties must be a hash reference!");
        $self->{__archive_extra_props} = $extra_props;
    }

    return $self;
}

sub _get_archive_format_from_filename {
    my ($self, $filename) = @_;

    # try to guess it if we don't have one
    my (undef, undef, $suffix) = File::Basename::fileparse($filename, @ARCHIVE_EXTENSIONS);
    $suffix =~ s/^\.//;
    return $ARCHIVE_TYPES{$suffix};
}

=head2 runtests

Takes the same arguments as L<TAP::Harness>'s version and returns the
same thing (a L<TAP::Parser::Aggregator> object). The only difference
is that in addition to the normal test running and progress output
we also create the TAP Archive when it's all done.

=cut

sub runtests {
    my ($self, @files) = @_;

    # tell TAP::Harness to put the raw tap someplace we can find it later
    my $dir = $self->{__archive_tempdir};
    $ENV{PERL_TEST_HARNESS_DUMP_TAP} = $dir;

    # get some meta information about this run
    my %meta = (
        file_order => \@files,
        start_time => time(),
    );

    my $aggregator = $self->SUPER::runtests(@files);

    $meta{stop_time} = time();

    my @parsers = $aggregator->parsers;
    for ( my $i = 0; $i < @parsers; $i++ ) {
        $parsers[ $i ] = {
            start_time  => $parsers[ $i ]->start_time,
            end_time    => $parsers[ $i ]->end_time,
            description => $files[ $i ],
        };
    }
    $meta{file_attributes} = \@parsers;

    my $cwd         = Cwd::getcwd();
    my $is_dir      = $self->{__archive_is_directory};
    my ($archive, $output_file);
    if( $is_dir ) {
        $output_file = $self->{__archive_tempdir};
    } else {
        $output_file = $self->{__archive_file};

        # go into the dir so that we can reference files
        # relatively and put them in the archive that way
        chdir($dir) or $self->_croak("Could not change to directory $dir: $!");

        unless (File::Spec->file_name_is_absolute($output_file)) {
            $output_file = File::Spec->catfile($cwd, $output_file);
        }

        # create the archive
        $archive = Archive::Tar->new();
        $archive->add_files($self->_get_all_tap_files);
        chdir($cwd) or $self->_croak("Could not return to directory $cwd: $!");
    }
 
    # add in any extra files
    if(my $x_files = $self->{__archive_extra_files}) {
        my @rel_x_files;
        foreach my $x_file (@$x_files) {
            # handle both relative and absolute file names
            my $rel_file;
            if( File::Spec->file_name_is_absolute($x_file) ) {
                $rel_file = File::Spec->abs2rel($x_file, $cwd);
            } else {
                $rel_file = $x_file;
            }
            push(@rel_x_files, $rel_file);
        }
        $archive->add_files(@rel_x_files) unless $is_dir;
        $meta{extra_files} = \@rel_x_files;
    }

    # add any extra_properties to the meta
    if(my $extra_props = $self->{__archive_extra_props}) {
        $meta{extra_properties} = $extra_props;
    }

    # create the YAML meta file
    my $yaml = YAML::Tiny->new();
    $yaml->[0] = \%meta;
    if( $is_dir ) {
        my $meta_file = File::Spec->catfile($output_file, 'meta.yml');
        open(my $out, '>', $meta_file) or die "Could not create meta.yml: $!";
        print $out $yaml->write_string;
        close($out);
    } else {
        $archive->add_data('meta.yml', $yaml->write_string);
        $archive->write($output_file, $self->{__archive_format} eq 'tar.gz') or die $archive->errstr;
        # be nice and clean up
        File::Path::rmtree($dir);
    }

    print "\nTAP Archive created at $output_file\n" unless $self->verbosity < -1;

    return $aggregator;
}

sub _get_all_tap_files {
    my ($self, $dir, $meta) = @_;
    $dir ||= $self->{__archive_tempdir};
    my @files;
    my %x_files;
    if($meta && $meta->{extra_files}) {
        %x_files = map { $_ => 1 } @{$meta->{extra_files}};
    }

    File::Find::find(
        {
            no_chdir => 1,
            wanted   => sub {
                return if /^\./;
                return if -d;
                my $rel_name = File::Spec->abs2rel($_, $dir);
                return if $rel_name eq 'meta.yml';
                push(@files, $rel_name) unless $x_files{$rel_name};
            },
        },
        $dir
    );
    return @files;
}

=head2 aggregator_from_archive

This class method will return a L<TAP::Parser::Aggregator> object
when given a TAP Archive to open and parse. It's pretty much the reverse
of creating a TAP Archive from using C<new> and C<runtests>.

It takes a hash of arguments which are as follows:

=over

=item archive

The path to the archive file. This can also be a directory if you created
the archive as a directory.  This is required.

=item parser_callbacks

This is a hash ref containing callbacks for the L<TAP::Parser> objects
that are created while parsing the TAP files. See the L<TAP::Parser>
documentation for details about these callbacks.

=item made_parser_callback

This callback is executed every time a new L<TAP::Parser> object
is created. It will be passed the new parser object, the name
of the file to be parsed, and also the full (temporary) path of that file.

=item meta_yaml_callback

This is a subroutine that will be called if we find and parse a YAML
file containing meta information about the test run in the archive.
The structure of the YAML file will be passed in as an argument.

=back

    my $aggregator = TAP::Harness::Archive->aggregator_from_archive(
        {
            archive          => 'my_tests.tar.gz',
            parser_callbacks => {
                plan    => sub { warn "Nice to see you plan ahead..." },
                unknown => sub { warn "Your TAP is bad!" },
            },
            made_parser_callback => sub {
                my ($parser, $file, $full_path) = @_;
                warn "$file is temporarily located at $full_path\n";
            }
            
        }
    );

=cut

sub aggregator_from_archive {
    my ($class, $args) = @_;
    my $meta;

    my $file = $args->{archive}
      or $class->_croak("You must provide the path to the archive!");

    my $is_directory = -d $file;

    # extract the files out into a temporary directory
    my $dir = $is_directory ? $file : File::Temp::tempdir();
    my $cwd = Cwd::getcwd();
    chdir($dir) or $class->_croak("Could not change to directory $dir: $!");
    my @files;

    Archive::Tar->new()->extract_archive($file) unless $is_directory;
    my @tap_files;

    # do we have a meta.yml file in the archive?
    my $yaml_file = File::Spec->catfile($dir, 'meta.yml');
    if( -e $yaml_file) {

        # parse it into a structure
        $meta = YAML::Tiny->new()->read($yaml_file);
        die "Could not read YAML $yaml_file: " . YAML::Tiny->errstr if YAML::Tiny->errstr;

        if($args->{meta_yaml_callback}) {
            $args->{meta_yaml_callback}->($meta);
        }
        $meta = $meta->[0];

        if($meta->{file_order} && ref $meta->{file_order} eq 'ARRAY') {
            foreach my $file (@{$meta->{file_order}}) {
                push(@tap_files, $file) if -e $file;
            }
        }
    }

    # if we didn't get the files from the YAML file, just find them all
    unless(@tap_files) {
        @tap_files = $class->_get_all_tap_files($dir, $meta);
    }

    # now create the aggregator
    my $aggregator = TAP::Parser::Aggregator->new();
    foreach my $tap_file (@tap_files) {
        open(my $fh, $tap_file) or die "Could not open $tap_file for reading: $!";
        my $parser = TAP::Parser->new({source => $fh, callbacks => $args->{parser_callbacks}});
        if($args->{made_parser_callback}) {
            $args->{made_parser_callback}->($parser, $tap_file, File::Spec->catfile($dir, $tap_file));
        }
        $parser->run;
        $aggregator->add($tap_file, $parser);
    }

    # be nice and clean up
    chdir($cwd) or $class->_croak("Could not return to directory $cwd: $!");
    File::Path::rmtree($dir) unless $is_directory;

    return $aggregator;
}

=head1 AUTHOR

Michael Peters, C<< <mpeters at plusthree.com> >>

=head1 BUGS

Please report any bugs or feature requests to
C<bug-tap-harness-archive at rt.cpan.org>, or through the web interface at
L<http://rt.cpan.org/NoAuth/ReportBug.html?Queue=TAP-Harness-Archive>.
I will be notified, and then you'll automatically be notified of progress on
your bug as I make changes.

=head1 SUPPORT

You can find documentation for this module with the perldoc command.

    perldoc TAP::Harness::Archive

You can also look for information at:

=over 4

=item * AnnoCPAN: Annotated CPAN documentation

L<http://annocpan.org/dist/TAP-Harness-Archive>

=item * CPAN Ratings

L<http://cpanratings.perl.org/d/TAP-Harness-Archive>

=item * RT: CPAN's request tracker

L<http://rt.cpan.org/NoAuth/Bugs.html?Dist=TAP-Harness-Archive>

=item * Search CPAN

L<http://search.cpan.org/dist/TAP-Harness-Archive>

=back

=head1 ACKNOWLEDGEMENTS

=over

=item * A big thanks to Plus Three, LP (L<http://www.plusthree.com>) for sponsoring my work on this module and other open source pursuits.

=item * Andy Armstrong

=back

=head1 COPYRIGHT & LICENSE

Copyright 2007 Michael Peters, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut

1;    # End of TAP::Harness::Archive

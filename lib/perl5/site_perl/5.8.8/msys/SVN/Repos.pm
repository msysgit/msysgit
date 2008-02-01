use strict;
use warnings;

package SVN::Repos;
use SVN::Base qw(Repos svn_repos_);

=head1 NAME

SVN::Repos - Subversion repository functions

=head1 SYNOPSIS

    require SVN::Core;
    require SVN::Repos;
    require SVN::Fs;

    my $repos = SVN::Repos::open ('/path/to/repos');
    print $repos->fs->youngest_rev;

=head1 DESCRIPTION

SVN::Repos wraps the functions in svn_repos.h. The actual namespace
for repos object is _p_svn_repos_t.

=head2 CONSTRUCTORS

=over

=item open ($path)

=item create ($path, undef, undef, $config, $fs_config)

=back

=head2 METHODS

Please consult the svn_repos.h section in the Subversion
API. Functions taking svn_repos_t * as the first inbound argument
could be used as methods of the object returned by open or create.

=cut

package _p_svn_repos_t;

my @methods = qw/fs get_logs get_commit_editor get_commit_editor2
                 path db_env lock_dir
		 db_lockfile hook_dir start_commit_hook
		 pre_commit_hook post_commit_hook
		 pre_revprop_change_hook post_revprop_change_hook
		 dated_revision fs_commit_txn fs_begin_txn_for_commit
		 fs_begin_txn_for_update fs_change_rev_prop
		 node_editor dump_fs load_fs get_fs_build_parser/;

for (@methods) {
    no strict 'refs';
    *{$_} = *{"SVN::Repos::$_"};
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

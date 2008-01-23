# This file is part of Autoconf.                          -*- Autoconf -*-
# M4 macros used in building test suites.
# Copyright (C) 2000, 2001, 2002 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# As a special exception, the Free Software Foundation gives unlimited
# permission to copy, distribute and modify the configure scripts that
# are the output of Autoconf.  You need not follow the terms of the GNU
# General Public License when using or distributing such scripts, even
# though portions of the text of Autoconf appear in them.  The GNU
# General Public License (GPL) does govern all other use of the material
# that constitutes the Autoconf program.
#
# Certain portions of the Autoconf source text are designed to be copied
# (in certain cases, depending on the input) into the output of
# Autoconf.  We call these the "data" portions.  The rest of the Autoconf
# source text consists of comments plus executable code that decides which
# of the data portions to output in any given case.  We call these
# comments and executable code the "non-data" portions.  Autoconf never
# copies any of the non-data portions into its output.
#
# This special exception to the GPL applies to versions of Autoconf
# released by the Free Software Foundation.  When you make and
# distribute a modified version of Autoconf, you may extend this special
# exception to the GPL to apply to your modified version as well, *unless*
# your modified version has the potential to copy into its output some
# of the text that was the non-data portion of the version that you started
# with.  (In other words, unless your change moves or copies text from
# the non-data portions to the data portions.)  If your modification has
# such potential, you must delete any notice of this special exception
# to the GPL from your modified version.

# Use of diversions:
#
#  - DEFAULT
#    Overall initialization, value of $at_groups_all.
#  - OPTIONS
#    Option processing
#    Be ready to run the tests.
#  - TESTS
#    The core of the test suite, the ``normal'' diversion.
#  - TAIL
#    tail of the core for;case, overall wrap up, generation of debugging
#    scripts and statistics.

m4_define([_m4_divert(DEFAULT)],       5)
m4_define([_m4_divert(OPTIONS)],      10)
m4_define([_m4_divert(TESTS)],        50)
m4_define([_m4_divert(TAIL)],         60)


# AT_LINE
# -------
# Return the current file sans directory, a colon, and the current
# line.  Be sure to return a _quoted_ filename, so if, for instance,
# the user is lunatic enough to have a file named `dnl' (and I, for
# one, love to be brainless and stubborn sometimes), then we return a
# quoted name.
#
# Gee, we can't use simply
#
#  m4_bpatsubst(__file__, [^.*/\(.*\)], [[\1]])
#
# since then, since `dnl' doesn't match the pattern, it is returned
# with once quotation level less, so you lose!  And since GNU M4
# is one of the biggest junk in the whole universe wrt regexp, don't
# even think about using `?' or `\?'.  Bah, `*' will do.
# Pleeeeeeeease, Gary, provide us with dirname and ERE!
m4_define([AT_LINE],
[m4_bpatsubst(__file__, [^\(.*/\)*\(.*\)], [[\2]]):__line__])


# AT_INIT([TESTSUITE-NAME])
# -------------------------
# Begin test suite.
m4_define([AT_INIT],
[m4_pattern_forbid([^_?AT_])
m4_define([AT_TESTSUITE_NAME],
          m4_defn([AT_PACKAGE_STRING])[ test suite]m4_ifval([$1], [: $1]))
m4_define([AT_ordinal], 0)
m4_define([AT_banner_ordinal], 0)
AS_INIT
AS_PREPARE
m4_divert_push([DEFAULT])dnl

AS_PREPARE
SHELL=${CONFIG_SHELL-/bin/sh}

# How were we run?
at_cli_args="$[@]"

# Load the config file.
for at_file in atconfig atlocal
do
  test -r $at_file || continue
  . ./$at_file || AS_ERROR([invalid content: $at_file])
done

# atconfig delivers paths relative to the directory the test suite is
# in, but the groups themselves are run in testsuite-dir/group-dir.
if test -n "$at_top_srcdir"; then
  builddir=../..
  for at_dir in srcdir top_srcdir top_builddir
  do
    at_val=AS_VAR_GET(at_$at_dir)
    AS_VAR_SET($at_dir, $at_val/../..)
  done
fi

# Not all shells have the 'times' builtin; the subshell is needed to make
# sure we discard the 'times: not found' message from the shell.
at_times_skip=:
(times) >/dev/null 2>&1 && at_times_skip=false

# CLI Arguments to pass to the debugging scripts.
at_debug_args=
# -e sets to true
at_errexit_p=false
# Shall we be verbose?
at_verbose=:
at_quiet=echo

# Shall we keep the debug scripts?  Must be `:' when the suite is
# run by a debug script, so that the script doesn't remove itself.
at_debug_p=false
# Display help message?
at_help_p=false
# List test groups?
at_list_p=false
# Test groups to run
at_groups=

# The directory we are in.
at_dir=`pwd`
# The directory the whole suite works in.
# Should be absolutely to let the user `cd' at will.
at_suite_dir=$at_dir/$as_me.dir
# The file containing the location of the last AT_CHECK.
at_check_line_file=$at_suite_dir/at-check-line
# The files containing the output of the tested commands.
at_stdout=$at_suite_dir/at-stdout
at_stder1=$at_suite_dir/at-stder1
at_stderr=$at_suite_dir/at-stderr
# The file containing dates.
at_times_file=$at_suite_dir/at-times

m4_wrap([m4_divert_text([DEFAULT],
[# List of the tested programs.
at_tested='m4_ifdef([AT_tested], [AT_tested])'
# List of the all the test groups.
at_groups_all='AT_groups_all'
# As many dots as there are digits in the last test group number.
# Used to normalize the test group numbers so that `ls' lists them in
# numerical order.
at_format='m4_bpatsubst(m4_defn([AT_ordinal]), [.], [.])'
# Description of all the test groups.
at_help_all=
AT_help])])dnl
m4_divert([OPTIONS])

while test $[@%:@] -gt 0; do
  case $[1] in
    --help | -h )
        at_help_p=:
        ;;

    --list | -l )
        at_list_p=:
        ;;

    --version | -V )
        echo "$as_me (AT_PACKAGE_STRING)"
        exit 0
        ;;

    --clean | -c )
        rm -rf $at_suite_dir $as_me.log
        exit 0
        ;;

    --debug | -d )
        at_debug_p=:
        ;;

    --errexit | -e )
        at_debug_p=:
        at_errexit_p=:
        ;;

    --verbose | -v )
        at_verbose=echo; at_quiet=:
        ;;

    --trace | -x )
        at_traceon='set -vx'; at_traceoff='set +vx'
        ;;

    [[0-9] | [0-9][0-9] | [0-9][0-9][0-9] | [0-9][0-9][0-9][0-9]])
        at_groups="$at_groups$[1] "
        ;;

    # Ranges
    [[0-9]- | [0-9][0-9]- | [0-9][0-9][0-9]- | [0-9][0-9][0-9][0-9]-])
        at_range_start=`echo $[1] |tr -d '-'`
        at_range=`echo " $at_groups_all " | \
          sed -e 's,^.* '$at_range_start' ,'$at_range_start' ,'`
        at_groups="$at_groups$at_range "
        ;;

    [-[0-9] | -[0-9][0-9] | -[0-9][0-9][0-9] | -[0-9][0-9][0-9][0-9]])
        at_range_end=`echo $[1] |tr -d '-'`
        at_range=`echo " $at_groups_all " | \
          sed -e 's, '$at_range_end' .*$, '$at_range_end','`
        at_groups="$at_groups$at_range "
        ;;

    [[0-9]-[0-9] | [0-9]-[0-9][0-9] | [0-9]-[0-9][0-9][0-9]] | \
    [[0-9]-[0-9][0-9][0-9][0-9] | [0-9][0-9]-[0-9][0-9]] | \
    [[0-9][0-9]-[0-9][0-9][0-9] | [0-9][0-9]-[0-9][0-9][0-9][0-9]] | \
    [[0-9][0-9][0-9]-[0-9][0-9][0-9]] | \
    [[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]] | \
    [[0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]] )
        at_range_start=`echo $[1] |sed 's,-.*,,'`
        at_range_end=`echo $[1] |sed 's,.*-,,'`
        # FIXME: Maybe test to make sure start <= end?
        at_range=`echo " $at_groups_all " | \
          sed -e 's,^.* '$at_range_start' ,'$at_range_start' ,' \
              -e 's, '$at_range_end' .*$, '$at_range_end','`
        at_groups="$at_groups$at_range "
        ;;

    # Keywords.
    --keywords | -k )
        shift
        at_groups_selected=$at_help_all
        for at_keyword in `IFS=,; set X $[1]; shift; echo ${1+$[@]}`
        do
          # It is on purpose that we match the test group titles too.
          at_groups_selected=`echo "$at_groups_selected" |
			      grep -i "^[[^;]]*;[[^;]]*;.*$at_keyword"`
        done
        at_groups_selected=`echo "$at_groups_selected" | sed 's/;.*//'`
	# Smash the end of lines.
	at_groups_selected=`echo $at_groups_selected`
        at_groups="$at_groups$at_groups_selected "
        ;;

    *=*)
  	at_envvar=`expr "x$[1]" : 'x\([[^=]]*\)='`
  	# Reject names that are not valid shell variable names.
  	expr "x$at_envvar" : "[.*[^_$as_cr_alnum]]" >/dev/null &&
  	  AS_ERROR([invalid variable name: $at_envvar])
  	at_value=`expr "x$[1]" : 'x[[^=]]*=\(.*\)'`
  	at_value=`echo "$at_value" | sed "s/'/'\\\\\\\\''/g"`
  	eval "$at_envvar='$at_value'"
  	export $at_envvar
	# Propagate to debug scripts.
  	at_debug_args="$at_debug_args $[1]"
  	;;

     *) echo "$as_me: invalid option: $[1]" >&2
        echo "Try \`$[0] --help' for more information." >&2
        exit 1
        ;;
  esac
  shift
done

# Selected test groups.
test -z "$at_groups" && at_groups=$at_groups_all

# Help message.
if $at_help_p; then
  cat <<_ATEOF
Usage: $[0] [[OPTION]... [VARIABLE=VALUE]... [TESTS]]

Run all the tests, or the selected TESTS, and save a detailed log file.
Upon failure, create debugging scripts.

You should not change environment variables unless explicitly passed
as command line arguments.  Set \`AUTOTEST_PATH' to select the executables
to exercise.  Each relative directory is expanded as build and source
directories relatively to the top level of this distribution.  E.g.,

  $ $[0] AUTOTEST_PATH=bin

possibly amounts into

  PATH=/tmp/foo-1.0/bin:/src/foo-1.0/bin:\$PATH

Operation modes:
  -h, --help     print the help message, then exit
  -V, --version  print version number, then exit
  -c, --clean    remove all the files this test suite might create and exit
  -l, --list     describes all the tests, or the selected TESTS

Execution tuning:
  -k, --keywords=KEYWORDS
                 select the tests matching all the comma separated KEYWORDS
                 accumulates
  -e, --errexit  abort as soon as a test fails; implies --debug
  -v, --verbose  force more detailed output
                 default for debugging scripts
  -d, --debug    inhibit clean up and debug script creation
                 default for debugging scripts
  -x, --trace    enable tests shell tracing

Report bugs to <AT_PACKAGE_BUGREPORT>.
_ATEOF
  exit 0
fi

# List of tests.
if $at_list_p; then
  cat <<_ATEOF
AT_TESTSUITE_NAME test groups:

 NUM: FILENAME:LINE      TEST-GROUP-NAME
      KEYWORDS

_ATEOF
  # "  1 42  45 " => "^(1|42|45);".
  at_groups_pattern=`echo "$at_groups" | sed 's/^  *//;s/  *$//;s/  */|/g'`
  echo "$at_help_all" |
    awk 'BEGIN { FS = ";" }
         { if ($[1] !~ /^('"$at_groups_pattern"')$/) next }
         { if ($[1]) printf " %3d: %-18s %s\n", $[1], $[2], $[3]
           if ($[4]) printf "      %s\n", $[4] } '
  exit 0
fi

# Don't take risks: use only absolute directories in PATH.
#
# For stand-alone test suites, AUTOTEST_PATH is relative to `.'.
#
# For embedded test suites, AUTOTEST_PATH is relative to the top level
# of the package.  Then expand it into build/src parts, since users
# may create executables in both places.
#
# There might be directories that don't exist, but don't redirect
# builtins' (eg., cd) stderr directly: Ultrix's sh hates that.
AUTOTEST_PATH=`echo $AUTOTEST_PATH | tr ':' $PATH_SEPARATOR`
at_path=
_AS_PATH_WALK([$AUTOTEST_PATH $PATH],
[case $as_dir in
  [[\\/]]* | ?:[[\\/]]* )
    at_path=$at_path$PATH_SEPARATOR$as_dir
    ;;
  * )
    if test -z "$at_top_builddir"; then
      # Stand-alone test suite.
      at_path=$at_path$PATH_SEPARATOR$as_dir
    else
      # Embedded test suite.
      at_path=$at_path$PATH_SEPARATOR$at_top_builddir/$as_dir
      at_path=$at_path$PATH_SEPARATOR$at_top_srcdir/$as_dir
    fi
    ;;
esac])

# Now build and simplify PATH.
PATH=
_AS_PATH_WALK([$at_path],
[as_dir=`(cd "$as_dir" && pwd) 2>/dev/null`
test -d "$as_dir" || continue
case $PATH in
                  $as_dir                 | \
                  $as_dir$PATH_SEPARATOR* | \
  *$PATH_SEPARATOR$as_dir                 | \
  *$PATH_SEPARATOR$as_dir$PATH_SEPARATOR* ) ;;

  '') PATH=$as_dir ;;
   *) PATH=$PATH$PATH_SEPARATOR$as_dir ;;
esac])
export PATH

# Setting up the FDs.
# 5 is stdout conditioned by verbosity.
if test $at_verbose = echo; then
  exec 5>&1
else
  exec 5>/dev/null
fi

# 6 is the log file.  To be preserved if `-d'.
m4_define([AS_MESSAGE_LOG_FD], [6])
if $at_debug_p; then
  exec AS_MESSAGE_LOG_FD>/dev/null
else
  exec AS_MESSAGE_LOG_FD>$as_me.log
fi

# Banners and logs.
AS_BOX(m4_defn([AT_TESTSUITE_NAME])[.])
{
  AS_BOX(m4_defn([AT_TESTSUITE_NAME])[.])
  echo

  echo "$as_me: command line was:"
  echo "  $ $[0] $at_cli_args"
  echo

  # Try to find a few ChangeLogs in case it might help determining the
  # exact version.  Use the relative dir: if the top dir is a symlink,
  # find will not follow it (and options to follow the links are not
  # portable), which would result in no output here.
  if test -n "$at_top_srcdir"; then
    AS_BOX([ChangeLogs.])
    echo
    for at_file in `find "$at_top_srcdir" -name ChangeLog -print`
    do
      echo "$as_me: $at_file:"
      sed 's/^/| /;10q' $at_file
      echo
    done

    AS_UNAME
    echo
  fi

  # Contents of the config files.
  for at_file in atconfig atlocal
  do
    test -r $at_file || continue
    echo "$as_me: $at_file:"
    sed 's/^/| /' $at_file
    echo
  done

  AS_BOX([Tested programs.])
  echo
} >&AS_MESSAGE_LOG_FD

# Report what programs are being tested.
for at_program in : $at_tested
do
  test "$at_program" = : && continue
  _AS_PATH_WALK([$PATH], [test -f $as_dir/$at_program && break])
  if test -f $as_dir/$at_program; then
    {
      echo "AT_LINE: $as_dir/$at_program --version"
      $as_dir/$at_program --version
      echo
    } >&AS_MESSAGE_LOG_FD 2>&1
  else
    AS_ERROR([cannot find $at_program])
  fi
done

{
  AS_BOX([Silently running the tests.])
} >&AS_MESSAGE_LOG_FD

at_start_date=`date`
at_start_time=`(date +%s) 2>/dev/null`
echo "$as_me: starting at: $at_start_date" >&AS_MESSAGE_LOG_FD
at_pass_list=
at_fail_list=
at_skip_list=
at_group_count=0
m4_divert([TESTS])dnl

# Create the master directory if it doesn't already exist.
test -d $at_suite_dir ||
  mkdir $at_suite_dir ||
  AS_ERROR([cannot create $at_suite_dir])

# Can we diff with `/dev/null'?  DU 5.0 refuses.
if diff /dev/null /dev/null >/dev/null 2>&1; then
  at_devnull=/dev/null
else
  at_devnull=$at_suite_dir/devnull
  cp /dev/null $at_devnull
fi

# Use `diff -u' when possible.
if diff -u $at_devnull $at_devnull >/dev/null 2>&1; then
  at_diff='diff -u'
else
  at_diff=diff
fi


for at_group in $at_groups
do
  # Be sure to come back to the top test directory.
  cd $at_suite_dir

  case $at_group in
    banner-*) ;;
    *)
     # Skip tests we already run (using --keywords makes it easy to get
     # duplication).
     case " $at_pass_test $at_skip_test $at_fail_test " in
       *" $at_group "* ) continue;;
     esac

     # Normalize the test group number.
     at_group_normalized=`expr "00000$at_group" : ".*\($at_format\)"`

     # Create a fresh directory for the next test group, and enter.
     at_group_dir=$at_suite_dir/$at_group_normalized
     rm -rf $at_group_dir
     mkdir $at_group_dir ||
       AS_ERROR([cannot create $at_group_dir])
     cd $at_group_dir
    ;;
  esac

  at_status=0
  # Clearly separate the test groups when verbose.
  test $at_group_count != 0 && $at_verbose
  case $at_group in
dnl Test groups inserted here (TESTS).
m4_divert([TAIL])[]dnl

  * )
    echo "$as_me: no such test group: $at_group" >&2
    continue
    ;;
  esac

  # Be sure to come back to the suite directory, in particular
  # since below we might `rm' the group directory we are in currently.
  cd $at_suite_dir

  case $at_group in
    banner-*) ;;
    *)
      if test ! -f $at_check_line_file; then
        sed "s/^ */$as_me: warning: /" <<_ATEOF
        A failure happened in a test group before any test could be
        run. This means that test suite is improperly designed.  Please
        report this failure to <AT_PACKAGE_BUGREPORT>.
_ATEOF
    	echo "$at_setup_line" >$at_check_line_file
      fi
      at_group_count=`expr 1 + $at_group_count`
      $at_verbose $ECHO_N "$at_group. $at_setup_line: $ECHO_C"
      case $at_status in
        0)  at_msg="ok"
            at_pass_list="$at_pass_list $at_group"
            # Cleanup the group directory, unless the user wants the files.
            $at_debug_p || rm -rf $at_group_dir
            ;;
        77) at_msg="ok (skipped near \``cat $at_check_line_file`')"
            at_skip_list="$at_skip_list $at_group"
            # Cleanup the group directory, unless the user wants the files.
            $at_debug_p || rm -rf $at_group_dir
            ;;
        *)  at_msg="FAILED near \``cat $at_check_line_file`'"
            at_fail_list="$at_fail_list $at_group"
            # Up failure, keep the group directory for autopsy.
            # Create the debugging script.
            {
              echo "#! /bin/sh"
              echo 'test "${ZSH_VERSION+set}" = set && alias -g '\''${1+"$[@]"}'\''='\''"$[@]"'\'''
              echo "cd $at_dir"
              echo 'exec ${CONFIG_SHELL-'"$SHELL"'}' "$[0]" \
                   '-v -d' "$at_debug_args" "$at_group" '${1+"$[@]"}'
              echo 'exit 1'
            } >$at_group_dir/run
            chmod +x $at_group_dir/run
            ;;
      esac
      echo $at_msg
      at_log_msg="$at_group. $at_setup_line: $at_msg"
      # If the group failed, $at_times_file is not available.
      test -f $at_times_file &&
        at_log_msg="$at_log_msg	(`sed 1d $at_times_file`)"
      echo "$at_log_msg" >&AS_MESSAGE_LOG_FD
      $at_errexit_p && test -n "$at_fail_list" && break
      ;;
  esac
done

# Back to the top directory, in particular because we might
# rerun the suite verbosely.
cd $at_dir

# Compute the duration of the suite.
at_stop_date=`date`
at_stop_time=`(date +%s) 2>/dev/null`
echo "$as_me: ending at: $at_stop_date" >&AS_MESSAGE_LOG_FD
at_duration_s=`(expr $at_stop_time - $at_start_time) 2>/dev/null`
at_duration_m=`(expr $at_duration_s / 60) 2>/dev/null`
at_duration_h=`(expr $at_duration_m / 60) 2>/dev/null`
at_duration_s=`(expr $at_duration_s % 60) 2>/dev/null`
at_duration_m=`(expr $at_duration_m % 60) 2>/dev/null`
at_duration="${at_duration_h}h ${at_duration_m}m ${at_duration_s}s"
if test "$at_duration" != "h m s"; then
  echo "$as_me: test suite duration: $at_duration" >&AS_MESSAGE_LOG_FD
fi

# Wrap up the test suite with summary statistics.
at_skip_count=`set dummy $at_skip_list; shift; echo $[@%:@]`
at_fail_count=`set dummy $at_fail_list; shift; echo $[@%:@]`
if test $at_fail_count = 0; then
  if test $at_skip_count = 0; then
    AS_BOX([All $at_group_count tests were successful.])
  else
    AS_BOX([All $at_group_count tests were successful ($at_skip_count skipped).])
  fi
elif test $at_debug_p = false; then
  if $at_errexit_p; then
    AS_BOX([ERROR: One of the tests failed, inhibiting subsequent tests.])
  else
    AS_BOX([ERROR: Suite unsuccessful, $at_fail_count of $at_group_count tests failed.])
  fi

  # Normalize the names so that `ls' lists them in order.
  echo 'You may investigate any problem if you feel able to do so, in which'
  echo 'case the test suite provides a good starting point.'
  echo
  echo 'Now, failed tests will be executed again, verbosely, and logged'
  echo 'in the file '$as_me'.log.'

  {
    echo
    echo
    AS_BOX([Summary of the failures.])

    # Summary of failed and skipped tests.
    if test $at_fail_count != 0; then
      echo "Failed tests:"
      $SHELL $[0] $at_fail_list --list
      echo
    fi
    if test $at_skip_count != 0; then
      echo "Skipped tests:"
      $SHELL $[0] $at_skip_list --list
      echo
    fi
    echo

    AS_BOX([Verbosely re-running the failing tests.])
    echo
  } >&AS_MESSAGE_LOG_FD

  exec AS_MESSAGE_LOG_FD>/dev/null
  $SHELL $[0] -v -d $at_debug_args $at_fail_list 2>&1 | tee -a $as_me.log
  exec AS_MESSAGE_LOG_FD>>$as_me.log

  {
    echo
    if test -n "$at_top_srcdir"; then
      AS_BOX([Configuration logs.])
      echo
      for at_file in `find "$at_top_srcdir" -name config.log -print`
      do
  	echo "$as_me: $at_file:"
  	sed 's/^/| /' $at_file
  	echo
      done
    fi
  } >&AS_MESSAGE_LOG_FD


  AS_BOX([$as_me.log is created.])

  echo
  echo "Please send \`$as_me.log' and all information you think might help:"
  echo
  echo "   To: <AT_PACKAGE_BUGREPORT>"
  echo "   Subject: @<:@AT_PACKAGE_STRING@:>@ $as_me:$at_fail_list failed"
  echo
  exit 1
fi

exit 0
m4_divert_pop([TAIL])dnl
dnl End of AT_INIT: divert to KILL, only test groups are to be
dnl output, the rest is ignored.  Current diversion is BODY, inherited
dnl from M4sh.
m4_divert_push([KILL])
m4_wrap([m4_divert_pop([KILL])[]])
])# AT_INIT


# AT_TESTED(PROGRAMS)
# -------------------
# Specify the list of programs exercised by the test suite.  Their
# versions are logged, and in the case of embedded test suite, they
# must correspond to the version of the package..  The PATH should be
# already preset so the proper executable will be selected.
m4_define([AT_TESTED],
[m4_append_uniq([AT_tested], [$1], [ ])])


# AT_SETUP(DESCRIPTION)
# ---------------------
# Start a group of related tests, all to be executed in the same subshell.
# The group is testing what DESCRIPTION says.
m4_define([AT_SETUP],
[m4_ifdef([AT_keywords], [m4_undefine([AT_keywords])])
m4_define([AT_line], AT_LINE)
m4_define([AT_description], [$1])
m4_define([AT_ordinal], m4_incr(AT_ordinal))
m4_append([AT_groups_all], [ ]m4_defn([AT_ordinal]))
m4_divert_push([TESTS])dnl
  AT_ordinal ) @%:@ AT_ordinal. m4_defn([AT_line]): $1
    at_setup_line='m4_defn([AT_line])'
    $at_verbose "AT_ordinal. m4_defn([AT_line]): testing $1..."
    $at_quiet $ECHO_N "m4_format([[%3d: %-18s]],
                       AT_ordinal, m4_defn([AT_line]))[]$ECHO_C"
    (
      $at_traceon
])


# AT_KEYWORDS(KEYOWRDS)
# ---------------------
# Declare a list of keywords associated to the current test group.
m4_define([AT_KEYWORDS],
[m4_append_uniq([AT_keywords], [$1], [,])])


# AT_CLEANUP
# ----------
# Complete a group of related tests.
m4_define([AT_CLEANUP],
[m4_append([AT_help],
at_help_all=$at_help_all'm4_defn([AT_ordinal]);m4_defn([AT_line]);m4_defn([AT_description]);m4_ifdef([AT_keywords], [m4_defn([AT_keywords])])
'
)dnl
    $at_times_skip || times >$at_times_file
    )
    at_status=$?
    ;;

m4_divert_pop([TESTS])dnl Back to KILL.
])# AT_CLEANUP


# AT_BANNER(TEXT)
# ---------------
# Output TEXT without any shell expansion.
m4_define([AT_BANNER],
[m4_define([AT_banner_ordinal], m4_incr(AT_banner_ordinal))
m4_append([AT_groups_all], [ banner-]m4_defn([AT_banner_ordinal]))
m4_divert_text([TESTS],
[
  banner-AT_banner_ordinal ) @%:@ Banner AT_banner_ordinal. AT_LINE
    cat <<\_ATEOF

$1

_ATEOF
    ;;
])dnl
])# AT_BANNER


# AT_DATA(FILE, CONTENTS)
# -----------------------
# Initialize an input data FILE with given CONTENTS, which should end with
# an end of line.
# This macro is not robust to active symbols in CONTENTS *on purpose*.
# If you don't want CONTENT to be evaluated, quote it twice.
m4_define([AT_DATA],
[cat >$1 <<'_ATEOF'
$2[]_ATEOF
])


# AT_CHECK(COMMANDS, [STATUS = 0], STDOUT, STDERR)
# ------------------------------------------------
# Execute a test by performing given shell COMMANDS.  These commands
# should normally exit with STATUS, while producing expected STDOUT and
# STDERR contents.
#
# STATUS, STDOUT, and STDERR are not checked if equal to `ignore'.
#
# If STDOUT is `expout', then stdout is compared to the content of the file
# `expout'.  Likewise for STDERR and `experr'.
#
# If STDOUT is `stdout', then the stdout is left in the file `stdout',
# likewise for STDERR and `stderr'.  Don't do this:
#
#    AT_CHECK([command >out])
#    # Some checks on `out'
#
# do this instead:
#
#    AT_CHECK([command], [], [stdout])
#    # Some checks on `stdout'
#
# This is an unfortunate limitation inherited from Ultrix which will not
# let you redirect several times the same FD (see the Autoconf documentation).
# If you use the `AT_CHECK([command >out])' be sure to get a test suite
# that will show spurious failures.
#
# You might wonder why not just use `ignore' and directly use stdout and
# stderr left by the test suite.  Firstly because the names of these files
# is an internal detail, and secondly, because
#
#    AT_CHECK([command], [], [ignore])
#    AT_CHECK([check stdout])
#
# will use `stdout' both in input and output: undefined behavior would
# certainly result.  That's why the test suite will save them in `at-stdout'
# and `at-stderr', and will provide you with `stdout' and `stderr'.
#
# Any line of stderr starting with leading blanks and a `+' are filtered
# out, since most shells when tracing include subshell traces in stderr.
# This may cause spurious failures when the test suite is run with `-x'.
#
#
# Implementation Details
# ----------------------
# Ideally, we would like to run
#
#    ( $at_traceon; COMMANDS >at-stdout 2> at-stderr )
#
# but we must group COMMANDS as it is not limited to a single command, and
# then the shells will save the traces in at-stderr. So we have to filter
# them out when checking stderr, and we must send them into the test suite's
# stderr to honor -x properly.
#
# Limiting COMMANDS to a single command is not good either, since them
# the user herself would use {} or (), and then we face the same problem.
#
# But then, there is no point in running
#
#   ( $at_traceon { $1 ; } >at-stdout 2>at-stder1 )
#
# instead of the simpler
#
#  ( $at_traceon; $1 ) >at-stdout 2>at-stder1
#
m4_define([AT_CHECK],
[$at_traceoff
$at_verbose "AT_LINE: AS_ESCAPE([$1])"
echo AT_LINE >$at_check_line_file
( $at_traceon; $1 ) >$at_stdout 2>$at_stder1
at_status=$?
grep '^ *+' $at_stder1 >&2
grep -v '^ *+' $at_stder1 >$at_stderr
at_failed=false
dnl Check stderr.
m4_case([$4],
        stderr, [(echo stderr:; tee stderr <$at_stderr) >&5],
        ignore, [(echo stderr:; cat $at_stderr) >&5],
        experr, [$at_diff experr $at_stderr >&5 || at_failed=:],
        [],     [$at_diff $at_devnull $at_stderr >&5 || at_failed=:],
        [echo >>$at_stderr; echo "AS_ESCAPE([$4])" | $at_diff - $at_stderr >&5 || at_failed=:])
dnl Check stdout.
m4_case([$3],
        stdout, [(echo stdout:; tee stdout <$at_stdout) >&5],
        ignore, [(echo stdout:; cat $at_stdout) >&5],
        expout, [$at_diff expout $at_stdout >&5 || at_failed=:],
        [],     [$at_diff $at_devnull $at_stdout >&5 || at_failed=:],
        [echo >>$at_stdout; echo "AS_ESCAPE([$3])" | $at_diff - $at_stdout >&5 || at_failed=:])
dnl Check exit val.  Don't `skip' if we are precisely checking $? = 77.
case $at_status in
m4_case([$2],
  [77],
    [],
    [   77) exit 77;;
])dnl
m4_case([$2],
  [ignore],
    [   *);;],
    [   m4_default([$2], [0])) ;;
   *) $at_verbose "AT_LINE: exit code was $at_status, expected m4_default([$2], [0])" >&2
      at_failed=:;;])
esac
AS_IF($at_failed, [$5], [$6])
$at_failed && exit 1
$at_traceon
])# AT_CHECK

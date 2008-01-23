# This file is part of Autoconf.                          -*- Autoconf -*-
# M4 sugar for common shell constructs.
# Requires GNU M4 and M4sugar.
# Copyright (C) 2000, 2001, 2002 Free Software Foundation, Inc.
#
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
#
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
#
# Written by Akim Demaille, Pavel Roskin, Alexandre Oliva, Lars J. Aas
# and many other people.


# We heavily use m4's diversions both for the initializations and for
# required macros, because in both cases we have to issue soon in
# output something which is discovered late.
#
#
# KILL is only used to suppress output.
#
# - BINSH
#   AC_REQUIRE'd #! /bin/sh line
# - HEADER-REVISION
#   RCS keywords etc.
# - HEADER-COMMENT
#   Purpose of the script etc.
# - HEADER-COPYRIGHT
#   Copyright notice(s)
# - M4SH-INIT
#   M4sh's initializations
#
# - BODY
#   The body of the script.


# _m4_divert(DIVERSION-NAME)
# --------------------------
# Convert a diversion name into its number.  Otherwise, return
# DIVERSION-NAME which is supposed to be an actual diversion number.
# Of course it would be nicer to use m4_case here, instead of zillions
# of little macros, but it then takes twice longer to run `autoconf'!
m4_define([_m4_divert(BINSH)],             0)
m4_define([_m4_divert(HEADER-REVISION)],   1)
m4_define([_m4_divert(HEADER-COMMENT)],    2)
m4_define([_m4_divert(HEADER-COPYRIGHT)],  3)
m4_define([_m4_divert(M4SH-INIT)],         4)
m4_define([_m4_divert(BODY)],           1000)

# Aaarg.  Yet it starts with compatibility issues...  Libtool wants to
# use NOTICE to insert its own LIBTOOL-INIT stuff.  People should ask
# before diving into our internals :(
m4_copy([_m4_divert(M4SH-INIT)], [_m4_divert(NOTICE)])



## ------------------------- ##
## 1. Sanitizing the shell.  ##
## ------------------------- ##


# AS_REQUIRE(NAME-TO-CHECK, [BODY-TO-EXPAND = NAME-TO-CHECK])
# -----------------------------------------------------------
# BODY-TO-EXPAND is some initialization which must be expanded in the
# M4SH-INIT section when expanded (required or not).  This is very
# different from m4_require.  For instance:
#
#      m4_defun([_FOO_PREPARE], [foo=foo])
#      m4_defun([FOO],
#      [m4_require([_FOO_PREPARE])dnl
#      echo $foo])
#
#      m4_defun([_BAR_PREPARE], [bar=bar])
#      m4_defun([BAR],
#      [AS_REQUIRE([_BAR_PREPARE])dnl
#      echo $bar])
#
#      AS_INIT
#      foo1=`FOO`
#      foo2=`FOO`
#      bar1=`BAR`
#      bar2=`BAR`
#
# gives
#
#      #! /bin/sh
#      bar=bar
#
#      foo1=`foo=foo
#      echo $foo`
#      foo2=`echo $foo`
#      bar1=`echo $bar`
#      bar2=`echo $bar`
#
m4_define([AS_REQUIRE],
[m4_provide_if([$1], [],
               [m4_divert_text([M4SH-INIT], [$1])])])


# AS_SHELL_SANITIZE
# -----------------
# Try to be as Bourne and/or POSIX as possible.
m4_defun([AS_SHELL_SANITIZE],
[## --------------------- ##
## M4sh Initialization.  ##
## --------------------- ##

# Be Bourne compatible
if test -n "${ZSH_VERSION+set}" && (emulate sh) >/dev/null 2>&1; then
  emulate sh
  NULLCMD=:
  [#] Zsh 3.x and 4.x performs word splitting on ${1+"$[@]"}, which
  # is contrary to our usage.  Disable this feature.
  alias -g '${1+"$[@]"}'='"$[@]"'
elif test -n "${BASH_VERSION+set}" && (set -o posix) >/dev/null 2>&1; then
  set -o posix
fi

_AS_UNSET_PREPARE

# Work around bugs in pre-3.0 UWIN ksh.
$as_unset ENV MAIL MAILPATH
PS1='$ '
PS2='> '
PS4='+ '

# NLS nuisances.
for as_var in \
  LANG LANGUAGE LC_ADDRESS LC_ALL LC_COLLATE LC_CTYPE LC_IDENTIFICATION \
  LC_MEASUREMENT LC_MESSAGES LC_MONETARY LC_NAME LC_NUMERIC LC_PAPER \
  LC_TELEPHONE LC_TIME
do
  if (set +x; test -n "`(eval $as_var=C; export $as_var) 2>&1`"); then
    eval $as_var=C; export $as_var
  else
    $as_unset $as_var
  fi
done

# Required to use basename.
_AS_EXPR_PREPARE
_AS_BASENAME_PREPARE

# Name of the executable.
as_me=`AS_BASENAME("$[0]")`

])


# _AS_PREPARE
# -----------
# This macro has a very special status.  Normal use of M4sh relies
# heavily on AS_REQUIRE, so that needed initializations (such as
# _AS_TEST_PREPARE) are performed on need, not on demand.  But
# Autoconf is the first client of M4sh, and for two reasons: configure
# and config.status.  Relying on AS_REQUIRE is of course fine for
# configure, but fails for config.status (which is created by
# configure).  So we need a means to force the inclusion of the
# various _AS_PREPARE_* on top of config.status.  That's basically why
# there are so many _AS_PREPARE_* below, and that's also why it is
# important not to forget some: config.status needs them.
m4_defun([_AS_PREPARE],
[# PATH needs CR, and LINENO needs CR and PATH.
_AS_CR_PREPARE
_AS_PATH_SEPARATOR_PREPARE
_AS_LINENO_PREPARE

_AS_ECHO_N_PREPARE
_AS_EXPR_PREPARE
_AS_LN_S_PREPARE
_AS_MKDIR_P_PREPARE
_AS_TEST_PREPARE
_AS_TR_CPP_PREPARE
_AS_TR_SH_PREPARE

# IFS
# We need space, tab and new line, in precisely that order.
as_nl='
'
IFS=" 	$as_nl"

# CDPATH.
$as_unset CDPATH
])


# AS_PREPARE
# ----------
# Output all the M4sh possible initialization into the initialization
# diversion.
m4_defun([AS_PREPARE],
[m4_divert_text([M4SH-INIT], [_AS_PREPARE])])


## ----------------------------- ##
## 2. Wrappers around builtins.  ##
## ----------------------------- ##

# This section is lexicographically sorted.


# AS_EXIT([EXIT-CODE = 1])
# ------------------------
# Exit and set exit code to EXIT-CODE in the way that it's seen
# within "trap 0".
#
# We cannot simply use "exit N" because some shells (zsh and Solaris sh)
# will not set $? to N while running the code set by "trap 0"
# So we set $? by executing "exit N" in the subshell and then exit.
# Other shells don't use `$?' as default for `exit', hence just repeating
# the exit value can only help improving portability.
m4_define([AS_EXIT],
[{ (exit m4_default([$1], 1)); exit m4_default([$1], 1); }])


# AS_IF(TEST, [IF-TRUE], [IF-FALSE])
# ----------------------------------
# Expand into
# | if TEST; then
# |   IF-TRUE
# | else
# |   IF-FALSE
# | fi
# with simplifications is IF-TRUE and/or IF-FALSE is empty.
#
# FIXME: Be n-ary, just as m4_if.
m4_define([AS_IF],
[m4_ifval([$2$3],
[if $1; then
  m4_ifval([$2], [$2], :)
m4_ifvaln([$3],
[else
  $3])dnl
fi
])dnl
])# AS_IF


# _AS_UNSET_PREPARE
# -----------------
# AS_UNSET depends upon $as_unset: compute it.
m4_defun([_AS_UNSET_PREPARE],
[# Support unset when possible.
if (FOO=FOO; unset FOO) >/dev/null 2>&1; then
  as_unset=unset
else
  as_unset=false
fi
])


# AS_UNSET(VAR, [VALUE-IF-UNSET-NOT-SUPPORTED = `'])
# --------------------------------------------------
# Try to unset the env VAR, otherwise set it to
# VALUE-IF-UNSET-NOT-SUPPORTED.  `as_unset' must have been computed.
m4_defun([AS_UNSET],
[AS_REQUIRE([_AS_UNSET_PREPARE])dnl
$as_unset $1 || test "${$1+set}" != set || { $1=$2; export $1; }])






## ------------------------------------------ ##
## 3. Error and warnings at the shell level.  ##
## ------------------------------------------ ##

# If AS_MESSAGE_LOG_FD is defined, shell messages are duplicated there
# too.


# AS_ESCAPE(STRING, [CHARS = $"'\])
# ---------------------------------
# Escape the CHARS in STRING.
m4_define([AS_ESCAPE],
[m4_bpatsubst([$1],
             m4_ifval([$2], [[\([$2]\)]], [[\([\"$`]\)]]),
             [\\\1])])


# _AS_QUOTE_IFELSE(STRING, IF-MODERN-QUOTATION, IF-OLD-QUOTATION)
# ---------------------------------------------------------------
# Compatibility glue between the old AS_MSG suite which did not
# quote anything, and the modern suite which quotes the quotes.
# If STRING contains `\\' or `\$', it's modern.
# If STRING contains `\"' or `\`', it's old.
# Otherwise it's modern.
# We use two quotes in the pattern to keep highlighting tools at peace.
m4_define([_AS_QUOTE_IFELSE],
[m4_bmatch([$1],
          [\\[\\$]], [$2],
          [\\[`""]], [$3],
          [$2])])


# _AS_ECHO_UNQUOTED(STRING, [FD = AS_MESSAGE_FD])
# -----------------------------------------------
# Perform shell expansions on STRING and echo the string to FD.
m4_define([_AS_ECHO_UNQUOTED],
[echo "$1" >&m4_default([$2], [AS_MESSAGE_FD])])


# _AS_QUOTE(STRING, [CHARS = `"])
# -------------------------------
# If there are quoted (via backslash) backquotes do nothing, else
# backslash all the quotes.
m4_define([_AS_QUOTE],
[_AS_QUOTE_IFELSE([$1],
                  [AS_ESCAPE([$1], m4_default([$2], [`""]))],
                  [m4_warn([obsolete],
           [back quotes and double quotes must not be escaped in: $1])dnl
$1])])


# _AS_ECHO(STRING, [FD = AS_MESSAGE_FD])
# --------------------------------------
# Protect STRING from backquote expansion, echo the result to FD.
m4_define([_AS_ECHO],
[_AS_ECHO_UNQUOTED([_AS_QUOTE([$1])], [$2])])


# _AS_ECHO_N_PREPARE
# ------------------
# Check whether to use -n, \c, or newline-tab to separate
# checking messages from result messages.
# Don't try to cache, since the results of this macro are needed to
# display the checking message.  In addition, caching something used once
# has little interest.
# Idea borrowed from dist 3.0.  Use `*c*,', not `*c,' because if `\c'
# failed there is also a new-line to match.
m4_defun([_AS_ECHO_N_PREPARE],
[case `echo "testing\c"; echo 1,2,3`,`echo -n testing; echo 1,2,3` in
  *c*,-n*) ECHO_N= ECHO_C='
' ECHO_T='	' ;;
  *c*,*  ) ECHO_N=-n ECHO_C= ECHO_T= ;;
  *)       ECHO_N= ECHO_C='\c' ECHO_T= ;;
esac
])# _AS_ECHO_N_PREPARE


# _AS_ECHO_N(STRING, [FD = AS_MESSAGE_FD])
# ----------------------------------------
# Same as _AS_ECHO, but echo doesn't return to a new line.
m4_define([_AS_ECHO_N],
[AS_REQUIRE([_AS_ECHO_N_PREPARE])dnl
echo $ECHO_N "_AS_QUOTE([$1])$ECHO_C" >&m4_default([$2],
                                                    [AS_MESSAGE_FD])])


# AS_MESSAGE(STRING, [FD = AS_MESSAGE_FD])
# ----------------------------------------
m4_define([AS_MESSAGE],
[m4_ifset([AS_MESSAGE_LOG_FD],
          [{ _AS_ECHO([$as_me:$LINENO: $1], [AS_MESSAGE_LOG_FD])
_AS_ECHO([$as_me: $1], [$2]);}],
          [_AS_ECHO([$as_me: $1], [$2])])[]dnl
])


# AS_WARN(PROBLEM)
# ----------------
m4_define([AS_WARN],
[AS_MESSAGE([WARNING: $1], [2])])# AS_WARN


# AS_ERROR(ERROR, [EXIT-STATUS = 1])
# ----------------------------------
m4_define([AS_ERROR],
[{ AS_MESSAGE([error: $1], [2])
   AS_EXIT([$2]); }[]dnl
])# AS_ERROR



## -------------------------------------- ##
## 4. Portable versions of common tools.  ##
## -------------------------------------- ##

# This section is lexicographically sorted.


# AS_DIRNAME(PATHNAME)
# --------------------
# Simulate running `dirname(1)' on PATHNAME, not all systems have it.
# This macro must be usable from inside ` `.
#
# Prefer expr to echo|sed, since expr is usually faster and it handles
# backslashes and newlines correctly.  However, older expr
# implementations (e.g. SunOS 4 expr and Solaris 8 /usr/ucb/expr) have
# a silly length limit that causes expr to fail if the matched
# substring is longer than 120 bytes.  So fall back on echo|sed if
# expr fails.
m4_defun([AS_DIRNAME_EXPR],
[AS_REQUIRE([_AS_EXPR_PREPARE])dnl
$as_expr X[]$1 : 'X\(.*[[^/]]\)//*[[^/][^/]]*/*$' \| \
         X[]$1 : 'X\(//\)[[^/]]' \| \
         X[]$1 : 'X\(//\)$' \| \
         X[]$1 : 'X\(/\)' \| \
         .     : '\(.\)'])

m4_defun([AS_DIRNAME_SED],
[echo X[]$1 |
    sed ['/^X\(.*[^/]\)\/\/*[^/][^/]*\/*$/{ s//\1/; q; }
  	  /^X\(\/\/\)[^/].*/{ s//\1/; q; }
  	  /^X\(\/\/\)$/{ s//\1/; q; }
  	  /^X\(\/\).*/{ s//\1/; q; }
  	  s/.*/./; q']])

m4_defun([AS_DIRNAME],
[(dirname $1) 2>/dev/null ||
AS_DIRNAME_EXPR([$1]) 2>/dev/null ||
AS_DIRNAME_SED([$1])])


# AS_BASENAME(PATHNAME)
# --------------------
# Simulate running `basename(1)' on PATHNAME, not all systems have it.
# Also see the comments for AS_DIRNAME.

m4_defun([AS_BASENAME_EXPR],
[AS_REQUIRE([_AS_EXPR_PREPARE])dnl
$as_expr X/[]$1 : '.*/\([[^/][^/]*]\)/*$' \| \
	 X[]$1 : 'X\(//\)$' \| \
	 X[]$1 : 'X\(/\)$' \| \
	 .     : '\(.\)'])

m4_defun([AS_BASENAME_SED],
[echo X/[]$1 |
    sed ['/^.*\/\([^/][^/]*\)\/*$/{ s//\1/; q; }
  	  /^X\/\(\/\/\)$/{ s//\1/; q; }
  	  /^X\/\(\/\).*/{ s//\1/; q; }
  	  s/.*/./; q']])

m4_defun([AS_BASENAME],
[AS_REQUIRE([_$0_PREPARE])dnl
$as_basename $1 ||
AS_BASENAME_EXPR([$1]) 2>/dev/null ||
AS_BASENAME_SED([$1])])


# AS_EXECUTABLE_P
# ---------------
# Check whether a file is executable.
m4_defun([AS_EXECUTABLE_P],
[AS_REQUIRE([_AS_TEST_PREPARE])dnl
$as_executable_p $1[]dnl
])# AS_EXECUTABLE_P


# _AS_BASENAME_PREPARE
# --------------------
# Avoid Solaris 9 /usr/ucb/basename, as `basename /' outputs an empty line.
m4_defun([_AS_BASENAME_PREPARE],
[if (basename /) >/dev/null 2>&1 && test "X`basename / 2>&1`" = "X/"; then
  as_basename=basename
else
  as_basename=false
fi
])# _AS_BASENAME_PREPARE

# _AS_EXPR_PREPARE
# ----------------
# Some expr work properly (i.e. compute and issue the right result),
# but exit with failure.  When a fall back to expr (as in AS_DIRNAME)
# is provided, you get twice the result.  Prevent this.
m4_defun([_AS_EXPR_PREPARE],
[if expr a : '\(a\)' >/dev/null 2>&1; then
  as_expr=expr
else
  as_expr=false
fi
])# _AS_EXPR_PREPARE

# _AS_LINENO_WORKS
# ---------------
# Succeed if the currently executing shell supports LINENO.
# This macro does not expand to a single shell command, so be careful
# when using it.  Surrounding the body of this macro with {} would
# cause "bash -c '_ASLINENO_WORKS'" to fail (with Bash 2.05, anyway),
# but that bug is irrelevant to our use of LINENO.
m4_define([_AS_LINENO_WORKS],
[
  as_lineno_1=$LINENO
  as_lineno_2=$LINENO
  as_lineno_3=`(expr $as_lineno_1 + 1) 2>/dev/null`
  test "x$as_lineno_1" != "x$as_lineno_2" &&
  test "x$as_lineno_3"  = "x$as_lineno_2" dnl
])

# _AS_LINENO_PREPARE
# ------------------
# If LINENO is not supported by the shell, produce a version of this
# script where LINENO is hard coded.
# Comparing LINENO against _oline_ is not a good solution, since in
# the case of embedded executables (such as config.status within
# configure) you'd compare LINENO wrt config.status vs. _oline_ vs
# configure.
m4_define([_AS_LINENO_PREPARE],
[AS_REQUIRE([_AS_CR_PREPARE])dnl
_AS_LINENO_WORKS || {
  # Find who we are.  Look in the path if we contain no path at all
  # relative or not.
  case $[0] in
    *[[\\/]]* ) as_myself=$[0] ;;
    *) _AS_PATH_WALK([],
                   [test -r "$as_dir/$[0]" && as_myself=$as_dir/$[0] && break])
       ;;
  esac
  # We did not find ourselves, most probably we were run as `sh COMMAND'
  # in which case we are not to be found in the path.
  if test "x$as_myself" = x; then
    as_myself=$[0]
  fi
  if test ! -f "$as_myself"; then
    AS_ERROR([cannot find myself; rerun with an absolute path])
  fi
  case $CONFIG_SHELL in
  '')
    _AS_PATH_WALK([/bin$PATH_SEPARATOR/usr/bin$PATH_SEPARATOR$PATH],
      [for as_base in sh bash ksh sh5; do
	 case $as_dir in
	 /*)
	   if ("$as_dir/$as_base" -c '_AS_LINENO_WORKS') 2>/dev/null; then
	     AS_UNSET(BASH_ENV)
	     AS_UNSET(ENV)
	     CONFIG_SHELL=$as_dir/$as_base
	     export CONFIG_SHELL
	     exec "$CONFIG_SHELL" "$[0]" ${1+"$[@]"}
	   fi;;
	 esac
       done]);;
  esac

  # Create $as_me.lineno as a copy of $as_myself, but with $LINENO
  # uniformly replaced by the line number.  The first 'sed' inserts a
  # line-number line before each line; the second 'sed' does the real
  # work.  The second script uses 'N' to pair each line-number line
  # with the numbered line, and appends trailing '-' during
  # substitution so that $LINENO is not a special case at line end.
  # (Raja R Harinath suggested sed '=', and Paul Eggert wrote the
  # second 'sed' script.  Blame Lee E. McMahon for sed's syntax.  :-)
  sed '=' <$as_myself |
    sed '
      N
      s,$,-,
      : loop
      s,^\([['$as_cr_digits']]*\)\(.*\)[[$]]LINENO\([[^'$as_cr_alnum'_]]\),\1\2\1\3,
      t loop
      s,-$,,
      s,^[['$as_cr_digits']]*\n,,
    ' >$as_me.lineno &&
  chmod +x $as_me.lineno ||
    AS_ERROR([cannot create $as_me.lineno; rerun with a POSIX shell])

  # Don't try to exec as it changes $[0], causing all sort of problems
  # (the dirname of $[0] is not the place where we might find the
  # original and so on.  Autoconf is especially sensible to this).
  . ./$as_me.lineno
  # Exit status is that of the last command.
  exit
}
])# _AS_LINENO_PREPARE


# _AS_LN_S_PREPARE
# ----------------
# Don't use conftest.sym to avoid filename issues on DJGPP, where this
# would yield conftest.sym.exe for DJGPP < 2.04.  And don't use `conftest'
# as base name to avoid prohibiting concurrency (e.g., concurrent
# config.statuses).
m4_defun([_AS_LN_S_PREPARE],
[rm -f conf$$ conf$$.exe conf$$.file
echo >conf$$.file
if ln -s conf$$.file conf$$ 2>/dev/null; then
  # We could just check for DJGPP; but this test a) works b) is more generic
  # and c) will remain valid once DJGPP supports symlinks (DJGPP 2.04).
  if test -f conf$$.exe; then
    # Don't use ln at all; we don't have any links
    as_ln_s='cp -p'
  else
    as_ln_s='ln -s'
  fi
elif ln conf$$.file conf$$ 2>/dev/null; then
  as_ln_s=ln
else
  as_ln_s='cp -p'
fi
rm -f conf$$ conf$$.exe conf$$.file
])# _AS_LN_S_PREPARE


# _AS_PATH_SEPARATOR_PREPARE
# --------------------------
# Compute the path separator.
m4_defun([_AS_PATH_SEPARATOR_PREPARE],
[# The user is always right.
if test "${PATH_SEPARATOR+set}" != set; then
  echo "#! /bin/sh" >conf$$.sh
  echo  "exit 0"   >>conf$$.sh
  chmod +x conf$$.sh
  if (PATH="/nonexistent;."; conf$$.sh) >/dev/null 2>&1; then
    PATH_SEPARATOR=';'
  else
    PATH_SEPARATOR=:
  fi
  rm -f conf$$.sh
fi
])# _AS_PATH_SEPARATOR_PREPARE


# _AS_PATH_WALK([PATH = $PATH], BODY)
# -----------------------------------
# Walk through PATH running BODY for each `as_dir'.
#
# Still very private as its interface looks quite bad.
#
# `$as_dummy' forces splitting on constant user-supplied paths.
# POSIX.2 field splitting is done only on the result of word
# expansions, not on literal text.  This closes a longstanding sh security
# hole.  Optimize it away when not needed, i.e., if there are no literal
# path separators.
m4_define([_AS_PATH_WALK],
[AS_REQUIRE([_AS_PATH_SEPARATOR_PREPARE])dnl
as_save_IFS=$IFS; IFS=$PATH_SEPARATOR
m4_bmatch([$1], [[:;]],
[as_dummy="$1"
for as_dir in $as_dummy],
[for as_dir in m4_default([$1], [$PATH])])
do
  IFS=$as_save_IFS
  test -z "$as_dir" && as_dir=.
  $2
done
])


# AS_LN_S(FILE, LINK)
# -------------------
# FIXME: Should we add the glue code to handle properly relative symlinks
# simulated with `ln' or `cp'?
m4_defun([AS_LN_S],
[AS_REQUIRE([_AS_LN_S_PREPARE])dnl
$as_ln_s $1 $2
])


# _AS_MKDIR_P_PREPARE
# -------------------
m4_defun([_AS_MKDIR_P_PREPARE],
[if mkdir -p . 2>/dev/null; then
  as_mkdir_p=:
else
  as_mkdir_p=false
fi
])# _AS_MKDIR_P_PREPARE

# AS_MKDIR_P(PATH)
# ----------------
# Emulate `mkdir -p' with plain `mkdir'.
m4_define([AS_MKDIR_P],
[AS_REQUIRE([_$0_PREPARE])dnl
{ if $as_mkdir_p; then
    mkdir -p $1
  else
    as_dir=$1
    as_dirs=
    while test ! -d "$as_dir"; do
      as_dirs="$as_dir $as_dirs"
      as_dir=`AS_DIRNAME("$as_dir")`
    done
    test ! -n "$as_dirs" || mkdir $as_dirs
  fi || AS_ERROR([cannot create directory $1]); }
])# AS_MKDIR_P


# _AS_BROKEN_TEST_PREPARE
# -----------------------
# FIXME: This does not work and breaks way too many things.
#
# Find out ahead of time whether we want test -x (preferred) or test -f
# to check whether a file is executable.
m4_defun([_AS_BROKEN_TEST_PREPARE],
[# Find out how to test for executable files. Don't use a zero-byte file,
# as systems may use methods other than mode bits to determine executability.
cat >conf$$.file <<_ASEOF
@%:@! /bin/sh
exit 0
_ASEOF
chmod +x conf$$.file
if test -x conf$$.file >/dev/null 2>&1; then
  as_executable_p="test -x"
elif test -f conf$$.file >/dev/null 2>&1; then
  as_executable_p="test -f"
else
  AS_ERROR([cannot check whether a file is executable on this system])
fi
rm -f conf$$.file
])# _AS_BROKEN_TEST_PREPARE


# _AS_TEST_PREPARE
# ----------------
m4_defun([_AS_TEST_PREPARE],
[as_executable_p="test -f"
])# _AS_BROKEN_TEST_PREPARE






## ------------------ ##
## 5. Common idioms.  ##
## ------------------ ##

# This section is lexicographically sorted.


# AS_BOX(MESSAGE, [FRAME-CHARACTER = `-'])
# ----------------------------------------
# Output MESSAGE, a single line text, framed with FRAME-CHARACTER (which
# must not be `/').
m4_define([AS_BOX],
[AS_LITERAL_IF([$1],
               [_AS_BOX_LITERAL($@)],
               [_AS_BOX_INDIR($@)])])

# _AS_BOX_LITERAL(MESSAGE, [FRAME-CHARACTER = `-'])
# -------------------------------------------------
m4_define([_AS_BOX_LITERAL],
[cat <<\_ASBOX
m4_text_box($@)
_ASBOX])

# _AS_BOX_INDIR(MESSAGE, [FRAME-CHARACTER = `-'])
# -----------------------------------------------
m4_define([_AS_BOX_INDIR],
[sed 'h;s/./m4_default([$2], [-])/g;s/^.../@%:@@%:@ /;s/...$/ @%:@@%:@/;p;x;p;x' <<_ASBOX
@%:@@%:@ $1 @%:@@%:@
_ASBOX])


# AS_LITERAL_IF(EXPRESSION, IF-LITERAL, IF-NOT-LITERAL)
# -----------------------------------------------------
# If EXPRESSION has shell indirections ($var or `expr`), expand
# IF-INDIR, else IF-NOT-INDIR.
# This is an *approximation*: for instance EXPRESSION = `\$' is
# definitely a literal, but will not be recognized as such.
m4_define([AS_LITERAL_IF],
[m4_bmatch([$1], [[`$]],
           [$3], [$2])])


# AS_TMPDIR(PREFIX, [DIRECTORY = $TMPDIR [= /tmp]])
# -------------------------------------------------
# Create as safely as possible a temporary directory in DIRECTORY
# which name is inspired by PREFIX (should be 2-4 chars max), and set
# trap mechanisms to remove it.
m4_define([AS_TMPDIR],
[# Create a temporary directory, and hook for its removal unless debugging.
$debug ||
{
  trap 'exit_status=$?; rm -rf $tmp && exit $exit_status' 0
  trap 'AS_EXIT([1])' 1 2 13 15
}

# Create a (secure) tmp directory for tmp files.
m4_if([$2], [], [: ${TMPDIR=/tmp}])
{
  tmp=`(umask 077 && mktemp -d -q "m4_default([$2], [$TMPDIR])/$1XXXXXX") 2>/dev/null` &&
  test -n "$tmp" && test -d "$tmp"
}  ||
{
  tmp=m4_default([$2], [$TMPDIR])/$1$$-$RANDOM
  (umask 077 && mkdir $tmp)
} ||
{
   echo "$me: cannot create a temporary directory in m4_default([$2], [$TMPDIR])" >&2
   AS_EXIT
}dnl
])# AS_TMPDIR


# AS_UNAME
# --------
# Try to describe this machine.  Meant for logs.
m4_define([AS_UNAME],
[{
cat <<_ASUNAME
m4_text_box([Platform.])

hostname = `(hostname || uname -n) 2>/dev/null | sed 1q`
uname -m = `(uname -m) 2>/dev/null || echo unknown`
uname -r = `(uname -r) 2>/dev/null || echo unknown`
uname -s = `(uname -s) 2>/dev/null || echo unknown`
uname -v = `(uname -v) 2>/dev/null || echo unknown`

/usr/bin/uname -p = `(/usr/bin/uname -p) 2>/dev/null || echo unknown`
/bin/uname -X     = `(/bin/uname -X) 2>/dev/null     || echo unknown`

/bin/arch              = `(/bin/arch) 2>/dev/null              || echo unknown`
/usr/bin/arch -k       = `(/usr/bin/arch -k) 2>/dev/null       || echo unknown`
/usr/convex/getsysinfo = `(/usr/convex/getsysinfo) 2>/dev/null || echo unknown`
hostinfo               = `(hostinfo) 2>/dev/null               || echo unknown`
/bin/machine           = `(/bin/machine) 2>/dev/null           || echo unknown`
/usr/bin/oslevel       = `(/usr/bin/oslevel) 2>/dev/null       || echo unknown`
/bin/universe          = `(/bin/universe) 2>/dev/null          || echo unknown`

_ASUNAME

_AS_PATH_WALK([$PATH], [echo "PATH: $as_dir"])
}])



## ------------------------------------ ##
## Common m4/sh character translation.  ##
## ------------------------------------ ##

# The point of this section is to provide high level macros comparable
# to m4's `translit' primitive, but m4/sh polymorphic.
# Transliteration of literal strings should be handled by m4, while
# shell variables' content will be translated at runtime (tr or sed).


# _AS_CR_PREPARE
# --------------
# Output variables defining common character ranges.
# See m4_cr_letters etc.
m4_defun([_AS_CR_PREPARE],
[# Avoid depending upon Character Ranges.
as_cr_letters='abcdefghijklmnopqrstuvwxyz'
as_cr_LETTERS='ABCDEFGHIJKLMNOPQRSTUVWXYZ'
as_cr_Letters=$as_cr_letters$as_cr_LETTERS
as_cr_digits='0123456789'
as_cr_alnum=$as_cr_Letters$as_cr_digits
])


# _AS_TR_SH_PREPARE
# -----------------
m4_defun([_AS_TR_SH_PREPARE],
[AS_REQUIRE([_AS_CR_PREPARE])dnl
# Sed expression to map a string onto a valid variable name.
as_tr_sh="sed y%*+%pp%;s%[[^_$as_cr_alnum]]%_%g"
])


# AS_TR_SH(EXPRESSION)
# --------------------
# Transform EXPRESSION into a valid shell variable name.
# sh/m4 polymorphic.
# Be sure to update the definition of `$as_tr_sh' if you change this.
m4_defun([AS_TR_SH],
[AS_REQUIRE([_$0_PREPARE])dnl
AS_LITERAL_IF([$1],
              [m4_bpatsubst(m4_translit([[$1]], [*+], [pp]),
                            [[^a-zA-Z0-9_]], [_])],
              [`echo "$1" | $as_tr_sh`])])


# _AS_TR_CPP_PREPARE
# ------------------
m4_defun([_AS_TR_CPP_PREPARE],
[AS_REQUIRE([_AS_CR_PREPARE])dnl
# Sed expression to map a string onto a valid CPP name.
as_tr_cpp="sed y%*$as_cr_letters%P$as_cr_LETTERS%;s%[[^_$as_cr_alnum]]%_%g"
])


# AS_TR_CPP(EXPRESSION)
# ---------------------
# Map EXPRESSION to an upper case string which is valid as rhs for a
# `#define'.  sh/m4 polymorphic.  Be sure to update the definition
# of `$as_tr_cpp' if you change this.
m4_defun([AS_TR_CPP],
[AS_REQUIRE([_$0_PREPARE])dnl
AS_LITERAL_IF([$1],
              [m4_bpatsubst(m4_translit([[$1]],
                                        [*abcdefghijklmnopqrstuvwxyz],
                                        [PABCDEFGHIJKLMNOPQRSTUVWXYZ]),
                           [[^A-Z0-9_]], [_])],
              [`echo "$1" | $as_tr_cpp`])])


# _AS_TR_PREPARE
# --------------
m4_defun([_AS_TR_PREPARE],
[AS_REQUIRE([_AS_TR_SH_PREPARE])dnl
AS_REQUIRE([_AS_TR_CPP_PREPARE])dnl
])




## --------------------------------------------------- ##
## Common m4/sh handling of variables (indirections).  ##
## --------------------------------------------------- ##


# The purpose of this section is to provide a uniform API for
# reading/setting sh variables with or without indirection.
# Typically, one can write
#   AS_VAR_SET(var, val)
# or
#   AS_VAR_SET(as_$var, val)
# and expect the right thing to happen.


# AS_VAR_SET(VARIABLE, VALUE)
# ---------------------------
# Set the VALUE of the shell VARIABLE.
# If the variable contains indirections (e.g. `ac_cv_func_$ac_func')
# perform whenever possible at m4 level, otherwise sh level.
m4_define([AS_VAR_SET],
[AS_LITERAL_IF([$1],
               [$1=$2],
               [eval "$1=$2"])])


# AS_VAR_GET(VARIABLE)
# --------------------
# Get the value of the shell VARIABLE.
# Evaluates to $VARIABLE if there are no indirection in VARIABLE,
# else into the appropriate `eval' sequence.
m4_define([AS_VAR_GET],
[AS_LITERAL_IF([$1],
               [$$1],
               [`eval echo '${'m4_bpatsubst($1, [[\\`]], [\\\&])'}'`])])


# AS_VAR_TEST_SET(VARIABLE)
# -------------------------
# Expands into the `test' expression which is true if VARIABLE
# is set.  Polymorphic.  Should be dnl'ed.
m4_define([AS_VAR_TEST_SET],
[AS_LITERAL_IF([$1],
               [test "${$1+set}" = set],
               [eval "test \"\${$1+set}\" = set"])])


# AS_VAR_SET_IF(VARIABLE, IF-TRUE, IF-FALSE)
# ------------------------------------------
# Implement a shell `if-then-else' depending whether VARIABLE is set
# or not.  Polymorphic.
m4_define([AS_VAR_SET_IF],
[AS_IF([AS_VAR_TEST_SET([$1])], [$2], [$3])])


# AS_VAR_PUSHDEF and AS_VAR_POPDEF
# --------------------------------
#

# Sometimes we may have to handle literals (e.g. `stdlib.h'), while at
# other moments, the same code may have to get the value from a
# variable (e.g., `ac_header').  To have a uniform handling of both
# cases, when a new value is about to be processed, declare a local
# variable, e.g.:
#
#   AS_VAR_PUSHDEF([header], [ac_cv_header_$1])
#
# and then in the body of the macro, use `header' as is.  It is of
# first importance to use `AS_VAR_*' to access this variable.  Don't
# quote its name: it must be used right away by m4.
#
# If the value `$1' was a literal (e.g. `stdlib.h'), then `header' is
# in fact the value `ac_cv_header_stdlib_h'.  If `$1' was indirect,
# then `header's value in m4 is in fact `$ac_header', the shell
# variable that holds all of the magic to get the expansion right.
#
# At the end of the block, free the variable with
#
#   AS_VAR_POPDEF([header])


# AS_VAR_PUSHDEF(VARNAME, VALUE)
# ------------------------------
# Define the m4 macro VARNAME to an accessor to the shell variable
# named VALUE.  VALUE does not need to be a valid shell variable name:
# the transliteration is handled here.  To be dnl'ed.
m4_define([AS_VAR_PUSHDEF],
[AS_LITERAL_IF([$2],
               [m4_pushdef([$1], [AS_TR_SH($2)])],
               [as_$1=AS_TR_SH($2)
m4_pushdef([$1], [$as_[$1]])])])


# AS_VAR_POPDEF(VARNAME)
# ----------------------
# Free the shell variable accessor VARNAME.  To be dnl'ed.
m4_define([AS_VAR_POPDEF],
[m4_popdef([$1])])



## ----------------- ##
## Setting M4sh up.  ##
## ----------------- ##


# AS_INIT
# -------
m4_define([AS_INIT],
[m4_init

# Forbidden tokens and exceptions.
m4_pattern_forbid([^_?AS_])

# Bangshe and minimal initialization.
m4_divert_text([BINSH], [@%:@! /bin/sh])
m4_divert_text([M4SH-INIT], [AS_SHELL_SANITIZE])

# Let's go!
m4_wrap([m4_divert_pop([BODY])[]])
m4_divert_push([BODY])[]dnl
])

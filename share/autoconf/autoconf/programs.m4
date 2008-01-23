# This file is part of Autoconf.                       -*- Autoconf -*-
# Checking for programs.
# Copyright (C) 1992, 1993, 1994, 1995, 1996, 1998, 1999, 2000, 2001, 2002
# Free Software Foundation, Inc.

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
#
# Written by David MacKenzie, with help from
# Franc,ois Pinard, Karl Berry, Richard Pixley, Ian Lance Taylor,
# Roland McGrath, Noah Friedman, david d zuhn, and many others.


## ----------------------------- ##
## Generic checks for programs.  ##
## ----------------------------- ##


# AC_CHECK_PROG(VARIABLE, PROG-TO-CHECK-FOR,
#               [VALUE-IF-FOUND], [VALUE-IF-NOT-FOUND],
#               [PATH], [REJECT])
# -----------------------------------------------------
AC_DEFUN([AC_CHECK_PROG],
[# Extract the first word of "$2", so it can be a program name with args.
set dummy $2; ac_word=$[2]
AC_MSG_CHECKING([for $ac_word])
AC_CACHE_VAL(ac_cv_prog_$1,
[if test -n "$$1"; then
  ac_cv_prog_$1="$$1" # Let the user override the test.
else
m4_ifvaln([$6],
[  ac_prog_rejected=no])dnl
_AS_PATH_WALK([$5],
[for ac_exec_ext in '' $ac_executable_extensions; do
  if AS_EXECUTABLE_P(["$as_dir/$ac_word$ac_exec_ext"]); then
m4_ifvaln([$6],
[    if test "$as_dir/$ac_word$ac_exec_ext" = "$6"; then
       ac_prog_rejected=yes
       continue
     fi])dnl
    ac_cv_prog_$1="$3"
    echo "$as_me:$LINENO: found $as_dir/$ac_word$ac_exec_ext" >&AS_MESSAGE_LOG_FD
    break 2
  fi
done])
m4_ifvaln([$6],
[if test $ac_prog_rejected = yes; then
  # We found a bogon in the path, so make sure we never use it.
  set dummy $ac_cv_prog_$1
  shift
  if test $[@%:@] != 0; then
    # We chose a different compiler from the bogus one.
    # However, it has the same basename, so the bogon will be chosen
    # first if we set $1 to just the basename; use the full file name.
    shift
    ac_cv_prog_$1="$as_dir/$ac_word${1+' '}$[@]"
m4_if([$2], [$4],
[  else
    # Default is a loser.
    AC_MSG_ERROR([$1=$6 unacceptable, but no other $4 found in dnl
m4_default([$5], [\$PATH])])
])dnl
  fi
fi])dnl
dnl If no 4th arg is given, leave the cache variable unset,
dnl so AC_CHECK_PROGS will keep looking.
m4_ifvaln([$4],
[  test -z "$ac_cv_prog_$1" && ac_cv_prog_$1="$4"])dnl
fi])dnl
$1=$ac_cv_prog_$1
if test -n "$$1"; then
  AC_MSG_RESULT([$$1])
else
  AC_MSG_RESULT([no])
fi
AC_SUBST($1)dnl
])# AC_CHECK_PROG


# AC_CHECK_PROGS(VARIABLE, PROGS-TO-CHECK-FOR, [VALUE-IF-NOT-FOUND],
#                [PATH])
# ------------------------------------------------------------------
AC_DEFUN([AC_CHECK_PROGS],
[for ac_prog in $2
do
  AC_CHECK_PROG([$1], [$ac_prog], [$ac_prog], , [$4])
  test -n "$$1" && break
done
m4_ifvaln([$3], [test -n "$$1" || $1="$3"])])


# AC_PATH_PROG(VARIABLE, PROG-TO-CHECK-FOR, [VALUE-IF-NOT-FOUND], [PATH])
# -----------------------------------------------------------------------
AC_DEFUN([AC_PATH_PROG],
[# Extract the first word of "$2", so it can be a program name with args.
set dummy $2; ac_word=$[2]
AC_MSG_CHECKING([for $ac_word])
AC_CACHE_VAL([ac_cv_path_$1],
[case $$1 in
  [[\\/]]* | ?:[[\\/]]*)
  ac_cv_path_$1="$$1" # Let the user override the test with a path.
  ;;
  *)
  _AS_PATH_WALK([$4],
[for ac_exec_ext in '' $ac_executable_extensions; do
  if AS_EXECUTABLE_P(["$as_dir/$ac_word$ac_exec_ext"]); then
    ac_cv_path_$1="$as_dir/$ac_word$ac_exec_ext"
    echo "$as_me:$LINENO: found $as_dir/$ac_word$ac_exec_ext" >&AS_MESSAGE_LOG_FD
    break 2
  fi
done])
dnl If no 3rd arg is given, leave the cache variable unset,
dnl so AC_PATH_PROGS will keep looking.
m4_ifvaln([$3],
[  test -z "$ac_cv_path_$1" && ac_cv_path_$1="$3"])dnl
  ;;
esac])dnl
AC_SUBST([$1], [$ac_cv_path_$1])
if test -n "$$1"; then
  AC_MSG_RESULT([$$1])
else
  AC_MSG_RESULT([no])
fi
])# AC_PATH_PROG


# AC_PATH_PROGS(VARIABLE, PROGS-TO-CHECK-FOR, [VALUE-IF-NOT-FOUND],
#               [PATH])
# -----------------------------------------------------------------
AC_DEFUN([AC_PATH_PROGS],
[for ac_prog in $2
do
  AC_PATH_PROG([$1], [$ac_prog], , [$4])
  test -n "$$1" && break
done
m4_ifvaln([$3], [test -n "$$1" || $1="$3"])dnl
])




## -------------------------- ##
## Generic checks for tools.  ##
## -------------------------- ##


# AC_CHECK_TOOL_PREFIX
# --------------------
AU_DEFUN([AC_CHECK_TOOL_PREFIX])


# AC_PATH_TOOL(VARIABLE, PROG-TO-CHECK-FOR, [VALUE-IF-NOT-FOUND], [PATH])
# -----------------------------------------------------------------------
# (Use different variables $1 and ac_pt_$1 so that cache vars don't conflict.)
AC_DEFUN([AC_PATH_TOOL],
[if test -n "$ac_tool_prefix"; then
  AC_PATH_PROG([$1], [${ac_tool_prefix}$2], , [$4])
fi
if test -z "$ac_cv_path_$1"; then
  ac_pt_$1=$$1
  AC_PATH_PROG([ac_pt_$1], [$2], [$3], [$4])
  $1=$ac_pt_$1
else
  $1="$ac_cv_path_$1"
fi
])# AC_PATH_TOOL


# AC_CHECK_TOOL(VARIABLE, PROG-TO-CHECK-FOR, [VALUE-IF-NOT-FOUND], [PATH])
# ------------------------------------------------------------------------
# (Use different variables $1 and ac_ct_$1 so that cache vars don't conflict.)
AC_DEFUN([AC_CHECK_TOOL],
[if test -n "$ac_tool_prefix"; then
  AC_CHECK_PROG([$1], [${ac_tool_prefix}$2], [${ac_tool_prefix}$2], , [$4])
fi
if test -z "$ac_cv_prog_$1"; then
  ac_ct_$1=$$1
  AC_CHECK_PROG([ac_ct_$1], [$2], [$2], [$3], [$4])
  $1=$ac_ct_$1
else
  $1="$ac_cv_prog_$1"
fi
])# AC_CHECK_TOOL


# AC_CHECK_TOOLS(VARIABLE, PROGS-TO-CHECK-FOR, [VALUE-IF-NOT-FOUND],
#                [PATH])
# ------------------------------------------------------------------
# Check for each tool in PROGS-TO-CHECK-FOR with the cross prefix. If
# none can be found with a cross prefix, then use the first one that
# was found without the cross prefix.
AC_DEFUN([AC_CHECK_TOOLS],
[if test -n "$ac_tool_prefix"; then
  for ac_prog in $2
  do
    AC_CHECK_PROG([$1],
                  [$ac_tool_prefix$ac_prog], [$ac_tool_prefix$ac_prog],,
                  [$4])
    test -n "$$1" && break
  done
fi
if test -z "$$1"; then
  ac_ct_$1=$$1
  AC_CHECK_PROGS([ac_ct_$1], [$2], [$3], [$4])
  $1=$ac_ct_$1
fi
])# AC_CHECK_TOOLS



## ---------------- ##
## Specific tests.  ##
## ---------------- ##

# Please, keep this section sorted.
# (But of course when keeping related things together).

# Check for gawk first since it's generally better.
AN_MAKEVAR([AWK],  [AC_PROG_AWK])
AN_PROGRAM([awk],  [AC_PROG_AWK])
AN_PROGRAM([gawk], [AC_PROG_AWK])
AN_PROGRAM([mawk], [AC_PROG_AWK])
AN_PROGRAM([nawk], [AC_PROG_AWK])
AC_DEFUN([AC_PROG_AWK],
[AC_CHECK_PROGS(AWK, gawk mawk nawk awk, )])


# AC_PROG_EGREP
# -------------
AC_DEFUN([AC_PROG_EGREP],
[AC_CACHE_CHECK([for egrep], [ac_cv_prog_egrep],
   [if echo a | (grep -E '(a|b)') >/dev/null 2>&1
    then ac_cv_prog_egrep='grep -E'
    else ac_cv_prog_egrep='egrep'
    fi])
 EGREP=$ac_cv_prog_egrep
 AC_SUBST([EGREP])
])# AC_PROG_EGREP


# AC_PROG_FGREP
# -------------
AC_DEFUN([AC_PROG_FGREP],
[AC_CACHE_CHECK([for fgrep], [ac_cv_prog_fgrep],
   [if echo 'ab*c' | (grep -F 'ab*c') >/dev/null 2>&1
    then ac_cv_prog_fgrep='grep -F'
    else ac_cv_prog_fgrep='fgrep'
    fi])
 FGREP=$ac_cv_prog_fgrep
 AC_SUBST([FGREP])
])# AC_PROG_FGREP


# AC_PROG_INSTALL
# ---------------
AN_MAKEVAR([INSTALL], [AC_PROG_INSTALL])
AN_PROGRAM([install], [AC_PROG_INSTALL])
AC_DEFUN([AC_PROG_INSTALL],
[AC_REQUIRE([AC_CONFIG_AUX_DIR_DEFAULT])dnl
# Find a good install program.  We prefer a C program (faster),
# so one script is as good as another.  But avoid the broken or
# incompatible versions:
# SysV /etc/install, /usr/sbin/install
# SunOS /usr/etc/install
# IRIX /sbin/install
# AIX /bin/install
# AmigaOS /C/install, which installs bootblocks on floppy discs
# AIX 4 /usr/bin/installbsd, which doesn't work without a -g flag
# AFS /usr/afsws/bin/install, which mishandles nonexistent args
# SVR4 /usr/ucb/install, which tries to use the nonexistent group "staff"
# ./install, which can be erroneously created by make from ./install.sh.
AC_MSG_CHECKING([for a BSD-compatible install])
if test -z "$INSTALL"; then
AC_CACHE_VAL(ac_cv_path_install,
[_AS_PATH_WALK([$PATH],
[# Account for people who put trailing slashes in PATH elements.
case $as_dir/ in
  ./ | .// | /[cC]/* | \
  /etc/* | /usr/sbin/* | /usr/etc/* | /sbin/* | /usr/afsws/bin/* | \
  /usr/ucb/* ) ;;
  *)
    # OSF1 and SCO ODT 3.0 have their own names for install.
    # Don't use installbsd from OSF since it installs stuff as root
    # by default.
    for ac_prog in ginstall scoinst install; do
      for ac_exec_ext in '' $ac_executable_extensions; do
        if AS_EXECUTABLE_P(["$as_dir/$ac_prog$ac_exec_ext"]); then
          if test $ac_prog = install &&
            grep dspmsg "$as_dir/$ac_prog$ac_exec_ext" >/dev/null 2>&1; then
            # AIX install.  It has an incompatible calling convention.
            :
          elif test $ac_prog = install &&
            grep pwplus "$as_dir/$ac_prog$ac_exec_ext" >/dev/null 2>&1; then
            # program-specific install script used by HP pwplus--don't use.
            :
          else
            ac_cv_path_install="$as_dir/$ac_prog$ac_exec_ext -c"
            break 3
          fi
        fi
      done
    done
    ;;
esac])
])dnl
  if test "${ac_cv_path_install+set}" = set; then
    INSTALL=$ac_cv_path_install
  else
    # As a last resort, use the slow shell script.  We don't cache a
    # path for INSTALL within a source directory, because that will
    # break other packages using the cache if that directory is
    # removed, or if the path is relative.
    INSTALL=$ac_install_sh
  fi
fi
dnl We do special magic for INSTALL instead of AC_SUBST, to get
dnl relative paths right.
AC_MSG_RESULT([$INSTALL])

# Use test -z because SunOS4 sh mishandles braces in ${var-val}.
# It thinks the first close brace ends the variable substitution.
test -z "$INSTALL_PROGRAM" && INSTALL_PROGRAM='${INSTALL}'
AC_SUBST(INSTALL_PROGRAM)dnl

test -z "$INSTALL_SCRIPT" && INSTALL_SCRIPT='${INSTALL}'
AC_SUBST(INSTALL_SCRIPT)dnl

test -z "$INSTALL_DATA" && INSTALL_DATA='${INSTALL} -m 644'
AC_SUBST(INSTALL_DATA)dnl
])# AC_PROG_INSTALL


# AC_PROG_LEX
# -----------
# Look for flex or lex.  Set its associated library to LEXLIB.
# Check if lex declares yytext as a char * by default, not a char[].
AN_MAKEVAR([LEX],  [AC_PROG_LEX])
AN_PROGRAM([lex],  [AC_PROG_LEX])
AN_PROGRAM([flex], [AC_PROG_LEX])
AC_DEFUN_ONCE([AC_PROG_LEX],
[AC_CHECK_PROGS(LEX, flex lex, :)
if test -z "$LEXLIB"
then
  AC_CHECK_LIB(fl, yywrap, LEXLIB="-lfl",
    [AC_CHECK_LIB(l, yywrap, LEXLIB="-ll")])
fi
AC_SUBST(LEXLIB)
if test "x$LEX" != "x:"; then
  _AC_PROG_LEX_YYTEXT_DECL
fi])


# _AC_PROG_LEX_YYTEXT_DECL
# ------------------------
# Check if lex declares yytext as a char * by default, not a char[].
m4_define([_AC_PROG_LEX_YYTEXT_DECL],
[AC_CACHE_CHECK(lex output file root, ac_cv_prog_lex_root,
[# The minimal lex program is just a single line: %%.  But some broken lexes
# (Solaris, I think it was) want two %% lines, so accommodate them.
cat >conftest.l <<_ACEOF
%%
%%
_ACEOF
AC_TRY_EVAL(LEX conftest.l)
if test -f lex.yy.c; then
  ac_cv_prog_lex_root=lex.yy
elif test -f lexyy.c; then
  ac_cv_prog_lex_root=lexyy
else
  AC_MSG_ERROR([cannot find output from $LEX; giving up])
fi])
rm -f conftest.l
AC_SUBST([LEX_OUTPUT_ROOT], [$ac_cv_prog_lex_root])dnl

AC_CACHE_CHECK(whether yytext is a pointer, ac_cv_prog_lex_yytext_pointer,
[# POSIX says lex can declare yytext either as a pointer or an array; the
# default is implementation-dependent. Figure out which it is, since
# not all implementations provide the %pointer and %array declarations.
ac_cv_prog_lex_yytext_pointer=no
echo 'extern char *yytext;' >>$LEX_OUTPUT_ROOT.c
ac_save_LIBS=$LIBS
LIBS="$LIBS $LEXLIB"
AC_LINK_IFELSE([`cat $LEX_OUTPUT_ROOT.c`], ac_cv_prog_lex_yytext_pointer=yes)
LIBS=$ac_save_LIBS
rm -f "${LEX_OUTPUT_ROOT}.c"
])
dnl
if test $ac_cv_prog_lex_yytext_pointer = yes; then
  AC_DEFINE(YYTEXT_POINTER, 1,
            [Define to 1 if `lex' declares `yytext' as a `char *' by default,
             not a `char[]'.])
fi
])# _AC_PROG_LEX_YYTEXT_DECL


# Require AC_PROG_LEX in case some people were just calling this macro.
AU_DEFUN([AC_DECL_YYTEXT],  [AC_PROG_LEX])


# AC_PROG_LN_S
# ------------
AN_MAKEVAR([LN], [AC_PROG_LN_S])
AN_PROGRAM([ln], [AC_PROG_LN_S])
AC_DEFUN([AC_PROG_LN_S],
[AC_MSG_CHECKING([whether ln -s works])
AC_SUBST([LN_S], [$as_ln_s])dnl
if test "$LN_S" = "ln -s"; then
  AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no, using $LN_S])
fi
])# AC_PROG_LN_S


# AC_PROG_MAKE_SET
# ----------------
# Define SET_MAKE to set ${MAKE} if make doesn't.
AN_MAKEVAR([MAKE], [AC_PROG_MAKE_SET])
AN_PROGRAM([make], [AC_PROG_MAKE_SET])
AC_DEFUN([AC_PROG_MAKE_SET],
[AC_MSG_CHECKING([whether ${MAKE-make} sets \$(MAKE)])
set dummy ${MAKE-make}; ac_make=`echo "$[2]" | sed 'y,./+-,__p_,'`
AC_CACHE_VAL(ac_cv_prog_make_${ac_make}_set,
[cat >conftest.make <<\_ACEOF
all:
	@echo 'ac_maketemp="$(MAKE)"'
_ACEOF
# GNU make sometimes prints "make[1]: Entering...", which would confuse us.
eval `${MAKE-make} -f conftest.make 2>/dev/null | grep temp=`
if test -n "$ac_maketemp"; then
  eval ac_cv_prog_make_${ac_make}_set=yes
else
  eval ac_cv_prog_make_${ac_make}_set=no
fi
rm -f conftest.make])dnl
if eval "test \"`echo '$ac_cv_prog_make_'${ac_make}_set`\" = yes"; then
  AC_MSG_RESULT([yes])
  SET_MAKE=
else
  AC_MSG_RESULT([no])
  SET_MAKE="MAKE=${MAKE-make}"
fi
AC_SUBST([SET_MAKE])dnl
])# AC_PROG_MAKE_SET


# AC_PROG_RANLIB
# --------------
AN_MAKEVAR([RANLIB], [AC_PROG_RANLIB])
AN_PROGRAM([ranlib], [AC_PROG_RANLIB])
AC_DEFUN([AC_PROG_RANLIB],
[AC_CHECK_TOOL(RANLIB, ranlib, :)])


# AC_RSH
# ------
# I don't know what it used to do, but it no longer does.
AU_DEFUN([AC_RSH],
[AC_DIAGNOSE([obsolete], [$0: is no longer supported.
Remove this warning when you adjust the code.])])


# AC_PROG_YACC
# ------------
AN_MAKEVAR([BISON],  [AC_PROG_YACC])
AN_MAKEVAR([YACC],  [AC_PROG_YACC])
AN_PROGRAM([yacc],  [AC_PROG_YACC])
AN_PROGRAM([byacc], [AC_PROG_YACC])
AN_PROGRAM([bison], [AC_PROG_YACC])
AC_DEFUN([AC_PROG_YACC],
[AC_CHECK_PROGS(YACC, 'bison -y' byacc, yacc)])

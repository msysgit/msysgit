/* getcp.c - Copyright (C) 2010 Pat Thoyts <patthoyts@users.sourceforge.net>
 *
 *	Get the current OEM or ANSI code-page.
 *
 * This utility prints the current ANSI or OEM code-page id without any
 * dependence on the current locate. Windows provides the 'chcp' command
 * which prints the code page when called without any arguments, but the
 * output is dependent on the current language which complicates parsing.
 *
 * Usage: getcp ?-ansi | -oem?
 *
 */

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    UINT cp;
    if (argc > 1 && strncmp(argv[1], "-oem", 4) == 0) {
        cp = GetOEMCP();
    } else {
        cp = GetACP();
    }
    printf("%u\n", cp);
    return 0;
}

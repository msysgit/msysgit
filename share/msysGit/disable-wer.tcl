#!/mingw/bin/tclsh

# Use this script to set the registry settings to disable the 'a problem
# caused the program to stop working' dialog box when something crashed.
#
# This is desirable e.g. when running Git's test suite since a single
# crash would simply block the complete process.

package require registry 1.0

set wer "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows"
set wer "$wer\\Windows Error Reporting"
registry set "$wer" "Disabled" 1 dword
registry set "$wer" "ForceQueue" 1 dword
registry set "$wer" "DontShowUI" 1 dword
registry set "$wer\\Consent" "DefaultConsent" 1 dword

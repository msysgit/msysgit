w00w00 improved version of depends.exe (minus the GUI + automated searching)
Matt Conover (shok@dataforce.net)
April 2003

This will find *.exe, *.dll, *.sys, and *.pyd (Python DLLs) that imports a certain DLL or function in a DLL (e.g., import wsock32.dll or import msvcrt.dll!_snprintf) or export a certain function. It can be useful when you don't know what libraries export a certain function (like RtlInitUnicodeString) or you want to find all applications using a function in a DLL with a known vulnerability.

Usage: w00depends test.dll c:\dir\test.exe
        Report if c:\dir\test.exe imports test.dll
        
Examples:
w00depends test.dll!funcname c:\dir\test.exe
        Report if c:\dir\test.exe imports test.dll!funcname
w00depends test.dll c:\dir
        Find executables importing test.dll in c:\dir
w00depends test.dll!funcname c:\dir
        Find executables importing funcname from test.dll in c:\dir
w00depends test!funcname c:\dir
        Find executables importing funcname from test.dll in c:\dir
w00depends test!ord_1234 c:\dir
        Find executables importing ordinal 1234 (in decimal) from test.dll in c:\dir
w00depends -e funcname c:\dir
        Find all DLLs exporting funcname in c:\dir

Output will look like this:        
C:\> w00depends kernel32!CreateFileA c:\winnt\system32
Match found: c:\winnt\system32\ACrd10SM.dll imports kernel32!createfilea
Match found: c:\winnt\system32\actmovie.exe imports kernel32!createfilea
Match found: c:\winnt\system32\ACUMon.exe imports kernel32!createfilea
Match found: c:\winnt\system32\ADVAPI32.DLL imports kernel32!createfilea
Match found: c:\winnt\system32\advpack.dll imports kernel32!createfilea
Match found: c:\winnt\system32\atmadm.exe imports kernel32!createfilea
Match found: c:\winnt\system32\AUTMGR32.EXE imports kernel32!createfilea
Match found: c:\winnt\system32\Axntbc32.dll imports kernel32!createfilea
Match found: c:\winnt\system32\Axntcp32.dll imports kernel32!createfilea
Match found: c:\winnt\system32\cabinet.dll imports kernel32!createfilea
Match found: c:\winnt\system32\catsrvut.dll imports kernel32!createfilea

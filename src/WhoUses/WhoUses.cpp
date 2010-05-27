// Written by Zoltan Csizmadia, zoltan_csizmadia@yahoo.com
// For companies(Austin,TX): If you would like to get my resume, send an email.
//
// The source is free, but if you want to use it, mention my name and e-mail
// address
//
///////////////////////////////////////////////////////////////////////////////
//
// WhoUses.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "SystemInfo.h"

LPCTSTR GetFileNamePosition( LPCTSTR lpPath )
{
	LPCTSTR lpAct = lpPath + _tcslen( lpPath );

	while ( lpAct > lpPath && *lpAct != _T('\\') && *lpAct != _T('/') )
		lpAct--;

	if ( lpAct > lpPath )
		lpAct++;

	return lpAct;
}

void WhoUsesModule( LPCTSTR lpFileName, BOOL bFullPathCheck )
{
	string processName;
	BOOL bShow = FALSE;
	SystemProcessInformation::SYSTEM_PROCESS_INFORMATION* p;
	
	SystemProcessInformation pi;
	SystemModuleInformation mi;

	if ( !mi.Refresh() )
	{
		_tprintf( _T("SystemModulesInformation::Refresh() failed.\n") );
		return;
	}

	if ( mi.m_ModuleInfos.empty() )
	{
		_tprintf( _T("No module information\n") );
		return;
	}

	pi.Refresh();
			
	_tprintf( _T("%-6s  %-20s  %s\n"), _T("PID"), _T("Name"), _T("Path") );
	_tprintf( _T("------------------------------------------------------------------\n") );

	for (list<SystemModuleInformation::MODULE_INFO>::iterator iter2 = mi.m_ModuleInfos.begin(); iter2 != mi.m_ModuleInfos.end(); iter2++) {
		SystemModuleInformation::MODULE_INFO& m = *iter2;

		if ( bFullPathCheck )
			bShow =	_tcsicmp( m.FullPath, lpFileName ) == 0;
		else
			bShow =	_tcsicmp( GetFileNamePosition(m.FullPath), lpFileName ) == 0;
		
		if ( bShow )
		{
			p = pi.m_ProcessInfos[m.ProcessId];
			if (p) {
				SystemInfoUtils::Unicode2string( &p->usName, processName );
			}
			else
				processName = "";

				_tprintf( _T("0x%04X  %-20s  %s\n"), 
					m.ProcessId, 
					processName.c_str(), 
					m.FullPath );
		}
	}
}

void WhoUsesFile( LPCTSTR lpFileName, BOOL bFullPathCheck )
{
	BOOL bShow = FALSE;
	string name;
	string processName;
	string deviceFileName;
	string fsFilePath;
	SystemProcessInformation::SYSTEM_PROCESS_INFORMATION* p;
	SystemProcessInformation pi;
	SystemHandleInformation hi;

	if ( bFullPathCheck )
	{
		if ( !SystemInfoUtils::GetDeviceFileName( lpFileName, deviceFileName ) )
		{
			_tprintf( _T("GetDeviceFileName() failed.\n") );
			return;
		}
	}

	hi.SetFilter( _T("File"), TRUE );

	if ( hi.m_HandleInfos.empty() )
	{
		_tprintf( _T("No handle information\n") );
		return;
	}
	
	pi.Refresh();

	_tprintf( _T("%-6s  %-20s  %s\n"), _T("PID"), _T("Name"), _T("Path") );
	_tprintf( _T("------------------------------------------------------\n") );

	for (list<SystemHandleInformation::SYSTEM_HANDLE>::iterator iter = hi.m_HandleInfos.begin(); iter != hi.m_HandleInfos.end(); iter++) {
		SystemHandleInformation::SYSTEM_HANDLE& h = *iter;

		p = pi.m_ProcessInfos[h.ProcessID];
		if (p) {
			SystemInfoUtils::Unicode2string( &p->usName, processName );
		}
		else
			processName = "";

		//NT4 Stupid thing if it is the services.exe and I call GetName :((
		if ( INtDll::dwNTMajorVersion == 4 && _tcsicmp( processName.c_str(), _T("services.exe" ) ) == 0 )
			continue;
		
		hi.GetName( (HANDLE)h.HandleNumber, name, (DWORD)h.ProcessID );

		if ( bFullPathCheck )
			bShow =	_tcsicmp( name.c_str(), deviceFileName.c_str() ) == 0;
		else
			bShow =	_tcsicmp( GetFileNamePosition(name.c_str()), lpFileName ) == 0;

		if ( bShow )
		{
			if ( !bFullPathCheck )
			{
				fsFilePath = "";
				SystemInfoUtils::GetFsFileName( name.c_str(), fsFilePath );
			}
			
			_tprintf( _T("0x%04X  %-20s  %s\n"), 
				h.ProcessID, 
				processName.c_str(),
				!bFullPathCheck ? fsFilePath.c_str() : lpFileName );
		}
	}
}

void EnableDebugPriv( void )
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	// enable the SeDebugPrivilege
	if ( ! OpenProcessToken( GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
	{
		_tprintf( _T("OpenProcessToken() failed, Error = %d SeDebugPrivilege is not available.\n") , GetLastError() );
		return;
	}

	if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
		_tprintf( _T("LookupPrivilegeValue() failed, Error = %d SeDebugPrivilege is not available.\n"), GetLastError() );
		CloseHandle( hToken );
		return;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if ( ! AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
		_tprintf( _T("AdjustTokenPrivileges() failed, Error = %d SeDebugPrivilege is not available.\n"), GetLastError() );
		
	CloseHandle( hToken );
}

void ShowUsage()
{
	_tprintf( _T("WhoUses 1.0 for www.codeguru.com\n") );
	_tprintf( _T("Written by Zoltan Csizmadia, zoltan_csizmadia@yahoo.com \n") );
	_tprintf( _T("\n") );
	_tprintf( _T("Usage: WhoUses.exe [-M] fileName\n") );
	_tprintf( _T("\n") );
	_tprintf( _T("          -M            fileName is a module name ( EXE, DLL, ... )\n") );
	_tprintf( _T("          fileName      File name\n") );
	_tprintf( _T("\n") );
	_tprintf( _T("Examples:\n") );
	_tprintf( _T("\n") );
	_tprintf( _T("          WhoUses.exe -M kernel32.dll\n") );
	_tprintf( _T("          WhoUses.exe -M c:\\test\\test.dll\n") );
	_tprintf( _T("          WhoUses.exe yourTextFile.txt\n") );
	_tprintf( _T("          WhoUses.exe c:\\pagefile.sys\n") );
	_tprintf( _T("          WhoUses.exe Serial0\n") );
}

int _tmain(int argc, TCHAR* argv[])
{
	ULONG nonSwitchCount = 0;
	BOOL bModule = FALSE;
	LPCTSTR lpPath = NULL;
	BOOL bFullPathCheck = FALSE;
	BOOL bUsage = TRUE;
	TCHAR lpFilePath[_MAX_PATH];
	
	for ( int i = 1; i < argc; i++ )
	{
		if ( _tcsicmp( argv[i], _T("-h" ) ) == 0 || _tcsicmp( argv[i], _T("-?" ) ) == 0 )
		{
			bUsage = TRUE;
			break;
		}
		else
		if ( _tcsicmp( argv[i], _T("-m" ) ) == 0 || _tcsicmp( argv[i], _T("-m" ) ) == 0 )
		{
			bModule = TRUE;
		}
		else
		{
			if ( nonSwitchCount != 0 )
			{
				bUsage = TRUE;
				break;
			}

			lpPath = argv[i];

			bUsage = FALSE;

			nonSwitchCount++;
		}
	}

	if ( bUsage )
	{
		ShowUsage();
		return -1;
	}

	EnableDebugPriv();

	bFullPathCheck = GetFileNamePosition( lpPath ) != lpPath ;

	if ( bFullPathCheck )
	{
		if ( GetFullPathName( lpPath, _MAX_PATH, lpFilePath, NULL ) == 0 )
		{
			_tprintf( _T("GetFullPathName() failed. Error = %d\n"), GetLastError() );
			return -2;
		}
	}
	else
		_tcscpy( lpFilePath, GetFileNamePosition( lpPath ) );
	
	if ( bModule )
		WhoUsesModule( lpFilePath, bFullPathCheck );
	else
		WhoUsesFile( lpFilePath, bFullPathCheck );
	
	return 0;
}

#ifndef _WTSAPI32_H
#define _WTSAPI32_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
#if (_WIN32_WINNT >= 0x0501)
// session notification message
#define WM_WTSSESSION_CHANGE		0x02B1

// session notification message flags
#define WTS_CONSOLE_CONNECT			0x1
#define WTS_CONSOLE_DISCONNECT		0x2
#define WTS_REMOTE_CONNECT			0x3
#define WTS_REMOTE_DISCONNECT		0x4
#define WTS_SESSION_LOGON			0x5
#define WTS_SESSION_LOGOFF			0x6
#define WTS_SESSION_LOCK			0x7
#define WTS_SESSION_UNLOCK			0x8
#define WTS_SESSION_REMOTE_CONTROL	0x9

// WTSRegisterSessionNotifiction flags
#define NOTIFY_FOR_THIS_SESSION		0
#define NOTIFY_FOR_ALL_SESSIONS		1

BOOL WINAPI WTSRegisterSessionNotification(HWND hWnd, DWORD dwFlags);
BOOL WINAPI WTSUnRegisterSessionNotification(HWND hWnd);
#endif /* _WIN32_WINNT >= 0x0501 */

#if (_WIN32_WINNT >= 0x0500)

// WTSWaitSystemEvent local server handle
#define WTS_CURRENT_SERVER_HANDLE	0

// WTSWaitSystemEvent flags
#define WTS_EVENT_NONE				0x00000000
#define WTS_EVENT_CREATE			0x00000001
#define WTS_EVENT_DELETE			0x00000002
#define WTS_EVENT_RENAME			0x00000004
#define WTS_EVENT_CONNECT			0x00000008
#define WTS_EVENT_DISCONNECT		0x00000010
#define WTS_EVENT_LOGON				0x00000020
#define WTS_EVENT_LOGOFF			0x00000040
#define WTS_EVENT_STATECHANGE		0x00000080
#define WTS_EVENT_LICENSE			0x00000100
#define WTS_EVENT_ALL				0x7FFFFFFF
#define WTS_EVENT_FLUSH				0x80000000

BOOL WINAPI WTSWaitSystemEvent(HANDLE hServer, DWORD EventMask, DWORD* pEventFlags);
#endif /* _WIN32_WINNT >= 0x0500 */

#ifdef __cplusplus
}
#endif

#endif /* _WTSAPI32_H */

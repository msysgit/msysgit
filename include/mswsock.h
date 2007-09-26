/*
 * mswsock.h
 * MS-specific extensions to Windows Sockets 1.1, exported from mswsock.dll.
 * These functions are N/A on Windows9x.
 *
 * This file is part of a free library for the Win32 API.
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
         
#ifndef _MSWSOCK_H
#define _MSWSOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#define SO_CONNDATA	0x7000
#define SO_CONNOPT	0x7001
#define SO_DISCDATA	0x7002
#define SO_DISCOPT	0x7003
#define SO_CONNDATALEN	0x7004
#define SO_CONNOPTLEN	0x7005
#define SO_DISCDATALEN	0x7006
#define SO_DISCOPTLEN	0x7007
#define SO_OPENTYPE	0x7008
#define SO_SYNCHRONOUS_ALERT	0x10
#define SO_SYNCHRONOUS_NONALERT	0x20
#define SO_MAXDG	0x7009
#define SO_MAXPATHDG	0x700A
#define SO_UPDATE_ACCEPT_CONTEXT	0x700B
#define SO_CONNECT_TIME	0x700C
#define TCP_BSDURGENT	0x7000

#define TF_DISCONNECT   1
#define TF_REUSE_SOCKET 2
#define TF_WRITE_BEHIND 4
#define TF_USE_DEFAULT_WORKER   0
#define TF_USE_SYSTEM_THREAD    16
#define TF_USE_KERNEL_APC   32

typedef struct _TRANSMIT_FILE_BUFFERS {
	PVOID Head;
	DWORD HeadLength;
	PVOID Tail;
	DWORD TailLength;
} TRANSMIT_FILE_BUFFERS, *PTRANSMIT_FILE_BUFFERS, *LPTRANSMIT_FILE_BUFFERS;

int PASCAL WSARecvEx(SOCKET,char*,int,int*);
BOOL PASCAL TransmitFile(SOCKET,HANDLE,DWORD,DWORD,LPOVERLAPPED,LPTRANSMIT_FILE_BUFFERS,DWORD);
BOOL PASCAL AcceptEx(SOCKET,SOCKET,PVOID,DWORD,DWORD,DWORD,LPDWORD,LPOVERLAPPED);
VOID PASCAL GetAcceptExSockaddrs(PVOID,DWORD,DWORD,DWORD,struct sockaddr**, LPINT, struct sockaddr**, LPINT);

#ifdef __cplusplus
}
#endif
#endif  /*  _MSWSOCK_H */


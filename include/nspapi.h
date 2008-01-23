#ifndef _NSPAPI_H
#define _NSPAPI_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct _SOCKET_ADDRESS {
	LPSOCKADDR lpSockaddr;
	INT iSockaddrLength;
} SOCKET_ADDRESS,*PSOCKET_ADDRESS,*LPSOCKET_ADDRESS;
typedef struct _CSADDR_INFO {
	SOCKET_ADDRESS LocalAddr;
	SOCKET_ADDRESS RemoteAddr;
	INT iSocketType;
	INT iProtocol;
} CSADDR_INFO,*PCSADDR_INFO,*LPCSADDR_INFO;
#ifdef __cplusplus
}
#endif
#endif /* _NSPAPI_H */

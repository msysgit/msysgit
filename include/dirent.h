#ifdef __cplusplus
extern "C" {
#endif
#include <sys/dirent.h>

#if !defined(MAXNAMLEN) && !defined(_POSIX_SOURCE)
#define MAXNAMLEN 1024
#endif

#ifdef __cplusplus
}
#endif

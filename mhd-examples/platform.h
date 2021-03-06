#ifndef MHD_PLATFORM_H
#define MHD_PLATFORM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <stddef.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

/* different OSes have fd_set in
   a broad range of header files;
   we just include most of them (if they
   are available) */


#if defined(__VXWORKS__) || defined(__vxworks) || defined(OS_VXWORKS)
#include <stdarg.h>
#include <sys/mman.h>
#ifdef HAVE_SOCKLIB_H
#include <sockLib.h>
#endif /* HAVE_SOCKLIB_H */
#ifdef HAVE_INETLIB_H
#include <inetLib.h>
#endif /* HAVE_INETLIB_H */
#endif /* __VXWORKS__ */

#if HAVE_MEMORY_H
#include <memory.h>
#endif

#if HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif
#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <sys/time.h>
#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#if HAVE_SYS_MSG_H
#include <sys/msg.h>
#endif
#if HAVE_SYS_MMAN_H
#include <sys/mman.h>
#endif
#if HAVE_TIME_H
#include <time.h>
#endif
#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#if defined(_WIN32) && !defined(__CYGWIN__)
#ifndef WIN32_LEAN_AND_MEAN
/* Do not include unneeded parts of W32 headers. */
#define WIN32_LEAN_AND_MEAN 1
#endif /* !WIN32_LEAN_AND_MEAN */
#include <winsock2.h>
#include <ws2tcpip.h>
#endif /* _WIN32 && !__CYGWIN__ */

#if defined(__CYGWIN__) && !defined(_SYS_TYPES_FD_SET)
/* Do not define __USE_W32_SOCKETS under Cygwin! */
#error Cygwin with winsock fd_set is not supported
#endif

#if defined(_WIN32) && !defined(__CYGWIN__)
#define sleep(seconds) ((SleepEx((seconds)*1000, 1)==0)?0:(seconds))
#define usleep(useconds) ((SleepEx((useconds)/1000, 1)==0)?0:-1)
#endif

#if defined(_MSC_FULL_VER) && !defined (_SSIZE_T_DEFINED)
#define _SSIZE_T_DEFINED
typedef intptr_t ssize_t;
#endif /* !_SSIZE_T_DEFINED */

#ifndef _WIN32
typedef time_t _MHD_TIMEVAL_TV_SEC_TYPE;
#else  /* _WIN32 */
typedef long _MHD_TIMEVAL_TV_SEC_TYPE;
#endif /* _WIN32 */

#if !defined(IPPROTO_IPV6) && defined(_MSC_FULL_VER) && _WIN32_WINNT >= 0x0501
/* VC use IPPROTO_IPV6 as part of enum */
#define IPPROTO_IPV6 IPPROTO_IPV6
#endif

#endif

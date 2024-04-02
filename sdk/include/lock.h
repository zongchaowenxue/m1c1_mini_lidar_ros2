

#ifndef LOCK_H_
#define LOCK_H_


#ifdef HAVE_SYS_FILE_H
#   include <sys/file.h>
#endif /* HAVE_SYS_FILE_H */
#ifdef LFS  /* File Lock Server */
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#endif /* FLS */
#if defined(__linux__)
#	include <linux/types.h> /* fix for linux-2.3.4? kernels */
#	include <linux/serial.h>
#	include <linux/version.h>
#endif /* __linux__ */
#if defined(__sun__)
#	include <sys/filio.h>
#	include <sys/mkdev.h>
#endif /* __sun__ */
#if defined(__hpux__)
#	include <sys/modem.h>
#endif /* __hpux__ */
/* FIXME -- new file */
#if defined(__APPLE__)
#	include <CoreFoundation/CoreFoundation.h>
#	include <IOKit/IOKitLib.h>
#	include <IOKit/serial/IOSerialKeys.h>
#	include <IOKit/IOBSD.h>
#endif /* __APPLE__ */
#ifdef __unixware__
#	include  <sys/filio.h>
#endif /* __unixware__ */
#ifdef HAVE_PWD_H
#include	<pwd.h>
#endif /* HAVE_PWD_H */
#ifdef HAVE_GRP_H
#include 	<grp.h>
#endif /* HAVE_GRP_H */
#include <math.h>
#ifdef LIBLOCKDEV
#include	<lockdev.h>
#endif /* LIBLOCKDEV */



/*  Ports known on the OS */
#if defined(__linux__)
#	define DEVICEDIR "/dev/"
#	define LOCKDIR "/var/lock"
#	define LOCKFILEPREFIX "LCK.."
#	define FHS
#endif /* __linux__ */
#if defined(__QNX__)
#	define DEVICEDIR "/dev/"
#	define LOCKDIR ""
#	define LOCKFILEPREFIX ""
#endif /* qnx */
#if defined(__sgi__) || defined(sgi)
#	define DEVICEDIR "/dev/"
#	define LOCKDIR "/usr/spool/uucp"
#	define LOCKFILEPREFIX "LK."
#	define UUCP
#endif /* __sgi__ || sgi */
#if defined(__FreeBSD__)
#	define DEVICEDIR "/dev/"
#	define LOCKDIR "/var/spool/lock"
#	define LOCKFILEPREFIX "LK.."
#	define UUCP
#endif /* __FreeBSD__ */
#if defined(__APPLE__)
#	define DEVICEDIR "/dev/"
/*#	define LOCKDIR "/var/spool/uucp"*/
#	define LOCKDIR "/var/lock"
#	define LOCKFILEPREFIX "LK."
#	define UUCP
#endif /* __APPLE__ */
#if defined(__NetBSD__)
#	define DEVICEDIR "/dev/"
#	define LOCKDIR "/var/lock"
/*#	define LOCKDIR "/usr/spool/uucp"*/
#	define LOCKFILEPREFIX "LK."
#	define UUCP
#endif /* __NetBSD__ */
#if defined(__unixware__)
#	define DEVICEDIR "/dev/"
/* really this only fully works for OpenServer */
#	define LOCKDIR "/var/spool/uucp/"
#	define LOCKFILEPREFIX "LK."

#	define OLDUUCP
#endif
#if defined(__hpux__)
/* modif cath */
#	define DEVICEDIR "/dev/"
#	define LOCKDIR "/var/spool/uucp"
#	define LOCKFILEPREFIX "LCK."
#	define UUCP
#endif /* __hpux__ */
#if defined(__osf__)  /* Digital Unix */
#	define DEVICEDIR "/dev/"
#	define LOCKDIR ""
#	define LOCKFILEPREFIX "LK."
#	define UUCP
#endif /* __osf__ */
#if defined(__sun__) /* Solaris */
#	define DEVICEDIR "/dev/"
#	define LOCKDIR "/var/spool/locks"
#	define LOCKFILEPREFIX "LK."
/*
#	define UUCP
*/
#endif /* __sun__ */
#if defined(__BEOS__)
#	define DEVICEDIR "/dev/ports/"
#	define LOCKDIR ""
#	define LOCKFILEPREFIX ""
#	define UUCP
#endif /* __BEOS__ */
#if defined(WIN32)
#	define DEVICEDIR "//./"
#	define LOCKDIR ""
#	define LOCKFILEPREFIX ""
#endif /* WIN32 */

/* allow people to override the directories */
/* #define USER_LOCK_DIRECTORY "/home/tjarvi/1.5/build" */
#ifdef USER_LOCK_DIRECTORY
#	define LOCKDIR USER_LOCK_DIRECTORY
#endif /* USER_LOCK_DIRECTORY */

#ifdef DISABLE_LOCKFILES
#undef UUCP
#undef FHS
#undef OLDUUCP
#endif /* DISABLE_LOCKFILES */

/*  That should be all you need to look at in this file for porting */
#ifdef LFS  /*  Use a Lock File Server */
#	define LOCK lfs_lock
#	define UNLOCK lfs_unlock
#elif defined(UUCP)
#	define LOCK uucp_lock
#	define UNLOCK uucp_unlock
#elif defined(OLDUUCP)
/*
   We can handle the old style if needed here see __unixware__ above.
   defaulting to rxtx-1.4-8 behavior for now.
   see also __sco__ in SerialImp.c when changing this for a possible
   bug
   FIXME
*/
#	define LOCK fhs_lock
#	define UNLOCK fhs_unlock
#elif defined(FHS)
#ifdef LIBLOCKDEV
#	define LOCK lib_lock_dev_lock
#	define UNLOCK lib_lock_dev_unlock
#else
#	define LOCK fhs_lock
#	define UNLOCK fhs_unlock
#endif /* LIBLOCKDEV */
#else
#	define LOCK system_does_not_lock
#	define UNLOCK system_does_not_unlock
#endif /* UUCP */



//#ifndef __WIN32__
//#define UUCP_LOCK_DIR "/var/lock"

#ifdef __cplusplus
extern "C" {
#endif
//int uucp_lock( const char *file);
//int uucp_unlock(void);
int check_group_uucp();
int check_lock_pid(const char *file, int openpid);
int lock_device(const char *);
void unlock_device(const char *);
int is_device_locked(const char *);
int check_lock_status(const char *);
int lfs_unlock(const char *, int);
int lfs_lock(const char *, int);
int lib_lock_dev_unlock(const char *, int);
int lib_lock_dev_lock(const char *, int);
void fhs_unlock(const char *, int);
int fhs_lock(const char *, int);
void uucp_unlock(const char *, int);
int uucp_lock(const char *, int);

#ifdef __cplusplus
}
#endif

//#endif

#endif /* LOCK_H_ */

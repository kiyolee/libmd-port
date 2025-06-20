#ifndef _SKEIN_PORT_H_
#define _SKEIN_PORT_H_
/*******************************************************************
**
** Platform-specific definitions for Skein hash function.
**
** Source code author: Doug Whiting, 2008.
**
** This algorithm and source code is released to the public domain.
**
** Many thanks to Brian Gladman for his portable header files.
**
** To port Skein to an "unsupported" platform, change the definitions
** in this file appropriately.
** 
********************************************************************/

#ifdef __FreeBSD__
#include <sys/endian.h>
#endif
#include <sys/types.h>

#if defined(__linux__) || defined(__APPLE__)
#include <stdint.h>
#endif

#ifdef _WIN32
#include "../../supp/w32defs.h"
#endif
#ifdef __OS400__
#include "../../supp/isdefs.h"
#endif

#ifndef _SPL_SYS_TYPES_H_ /* Avoid redefining this typedef */
typedef unsigned int    uint_t;             /* native unsigned integer */
#endif
typedef uint8_t         u08b_t;             /*  8-bit unsigned integer */
typedef uint32_t        uint_32t;           /* 32-bit unsigned integer */
typedef uint64_t        u64b_t;             /* 64-bit unsigned integer */

#ifndef RotL_64
#define RotL_64(x,N)    (((x) << (N)) | ((x) >> (64-(N))))
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __FreeBSD__
__BEGIN_DECLS
#endif

/*
 * Skein is "natively" little-endian (unlike SHA-xxx), for optimal
 * performance on x86 CPUs.  The Skein code requires the following
 * definitions for dealing with endianness:
 *
 *    SKEIN_NEED_SWAP:  0 for little-endian, 1 for big-endian
 *    Skein_Put64_LSB_First
 *    Skein_Get64_LSB_First
 *    Skein_Swap64
 *
 * If SKEIN_NEED_SWAP is defined at compile time, it is used here
 * along with the portable versions of Put64/Get64/Swap64, which 
 * are slow in general.
 *
 * Otherwise, an "auto-detect" of endianness is attempted below.
 * If the default handling doesn't work well, the user may insert
 * platform-specific code instead (e.g., for big-endian CPUs).
 *
 */
#ifndef SKEIN_NEED_SWAP /* compile-time "override" for endianness? */

#if BYTE_ORDER == BIG_ENDIAN
    /* here for big-endian CPUs */
#define SKEIN_NEED_SWAP   (1)
#ifdef  SKEIN_PORT_CODE
void    Skein_Put64_LSB_First(u08b_t *dst,const u64b_t *src,size_t bCnt);
void    Skein_Get64_LSB_First(u64b_t *dst,const u08b_t *src,size_t wCnt);
#endif /* ifdef SKEIN_PORT_CODE */
#elif BYTE_ORDER == LITTLE_ENDIAN
    /* here for x86 and x86-64 CPUs (and other detected little-endian CPUs) */
#define SKEIN_NEED_SWAP   (0)
#define Skein_Put64_LSB_First(dst08,src64,bCnt) memcpy(dst08,src64,bCnt)
#define Skein_Get64_LSB_First(dst64,src08,wCnt) memcpy(dst64,src08,8*(wCnt))
#else
#error "Skein needs endianness setting!"
#endif

#endif /* ifndef SKEIN_NEED_SWAP */

/*
 ******************************************************************
 *      Provide any definitions still needed.
 ******************************************************************
 */
#ifndef Skein_Swap64  /* swap for big-endian, nop for little-endian */
#if     SKEIN_NEED_SWAP
#ifdef __OS400__
#define USE_LIBMD_BSWAP_SAFE
#endif
#include "supp/bswap.h"
#ifdef __OS400__
#define Skein_Swap64(w64)  _libmd_bswap64_safe(w64)
#else
#define Skein_Swap64(w64)  _libmd_bswap64(w64)
#endif
#else
#define Skein_Swap64(w64)  (w64)
#endif
#endif  /* ifndef Skein_Swap64 */


#ifndef Skein_Put64_LSB_First
#ifdef SKEIN_PORT_CODE
#ifdef __FreeBSD__
/*
 *  FreeBSD's le64enc() is alignment-agnostic and so cannot be
 *  optimized into CPU bswap even if that is available.
 *  libmd-port uses optimizable code instead.
 *  For CPUs having alignment problem, these may need to change
 *  to follow what FreeBSD does.
 */
#define le64enc _libmd_le64enc
#endif
static __inline void
le64enc(void *pp, uint64_t u)
{
    *((uint64_t *)pp) = Skein_Swap64(u);
}
#endif
void    Skein_Put64_LSB_First(u08b_t *dst,const u64b_t *src,size_t bCnt)
#ifdef  SKEIN_PORT_CODE /* instantiate the function code here? */
{
    size_t n;

    for (n = 0; n < bCnt / 8; n++)
        le64enc(dst + n * 8, src[n]);
}
#else
; /* output only the function prototype */
#endif
#endif   /* ifndef Skein_Put64_LSB_First */


#ifndef Skein_Get64_LSB_First
#ifdef SKEIN_PORT_CODE
#ifdef __FreeBSD__
/*
 *  FreeBSD's le64dec() is alignment-agnostic and so cannot be
 *  optimized into CPU bswap even if that is available.
 *  libmd-port uses optimizable code instead.
 *  For CPUs having alignment problem, these may need to change
 *  to follow what FreeBSD does.
 */
#define le64dec _libmd_le64dec
#endif
static __inline uint64_t
le64dec(const void *pp)
{
    return Skein_Swap64(*((const uint64_t *)pp));
}
#endif
void    Skein_Get64_LSB_First(u64b_t *dst,const u08b_t *src,size_t wCnt)
#ifdef  SKEIN_PORT_CODE /* instantiate the function code here? */
{
    size_t n;

    for (n = 0; n < wCnt; n++)
        dst[n] = le64dec(src + n * 8);
}
#else
; /* output only the function prototype */
#endif
#endif   /* ifndef Skein_Get64_LSB_First */

#ifdef LIBMD_WITH_PREFIX

/* Start FreeBSD libmd shims */

/* Ensure libmd symbols do not clash with libcrypto */

#ifndef SKEIN256_Init
#define SKEIN256_Init		_libmd_SKEIN256_Init
#define SKEIN512_Init		_libmd_SKEIN512_Init
#define SKEIN1024_Init		_libmd_SKEIN1024_Init
#endif
#ifndef SKEIN256_Update
#define SKEIN256_Update		_libmd_SKEIN256_Update
#define SKEIN512_Update		_libmd_SKEIN512_Update
#define SKEIN1024_Update	_libmd_SKEIN1024_Update
#endif
#ifndef SKEIN256_Final
#define SKEIN256_Final		_libmd_SKEIN256_Final
#define SKEIN512_Final		_libmd_SKEIN512_Final
#define SKEIN1024_Final		_libmd_SKEIN1024_Final
#endif
#ifndef SKEIN256_End
#define SKEIN256_End		_libmd_SKEIN256_End
#define SKEIN512_End		_libmd_SKEIN512_End
#define SKEIN1024_End		_libmd_SKEIN1024_End
#endif
#ifndef SKEIN256_Fd
#define SKEIN256_Fd		_libmd_SKEIN256_Fd
#define SKEIN512_Fd		_libmd_SKEIN512_Fd
#define SKEIN1024_Fd		_libmd_SKEIN1024_Fd
#endif
#ifndef SKEIN256_FdChunk
#define SKEIN256_FdChunk	_libmd_SKEIN256_FdChunk
#define SKEIN512_FdChunk	_libmd_SKEIN512_FdChunk
#define SKEIN1024_FdChunk	_libmd_SKEIN1024_FdChunk
#endif
#ifndef SKEIN256_File
#define SKEIN256_File		_libmd_SKEIN256_File
#define SKEIN512_File		_libmd_SKEIN512_File
#define SKEIN1024_File		_libmd_SKEIN1024_File
#endif
#ifndef SKEIN256_FileChunk
#define SKEIN256_FileChunk	_libmd_SKEIN256_FileChunk
#define SKEIN512_FileChunk	_libmd_SKEIN512_FileChunk
#define SKEIN1024_FileChunk	_libmd_SKEIN1024_FileChunk
#endif
#ifndef SKEIN256_Data
#define SKEIN256_Data		_libmd_SKEIN256_Data
#define SKEIN512_Data		_libmd_SKEIN512_Data
#define SKEIN1024_Data		_libmd_SKEIN1024_Data
#endif

#ifndef SKEIN256_ContextSize
#define SKEIN256_ContextSize	_libmd_SKEIN256_ContextSize
#define SKEIN512_ContextSize	_libmd_SKEIN512_ContextSize
#define SKEIN1024_ContextSize	_libmd_SKEIN1024_ContextSize
#endif
#ifndef SKEIN256_Create
#define SKEIN256_Create		_libmd_SKEIN256_Create
#define SKEIN512_Create		_libmd_SKEIN512_Create
#define SKEIN1024_Create	_libmd_SKEIN1024_Create
#endif
#ifndef SKEIN256_Destroy
#define SKEIN256_Destroy	_libmd_SKEIN256_Destroy
#define SKEIN512_Destroy	_libmd_SKEIN512_Destroy
#define SKEIN1024_Destroy	_libmd_SKEIN1024_Destroy
#endif
#ifndef SKEIN256_DigestSize
#define SKEIN256_DigestSize	_libmd_SKEIN256_DigestSize
#define SKEIN512_DigestSize	_libmd_SKEIN512_DigestSize
#define SKEIN1024_DigestSize	_libmd_SKEIN1024_DigestSize
#endif

#endif

#ifdef __FreeBSD__
__END_DECLS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif   /* ifndef _SKEIN_PORT_H_ */

/* MD5.H - header file for MD5C.C
 * $FreeBSD: src/sys/sys/md5.h,v 1.20.10.1.6.1 2010/12/21 17:09:25 kensmith Exp $
 */

/*-
 Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

#ifndef _SYS_MD5_H_
#define _SYS_MD5_H_

#ifdef unix
#include <sys/cdefs.h>
#endif

#ifdef _MSC_VER
#include "supp/w32defs.h"
#endif
#ifdef __OS400__
#include "supp/isdefs.h"
#endif

#define MD5_BLOCK_LENGTH		64
#define MD5_DIGEST_LENGTH		16
#define MD5_DIGEST_STRING_LENGTH	(MD5_DIGEST_LENGTH * 2 + 1)

#ifdef MD_INTERNAL

/* MD5 context. */
typedef struct MD5Context {
  u_int32_t state[4];	/* state (ABCD) */
  u_int32_t count[2];	/* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];	/* input buffer */
} MD5_CTX;

#if !defined(MD5_API) && defined(MD_DLL) && defined(_MSC_VER)
#define MD5_API __declspec(dllexport)
#endif

#else
typedef struct MD5Context MD5_CTX;
#endif

#ifndef MD5_API
#define MD5_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __FreeBSD__
__BEGIN_DECLS
#endif
MD5_API void   MD5Init (MD5_CTX *);
MD5_API void   MD5Update (MD5_CTX *, const void *, unsigned int);
MD5_API void   MD5Final (unsigned char [16], MD5_CTX *);
MD5_API char * MD5End(MD5_CTX *, char *);
MD5_API char * MD5File(const char *, char *);
MD5_API char * MD5FileChunk(const char *, char *, off_t, off_t);
MD5_API char * MD5Data(const void *, unsigned int, char *);
MD5_API int    MD5ContextSize(void);
MD5_API MD5_CTX *MD5Create(void);
MD5_API void   MD5Destroy(MD5_CTX *);
MD5_API int    MD5DigestSize(void);
#ifdef __FreeBSD__
__END_DECLS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _SYS_MD5_H_ */

/* MD4.H - header file for MD4C.C
 */

/*-
   SPDX-License-Identifier: RSA-MD

   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
   rights reserved.

   License to copy and use this software is granted provided that it
   is identified as the "RSA Data Security, Inc. MD4 Message-Digest
   Algorithm" in all material mentioning or referencing this software
   or this function.
   License is also granted to make and use derivative works provided
   that such works are identified as "derived from the RSA Data
   Security, Inc. MD4 Message-Digest Algorithm" in all material
   mentioning or referencing the derived work.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.
 */

#ifndef _MD4_H_
#define _MD4_H_

#ifdef _WIN32
#include "supp/w32defs.h"
#endif
#ifdef __OS400__
#include "supp/isdefs.h"
#endif

#define MD4_DIGEST_LENGTH		16
#define MD4_DIGEST_STRING_LENGTH	(MD4_DIGEST_LENGTH * 2 + 1)

#ifdef LIBMD_INTERNAL

#define MD4_BLOCK_LENGTH		64

/* MD4 context. */
typedef struct MD4Context {
  u_int32_t state[4];	/* state (ABCD) */
  u_int32_t count[2];	/* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[MD4_BLOCK_LENGTH];	/* input buffer */
} MD4_CTX;

#if !defined(MD4_API) && defined(LIBMD_DLL) && defined(_MSC_VER)
#define MD4_API __declspec(dllexport)
#endif

#else
typedef struct MD4Context MD4_CTX;
#endif

#ifndef MD4_API
#define MD4_API
#endif

#ifdef unix
#include <sys/cdefs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __FreeBSD__
__BEGIN_DECLS
#endif

#ifdef LIBMD_WITH_PREFIX

/* Ensure libmd symbols do not clash with libcrypto */

#ifndef MD4Init
#define MD4Init		_libmd_MD4Init
#endif
#ifndef MD4Update
#define MD4Update	_libmd_MD4Update
#endif
#ifndef MD4Pad
#define MD4Pad		_libmd_MD4Pad
#endif
#ifndef MD4Final
#define MD4Final	_libmd_MD4Final
#endif
#ifndef MD4End
#define MD4End		_libmd_MD4End
#endif
#ifndef MD4Fd
#define MD4Fd		_libmd_MD4Fd
#endif
#ifndef MD4FdChunk
#define MD4FdChunk	_libmd_MD4FdChunk
#endif
#ifndef MD4File
#define MD4File		_libmd_MD4File
#endif
#ifndef MD4FileChunk
#define MD4FileChunk	_libmd_MD4FileChunk
#endif
#ifndef MD4Data
#define MD4Data		_libmd_MD4Data
#endif

#ifndef MD4ContextSize
#define MD4ContextSize	_libmd_MD4ContextSize
#endif
#ifndef MD4Create
#define MD4Create	_libmd_MD4Create
#endif
#ifndef MD4Destroy
#define MD4Destroy	_libmd_MD4Destroy
#endif
#ifndef MD4DigestSize
#define MD4DigestSize	_libmd_MD4DigestSize
#endif

#endif

MD4_API void   MD4Init(MD4_CTX *);
MD4_API void   MD4Update(MD4_CTX *, const void *, size_t);
MD4_API void   MD4Final(unsigned char [MD4_DIGEST_LENGTH], MD4_CTX *);
MD4_API char * MD4End(MD4_CTX *, char *);
MD4_API char * MD4Fd(int, char *);
MD4_API char * MD4FdChunk(int, char *, off_t, off_t);
MD4_API char * MD4File(const char *, char *);
MD4_API char * MD4FileChunk(const char *, char *, off_t, off_t);
MD4_API char * MD4Data(const void *, size_t, char *);
MD4_API int    MD4ContextSize(void);
MD4_API MD4_CTX * MD4Create(void);
MD4_API void   MD4Destroy(MD4_CTX *);
MD4_API int    MD4DigestSize(void);
MD4_API void   MD4DigestFree(char *);

#ifdef __FreeBSD__
__END_DECLS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MD4_H_ */

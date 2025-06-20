/* crypto/ripemd/ripemd.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the routines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

/*
 */

#ifndef HEADER_RIPEMD_H
#define HEADER_RIPEMD_H

#ifdef unix
#include <sys/cdefs.h>
#endif
#include <sys/types.h>		/* XXX switch to machine/ansi.h and __ types */

#ifdef _WIN32
#include "supp/w32defs.h"
#endif
#ifdef __OS400__
#include "supp/isdefs.h"
#endif

#define RIPEMD160_DIGEST_LENGTH		20
#define RIPEMD160_DIGEST_STRING_LENGTH	(RIPEMD160_DIGEST_LENGTH * 2 + 1)

#ifdef LIBMD_INTERNAL

#define RIPEMD160_CBLOCK	64
#define RIPEMD160_LBLOCK	16
#define RIPEMD160_BLOCK		16
#define RIPEMD160_LAST_BLOCK	56
#define RIPEMD160_LENGTH_BLOCK	8

typedef struct RIPEMD160state_st {
	u_int32_t A,B,C,D,E;
	u_int32_t Nl,Nh;
	u_int32_t data[RIPEMD160_LBLOCK];
	int num;
} RIPEMD160_CTX;

#if !defined(RIPEMD160_API) && defined(LIBMD_DLL) && defined(_MSC_VER)
#define RIPEMD160_API __declspec(dllexport)
#endif

#else
typedef struct RIPEMD160state_st RIPEMD160_CTX;
#endif

#ifndef RIPEMD160_API
#define RIPEMD160_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __FreeBSD__
__BEGIN_DECLS
#endif

#ifdef LIBMD_WITH_PREFIX

/* Ensure libmd symbols do not clash with libcrypto */

#ifndef RIPEMD160_Init
#define RIPEMD160_Init		_libmd_RIPEMD160_Init
#endif
#ifndef RIPEMD160_Update
#define RIPEMD160_Update	_libmd_RIPEMD160_Update
#endif
#ifndef RIPEMD160_Final
#define RIPEMD160_Final		_libmd_RIPEMD160_Final
#endif
#ifndef RIPEMD160_End
#define RIPEMD160_End		_libmd_RIPEMD160_End
#endif
#ifndef RIPEMD160_Fd
#define RIPEMD160_Fd		_libmd_RIPEMD160_Fd
#endif
#ifndef RIPEMD160_FdChunk
#define RIPEMD160_FdChunk	_libmd_RIPEMD160_FdChunk
#endif
#ifndef RIPEMD160_File
#define RIPEMD160_File		_libmd_RIPEMD160_File
#endif
#ifndef RIPEMD160_FileChunk
#define RIPEMD160_FileChunk	_libmd_RIPEMD160_FileChunk
#endif
#ifndef RIPEMD160_Data
#define RIPEMD160_Data		_libmd_RIPEMD160_Data
#endif

#ifndef RIPEMD160_Transform
#define RIPEMD160_Transform	_libmd_RIPEMD160_Transform
#endif
#ifndef RMD160_version
#define RMD160_version		_libmd_RMD160_version
#endif
#ifndef ripemd160_block
#define ripemd160_block		_libmd_ripemd160_block
#endif

#ifndef RIPEMD160_ContextSize
#define RIPEMD160_ContextSize	_libmd_RIPEMD160_ContextSize
#endif
#ifndef RIPEMD160_Create
#define RIPEMD160_Create	_libmd_RIPEMD160_Create
#endif
#ifndef RIPEMD160_Destroy
#define RIPEMD160_Destroy	_libmd_RIPEMD160_Destroy
#endif
#ifndef RIPEMD160_DigestSize
#define RIPEMD160_DigestSize	_libmd_RIPEMD160_DigestSize
#endif

#endif

RIPEMD160_API void   RIPEMD160_Init(RIPEMD160_CTX *c);
RIPEMD160_API void   RIPEMD160_Update(RIPEMD160_CTX *c, const void *data,
                                      size_t len);
RIPEMD160_API void   RIPEMD160_Final(unsigned char *md, RIPEMD160_CTX *c);
RIPEMD160_API char  *RIPEMD160_End(RIPEMD160_CTX *, char *);
RIPEMD160_API char  *RIPEMD160_Fd(int, char *);
RIPEMD160_API char  *RIPEMD160_FdChunk(int, char *, off_t, off_t);
RIPEMD160_API char  *RIPEMD160_File(const char *, char *);
RIPEMD160_API char  *RIPEMD160_FileChunk(const char *, char *, off_t, off_t);
RIPEMD160_API char  *RIPEMD160_Data(const void *, size_t, char *);
RIPEMD160_API int    RIPEMD160_ContextSize(void);
RIPEMD160_API RIPEMD160_CTX *RIPEMD160_Create(void);
RIPEMD160_API void   RIPEMD160_Destroy(RIPEMD160_CTX *);
RIPEMD160_API int    RIPEMD160_DigestSize(void);
RIPEMD160_API void   RIPEMD160_DigestFree(char *);

#ifdef __FreeBSD__
__END_DECLS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

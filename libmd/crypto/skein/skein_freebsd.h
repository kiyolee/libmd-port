/*-
 * Copyright 2016 Allan Jude
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
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
 * $FreeBSD: release/12.1.0/sys/crypto/skein/skein_freebsd.h 307584 2016-10-18 23:20:49Z asomers $
 */

#ifndef _SKEIN_FREEBSD_H_
#define _SKEIN_FREEBSD_H_

#define SKEIN256_DIGEST_LENGTH		32
#define SKEIN256_DIGEST_STRING_LENGTH	(SKEIN256_DIGEST_LENGTH * 2 + 1)
#define SKEIN512_DIGEST_LENGTH		64
#define SKEIN512_DIGEST_STRING_LENGTH	(SKEIN512_DIGEST_LENGTH * 2 + 1)
#define SKEIN1024_DIGEST_LENGTH		128
#define SKEIN1024_DIGEST_STRING_LENGTH	(SKEIN1024_DIGEST_LENGTH * 2 + 1)

#ifdef LIBMD_INTERNAL

#define  SKEIN_256_BLOCK_BYTES ( 8*SKEIN_256_STATE_WORDS)
#define  SKEIN_512_BLOCK_BYTES ( 8*SKEIN_512_STATE_WORDS)
#define  SKEIN1024_BLOCK_BYTES ( 8*SKEIN1024_STATE_WORDS)

#define SKEIN256_BLOCK_LENGTH		SKEIN_256_BLOCK_BYTES
#define SKEIN512_BLOCK_LENGTH		SKEIN_512_BLOCK_BYTES
#define SKEIN1024_BLOCK_LENGTH		SKEIN1024_BLOCK_BYTES

#if !defined(SKEIN256_API) && defined(LIBMD_DLL) && defined(_MSC_VER)
#define SKEIN256_API __declspec(dllexport)
#endif
#if !defined(SKEIN512_API) && defined(LIBMD_DLL) && defined(_MSC_VER)
#define SKEIN512_API __declspec(dllexport)
#endif
#if !defined(SKEIN1024_API) && defined(LIBMD_DLL) && defined(_MSC_VER)
#define SKEIN1024_API __declspec(dllexport)
#endif

#else
struct Skein_256_Ctxt_t;
struct Skein_512_Ctxt_t;
struct Skein1024_Ctxt_t;
#endif

/* Make the context types look like the other hashes on FreeBSD */
typedef Skein_256_Ctxt_t    SKEIN256_CTX;
typedef Skein_512_Ctxt_t    SKEIN512_CTX;
typedef Skein1024_Ctxt_t    SKEIN1024_CTX;

#ifndef SKEIN256_API
#define SKEIN256_API
#endif
#ifndef SKEIN512_API
#define SKEIN512_API
#endif
#ifndef SKEIN1024_API
#define SKEIN1024_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Make the prototypes look like the other hashes */
SKEIN256_API  void SKEIN256_Init  (SKEIN256_CTX *ctx);
SKEIN512_API  void SKEIN512_Init  (SKEIN512_CTX *ctx);
SKEIN1024_API void SKEIN1024_Init  (SKEIN1024_CTX *ctx);

SKEIN256_API  void SKEIN256_Update(SKEIN256_CTX *ctx, const void *in, size_t len);
SKEIN512_API  void SKEIN512_Update(SKEIN512_CTX *ctx, const void *in, size_t len);
SKEIN1024_API void SKEIN1024_Update(SKEIN1024_CTX *ctx, const void *in, size_t len);

#if defined(__cplusplus) || defined(_MSC_VER)
#define __skein_min_size(n) n
#else
#define __skein_min_size(n) static n
#endif

SKEIN256_API  void SKEIN256_Final(unsigned char digest[__skein_min_size(SKEIN256_DIGEST_LENGTH)],
    SKEIN256_CTX *ctx);
SKEIN512_API  void SKEIN512_Final(unsigned char digest[__skein_min_size(SKEIN512_DIGEST_LENGTH)],
    SKEIN512_CTX *ctx);
SKEIN1024_API void SKEIN1024_Final(unsigned char digest[__skein_min_size(SKEIN1024_DIGEST_LENGTH)],
    SKEIN1024_CTX *ctx);

#undef __skein_min_size

#ifndef _KERNEL
SKEIN256_API  char  *SKEIN256_End(SKEIN256_CTX *, char *);
SKEIN512_API  char  *SKEIN512_End(SKEIN512_CTX *, char *);
SKEIN1024_API char  *SKEIN1024_End(SKEIN1024_CTX *, char *);
SKEIN256_API  char  *SKEIN256_Data(const void *, size_t, char *);
SKEIN512_API  char  *SKEIN512_Data(const void *, size_t, char *);
SKEIN1024_API char  *SKEIN1024_Data(const void *, size_t, char *);
SKEIN256_API  char  *SKEIN256_Fd(int, char *);
SKEIN512_API  char  *SKEIN512_Fd(int, char *);
SKEIN1024_API char  *SKEIN1024_Fd(int, char *);
SKEIN256_API  char  *SKEIN256_FdChunk(int, char *, off_t, off_t);
SKEIN512_API  char  *SKEIN512_FdChunk(int, char *, off_t, off_t);
SKEIN1024_API char  *SKEIN1024_FdChunk(int, char *, off_t, off_t);
SKEIN256_API  char  *SKEIN256_File(const char *, char *);
SKEIN512_API  char  *SKEIN512_File(const char *, char *);
SKEIN1024_API char  *SKEIN1024_File(const char *, char *);
SKEIN256_API  char  *SKEIN256_FileChunk(const char *, char *, off_t, off_t);
SKEIN512_API  char  *SKEIN512_FileChunk(const char *, char *, off_t, off_t);
SKEIN1024_API char  *SKEIN1024_FileChunk(const char *, char *, off_t, off_t);
#endif

SKEIN256_API  int    SKEIN256_ContextSize(void);
SKEIN256_API  SKEIN256_CTX *SKEIN256_Create(void);
SKEIN256_API  void   SKEIN256_Destroy(SKEIN256_CTX *);
SKEIN256_API  int    SKEIN256_DigestSize(void);
SKEIN256_API  void   SKEIN256_DigestFree(char *);

SKEIN512_API  int    SKEIN512_ContextSize(void);
SKEIN512_API  SKEIN512_CTX *SKEIN512_Create(void);
SKEIN512_API  void   SKEIN512_Destroy(SKEIN512_CTX *);
SKEIN512_API  int    SKEIN512_DigestSize(void);
SKEIN512_API  void   SKEIN512_DigestFree(char *);

SKEIN1024_API int    SKEIN1024_ContextSize(void);
SKEIN1024_API SKEIN1024_CTX *SKEIN1024_Create(void);
SKEIN1024_API void   SKEIN1024_Destroy(SKEIN1024_CTX *);
SKEIN1024_API int    SKEIN1024_DigestSize(void);
SKEIN1024_API void   SKEIN1024_DigestFree(char *);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif	/* ifndef _SKEIN_FREEBSD_H_ */

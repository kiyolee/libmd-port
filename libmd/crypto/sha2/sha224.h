/*-
 * Copyright 2005 Colin Percival
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
 */

#ifndef _SHA224_H_
#define _SHA224_H_

#ifndef _KERNEL
#include <sys/types.h>
#endif

#if defined(__linux__) || defined(__APPLE__)
#include <stdint.h>
#endif

#ifdef _WIN32
#include "../../supp/w32defs.h"
#endif
#ifdef __OS400__
#include "../../supp/isdefs.h"
#endif

#define SHA224_DIGEST_LENGTH		28
#define SHA224_DIGEST_STRING_LENGTH	(SHA224_DIGEST_LENGTH * 2 + 1)

#ifdef LIBMD_INTERNAL

#define SHA224_BLOCK_LENGTH		64

typedef struct SHA224Context {
	uint32_t state[8];
	uint64_t count;
	uint8_t buf[SHA224_BLOCK_LENGTH];
} SHA224_CTX;

#if !defined(SHA224_API) && defined(LIBMD_DLL) && defined(_MSC_VER)
#define SHA224_API __declspec(dllexport)
#endif

#else
typedef struct SHA224Context SHA224_CTX;
#endif

#ifndef SHA224_API
#define SHA224_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __FreeBSD__
__BEGIN_DECLS
#endif

#ifdef LIBMD_WITH_PREFIX

/* Ensure libmd symbols do not clash with libcrypto */

#ifndef SHA224_Init
#define SHA224_Init		_libmd_SHA224_Init
#endif
#ifndef SHA224_Update
#define SHA224_Update		_libmd_SHA224_Update
#endif
#ifndef SHA224_Final
#define SHA224_Final		_libmd_SHA224_Final
#endif
#ifndef SHA224_End
#define SHA224_End		_libmd_SHA224_End
#endif
#ifndef SHA224_Fd
#define SHA224_Fd		_libmd_SHA224_Fd
#endif
#ifndef SHA224_FdChunk
#define SHA224_FdChunk		_libmd_SHA224_FdChunk
#endif
#ifndef SHA224_File
#define SHA224_File		_libmd_SHA224_File
#endif
#ifndef SHA224_FileChunk
#define SHA224_FileChunk	_libmd_SHA224_FileChunk
#endif
#ifndef SHA224_Data
#define SHA224_Data		_libmd_SHA224_Data
#endif

#ifndef SHA224_version
#define SHA224_version		_libmd_SHA224_version
#endif

#ifndef SHA224_ContextSize
#define SHA224_ContextSize	_libmd_SHA224_ContextSize
#endif
#ifndef SHA224_Create
#define SHA224_Create		_libmd_SHA224_Create
#endif
#ifndef SHA224_Destroy
#define SHA224_Destroy		_libmd_SHA224_Destroy
#endif
#ifndef SHA224_DigestSize
#define SHA224_DigestSize	_libmd_SHA224_DigestSize
#endif

#endif

#if defined(__cplusplus) || defined(_MSC_VER)
#define __sha224_min_size(n) n
#else
#define __sha224_min_size(n) static n
#endif

SHA224_API void   SHA224_Init(SHA224_CTX *);
SHA224_API void   SHA224_Update(SHA224_CTX *, const void *, size_t);
SHA224_API void   SHA224_Final(unsigned char [__sha224_min_size(SHA224_DIGEST_LENGTH)],
    SHA224_CTX *);
#ifndef _KERNEL
SHA224_API char  *SHA224_End(SHA224_CTX *, char *);
SHA224_API char  *SHA224_Data(const void *, size_t, char *);
SHA224_API char  *SHA224_Fd(int, char *);
SHA224_API char  *SHA224_FdChunk(int, char *, off_t, off_t);
SHA224_API char  *SHA224_File(const char *, char *);
SHA224_API char  *SHA224_FileChunk(const char *, char *, off_t, off_t);
#endif
SHA224_API int    SHA224_ContextSize(void);
SHA224_API SHA224_CTX *SHA224_Create(void);
SHA224_API void   SHA224_Destroy(SHA224_CTX *);
SHA224_API int    SHA224_DigestSize(void);
SHA224_API void   SHA224_DigestFree(char *);

#undef __sha224_min_size

#ifdef __FreeBSD__
__END_DECLS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_SHA224_H_ */

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
 *
 * $FreeBSD: release/11.0.0/sys/crypto/sha2/sha384.h 300773 2016-05-26 19:29:29Z cem $
 */

#ifndef _SHA384_H_
#define _SHA384_H_

#ifndef _KERNEL
#include <sys/types.h>
#endif

#ifdef __linux__
#include <stdint.h>
#endif

#ifdef _MSC_VER
#include "supp/w32defs.h"
#endif
#ifdef __OS400__
#include "supp/isdefs.h"
#endif

#define SHA384_DIGEST_LENGTH		48
#define SHA384_DIGEST_STRING_LENGTH	(SHA384_DIGEST_LENGTH * 2 + 1)

#ifdef LIBMD_INTERNAL

#define SHA384_BLOCK_LENGTH		128

typedef struct SHA384Context {
	uint64_t state[8];
	uint64_t count[2];
	uint8_t buf[SHA384_BLOCK_LENGTH];
} SHA384_CTX;

#if !defined(SHA384_API) && defined(LIBMD_DLL) && defined(_MSC_VER)
#define SHA384_API __declspec(dllexport)
#endif

#else
typedef struct SHA384Context SHA384_CTX;
#endif

#ifndef SHA384_API
#define SHA384_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __FreeBSD__
__BEGIN_DECLS
#endif

#ifdef LIBMD_WITH_PREFIX

/* Ensure libmd symbols do not clash with libcrypto */

#ifndef SHA384_Init
#define SHA384_Init		_libmd_SHA384_Init
#endif
#ifndef SHA384_Update
#define SHA384_Update		_libmd_SHA384_Update
#endif
#ifndef SHA384_Final
#define SHA384_Final		_libmd_SHA384_Final
#endif
#ifndef SHA384_End
#define SHA384_End		_libmd_SHA384_End
#endif
#ifndef SHA384_File
#define SHA384_File		_libmd_SHA384_File
#endif
#ifndef SHA384_FileChunk
#define SHA384_FileChunk	_libmd_SHA384_FileChunk
#endif
#ifndef SHA384_Data
#define SHA384_Data		_libmd_SHA384_Data
#endif

#ifndef SHA384_version
#define SHA384_version		_libmd_SHA384_version
#endif

#endif

SHA384_API void    SHA384_Init(SHA384_CTX *);
SHA384_API void    SHA384_Update(SHA384_CTX *, const void *, size_t);
SHA384_API void    SHA384_Final(unsigned char [SHA384_DIGEST_LENGTH], SHA384_CTX *);
#ifndef _KERNEL
SHA384_API char   *SHA384_End(SHA384_CTX *, char *);
SHA384_API char   *SHA384_Data(const void *, unsigned int, char *);
SHA384_API char   *SHA384_File(const char *, char *);
SHA384_API char   *SHA384_FileChunk(const char *, char *, off_t, off_t);
#endif
SHA384_API int    SHA384_ContextSize(void);
SHA384_API SHA384_CTX *SHA384_Create(void);
SHA384_API void   SHA384_Destroy(SHA384_CTX *);
SHA384_API int    SHA384_DigestSize(void);

#ifdef __FreeBSD__
__END_DECLS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_SHA384_H_ */

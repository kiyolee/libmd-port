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
 * $FreeBSD: release/10.3.0/lib/libmd/sha512.h 220496 2011-04-09 13:56:29Z markm $
 */

#ifndef _SHA512_H_
#define _SHA512_H_

#include <sys/types.h>

#ifdef __linux__
#include <stdint.h>
#endif

#ifdef _MSC_VER
#include "supp/w32defs.h"
#endif
#ifdef __OS400__
#include "supp/isdefs.h"
#endif

#ifdef MD_INTERNAL

typedef struct SHA512Context {
	uint64_t state[8];
	uint64_t count[2];
	unsigned char buf[128];
} SHA512_CTX;

#if !defined(SHA512_API) && defined(MD_DLL) && defined(_MSC_VER)
#define SHA512_API __declspec(dllexport)
#endif

#else
typedef struct SHA512Context SHA512_CTX;
#endif

#ifndef SHA512_API
#define SHA512_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __FreeBSD__
__BEGIN_DECLS
#endif
SHA512_API void   SHA512_Init(SHA512_CTX *);
SHA512_API void   SHA512_Update(SHA512_CTX *, const void *, size_t);
SHA512_API void   SHA512_Final(unsigned char [64], SHA512_CTX *);
SHA512_API char  *SHA512_End(SHA512_CTX *, char *);
SHA512_API char  *SHA512_File(const char *, char *);
SHA512_API char  *SHA512_FileChunk(const char *, char *, off_t, off_t);
SHA512_API char  *SHA512_Data(const void *, unsigned int, char *);
SHA512_API int    SHA512_ContextSize(void);
SHA512_API SHA512_CTX *SHA512_Create(void);
SHA512_API void   SHA512_Destroy(SHA512_CTX *);
SHA512_API int    SHA512_DigestSize(void);
#ifdef __FreeBSD__
__END_DECLS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_SHA512_H_ */

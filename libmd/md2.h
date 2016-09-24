/* MD2.H - header file for MD2C.C
 * $FreeBSD: release/8.2.0/lib/libmd/md2.h 154479 2006-01-17 15:35:57Z phk $
 */

/* Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All
   rights reserved.

   License to copy and use this software is granted for
   non-commercial Internet Privacy-Enhanced Mail provided that it is
   identified as the "RSA Data Security, Inc. MD2 Message Digest
   Algorithm" in all material mentioning or referencing this software
   or this function.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.
 */

#ifndef _MD2_H_
#define _MD2_H_

#ifdef unix
#include <sys/cdefs.h>
#endif

#ifdef MD_INTERNAL

typedef struct MD2Context {
  unsigned char state[16];	/* state */
  unsigned char checksum[16];	/* checksum */
  unsigned int count;		/* number of bytes, modulo 16 */
  unsigned char buffer[16];	/* input buffer */
} MD2_CTX;

#if !defined(MD2_API) && defined(MD_DLL) && defined(_MSC_VER)
#define MD2_API __declspec(dllexport)
#endif

#else
typedef struct MD2Context MD2_CTX;
#endif

#ifndef MD2_API
#define MD2_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __FreeBSD__
__BEGIN_DECLS
#endif
MD2_API void   MD2Init(MD2_CTX *);
MD2_API void   MD2Update(MD2_CTX *, const void *, unsigned int);
#if 0
void   MD2Pad(MD2_CTX *);
#endif
MD2_API void   MD2Final(unsigned char [16], MD2_CTX *);
MD2_API char * MD2End(MD2_CTX *, char *);
MD2_API char * MD2File(const char *, char *);
MD2_API char * MD2FileChunk(const char *, char *, off_t, off_t);
MD2_API char * MD2Data(const void *, unsigned int, char *);
MD2_API int    MD2ContextSize(void);
MD2_API MD2_CTX *MD2Create(void);
MD2_API void   MD2Destroy(MD2_CTX *);
MD2_API int    MD2DigestSize(void);
#ifdef __FreeBSD__
__END_DECLS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MD2_H_ */

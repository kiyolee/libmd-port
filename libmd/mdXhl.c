/* mdXhl.c
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <phk@FreeBSD.org> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 */

#ifdef unix
#include <sys/cdefs.h>
#endif
#ifdef __FreeBSD__
__FBSDID("$FreeBSD: release/11.0.0/lib/libmd/mdXhl.c 294037 2016-01-14 21:08:23Z jtl $");
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef unix
#include <unistd.h>
#endif
#ifdef _MSC_VER
#include <io.h>
#if _MSC_VER >= 1500
#include <share.h>
#endif
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "mdX.h"

#ifndef O_BINARY
#ifdef _O_BINARY
#define O_BINARY _O_BINARY
#else
#define O_BINARY 0
#endif
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1400
#define open _open
#define close _close
#define lseek _lseek
#define read _read
#endif

MDX_API
char *
MDXEnd(MDX_CTX *ctx, char *buf)
{
	int i;
	unsigned char digest[LENGTH];
	static const char hex[]="0123456789abcdef";

	if (!buf)
		buf = malloc(2*LENGTH + 1);
	if (!buf)
		return 0;
	MDXFinal(digest, ctx);
	for (i = 0; i < LENGTH; i++) {
		buf[i+i] = hex[digest[i] >> 4];
		buf[i+i+1] = hex[digest[i] & 0x0f];
	}
	buf[i+i] = '\0';
	return buf;
}

MDX_API
char *
MDXFile(const char *filename, char *buf)
{
	return (MDXFileChunk(filename, buf, 0, 0));
}

MDX_API
char *
MDXFileChunk(const char *filename, char *buf, off_t ofs, off_t len)
{
	unsigned char buffer[16*1024];
	MDX_CTX ctx;
	struct stat stbuf;
	int fd, readrv, e;
	off_t remain;

	if (len < 0) {
		errno = EINVAL;
		return NULL;
	}

	MDXInit(&ctx);
#if defined(_MSC_VER) && _MSC_VER >= 1500
	if (_sopen_s(&fd, filename, O_RDONLY|O_BINARY, SH_DENYWR, 0) != 0) fd = -1;
#else
	fd = open(filename, O_RDONLY|O_BINARY);
#endif
	if (fd < 0)
		return NULL;
	if (ofs != 0) {
		errno = 0;
		if (lseek(fd, ofs, SEEK_SET) != ofs ||
		    (ofs == -1 && errno != 0)) {
			readrv = -1;
			goto error;
		}
	}
	remain = len;
	readrv = 0;
	while (len == 0 || remain > 0) {
		if (len == 0 || remain > sizeof(buffer))
			readrv = read(fd, buffer, sizeof(buffer));
		else
			readrv = read(fd, buffer, remain);
		if (readrv <= 0) 
			break;
		MDXUpdate(&ctx, buffer, readrv);
		remain -= readrv;
	} 
error:
	e = errno;
	close(fd);
	errno = e;
	if (readrv < 0)
		return NULL;
	return (MDXEnd(&ctx, buf));
}

MDX_API
char *
MDXData (const void *data, unsigned int len, char *buf)
{
	MDX_CTX ctx;

	MDXInit(&ctx);
	MDXUpdate(&ctx,data,len);
	return (MDXEnd(&ctx, buf));
}

MDX_API
int MDXContextSize(void)
{
	return sizeof(MDX_CTX);
}

MDX_API
MDX_CTX *MDXCreate(void)
{
	MDX_CTX *ctx = (MDX_CTX *)malloc(sizeof(MDX_CTX));
	if (ctx != NULL) MDXInit(ctx);
	return ctx;
}

MDX_API
void MDXDestroy(MDX_CTX *ctx)
{
	free(ctx);
}

MDX_API
int MDXDigestSize(void)
{
	return LENGTH;
}

#ifdef WEAK_REFS
/* When building libmd, provide weak references. Note: this is not
   activated in the context of compiling these sources for internal
   use in libcrypt.
 */
#undef MDXEnd
__weak_reference(_libmd_MDXEnd, MDXEnd);
#undef MDXFile
__weak_reference(_libmd_MDXFile, MDXFile);
#undef MDXFileChunk
__weak_reference(_libmd_MDXFileChunk, MDXFileChunk);
#undef MDXData
__weak_reference(_libmd_MDXData, MDXData);
#endif

/* vim: ts=4:sts=4:sw=4:noet
 */

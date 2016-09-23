/* mdXhl.c * ----------------------------------------------------------------------------
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
__FBSDID("$FreeBSD: src/lib/libmd/mdXhl.c,v 1.19.10.1.6.1 2010/12/21 17:09:25 kensmith Exp $");
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
	unsigned char buffer[BUFSIZ];
	MDX_CTX ctx;
	struct stat stbuf;
	int f, i, e;
	off_t n;

	MDXInit(&ctx);
#if defined(_MSC_VER) && _MSC_VER >= 1500
	if (_sopen_s(&f, filename, O_RDONLY|O_BINARY, SH_DENYWR, 0) != 0) f = -1;
#else
	f = open(filename, O_RDONLY|O_BINARY);
#endif
	if (f < 0)
		return 0;
	if (fstat(f, &stbuf) < 0)
		return 0;
	if (ofs > stbuf.st_size)
		ofs = stbuf.st_size;
	if ((len == 0) || (len > stbuf.st_size - ofs))
		len = stbuf.st_size - ofs;
	if (lseek(f, ofs, SEEK_SET) < 0)
		return 0;
	n = len;
	i = 0;
	while (n > 0) {
		if (n > sizeof(buffer))
			i = read(f, buffer, sizeof(buffer));
		else
			i = read(f, buffer, n);
		if (i < 0) 
			break;
		MDXUpdate(&ctx, buffer, i);
		n -= i;
	} 
	e = errno;
	close(f);
	errno = e;
	if (i < 0)
		return 0;
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

/* vim: ts=4:sts=4:sw=4:noet
 */

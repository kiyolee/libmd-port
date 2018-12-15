/* MDDRIVER.C - test driver for MD2, MD4 and MD5 */

/* Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All rights
 * reserved.
 * 
 * RSA Data Security, Inc. makes no representations concerning either the
 * merchantability of this software or the suitability of this software for
 * any particular purpose. It is provided "as is" without express or implied
 * warranty of any kind.
 * 
 * These notices must be retained in any copies of any part of this
 * documentation and/or software. */

#ifdef unix
#include <sys/cdefs.h>
#endif
#ifdef __FreeBSD__
__FBSDID("$FreeBSD: release/12.0.0/lib/libmd/mddriver.c 220496 2011-04-09 13:56:29Z markm $");
#endif

#include <sys/types.h>

#include <stdio.h>
#include <time.h>
#include <string.h>

#if defined(__OS400__)
#include "supp/e2a.h"
#endif

/* The following makes MD default to MD5 if it has not already been defined
 * with C compiler flags. */
#ifndef MD
#define MD 5
#endif

#if MD == 2
#include "md2.h"
#define MDData MD2Data
#endif
#if MD == 4
#include "md4.h"
#define MDData MD4Data
#endif
#if MD == 5
#include "md5.h"
#define MDData MD5Data
#endif

/* Digests a string and prints the result. */
static void 
MDString(const char *string)
{
	char buf[33];
#ifdef __OS400__
	char asc[1024];
	e2acpy(asc, string);
	MDData(asc, strlen(string), buf);
#else
	MDData(string, strlen(string), buf);
#endif
	printf("MD%d (\"%s\") = %s\n",
	       MD, string, buf);
}

/* Digests a reference suite of strings and prints the results. */
int
main(void)
{
	printf("MD%d test suite:\n", MD);

	MDString("");
	MDString("a");
	MDString("abc");
	MDString("message digest");
	MDString("abcdefghijklmnopqrstuvwxyz");
	MDString("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789");
	MDString("1234567890123456789012345678901234567890"
		"1234567890123456789012345678901234567890");

	return 0;
}

/* vim: ts=4:sts=4:sw=4:noet
 */

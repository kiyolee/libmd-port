/* RIPEMD160DRIVER.C - test driver for RIPEMD160 */

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
__FBSDID("$FreeBSD: release/12.2.0/lib/libmd/rmddriver.c 220496 2011-04-09 13:56:29Z markm $");
#endif

#include <sys/types.h>

#include <stdio.h>
#include <time.h>
#include <string.h>

#if defined(__OS400__)
#include "supp/e2a.h"
#endif

#include "ripemd.h"

/* Digests a string and prints the result. */
static void 
RIPEMD160String(const char *string)
{
	char buf[2*20 + 1];
#ifdef __OS400__
	char asc[1024];
	e2acpy(asc, string);
	RIPEMD160_Data(asc, strlen(string), buf);
#else
	RIPEMD160_Data(string, strlen(string), buf);
#endif
	printf("RIPEMD160 (\"%s\") = %s\n",
	       string, buf);
}

/* Digests a reference suite of strings and prints the results. */
int
main(void)
{
	printf("RIPEMD160 test suite:\n");

	RIPEMD160String("");
	RIPEMD160String("abc");
	RIPEMD160String("message digest");
	RIPEMD160String("abcdefghijklmnopqrstuvwxyz");
	RIPEMD160String("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789");
	RIPEMD160String("1234567890123456789012345678901234567890"
		"1234567890123456789012345678901234567890");

	return 0;
}

/* vim: ts=4:sts=4:sw=4:noet
 */

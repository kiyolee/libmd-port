/* SKEINDRIVER.C - test driver for SKEIN */

/*-
 * SPDX-License-Identifier: RSA-MD
 *
 * Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All rights
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
#include <sys/types.h>

#include <stdio.h>
#include <time.h>
#include <string.h>

#if defined(__OS400__)
#include "supp/e2a.h"
#endif

#include "skein.h"

/* The following makes SKEIN default to SKEIN512 if it has not already been
 * defined with C compiler flags. */
#ifndef SKEIN
#define SKEIN 512
#endif

#if SKEIN == 256
#undef SKEIN_Data
#define SKEIN_Data SKEIN256_Data
#elif SKEIN == 512
#undef SKEIN_Data
#define SKEIN_Data SKEIN512_Data
#elif SKEIN == 1024
#undef SKEIN_Data
#define SKEIN_Data SKEIN1024_Data
#endif

/* Digests a string and prints the result. */
static void
SKEINString(char *string)
{
	char buf[2*128 + 1];
#ifdef __OS400__
	char asc[1024];
	e2acpy(asc, string);
	SKEIN_Data(asc, strlen(string), buf);
#else
	SKEIN_Data(string, strlen(string), buf);
#endif
	printf("SKEIN%d (\"%s\") = %s\n",
	       SKEIN, string, buf);
}

/* Digests a reference suite of strings and prints the results. */
int
main(void)
{
	printf("SKEIN%d test suite:\n", SKEIN);

	SKEINString("");
	SKEINString("abc");
	SKEINString("message digest");
	SKEINString("abcdefghijklmnopqrstuvwxyz");
	SKEINString("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		  "abcdefghijklmnopqrstuvwxyz0123456789");
	SKEINString("1234567890123456789012345678901234567890"
		  "1234567890123456789012345678901234567890");

	return 0;
}

/* vim: ts=4:sts=4:sw=4:noet
 */

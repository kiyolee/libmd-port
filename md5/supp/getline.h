// SPDX-License-Identifier: MIT
// Copyright (c) Kelvin Lee.

#ifndef MD5_SUPP_GETLINE_H
#define MD5_SUPP_GETLINE_H

#include <malloc.h>
#include <stdio.h>

#ifdef _MSC_VER
#include "../../libmd/supp/w32defs.h"
#endif

// The following is an implementation of getdelim() and getline() that do
// not exactly follow POSIX standard but should suit the needs here.

static ssize_t getdelim(char** pbuf, size_t* pbufsz, int delimiter, FILE* fi)
{
	const size_t bufszmin = 128;
	const size_t bufszmax = 1024 * 1024;
	char* cp;
	char* ep;

	if (pbuf == NULL || pbufsz == NULL || fi == NULL)
		return -1;

	if (*pbuf == NULL) {
		if (*pbufsz <= bufszmin)
			*pbufsz = bufszmin;
		if ((*pbuf = malloc(*pbufsz)) == NULL)
			return -1;
	}

	cp = *pbuf;
	ep = cp + *pbufsz - 1; // Reserve one char for '\0'.
	for (;;) {
		char* bufnew;
		int c = EOF;
		while (!ferror(fi) && cp < ep && (c = fgetc(fi)) != EOF) {
			*cp++ = (char)c;
			if (c == delimiter) break;
		}
		if (ferror(fi))
			break;
		if (c == EOF || c == delimiter) {
			*cp = '\0';
			return cp - *pbuf;
		}
		if (*pbufsz >= bufszmax) // Do not expand any further.
			break;
		*pbufsz = (*pbufsz >= (bufszmax / 2)) ? bufszmax : (*pbufsz * 2);
		if ((bufnew = realloc(*pbuf, *pbufsz)) == NULL)
			break;
		cp = bufnew + (cp - *pbuf);
		ep = bufnew + *pbufsz - 1;
		*pbuf = bufnew;
	}

	return -1;
}

static ssize_t getline(char** pbuf, size_t* pbufsz, FILE* fi) {
	return getdelim(pbuf, pbufsz, '\n', fi);
}

#endif /* MD5_SUPP_GETLINE_H */

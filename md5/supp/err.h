// SPDX-License-Identifier: MIT
// Copyright (c) Kelvin Lee.

#ifndef MD5_SUPP_ERR_H
#define MD5_SUPP_ERR_H

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char *opt_progname;

static void
_vwarn(const char *fmt, va_list va)
{
	if (opt_progname && *opt_progname)
		fprintf(stderr, "%s: ", opt_progname);
	if (fmt != NULL) {
		vfprintf(stderr, fmt, va);
		fprintf(stderr, ": ");
	}
#if defined(_MSC_VER) && _MSC_VER >= 1500
	{
		char err[256];
		if (strerror_s(err, sizeof(err), errno) == 0)
			fprintf(stderr, "%s\n", err);
		else
			fprintf(stderr, "errno(%d)\n", errno);
	}
#else
	fprintf(stderr, "%s\n", strerror(errno));
#endif
}

static void
warn(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	_vwarn(fmt, va);
	va_end(va);
}

static void
err(int eval, const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	_vwarn(fmt, va);
	va_end(va);
	exit(eval);
}

static void
_vwarnx(const char *fmt, va_list va)
{
	if (opt_progname && *opt_progname)
		fprintf(stderr, "%s: ", opt_progname);
	if (fmt != NULL)
		vfprintf(stderr, fmt, va);
	putc('\n', stderr);
}

static void
warnx(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	_vwarnx(fmt, va);
	va_end(va);
}

static void
errx(int eval, const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	_vwarnx(fmt, va);
	va_end(va);
	exit(eval);
}

#endif /* MD5_SUPP_ERR_H */

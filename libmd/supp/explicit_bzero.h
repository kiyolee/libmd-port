// SPDX-License-Identifier: MIT
// Copyright (c) Kelvin Lee.

#ifndef LIBMD_SUPP_EXPLICIT_BZERO_H
#define LIBMD_SUPP_EXPLICIT_BZERO_H

#ifdef __linux__
#include <features.h>
#endif

#undef __LIBMD_HAVE_EXPLICIT_BZERO
#if defined(__FreeBSD__) || defined(__CYGWIN__)
#define __LIBMD_HAVE_EXPLICIT_BZERO
#elif defined(__GLIBC__)
#if __GLIBC_PREREQ(2, 25)
#define __LIBMD_HAVE_EXPLICIT_BZERO
#endif
#endif

#ifndef __LIBMD_HAVE_EXPLICIT_BZERO

#include <stdlib.h>

#if defined(_MSC_VER)
__forceinline
#else
static
#endif
void _libmd_explicit_bzero(void *ptr, size_t cnt)
{
    volatile char *cp = (volatile char *)ptr;
    while (cnt > 0) { *cp++ = '\0'; --cnt; }
}

#define explicit_bzero _libmd_explicit_bzero

#endif

#endif /* LIBMD_SUPP_EXPLICIT_BZERO_H */

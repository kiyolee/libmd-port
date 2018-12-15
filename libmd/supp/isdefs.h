#ifndef LIBMD_SUPP_ISDEFS_H
#define LIBMD_SUPP_ISDEFS_H

#include <stdint.h>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

#define BYTE_ORDER      4321
#define LITTLE_ENDIAN   1234
#define BIG_ENDIAN      4321

static void explicit_bzero(void *ptr, size_t cnt)
{
    volatile char *cp = (volatile char *)ptr;
    while (cnt > 0) { *cp++ = '\0'; --cnt; }
}

#endif /* LIBMD_SUPP_ISDEFS_H */

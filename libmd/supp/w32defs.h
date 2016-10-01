#ifndef W32DEFS_H
#define W32DEFS_H

#if defined(_MSC_VER) && _MSC_VER >= 1600
#include <stdint.h>
#else
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
#endif

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

#define BYTE_ORDER      1234
#define LITTLE_ENDIAN   1234
#define BIG_ENDIAN      4321

#endif

#ifndef LIBMD_SUPP_BSWAP_H
#define LIBMD_SUPP_BSWAP_H

#undef _libmd_bswap32
#undef _libmd_bswap64
#if defined(_MSC_VER)
#define _libmd_bswap32 _byteswap_ulong
#define _libmd_bswap64 _byteswap_uint64
#elif (defined(__GNUC__) && (__GNUC__ >= 5 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4))) || defined(__clang__)
#define _libmd_bswap32 __builtin_bswap32
#define _libmd_bswap64 __builtin_bswap64
#else
static __inline uint32_t _libmd_bswap32(register uint32_t u)
{
	u = ((u >>  8) & 0x00ff00ff) | ((u <<  8) & 0xff00ff00);
	u = ((u >> 16) & 0x0000ffff) | ((u << 16) & 0xffff0000);
	return u;
}
static __inline uint64_t _libmd_bswap64(register uint64_t u)
{
#if defined(_M_IX86) || defined(i386) // or any 32-bit CPU
	return ((uint64_t)_libmd_bswap32((uint32_t)u) << 32) | _libmd_bswap32((uint32_t)(u >> 32));
#else
	u = ((u >>  8) & 0x00ff00ff00ff00ff) | ((u <<  8) & 0xff00ff00ff00ff00);
	u = ((u >> 16) & 0x0000ffff0000ffff) | ((u << 16) & 0xffff0000ffff0000);
	u = ((u >> 32) & 0x00000000ffffffff) | ((u << 32) & 0xffffffff00000000);
	return u;
#endif
}
#endif

#endif /* LIBMD_SUPP_BSWAP_H */

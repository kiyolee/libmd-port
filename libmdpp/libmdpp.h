#ifndef _INCL_LIBMDPP_H
#define _INCL_LIBMDPP_H

#include <cstdint>
#include <vector>

#include "libmd/md4.h"
#include "libmd/md5.h"
#include "libmd/ripemd.h"
#include "libmd/sha.h"
#include "libmd/crypto/sha2/sha224.h"
#include "libmd/crypto/sha2/sha256.h"
#include "libmd/crypto/sha2/sha384.h"
#include "libmd/crypto/sha2/sha512.h"
#include "libmd/crypto/sha2/sha512t.h"
#include "libmd/crypto/skein/skein_freebsd.h"

namespace libmd {

enum class digest_type
{
    MD4,
    MD5,
    RIPEMD160,
    SHA,
    SHA1,
    SHA224,
    SHA256,
    SHA384,
    SHA512,
    SHA512_224,
    SHA512_256,
    SKEIN256,
    SKEIN512,
    SKEIN1024,
};

template<digest_type _DT>
struct digest_traits;

#define _DEF_DIGEST_TYPE(dt, fp) \
template<> \
struct digest_traits<libmd::digest_type::dt> { \
    typedef dt##_CTX context_type; \
    static constexpr const char* Name() { return #dt; } \
    static constexpr size_t DigestSize() { return dt##_DIGEST_LENGTH; } \
    static size_t ContextSize() { return fp##ContextSize(); } \
    static void Init(context_type* ctx) { fp##Init(ctx); } \
    static context_type* Create() { return fp##Create(); } \
    static void Destroy(context_type* ctx) { fp##Destroy(ctx); } \
    static void Update(context_type* ctx, const void* data, size_t datalen) { fp##Update(ctx, data, datalen); } \
    static void Final(unsigned char* buf, context_type* ctx) { return fp##Final(buf, ctx); } \
};

_DEF_DIGEST_TYPE(MD4, MD4)
_DEF_DIGEST_TYPE(MD5, MD5)
_DEF_DIGEST_TYPE(RIPEMD160, RIPEMD160_)
_DEF_DIGEST_TYPE(SHA, SHA_)
_DEF_DIGEST_TYPE(SHA1, SHA1_)
_DEF_DIGEST_TYPE(SHA224, SHA224_)
_DEF_DIGEST_TYPE(SHA256, SHA256_)
_DEF_DIGEST_TYPE(SHA384, SHA384_)
_DEF_DIGEST_TYPE(SHA512, SHA512_)
_DEF_DIGEST_TYPE(SHA512_224, SHA512_224_)
_DEF_DIGEST_TYPE(SHA512_256, SHA512_256_)
_DEF_DIGEST_TYPE(SKEIN256, SKEIN256_)
_DEF_DIGEST_TYPE(SKEIN512, SKEIN512_)
_DEF_DIGEST_TYPE(SKEIN1024, SKEIN1024_)

template<digest_type _DT>
class digest
{
private:
    typedef digest_traits<_DT> _traits_type;
    typedef typename _traits_type::context_type _context_type;

public:
    digest(): ctx_(_traits_type::Create()) {}
    ~digest() { if (ctx_) _traits_type::Destroy(ctx_); }
    static constexpr const char* name() { return _traits_type::Name(); }
    static constexpr size_t size() { return _traits_type::DigestSize(); }
    bool operator!() const { return !ctx_; }
    void reset() { if (ctx_) _traits_type::Init(ctx_); }
    void update(const void* data, size_t datalen) { if (ctx_) _traits_type::Update(ctx_, data, datalen); }
    std::vector<uint8_t> final()
    {
        if (!ctx_) return {};
        decltype(this->final()) dg(size());
        _traits_type::Final(dg.data(), ctx_);
        return dg;
    }

private:
    _context_type* ctx_;
};

} // namespace libmd

#endif // _INCL_LIBMDPP_H

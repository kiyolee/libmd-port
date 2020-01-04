#ifndef _INCL_LIBMDPP_H
#define _INCL_LIBMDPP_H

#ifdef __CYGWIN__
#include <sys/types.h>
#endif

#include <vector>
#include <utility>
#include <cstdint>
#include <cstring>

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
struct digest_traits<digest_type::dt> { \
    typedef dt##_CTX context_type; \
    static constexpr digest_type type{ digest_type::dt }; \
    static constexpr const char* name{ #dt }; \
    static constexpr size_t digest_size{ dt##_DIGEST_LENGTH }; \
    static size_t context_size() { return fp##ContextSize(); } \
    static void init(context_type* ctx) { fp##Init(ctx); } \
    static context_type* create() { return fp##Create(); } \
    static void destroy(context_type* ctx) { fp##Destroy(ctx); } \
    static void update(context_type* ctx, const void* data, size_t datalen) { fp##Update(ctx, data, datalen); } \
    static void final(unsigned char* buf, context_type* ctx) { return fp##Final(buf, ctx); } \
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

class digest_base
{
public:
    virtual bool operator!() const = 0;

    virtual digest_type type() const = 0;
    virtual const char* name() const = 0;
    virtual size_t size() const = 0;

    virtual void reset() = 0;
    virtual void update(const void* data, size_t datalen) = 0;
    virtual std::vector<uint8_t> final() = 0;
};

template<digest_type _DT>
class digest : public digest_base
{
private:
    typedef digest_traits<_DT> _traits_type;
    typedef typename _traits_type::context_type _context_type;

public:
    digest() : ctx_(_traits_type::create()) {}
    digest(digest const& _rhs) : ctx_(_rhs.ctx_ ? _traits_type::create() : nullptr) {
        if (ctx_) std::memcpy(ctx_, _rhs.ctx_, _traits_type::context_size());
    }
    digest(digest&& _rhs) : ctx_(std::move(_rhs.ctx_)) {
        _rhs.ctx_ = nullptr;
    }
    virtual ~digest() {
        if (ctx_) { _traits_type::destroy(ctx_); ctx_ = nullptr; }
    }

    digest& operator=(digest const& _rhs) {
        if (this == &_rhs) return *this;
        if (ctx_) {
            if (_rhs.ctx_) std::memcpy(ctx_, _rhs.ctx_, _traits_type::context_size());
            else { _traits_type::destroy(ctx_); ctx_ = nullptr; }
        } else {
            ctx_ = _rhs.ctx_ ? _traits_type::create() : nullptr;
            if (ctx_) std::memcpy(ctx_, _rhs.ctx_, _traits_type::context_size());
        }
        return *this;
    }
    digest& operator=(digest&& _rhs) {
        if (this == &_rhs) return *this;
        if (ctx_) _traits_type::destroy(ctx_);
        ctx_ = std::move(_rhs.ctx_);
        _rhs.ctx_ = nullptr;
        return *this;
    }

    virtual bool operator!() const final { return !ctx_; }

    virtual digest_type type() const final { return _traits_type::type; }
    virtual const char* name() const final { return _traits_type::name; }
    virtual size_t size() const final { return _traits_type::digest_size; }

    void reset() final {
        if (ctx_) _traits_type::init(ctx_);
    }
    void update(const void* data, size_t datalen) final {
        if (ctx_) _traits_type::update(ctx_, data, datalen);
    }
    std::vector<uint8_t> final() final {
        if (!ctx_) return {};
        decltype(this->final()) dg(size());
        _traits_type::final(dg.data(), ctx_);
        return dg;
    }

private:
    _context_type* ctx_;
};

} // namespace libmd

#endif // _INCL_LIBMDPP_H

// SPDX-License-Identifier: MIT
// Copyright (c) Kelvin Lee.

#if (!defined(_MSVC_LANG) && __cplusplus < 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG < 201402L)
#error Requires C++14.
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>

#include "libmdpp/libmdpp.h"

using namespace std;

namespace {

template<typename _T>
struct _hex_printer {
    _hex_printer(_T const& data) : data_(data) {}
    _T const& data_;
};

template<typename _T, enable_if_t<sizeof(typename _T::value_type) == 1, int> = 0>
ostream& operator<<(ostream& ostm, _hex_printer<_T> const& hp)
{
    for_each(hp.data_.cbegin(), hp.data_.cend(), [&](auto const& b){
        ostm << setw(2) << setfill('0') << hex << (unsigned int)(b);
    });
    return ostm;
}

template<libmd::digest_type ..._DT>
vector<pair<libmd::digest_type, libmd::digest_value> > _get_sums(const char* fn)
{
    ifstream in(fn, ios_base::in|ios_base::binary);
    if (!in) {
        cerr << ">>> failed to open \"" << fn << "\"." << endl;
        return {};
    }

    vector<unique_ptr<libmd::digest_base> > dgv;
    using _expander = int[];
    (void)_expander{ (void(dgv.push_back(make_unique<libmd::digest<_DT> >())), 0) ... };
   
    if (any_of(dgv.cbegin(), dgv.cend(), [](auto const& pdg) { return !(*pdg); })) {
        for (auto const& pdg : dgv) {
            if (!(*pdg)) cerr << ">>> failed to create " << pdg->name() << " context for \"" << fn << "\"." << endl;
        }
        return {};
    }

    auto pbuf = make_unique<array<char, 16*1024> >();
    while (!!in)
    {
        in.read(pbuf->data(), pbuf->size());
        if (!in && !in.eof()) {
            cerr << ">>> failed to read \"" << fn << "\"." << endl;
            return {};
        }
        for_each(dgv.begin(), dgv.end(), [&](auto const& pdg) {
            pdg->update(pbuf->data(), size_t(in.gcount()));
        });
    }

    decltype(_get_sums(fn)) sums;
    for_each(dgv.begin(), dgv.end(), [&](auto const& pdg) {
        sums.push_back(make_pair(pdg->type(), pdg->final()));
    });
    return sums;
}

template<libmd::digest_type _DT>
libmd::digest_value _get_sum(const char* fn)
{
    auto sums = _get_sums<_DT>(fn);
    return !sums.empty() ? sums[0].second : libmd::digest_value{};
}

} // namespace

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        const char* const fn = argv[i];
        //_get_sum<libmd::digest_type::MD5>(fn);
        //_get_sum<libmd::digest_type::SHA1>(fn);
        //_get_sum<libmd::digest_type::SHA256>(fn);
        auto sums = _get_sums<libmd::digest_type::MD5,
                              libmd::digest_type::RIPEMD160,
                              libmd::digest_type::SHA1,
                              libmd::digest_type::SHA256,
                              libmd::digest_type::SKEIN512>(fn);
        for_each(sums.cbegin(), sums.cend(), [&](auto const& sum) {
            cout << libmd::digest_name_of(sum.first) << " (" << fn << ") = " << _hex_printer<libmd::digest_value>(sum.second) << endl;
        });
    }
    return 0;
}

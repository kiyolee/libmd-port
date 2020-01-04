#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <array>
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

template<libmd::digest_type _DT>
void _get_sum(const char* fn)
{
    typedef libmd::digest<_DT> _digest;

    ifstream in(fn, ios_base::in|ios_base::binary);
    if (!in) {
        cerr << ">>> failed to open \"" << fn << "\"." << endl;
        return;
    }

    _digest dg;
    if (!dg) {
        cerr << ">>> failed to create " << dg.name() << " context for \"" << fn << "\"." << endl;
        return;
    }

    auto pbuf = make_unique<array<char, 16*1024> >();
    while (!!in)
    {
        in.read(pbuf->data(), pbuf->size());
        if (!in && !in.eof()) {
            cerr << ">>> failed to read \"" << fn << "\"." << endl;
            return;
        }
        dg.update(pbuf->data(), in.gcount());
    }

    auto sum = dg.final();

    cout << _hex_printer<decltype(sum)>(sum) << "  " << fn << endl;
}

} // namespace

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        //_get_sum<libmd::digest_type::MD5>(argv[i]);
        //_get_sum<libmd::digest_type::SHA256>(argv[i]);
        _get_sum<libmd::digest_type::SHA1>(argv[i]);
    }
    return 0;
}

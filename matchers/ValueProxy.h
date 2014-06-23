#ifndef LIBTEST_VALUEPROXY_H
#define LIBTEST_VALUEPROXY_H

#include "MatchProxy.h"

namespace test
{
    template<typename T>
    struct ValueProxy
    {
        MatchProxy<T> to;
        MatchProxy<T> to_not;

        explicit ValueProxy(const char* filename, int lineNumber, const T& value) : to(*this), to_not(*this, true), _value(value), _filename(filename), _lineNumber(lineNumber) {}

    private:
        friend struct MatchProxy<T>;

        const T&    _value;
        std::string _filename;
        int         _lineNumber;
    };
}

#endif	// LIBTEST_VALUEPROXY_H

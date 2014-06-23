#ifndef LIBTEST_MUST_H
#define LIBTEST_MUST_H

#include "ValueProxy.h"

namespace test
{
    struct Marker
    {
	const char* filename;
	int lineNumber;
    };

    template<typename T>
    const ValueProxy<T> operator,(const T& value, const Marker& marker)
    {
	return ValueProxy<T>(marker.filename, marker.lineNumber, value);
    }

    template<typename T>
    const MatchProxy<T> operator,(const ValueProxy<T>& value, bool negate)
    {
	return negate ? value.to_not : value.to;
    }

    template<typename T, typename MatcherType>
    void operator,(const MatchProxy<T>& matchProxy, const MatcherType& matcher)
    {
	matchProxy(matcher);
    }
}

#define must	    ,(test::Marker){__FILE__, __LINE__},false,
#define must_not    ,(test::Marker){__FILE__, __LINE__},true,

#endif	//LIBTEST_MUST_H

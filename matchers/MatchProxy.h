#ifndef LIBTEST_MATCHPROXY_H
#define LIBTEST_MATCHPROXY_H

#include <include/exception.h>

namespace test
{
    template<typename T> struct ValueProxy;

    template<typename T>
    struct MatchProxy
    {
        explicit MatchProxy(const ValueProxy<T>& value, bool negate_ = false) : _value(value), _negate(negate_) {}

        template<typename U>
        MatchProxy(const MatchProxy<U>&) = delete;

        template<typename U>
        MatchProxy& operator=(const MatchProxy<U>&) = delete;

        template<typename MatcherType>
	void operator()(const MatcherType& matcher) const
        {
	    if( matcher.matches(_value._value) == _negate )
		throw exception(_value._filename, _value._lineNumber, matcher.message(_value._value, _negate));
        }

        MatchProxy<T> negate() const
        {
            return MatchProxy<T>(_value, !_negate);
        }

    private:
        const ValueProxy<T>& _value;
        bool _negate;
    };
}

#endif	// LIBTEST_MATCHPROXY_H

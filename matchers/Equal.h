#ifndef LIBTEST_EQUAL_H
#define LIBTEST_EQUAL_H

#include <cstring>

#include "Matcher.h"

namespace test
{
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::unique_ptr<T>& obj)
    {
	return os << *obj;
    }

    template<typename T>
    struct Equal : public Matcher
    {
        explicit Equal(const T& expectedValue) : Matcher(), _expectedValue(expectedValue) {}

        template<typename U>
        bool matches(const U& actualValue) const
	{
	    return actualValue == _expectedValue;
	}

	bool matches(char* actualValue) const
	{
	    return strcmp(actualValue, &*_expectedValue) == 0;
	}

	bool matches(const char* actualValue) const
	{
	    return strcmp(actualValue, &*_expectedValue) == 0;
	}

	template<typename U>
	bool matches(const std::unique_ptr<U>& pointer) const
	{
	    return matches(pointer.get());
	}

    protected:
        virtual void message_suffix(std::ostream& os) const
	{
	    os << "equal <" << _expectedValue << ">";
	}

    private:
        const T& _expectedValue;
    };

    template<typename T>
    Equal<T> equal(const T& expectedValue)
    {
        return Equal<T>(expectedValue);
    }

#pragma mark Equality operators
    template<typename T, typename U>
    bool operator==(const ValueProxy<T>& actualValue, const U& expectedValue)
    {
        return actualValue.to == expectedValue;
    }

    template<typename T, typename U>
    bool operator==(const MatchProxy<T>& matchProxy, const U& expectedValue)
    {
        matchProxy(equal(expectedValue));
        return true;
    }

    template<typename T, typename U>
    bool operator!=(const ValueProxy<T>& actualValue, const U& expectedValue)
    {
        return actualValue.to != expectedValue;
    }

    template<typename T, typename U>
    bool operator!=(const MatchProxy<T>& matchProxy, const U& expectedValue)
    {
        matchProxy.negate()(equal(expectedValue));
        return true;
    }
}

#endif	// LIBTEST_EQUAL_H

#ifndef LIBTEST_BELESSTHAN_H
#define LIBTEST_BELESSTHAN_H

#include "Matcher.h"

namespace test
{
    template<typename T>
    struct BeLessThan : public Matcher
    {
        explicit BeLessThan(const T& expectedValue) : Matcher(), _expectedValue(expectedValue) {}

        template<typename U>
        bool matches(const U& actualValue) const
	{
	    return actualValue < _expectedValue;
	}

    protected:
        virtual void message_suffix(std::ostream& os) const
	{
	    os << "be less than <" << _expectedValue << ">";
	}

    private:
        const T& _expectedValue;
    };

    template<typename T>
    BeLessThan<T> be_less_than(const T& expectedValue)
    {
        return BeLessThan<T>(expectedValue);
    }
}

#endif	// LIBTEST_BELESSTHAN_H

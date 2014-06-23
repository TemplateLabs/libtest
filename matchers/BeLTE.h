#ifndef LIBTEST_BELESSTHANOREQUAL_H
#define LIBTEST_BELESSTHANOREQUAL_H

#include "Matcher.h"

namespace test
{
    template<typename T>
    struct BeLTE : public Matcher
    {
        explicit BeLTE(const T& expectedValue) : Matcher(), _expectedValue(expectedValue) {}

        template<typename U>
        bool matches(const U& actualValue) const
	{
	    return actualValue <= _expectedValue;
	}

    protected:
        virtual void message_suffix(std::ostream& os) const
	{
	    os << "be less than or equal to <" << _expectedValue << ">";
	}

    private:
        const T& _expectedValue;
    };

    template<typename T>
    BeLTE<T> be_lte(const T& expectedValue)
    {
        return BeLTE<T>(expectedValue);
    }

    template<typename T>
    BeLTE<T> be_less_than_or_equal_to(const T& expectedValue)
    {
        return be_lte(expectedValue);
    }
}

#endif	// LIBTEST_BELESSTHANOREQUAL_H

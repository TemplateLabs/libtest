#ifndef LIBTEST_BEGREATERTHANOREQUAL_H
#define LIBTEST_BEGREATERTHANOREQUAL_H

#include "Matcher.h"

namespace test
{
    template<typename T>
    struct BeGTE : public Matcher
    {
        explicit BeGTE(const T& expectedValue) : Matcher(), _expectedValue(expectedValue) {}

        template<typename U>
        bool matches(const U& actualValue) const
	{
	    return actualValue >= _expectedValue;
	}

    protected:
        virtual void message_suffix(std::ostream& os) const
	{
	    os << "be greater than or equal to <" << _expectedValue << ">";
	}

    private:
        const T& _expectedValue;
    };

    template<typename T>
    BeGTE<T> be_gte(const T& expectedValue)
    {
        return BeGTE<T>(expectedValue);
    }

    template<typename T>
    BeGTE<T> be_greater_than_or_equal_to(const T& expectedValue)
    {
        return be_gte(expectedValue);
    }
}

#endif	// LIBTEST_BEGREATERTHANOREQUAL_H

#ifndef LIBTEST_BEGREATERTHAN_H
#define LIBTEST_BEGREATERTHAN_H

#include "Matcher.h"

namespace test
{
    template<typename T>
    struct BeGreaterThan : public Matcher
    {
        explicit BeGreaterThan(const T& expectedValue) : Matcher(), _expectedValue(expectedValue) {}

        template<typename U>
        bool matches(const U& actualValue) const
	{
	    return actualValue > _expectedValue;
	}

    protected:
        virtual void message_suffix(std::ostream& os) const
	{
	    os << "be greater than <" << _expectedValue << ">";
	}

    private:
        const T& _expectedValue;
    };

    template<typename T>
    BeGreaterThan<T> be_greater_than(const T& expectedValue)
    {
        return BeGreaterThan<T>(expectedValue);
    }
}

#endif	// LIBTEST_BEGREATERTHAN_H

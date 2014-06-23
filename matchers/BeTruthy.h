#ifndef LIBTEST_BETRUTHY_H
#define LIBTEST_BETRUTHY_H

#include "Matcher.h"

namespace test
{
    struct BeTruthy : public Matcher
    {
        BeTruthy() : Matcher() {}

        template<typename U>
        bool matches(const U& actualValue) const
	{
	    return !!actualValue;
	}

    protected:
        virtual void message_suffix(std::ostream& os) const
	{
	    os << "evaluate to true";
	}
    };

    static const BeTruthy be_truthy = BeTruthy();
}

#endif	// LIBTEST_BETRUTHY_H

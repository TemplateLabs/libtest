#ifndef LIBTEST_BEFALSY_H
#define LIBTEST_BEFALSY_H

#include "Matcher.h"

namespace test
{
    struct BeFalsy : public Matcher
    {
        BeFalsy() : Matcher() {}

        template<typename U>
        bool matches(const U& actualValue) const
	{
	    return !actualValue;
	}

    protected:
        virtual void message_suffix(std::ostream& os) const
	{
	    os << "evaluate to false";
	}
    };

    static const BeFalsy be_falsy = BeFalsy();
}

#endif	// LIBTEST_BEFALSY_H

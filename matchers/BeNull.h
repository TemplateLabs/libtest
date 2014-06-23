#ifndef LIBTEST_BENULL_H
#define LIBTEST_BENULL_H

#include "Matcher.h"

namespace test
{
    struct BeNull : public Matcher
    {
        BeNull() : Matcher() {}

        template<typename U>
        bool matches(U *const & actualValue) const
	{
	    return !actualValue;
	}

    protected:
	void message_suffix(std::ostream& os) const
	{
	    os << "be nil";
	}
    };

    static const BeNull be_null = BeNull();
}

#endif	// LIBTEST_BENULL_H

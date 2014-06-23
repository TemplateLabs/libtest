#ifndef LIBTEST_BEEMPTY_H
#define LIBTEST_BEEMPTY_H

#include "Matcher.h"

namespace test
{
    struct BeEmpty : public Matcher
    {
        BeEmpty() : Matcher() {}

        template<typename U>
        bool matches(const U& container) const
	{
	    return container.empty();
	}

    protected:
	void message_suffix(std::ostream& os) const
	{
	    os << "be empty";
	}
    };

    static const BeEmpty be_empty = BeEmpty();
}

#endif	// LIBTEST_BEEMPTY_H

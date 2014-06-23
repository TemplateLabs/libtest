#ifndef LIBTEST_CONTAIN_H
#define LIBTEST_CONTAIN_H

#include <cstring>
#include <vector>

#include "Matcher.h"

namespace test
{
    template<typename T>
    struct Contain : public Matcher
    {
        explicit Contain(const T& element) : Matcher(), _element(element) {}

        template<typename U>
        bool matches(const U& container) const
	{
	    return container.find(_element) != container.end();
	}

        template<typename U>
        bool matches(const std::vector<U>& container) const
	{
	    return std::find(container.begin(), container.end(), _element) != container.end();
	}

	bool matches(const char *const container) const
	{
	    return (_element != NULL) && (container != NULL) && (strstr(container, _element) != NULL);
	}

	bool matches(char *const container) const
	{
	    return (_element != NULL) && (container != NULL) && (strstr(container, _element) != NULL);
	}

    protected:
	void message_suffix(std::ostream& os) const
	{
	    os << "contain <" << _element << ">";
	}

    private:
        const T& _element;
    };

    template<typename T>
    Contain<T> contain(const T& element)
    {
        return Contain<T>(element);
    }
}

#endif	// LIBTEST_CONTAIN_H

#ifndef LIBTEST_MATCHER_H
#define LIBTEST_MATCHER_H

#include <sstream>

namespace test
{
    struct Matcher
    {
        Matcher() {}

	template<typename U>
	std::ostream& message(std::ostream& os, const U& value, bool negate) const
	{
	    os << "Expected <" << value << "> " << (negate ? "to not " : "to ");
	    message_suffix(os);
	    return os;
	}

	template<typename U>
	std::string message(const U& value, bool negate) const
	{
	    std::ostringstream ss;
	    message(ss, value, negate);
	    return ss.str();
	}

	std::string message(char *const value, bool negate) const
	{
	    return message((value ? value : "NULL"), negate);
	}

        template<typename U>
	std::string message(const std::unique_ptr<U>& value, bool negate) const
	{
	    return message(value.get(), negate);
	}

	std::string message(const std::nullptr_t pointer, bool negate) const
	{
	    (void)pointer;
	    return message("nullptr", negate);
	}

	template<typename U>
	std::string message(std::function<U>& value, bool negate) const
	{
	    return message(typeid(value).name(), negate);
	}

	template<typename U>
	std::string message(const std::function<U>& value, bool negate) const
	{
	    return message(typeid(value).name(), negate);
	}

	template<typename U, template <class T, class = std::allocator<T> > class container >
	std::string message(const container<U>& value, bool negate) const
	{
	    return message(typeid(value).name(), negate);
	}

	template<typename U, template <class T, class = std::less<T>, class = std::allocator<T> > class container >
	std::string message(const container<U>& value, bool negate) const
	{
	    return message(typeid(value).name(), negate);
	}

	template<typename U, typename V, template <class K, class T, class = std::less<K>, class = std::allocator<std::pair<const K,T>> > class container >
	std::string message(const container<U,V>& value, bool negate) const
	{
	    return message(typeid(value).name(), negate);
	}

    protected:
        virtual void message_suffix(std::ostream& os) const = 0;
    };
}

#endif	// LIBTEST_MATCHER_H

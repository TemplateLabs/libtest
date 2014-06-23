#ifndef LIBTEST_THROWEXCEPTION_H
#define LIBTEST_THROWEXCEPTION_H

#include "Matcher.h"

namespace test
{
    template <typename T>
    class ThrowException : public Matcher
    {
    public:
        ThrowException() : Matcher(), _allow_subclasses(false) {}
        explicit ThrowException(bool allow_subclasses) : Matcher(), _allow_subclasses(allow_subclasses) {}

	template <typename U = std::exception>
        ThrowException<U> operator()() const
	{
	    return ThrowException<U>();
	}

	template <typename U = std::exception>
        ThrowException<U> operator()(const U& e) const
	{
	    (void)e;
	    return ThrowException<U>();
	}

        ThrowException& or_subclass()
	{
	    return ThrowException<T>(true);
	}

	template <typename U>
        bool matches(const U& block) const
	{
	    try
	    {
		block();
	    }
	    catch(const T& e)
	    {
		return true;
	    }
	    catch(...)	// Wrong exception
	    {
		_exception = std::current_exception();
	    }

	    return false;
	}

	template<typename U>
	std::string message(const U& value, bool negate) const
	{
	    std::ostringstream ss;
	    Matcher::message(ss, typeid(value).name(), negate);
	    return ss.str();
	}

    protected:
        void message_suffix(std::ostream& os) const
	{
	    os << "throw an exception";
	}

    private:
        bool	_allow_subclasses;
	mutable std::exception_ptr   _exception;
    };

    static const ThrowException<std::exception> throw_exception;
}

#endif	// LIBTEST_THROWEXCEPTION_H

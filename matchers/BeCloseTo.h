#ifndef LIBTEST_BECLOSETO_H
#define LIBTEST_BECLOSETO_H

#include "Matcher.h"

namespace test
{
    template<typename T>
    struct BeCloseTo : public Matcher
    {
        explicit BeCloseTo(const T& expectedValue): Matcher(), _expectedValue(expectedValue), _threshold(0.01) {}

        BeCloseTo<T>& within(float threshold)
	{
	    _threshold = threshold;
	    return *this;
	}

        template<typename U>
        bool matches(const U& actualValue) const
	{
	    return (actualValue > (_expectedValue - _threshold)) && (actualValue < (_expectedValue + _threshold));
	}

    protected:
        virtual void message_suffix(std::ostream& os) const
	{
	    os << "be close to <" << _expectedValue << ">" << " (within " << _threshold << ")";
	}

    private:
        const T& _expectedValue;
        float _threshold;
    };

    template<typename T>
    BeCloseTo<T> be_close_to(const T& expectedValue)
    {
        return BeCloseTo<T>(expectedValue);
    }
}

#endif	// LIBTEST_BECLOSETO_H

#ifndef LIBTEST_H
#define LIBTEST_H

#include "include/dispatcher.h"
#include "include/exception.h"
#include "include/registry.h"
#include "include/reporter.h"
#include "include/runner.h"
#include "matchers/matchers.h"

#define BEGIN_TEST(_name) 		\
namespace {				\
    const auto& _top_level_describe = test::Registry::instance().push_back([]{	\
	using namespace test;

#define END_TEST	});}

// Alias the wrapper macros for cases where other nomenclature makes more sense
#define BEGIN_SPEC(_name)	BEGIN_TEST(_name)
#define END_SPEC		END_TEST
#define SPEC_BEGIN(_name)	BEGIN_TEST(_name)
#define SPEC_END		END_TEST
#define TEST_BEGIN(_name)	BEGIN_TEST(_name)
#define TEST_END		END_TEST

namespace test
{
    typedef Runner::block_t block_t;

    inline void describe(const char* description, block_t block)
    {
	Runner::group(description, block);
    }

    inline void it(const char* description, block_t block)
    {
	Runner::example(description, block);
    }

    inline void fdescribe(const char* description, block_t block)
    {
	Runner::focus_group(description, block);
    }

    inline void fit(const char* description, block_t block)
    {
	Runner::focus_example(description, block);
    }

    inline void xdescribe(const char* description, block_t block)
    {
	Runner::skip_group(description, block);
    }

    inline void xit(const char* description, block_t block)
    {
	Runner::skip_example(description, block);
    }

    inline int run(int argc, char* argv[])
    {
	Reporter reporter;
	Dispatcher::instance().register_reporter(&reporter);

	return Runner::instance().run();
    }
}

#endif	// LIBTEST_H

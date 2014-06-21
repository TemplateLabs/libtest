#ifndef LIBTEST_H
#define LIBTEST_H

#include "include/dispatcher.h"
#include "include/registry.h"

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
    typedef Registry::block_t block_t;

    inline void describe(const char* description, block_t block)
    {
	auto& dispatcher = Dispatcher::instance();

	dispatcher.started_group();

	try
	{
	    block();
	}
	catch(std::exception& e)
	{
	    dispatcher.caught(e);
	}

	dispatcher.finished_group();
    }

    inline void it(const char* description, block_t block)
    {
	auto& dispatcher = Dispatcher::instance();

	dispatcher.started_example();

	try
	{
	    block();
	}
	catch(const std::exception& e)
	{
	    dispatcher.caught(e);
	}
	catch(...)
	{
	    dispatcher.caught_unknown();
	}

    	dispatcher.finished_example();
    }

    inline int run(int argc, char* argv[])
    {
	for( auto& block : Registry::instance() )
	    block();

	return 0;
    }
}

#endif	// LIBTEST_H

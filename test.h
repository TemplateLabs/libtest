#ifndef LIBTEST_H
#define LIBTEST_H

#include "include/dispatcher.h"
#include "include/exception.h"
#include "include/registry.h"
#include "include/reporter.h"
#include "include/runner.h"

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
	auto& runner = Runner::instance();

	runner.started_group();

	try
	{
	    block();
	}
	catch(const test::exception& e)
	{
	    runner.caught(e);
	}
	catch(const std::exception& e)
	{
	    runner.caught(e);
	}
	catch(...)
	{
	    runner.caught_unknown();
	}

	runner.finished_group();
    }

    inline void it(const char* description, block_t block)
    {
	auto& runner = Runner::instance();

	runner.started_example();

	try
	{
	    block();
	}
	catch(const test::exception& e)
	{
	    runner.caught(e);
	}
	catch(const std::exception& e)
	{
	    runner.caught(e);
	}
	catch(...)
	{
	    runner.caught_unknown();
	}

	runner.finished_example();
    }

    inline int run(int argc, char* argv[])
    {
	Reporter reporter;
	Dispatcher::instance().register_reporter(&reporter);

	return Runner::instance().run();
    }
}

#endif	// LIBTEST_H

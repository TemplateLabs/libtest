#ifndef LIBTEST_RUNNER_H
#define LIBTEST_RUNNER_H

#include "dispatcher.h"
#include "registry.h"

namespace test
{
    struct Runner
    {
	typedef Registry::block_t	block_t;

	static Runner& instance()
	{
	    static Runner runner;
	    return runner;
	}

	static void example(const char* description, block_t block)
	{
	    instance().do_example(description, block);
	}

	static void group(const char* description, block_t block)
	{
	    instance().do_group(description, block);
	}

	Runner() noexcept : dispatcher(Dispatcher::instance()) {}
	Runner(const Runner&) = delete;
	Runner& operator=(const Runner&) = delete;

	int run()
	{
	    dispatcher.started();

	    // Count the examples
	    run_mode = false;
	    example_index = 0;
	    for( auto& block : Registry::instance() )
		block();

	    // example_index should now correspond to the number of examples to be run
	    const unsigned example_count = example_index;

	    // Now run all of the examples
	    run_mode = true;
	    for( example_number = 0; example_number < example_count; ++example_number )
	    {
		example_index = 0;
		for( auto& block : Registry::instance() )
		    block();
	    }

	    dispatcher.finished();

	    return 0;
	}

	void do_example(const char* description, block_t block)
	{
	    if( run_mode )
	    {
		// Is this the example to be run?
		if( example_index == example_number )
		{
		    dispatcher.started_example();

		    try
		    {
			block();
		    }
		    catch(const test::exception& e)
		    {
			caught(e);
		    }
		    catch(const std::exception& e)
		    {
			caught(e);
		    }
		    catch(...)
		    {
			caught_unknown();
		    }

		    dispatcher.finished_example();
		}
	    }

	    ++example_index;
	}

	void do_group(const char* description, block_t block)
	{
	    (void) description;

	    if( run_mode )
		dispatcher.started_group();

	    try
	    {
		block();
	    }
	    catch(const test::exception& e)
	    {
		caught(e);
	    }
	    catch(const std::exception& e)
	    {
		caught(e);
	    }
	    catch(...)
	    {
		caught_unknown();
	    }

	    if( run_mode )
		dispatcher.finished_group();
	}

	void caught(const test::exception& error)
	{
	    dispatcher.caught(error);
	}

	void caught(const std::exception& error)
	{
	    dispatcher.caught(error);
	}

	void caught_unknown()
	{
	    dispatcher.caught_unknown();
	}

    private:
	Dispatcher& dispatcher;
	unsigned example_index;
	unsigned example_number;
	bool run_mode = false;
    };
};

#endif	// LIBTEST_RUNNER_H
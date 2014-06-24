#ifndef LIBTEST_RUNNER_H
#define LIBTEST_RUNNER_H

#include <map>

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
	    group_index = 0;
	    for( auto& block : Registry::instance() )
		block();

	    // example_index should now correspond to the number of examples to be run
	    const unsigned example_count = example_index;

	    // Now run all of the examples
	    run_mode = true;
	    for( example_number = 0; example_number < example_count; ++example_number )
	    {
		example_index = 0;
		group_index = 0;
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
		    dispatcher.started_example(description);

		    try
		    {
			block();
		    }
		    catch(const test::exception& failure)
		    {
			dispatcher.failure(failure);
		    }
		    catch(const std::exception& error)
		    {
			dispatcher.error(error);
		    }
		    catch(...)
		    {
			dispatcher.error();
		    }

		    dispatcher.finished_example();
		}
	    }

	    ++example_index;
	}

	void do_group(const char* description, block_t block)
	{
	    const auto first_example_index = example_index;
	    const auto this_group_index = group_index++;

	    bool has_example = false;
	    if( run_mode )
	    {
		const auto range = group_map[this_group_index];
		if( (example_number >= range.first) && (example_number < range.second) )
		{
		    dispatcher.started_group(description);
		    has_example = true;
		}
	    }

	    try
	    {
		block();
	    }
	    catch(const test::exception& failure)
	    {
		dispatcher.failure(failure);
	    }
	    catch(const std::exception& error)
	    {
		dispatcher.error(error);
	    }
	    catch(...)
	    {
		dispatcher.error();
	    }

	    if( run_mode )
	    {
		if( has_example )
		    dispatcher.finished_group();
	    }
	    else
	    {
		const auto ope_example_index = example_index;
		group_map[this_group_index] = std::make_pair(first_example_index, ope_example_index);
	    }
	}

    private:
	Dispatcher& dispatcher;

	unsigned example_index;
	unsigned example_number;
	bool run_mode = false;

	std::map<unsigned, std::pair<unsigned, unsigned>> group_map;
	unsigned group_index;
    };
};

#endif	// LIBTEST_RUNNER_H
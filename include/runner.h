#ifndef LIBTEST_RUNNER_H
#define LIBTEST_RUNNER_H

#include <map>
#include <set>

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

	static void focus_example(const char* description, block_t block)
	{
	    instance().do_example(description, block, true, true);
	}

	static void focus_group(const char* description, block_t block)
	{
	    instance().do_group(description, block, true, true);
	}

	static void skip_example(const char* description, block_t block)
	{
	    instance().do_example(description, block, true);
	}

	static void skip_group(const char* description, block_t block)
	{
	    instance().do_group(description, block, true);
	}

	Runner() noexcept : dispatcher(Dispatcher::instance()) {}
	Runner(const Runner&) = delete;
	Runner& operator=(const Runner&) = delete;

	int run()
	{
	    dispatcher.started();

	    // Count the examples
	    Registry::instance().run();

	    // example_index should now correspond to the number of examples to be run
	    const unsigned example_count = example_index;

	    // If there are focused examples, run only those
	    if( focus_set.size() )
	    {
		for( auto focus_number : focus_set )
		{
		    example_number = focus_number;
		    run_all_registry_blocks(true);
		}
	    }
	    else    // Otherwise, run all of the examples
	    {
		for( example_number = 0; example_number < example_count; ++example_number )
		    run_all_registry_blocks(true);
	    }

	    dispatcher.finished();

	    return 0;
	}

	void do_example(const char* description, block_t block, bool skip=false, bool focus=false)
	{
	    if( run_mode )
	    {
		// Is this the example to be run?
		if( example_index == example_number )
		{
		    // Skipping isn't allowed while focusing
		    if( (skip || group_skip) && !(focus || group_focus) )
			dispatcher.skipped_example(description);
		    else
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
	    }
	    else if( (focus || group_focus) && !group_skip )
	    {
		focus_set.insert(example_index);
	    }

	    ++example_index;
	}

	void do_group(const char* description, block_t block, bool skip=false, bool focus=false)
	{
	    const auto first_example_index = example_index;
	    const bool already_focused = group_focus;
	    const bool already_skipping = group_skip;
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

	    if( skip )
		group_skip = true;

	    // A group can't be focused if a parent group is skipped
	    if( group_skip )
		focus = false;

	    if( focus )
		group_focus = true;

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
		{
		    dispatcher.finished_group();
		}
	    }
	    else
	    {
		const auto ope_example_index = example_index;
		group_map[this_group_index] = std::make_pair(first_example_index, ope_example_index);
	    }

	    // Finished skipping this group
	    if( skip && !already_skipping )
		group_skip = false;

	    if( focus && !already_focused )
		group_focus = false;
	}

    private:
	Dispatcher& dispatcher;

	unsigned example_index;
	unsigned example_number;
	bool run_mode = false;

	std::set<unsigned> focus_set;
	std::map<unsigned, std::pair<unsigned, unsigned>> group_map;
	bool group_focus;
	unsigned group_index;
	bool group_skip;

	void run_all_registry_blocks(bool mode=false)
	{
	    run_mode = mode;
	    example_index = 0;
	    group_focus = false;
	    group_index = 0;
	    group_skip = false;
	    Registry::instance().run();
	}
    };
};

#endif	// LIBTEST_RUNNER_H
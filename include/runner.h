#ifndef LIBTEST_RUNNER_H
#define LIBTEST_RUNNER_H

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

	Runner() noexcept {}
	Runner(const Runner&) = delete;
	Runner& operator=(const Runner&) = delete;

	int run()
	{
	    auto& dispatcher = Dispatcher::instance();

	    dispatcher.started();

	    for( auto& block : Registry::instance() )
		block();

	    dispatcher.finished();

	    return 0;
	}

	void caught(const test::exception& error)
	{
	    Dispatcher::instance().caught(error);
	}

	void caught(const std::exception& error)
	{
	    Dispatcher::instance().caught(error);
	}

	void caught_unknown()
	{
	    Dispatcher::instance().caught_unknown();
	}

	void started_example()
	{
	    Dispatcher::instance().started_example();
	}

	void finished_example()
	{
	    Dispatcher::instance().finished_example();
	}

	void started_group()
	{
	    Dispatcher::instance().started_group();
	}

	void finished_group()
	{
	    Dispatcher::instance().finished_group();
	}
    };
};

#endif	// LIBTEST_RUNNER_H
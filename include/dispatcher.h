#ifndef LIBTEST_DISPATCHER_H
#define LIBTEST_DISPATCHER_H

#include <exception>

namespace test
{
    struct Dispatcher
    {
	static Dispatcher& instance()
	{
	    static Dispatcher dispatcher;
	    return dispatcher;
	}

	Dispatcher() noexcept {}
	Dispatcher(const Dispatcher&) = delete;
	Dispatcher& operator=(const Dispatcher&) = delete;

	void caught(const std::exception& error)
	{
	}

	void caught_unknown()
	{
	}

	void started_example()
	{
	}

	void finished_example()
	{
	}

	void started_group()
	{
	}

	void finished_group()
	{
	}
    };
};

#endif	// LIBTEST_DISPATCHER_H
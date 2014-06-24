#ifndef LIBTEST_DISPATCHER_H
#define LIBTEST_DISPATCHER_H

#include <exception>
#include <list>

#include "reporter.h"

namespace test
{
    struct Dispatcher
    {
	typedef Reporter::description_t	description_t;

	static Dispatcher& instance()
	{
	    static Dispatcher dispatcher;
	    return dispatcher;
	}

	Dispatcher() noexcept {}
	Dispatcher(const Dispatcher&) = delete;
	Dispatcher& operator=(const Dispatcher&) = delete;

	void register_reporter(Reporter* reporter)
	{
	    reporters.push_back(reporter);
	}

	void finished()
	{
	    for( auto reporter : reporters )
		reporter->finished();
	}

	void started()
	{
	    for( auto reporter : reporters )
		reporter->started();
	}

	void failure(const test::exception& failure)
	{
	    for( auto reporter : reporters )
		reporter->failure(failure);
	}

	void error(const std::exception& error)
	{
	    for( auto reporter : reporters )
		reporter->error(error);
	}

	void error()
	{
	    for( auto reporter : reporters )
		reporter->error();
	}

	void started_example(description_t description)
	{
	    for( auto reporter : reporters )
		reporter->started_example(description);
	}

	void finished_example()
	{
	    for( auto reporter : reporters )
		reporter->finished_example();
	}

	void started_group(description_t description)
	{
	    for( auto reporter : reporters )
		reporter->started_group(description);
	}

	void finished_group()
	{
	    for( auto reporter : reporters )
		reporter->finished_group();
	}

    private:
    	std::list<Reporter*> reporters;
    };
};

#endif	// LIBTEST_DISPATCHER_H
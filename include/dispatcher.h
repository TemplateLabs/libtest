#ifndef LIBTEST_DISPATCHER_H
#define LIBTEST_DISPATCHER_H

#include <exception>
#include <list>

#include "reporter.h"

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

	void caught(const std::exception& error)
	{
	    for( auto reporter : reporters )
		reporter->caught(error);
	}

	void caught_unknown()
	{
	    for( auto reporter : reporters )
		reporter->caught_unknown();
	}

	void started_example()
	{
	    for( auto reporter : reporters )
		reporter->started_example();
	}

	void finished_example()
	{
	    for( auto reporter : reporters )
		reporter->finished_example();
	}

	void started_group()
	{
	    for( auto reporter : reporters )
		reporter->started_group();
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
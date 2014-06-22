#ifndef LIBTEST_REPORTER_H
#define LIBTEST_REPORTER_H

#include <iostream>

#include <include/exception.h>

namespace test
{
    struct Reporter
    {
	Reporter() : error_count(0), example_count(0), failure_count(0) {}

	virtual void finished()
	{
	    auto _end_time = std::chrono::system_clock::now();
	    auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(_end_time - _start_time);
	    std::cout << "Finished in " << duration.count() << " seconds\n";
	    std::cout << example_count <<" examples, " << failure_count << " failures";

	    if( error_count )
		std::cout << ", " << error_count;

	    std::cout << std::endl;
	}

	virtual void started()
	{
	    _start_time = std::chrono::system_clock::now();
	}

	virtual void failure(const test::exception& failure)
	{
	    ++failure_count;
	    std::cout << "FAILURE " << failure.message() << std::endl;
	}

	virtual void error(const std::exception& error)
	{
	    ++error_count;
	    std::cout << "ERROR " << error.what() << std::endl;
	}

	virtual void error()
	{
	    ++error_count;
	    std::cout << "UNKNOWN ERROR\n";
	}

	virtual void started_example()
	{
	    ++example_count;
	}

	virtual void finished_example()
	{
	}

	virtual void started_group()
	{
	}

	virtual void finished_group()
	{
	}

    private:
	unsigned error_count;
	unsigned example_count;
	unsigned failure_count;
	std::chrono::system_clock::time_point	_start_time;
    };
};

#endif	// LIBTEST_REPORTER_H
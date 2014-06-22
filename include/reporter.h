#ifndef LIBTEST_REPORTER_H
#define LIBTEST_REPORTER_H

#include <iostream>

namespace test
{
    struct Reporter
    {
	Reporter() : example_count(0), failure_count(0) {}

	virtual void finished()
	{
	    auto _end_time = std::chrono::system_clock::now();
	    auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(_end_time - _start_time);
	    std::cout << "Finished in " << duration.count() << " seconds\n";
	    std::cout << example_count <<" examples, " << failure_count << " failures\n";
	}

	virtual void started()
	{
	    _start_time = std::chrono::system_clock::now();
	}

	virtual void caught(const std::exception& error)
	{
	    ++failure_count;
	}

	virtual void caught_unknown()
	{
	    ++failure_count;
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
	unsigned example_count;
	unsigned failure_count;
	std::chrono::system_clock::time_point	_start_time;
    };
};

#endif	// LIBTEST_REPORTER_H
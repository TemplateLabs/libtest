#ifndef LIBTEST_REPORTER_H
#define LIBTEST_REPORTER_H

#include <iostream>

#include <include/exception.h>

namespace test
{
    struct Reporter
    {
	typedef const char* description_t;
	typedef std::list<description_t> description_stack_t;

	Reporter() : error_count(0), example_count(0), failure_count(0) {}

	virtual void finished()
	{
	    auto _end_time = std::chrono::system_clock::now();
	    auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(_end_time - _start_time);
	    std::cout << "\nFinished in " << duration.count() << " seconds\n";

	    std::cout << example_count <<" examples, " << failure_count << " failure";
	    if( failure_count != 1 )
		std::cout << "s";

	    if( error_count )
	    {
		std::cout << ", " << error_count << " error";
		if( error_count != 1 )
		    std::cout << "s";
	    }

	    if( skip_count )
		std::cout << ", " << skip_count << " skipped";

	    std::cout << std::endl;
	}

	virtual void started()
	{
	    error_count = 0;
	    example_count = 0;
	    failure_count = 0;
	    skip_count = 0;
	    _start_time = std::chrono::system_clock::now();
	}

	virtual void failure(const test::exception& failure)
	{
	    ++failure_count;

	    std::cout << "\nFAILURE";

	    joined_description(std::cout, description_stack);

	    std::cout << " (" << failure.filename() << ":" << failure.linenumber() << ")";

	    if( description_stack.size() )
		std::cout << std::endl;
	    else
		std::cout << " ";

	    std::cout << failure.message()  << std::endl;
	}

	virtual void error(const std::exception& error)
	{
	    ++error_count;

	    std::cout << "\nERROR";

	    joined_description(std::cout, description_stack);

	    if( description_stack.size() )
		std::cout << std::endl;
	    else
		std::cout << " ";

	    std::cout << error.what() << std::endl;
	}

	virtual void error()
	{
	    ++error_count;

	    std::cout << "\nUNKNOWN ERROR";
	    joined_description(std::cout, description_stack);
	    std::cout << std::endl;
	}

	virtual void started_example(description_t description)
	{
	    ++example_count;
	    description_stack.push_back(description);
	}

	virtual void finished_example()
	{
	    description_stack.pop_back();
	}

	virtual void skipped_example(description_t description)
	{
	    ++example_count;
	    ++skip_count;
	}

	virtual void started_group(description_t description)
	{
	    description_stack.push_back(description);
	}

	virtual void finished_group()
	{
	    description_stack.pop_back();
	}

	virtual void skipped_group(description_t description)
	{
	}

    protected:
	void joined_description(std::ostream& os, description_stack_t& description_stack)
	{
	    for( const char* description : description_stack )
		os << " " << description;
	}

    private:
	unsigned error_count;
	unsigned example_count;
	unsigned failure_count;
	description_stack_t	description_stack;
	unsigned skip_count;
	std::chrono::system_clock::time_point	_start_time;
    };
};

#endif	// LIBTEST_REPORTER_H
#ifndef LIBTEST_REPORTER_H
#define LIBTEST_REPORTER_H

namespace test
{
    struct Reporter
    {
	virtual void finished()
	{
	}

	virtual void started()
	{
	}

	virtual void caught(const std::exception& error)
	{
	}

	virtual void caught_unknown()
	{
	}

	virtual void started_example()
	{
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
    };
};

#endif	// LIBTEST_REPORTER_H
#ifndef LIBTEST_REGISTRY_H
#define LIBTEST_REGISTRY_H

#include <functional>
#include <list>

namespace test
{
    struct Registry
    {
	typedef std::function<void ()>		block_t;
	typedef std::list<block_t>		blocks_t;
	typedef blocks_t::const_iterator	const_iterator;

	static Registry& instance()
	{
	    static Registry registry;
	    return registry;
	}

	Registry() noexcept {}
	Registry(const Registry&) = delete;
	Registry& operator=(const Registry&) = delete;

	block_t push_back(block_t block)
	{
	    blocks.push_back(block);
	    return block;
	}

	void run()
	{
	    for( auto& block : blocks )
		block();
	}

    private:
	blocks_t blocks;
    };
};

#endif	// LIBTEST_REGISTRY_H
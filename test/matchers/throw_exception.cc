#include <test.h>

TEST_BEGIN(ThrowException)

describe("throw_exception", []{
    describe("when no exception is specified", [&]{
	std::exception exception;
	std::function<void()> exception_block = [&]{ throw exception; };

        describe("when the block throws an exception", [&]{
	    it("must pass a positive match", [&]{
		exception_block must throw_exception;
	    });

	    it("must reject a negative match", [&]{
		[&]{ exception_block must_not throw_exception; } must throw_exception;
	    });
        });

        describe("when the block does not throw an exception", [&]{
	    std::function<void()> quiet_block = [&]{};

	    it("must pass a negative match", [&]{
		quiet_block must_not throw_exception;
	    });

	    it("must reject a positive match", [&]{
		[&]{ quiet_block must throw_exception; } must throw_exception;
	    });
        });
    });

    describe("with an exception class specified", [&]{
	std::logic_error expected_exception("logic_error");

        describe("when the block throws the expected exception", [&]{
	    std::function<void()> exception_block = [&]{ throw expected_exception; };

	    it("must pass a positive match", [&]{
		exception_block must throw_exception(expected_exception);
	    });

	    it("must reject a negative match", [&]{
		[&]{ exception_block must_not throw_exception(expected_exception); } must throw_exception;
	    });
        });

        describe("when the block throws an unrelated exception", [&]{
	    std::function<void()> unrelated_block = [&]{ throw std::range_error("range error"); };

	    it("must pass a negative match", [&]{
		unrelated_block must_not throw_exception(expected_exception);
	    });

	    it("must reject a positive match", [&]{
		[&]{ unrelated_block must throw_exception(expected_exception); } must throw_exception;
	    });
        });

        describe("when the block does not throw an exception", [&]{
	    std::function<void()> quiet_block = [&]{};

	    it("must pass a negative match", [&]{
		quiet_block must_not throw_exception(expected_exception);
	    });

	    it("must reject a positive match", [&]{
		[&]{ quiet_block must throw_exception(expected_exception); } must throw_exception;
	    });
        });
    });
});

SPEC_END

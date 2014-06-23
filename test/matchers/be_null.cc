#include <test.h>

TEST_BEGIN(BeNull)

describe("be_null", [&]{
    describe("when the value is a pointer to a built-in type", [&]{
        int* value;

        describe("which is NULL", [&]{
	    value = NULL;

	    it("must pass a positive match", [&]{
		value must be_null;
	    });

	    it("must reject a negative match", [&]{
		[&]{ value must_not be_null; } must throw_exception;
	    });
        });

        describe("which is not NULL", [&]{
            int i = 7;
	    value = &i;

	    it("must pass a negative match", [&]{
		value must_not be_null;
	    });

	    it("must reject a positive match", [&]{
		[&]{ value must be_null; } must throw_exception;
	    });
        });
    });
});

SPEC_END

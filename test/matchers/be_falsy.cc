#include <test.h>

TEST_BEGIN(BeFalsy)

describe("be_falsy", [&]{
    describe("when the value is a built-in type", [&]{
        bool value;

        describe("which evaluates to false", [&]{
	    value = false;

	    it("must accept a positive match", [&]{
		value must be_falsy;
	    });

	    it("must reject a negative match", [&]{
		[&]{ value must_not be_falsy; } must throw_exception;
            });
        });

        describe("which evaluates to true", [&]{
	    value = true;

	    it("must accept a negative match", [&]{
		value must_not be_falsy;
	    });

	    it("must reject a positive match", [&]{
		[&]{ value must be_falsy; } must throw_exception;
            });
        });
    });

    describe("when the value is nullptr", [&]{
	auto value = nullptr;

	it("must accept a positive match", [&]{
	    value must be_falsy;
	});

	it("must reject a negative match", [&]{
	    [&]{ value must_not be_falsy; } must throw_exception;
	});
    });

    describe("when the value is a pointer", [&]{
        char* value;

        describe("which evaluates to false", [&]{
	    value = NULL;

	    it("must accept a positive match", [&]{
		value must be_falsy;
	    });

	    it("must reject a negative match", [&]{
		[&]{ value must_not be_falsy; } must throw_exception;
	    });
        });

        describe("which evaluates to true", [&]{
	    value = (char*)"cat";

	    it("must accept a negative match", [&]{
		value must_not be_falsy;
	    });

	    it("must reject a positive match", [&]{
		[&]{ value must be_falsy; } must throw_exception;
            });
        });
    });
});

SPEC_END

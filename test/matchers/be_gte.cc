#include <test.h>

TEST_BEGIN(BeGTE)

describe("be_gte", [&]{
    int someInteger = 10;

    describe("when the actual value is a built-in type", [&]{
        int actualValue = someInteger;

        describe("and the expected value is the same built-in type", [&]{
            int expectedValue;

            describe("and the actual value is greater than the expected value", [&]{
		expectedValue = 1;

		it("must pass a positive match", [&]{
		    actualValue must be_gte(expectedValue);
		    actualValue must be_greater_than_or_equal_to(expectedValue);
		});

		it("must reject a negative match", [&]{
		    [&]{ actualValue must_not be_gte(expectedValue); } must throw_exception;
		    [&]{ actualValue must_not be_greater_than_or_equal_to(expectedValue); } must throw_exception;
		});
            });

            describe("and the actual value is less than the expected value", [&]{
		expectedValue = 100;

		it("must pass a negative match", [&]{
		    actualValue must_not be_gte(expectedValue);
		    actualValue must_not be_greater_than_or_equal_to(expectedValue);
		});

		it("must reject a positive match", [&]{
		    [&]{ actualValue must be_gte(expectedValue); } must throw_exception;
		    [&]{ actualValue must be_greater_than_or_equal_to(expectedValue); } must throw_exception;
		});
            });

            describe("and the actual value equals the expected value", [&]{
		expectedValue = actualValue;

		it("must pass a positive match", [&]{
		    actualValue must be_gte(expectedValue);
		    actualValue must be_greater_than_or_equal_to(expectedValue);
		});

		it("must reject a negative match", [&]{
		    [&]{ actualValue must_not be_gte(expectedValue); } must throw_exception;
		    [&]{ actualValue must_not be_greater_than_or_equal_to(expectedValue); } must throw_exception;
		});
            });
        });

        describe("and the expected value is a different, but comparable, built-in type", [&]{
            float expectedValue;

            describe("and the actual value is greater than the expected value", [&]{
		expectedValue = 1.1;

		it("must pass a positive match", [&]{
		    actualValue must be_gte(expectedValue);
		    actualValue must be_greater_than_or_equal_to(expectedValue);
		});

		it("must reject a negative match", [&]{
		    [&]{ actualValue must_not be_gte(expectedValue); } must throw_exception;
		    [&]{ actualValue must_not be_greater_than_or_equal_to(expectedValue); } must throw_exception;
		});
            });

            describe("and the actual value is less than the expected value", [&]{
		expectedValue = 100.1;

		it("must pass a negative match", [&]{
		    actualValue must_not be_gte(expectedValue);
		    actualValue must_not be_greater_than_or_equal_to(expectedValue);
		});

		it("must reject a positive match", [&]{
		    [&]{ actualValue must be_gte(expectedValue); } must throw_exception;
		    [&]{ actualValue must be_greater_than_or_equal_to(expectedValue); } must throw_exception;
		});
            });

            describe("and the actual value equals the expected value", [&]{
		expectedValue = someInteger / 1.0;

		it("must pass a positive match", [&]{
		    actualValue must be_gte(expectedValue);
		    actualValue must be_greater_than_or_equal_to(expectedValue);
		});

		it("must reject a negative match", [&]{
		    [&]{ actualValue must_not be_gte(expectedValue); } must throw_exception;
		    [&]{ actualValue must_not be_greater_than_or_equal_to(expectedValue); } must throw_exception;
		});
            });
        });
    });
});

SPEC_END

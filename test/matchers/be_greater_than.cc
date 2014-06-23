#include <test.h>

TEST_BEGIN(BeGreaterThan)

describe("be_greater_than", []{
    describe("when the actual value is a built-in type", [&]{
        int actualValue = 10;

        describe("and the expected value is the same built-in type", [&]{
            int expectedValue;

            describe("and the actual value is greater than the expected value", [&]{
		expectedValue = 1;

		it("must pass a positive match", [&]{
		    actualValue must be_greater_than(expectedValue);
		});

		it("must reject a negative match", [&]{
		    [&]{ actualValue must_not be_greater_than(expectedValue); } must throw_exception;
		});
            });

            describe("and the actual value is less than the expected value", [&]{
		expectedValue = 100;

		it("must pass a negative match", [&]{
		    actualValue must_not be_greater_than(expectedValue);
		});

		it("must reject a positive match", [&]{
		    [&]{ actualValue must be_greater_than(expectedValue); } must throw_exception;
		});
            });

            describe("and the actual value equals the expected value", [&]{
		expectedValue = actualValue;

		it("must pass a negative match", [&]{
		    actualValue must_not be_greater_than(expectedValue);
		});

		it("must reject a positive match", [&]{
		    [&]{ actualValue must be_greater_than(expectedValue); } must throw_exception;
		});
            });
        });

        describe("and the expected value is a different, but comparable, built-in type", [&]{
            float expectedValue;

            describe("and the actual value is greater than the expected value", [&]{
		expectedValue = 1.1;

		it("must pass a positive match", [&]{
		    actualValue must be_greater_than(expectedValue);
		});

		it("must reject a negative match", [&]{
		    [&]{ actualValue must_not be_greater_than(expectedValue); } must throw_exception;
		});
            });

            describe("and the actual value is less than the expected value", [&]{
		expectedValue = 100.1;

		it("must pass a negative match", [&]{
		    actualValue must_not be_greater_than(expectedValue);
		});

		it("must reject a positive match", [&]{
		    [&]{ actualValue must be_greater_than(expectedValue); } must throw_exception;
		});
            });

            describe("and the actual value equals the expected value", [&]{
		expectedValue = actualValue;

		it("must pass a negative match", [&]{
		    actualValue must_not be_greater_than(expectedValue);
		});

		it("must reject a positive match", [&]{
		    [&]{ actualValue must be_greater_than(expectedValue); } must throw_exception;
		});
            });
        });
    });
});

SPEC_END

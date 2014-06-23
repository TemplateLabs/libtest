#include <test.h>

TEST_BEGIN(Equal)

describe("when the actual value is a built-in type", []{
    int actualValue = 1;

    describe("and the expected value is the same built-in type", [&]{
	int expectedValue;

	describe("and the values are equal", [&]{
	    expectedValue = 1;

	    it("must accept a positive match", [&]{
		actualValue must equal(expectedValue);
	    });

	    it("must reject a negative match", [&]{
		[&]{ actualValue must_not equal(expectedValue); } must throw_exception;
	    });
	});

	describe("and the values are not equal", [&]{
	    expectedValue = 147;

	    it("must accept a negative match", [&]{
		actualValue must_not equal(expectedValue);
	    });

	    it("must reject a positive match", [&]{
		[&]{ actualValue must equal(expectedValue); } must throw_exception;
	    });
	});
    });

    describe("and the expected value is a different, but comparable, built-in type", [&]{
	long int expectedValue;

	describe("and the values are equal", [&]{
	    expectedValue = 1;

	    it("must accept a positive match", [&]{
		actualValue must equal(expectedValue);
	    });

	    it("must reject a negative match", [&]{
		[&]{ actualValue must_not equal(expectedValue); } must throw_exception;
	    });
	});

	describe("and the values are not equal", [&]{
	    expectedValue = 42;

	    it("must accept a negative match", [&]{
		actualValue must_not equal(expectedValue);
	    });

	    it("must reject a positive match", [&]{
		[&]{ actualValue must equal(expectedValue); } must throw_exception;
	    });
	});
    });
});

describe("when the actual value is declared as a C string", []{
    char* actualValue = (char*)"actualValue";

    describe("and the expected value is declared as a C string", [&]{
	std::unique_ptr<char> expectedValue;

	expectedValue.reset((char*)calloc(strlen(actualValue) + 1, sizeof(char)));

	describe("and the values are equal", [&]{
	    stpcpy(expectedValue.get(), actualValue);

	    it("must accept a positive match", [&]{
		actualValue must equal(expectedValue.get());
	    });

	    it("must reject a negative match", [&]{
		[&]{ actualValue must_not equal(expectedValue.get()); } must throw_exception;
	    });
	});

	describe("and the values are not equal", [&]{
	    stpcpy(expectedValue.get(), "expectedVal");

	    it("must accept a negative match", [&]{
		actualValue must_not equal(expectedValue.get());
	    });

	    it("must reject a positive match", [&]{
		[&]{ actualValue must equal(expectedValue.get()); } must throw_exception;
	    });
	});
    });

    describe("and the expected value is declared as a const C string", [&]{
	const char *expectedValue;

	describe("and the values are equal", [&]{
	    expectedValue = "actualValue";

	    it("must accept a positive match", [&]{
		actualValue must equal(expectedValue);
	    });

	    it("must reject a negative match", [&]{
		[&]{ actualValue must_not equal(expectedValue); } must throw_exception;
	    });
	});
    });

    describe("when the expected value is a unique_ptr to a C string", [&]{
	std::unique_ptr<char> expectedValue;

	expectedValue.reset((char*)calloc(strlen(actualValue) + 1, sizeof(char)));

	describe("and the values are equal", [&]{
	    stpcpy(expectedValue.get(), actualValue);

	    it("must accept a positive match", [&]{
		actualValue must equal(expectedValue);
	    });

	    it("must reject a negative match", [&]{
		[&]{ actualValue must_not equal(expectedValue); } must throw_exception;
	    });
	});
    });
});

describe("when the actual value is a unique_ptr", []{
    std::unique_ptr<char> actualValue;
    auto expectedValue = (char*)"expectedValue";

    actualValue.reset((char*)calloc(strlen(expectedValue) + 1, sizeof(char)));

    describe("when the strings are equal", [&]{
	stpcpy(actualValue.get(), expectedValue);

	it("must accept a positive match", [&]{
	    actualValue must equal(expectedValue);
	});
    });

    describe("when the strings are not equal", [&]{
	stpcpy(actualValue.get(), "hello");

	it("must accept a negative match", [&]{
	    actualValue must_not equal(expectedValue);
	});
    });
});

describe("when the actual value is declared as char array", []{
    describe("and the expected value is declared as a C string", []{
	char actualValue[] = "actualValue";

	describe("and the values are equal", [&]{
	    char* expectedValue = (char*)"actualValue";

	    it("must accept a positive match", [&]{
		actualValue must equal(expectedValue);
	    });

	    it("must reject a negative match", [&]{
		[&]{ actualValue must_not equal(expectedValue); } must throw_exception;
	    });
	});

	describe("and the values are not equal", [&]{
	    char* expectedValue = (char*)"expectedValue";

	    it("must reject a positive match", [&]{
		[&]{ actualValue must equal(expectedValue); } must throw_exception;
	    });

	    it("must accept a negative match", [&]{
		actualValue must_not equal(expectedValue);
	    });
	});
    });
});

SPEC_END
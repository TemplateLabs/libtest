#include <map>
#include <set>

#include <test.h>

TEST_BEGIN(Contain)

describe("contain", [&]{
    std::string element0("element0");
    std::string element1("element1");

    describe("when the container is an STL vector", [&]{
        describe("which contains the element", [&]{
            std::vector<std::string> container {element0, element1};

	    it("must pass a positive match", [&]{
		container must contain(element1);
	    });

	    it("must reject a negative match", [&]{
		[&]{ container must_not contain(element1); } must throw_exception;
	    });
        });

        describe("which does not contain the element", [&]{
            std::vector<int> container;

	    it("must pass a negative match", [&]{
		container must_not contain(4);
	    });

	    it("must reject a positive match", [&]{
		[&]{ container must contain(4); } must throw_exception;
	    });
        });
    });

    describe("when the container is an STL map", [&]{
        describe("which contains the expected key", [&]{
            std::map<int, int> container {{5, 6}, {7,10}};

	    it("must pass a positive match", [&]{
		container must contain(5);
	    });

	    it("must reject a negative match", [&]{
		[&]{ container must_not contain(5); } must throw_exception;
	    });
        });

        describe("which does not contain the expected value", [&]{
            std::map<int, int> container;

	    it("must pass a negative match", [&]{
		container must_not contain(6);
	    });

	    it("must reject a positive match", [&]{
		[&]{ container must contain(6); } must throw_exception;
	    });
        });
    });

    describe("when the container is an STL set", [&]{
        describe("which contains the element", [&]{
            std::set<int> container {5, 7};

	    it("must pass a positive match", [&]{
		container must contain(7);
	    });

	    it("must reject a negative match", [&]{
		[&]{ container must_not contain(7); } must throw_exception;
	    });
        });

        describe("which does not contain the element", [&]{
            std::set<int> container;

	    it("must pass a negative match", [&]{
		container must_not contain(7);
	    });

	    it("must reject a positive match", [&]{
		[&]{ container must contain(7); } must throw_exception;
	    });
        });
    });

    describe("when the container is a C string", [&]{
        describe("which is null", [&]{
            char* container = NULL;

	    it("must reject a positive match", [&]{
		[&]{ container must contain("foo"); } must throw_exception;
	    });
        });

        describe("which contains the substring", [&]{
            char* container = (char*)"jack and jill";
            char* element = (char*)"jack";

	    it("must pass a positive match", [&]{
		container must contain(element);
	    });

	    it("must reject a negative match", [&]{
		[&]{ container must_not contain(element); } must throw_exception;
	    });
        });

        describe("which does not contain the substring", [&]{
            char* container = (char*)"batman and robin";
            char* element = (char*)"catwoman";

	    it("must reject a positive match", [&]{
		[&]{ container must contain(element); } must throw_exception;
	    });

	    it("must pass a negative match", [&]{
		container must_not contain(element);
	    });
        });
    });

    describe("when the container is a const C string", [&]{
        describe("which contains the substring", [&]{
            const char* container = (char*)"jack and jill";
            const char* element = (char*)"jack";

	    it("must pass a positive match", [&]{
		container must contain(element);
	    });

	    it("must reject a negative match", [&]{
		[&]{ container must_not contain(element); } must throw_exception;
	    });
        });

        describe("which does not contain the substring", [&]{
            const char* container = (char*)"batman and robin";
            const char* element = (char*)"catwoman";

	    it("must reject a positive match", [&]{
		[&]{ container must contain(element); } must throw_exception;
	    });

	    it("must pass a negative match", [&]{
		container must_not contain(element);
	    });
        });
    });
});

SPEC_END

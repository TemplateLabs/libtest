Testing all the things
======================

Do you have things to do, and code to test? Does C++ make your eyes bleed? If so,
then step right up, because you've come to the right place.

libtest is a C++11 based framework with a less-painful syntax. If you're
familiar with [Cedar](http://github.com/pivotal/cedar), or
[RSpec](http://rspec.info/), you'll feel right at home.

Example
-------

```cpp
#include <test/test.h>

BEGIN_TEST(MyClass)

describe("when hitchhiking", []{
    MyClass frood;

    it("must know where its towel is", []{
         frood.has_towel() must be_truthy;
    });

    it("must know the answer", []{
        frood.answer must equal(42);
    });
});

END_TEST
```

Alternatives
------------

- [Cedar](http://github.com/pivotal/cedar) is where I learned how to do matchers in C++
- [RSpec](http://rspec.info/) is the origin of matcher syntax
- [Bandit](http://banditcpp.org/) is one of the first frameworks to make use of C+11
- [Igloo](http://igloo-testing.org/) is for when you're stuck with a non-C++11 compiler

License
-------

Copyright 2014 Brandon Fosdick <bfoz@bfoz.net> and released under the BSD
license.

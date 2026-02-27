#include <doctest/doctest.h> // for filloss, ResultBuilder, toStream, toSt...

#include <string>           // for basic_string
#include <string_view>      // for basic_string_view
#include <syzygy2d/hello.h> // for Greeter

TEST_CASE("hello.cc: Greeter::greet")
{
    auto test = syzygy2d::Greeter{};
    CHECK_EQ(test.greet("Bob"), "Hello, Bob!");
    CHECK_EQ(test.greet("Sarah"), "Howdy, Sarah!");
    CHECK_EQ(test.greet("John"), "Hi, John!");
}
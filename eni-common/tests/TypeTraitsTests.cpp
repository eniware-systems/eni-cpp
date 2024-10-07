//
// Created by void on 10/7/24.
//

#include "catch2/catch_all.hpp"
#include "eni/type_traits.h"

void foo(int a, const char *b, const float &c) {
}

TEST_CASE("can extract all arguments", "[TypeTraits][function_traits]") {
    using traits = eni::function_traits<decltype(foo)>;

    REQUIRE(traits::ArgsCount == 3);

    using a0 = traits::arg<0>;
    using a1 = traits::arg<1>;
    using a2 = traits::arg<2>;

    REQUIRE(std::is_same_v<a0, int>);
    REQUIRE(std::is_same_v<a1, const char *>);
    REQUIRE(std::is_same_v<a2, const float &>);
}

//
// Created by mvonkeil on 22.11.22.
//

#include <catch2/catch_all.hpp>

#include <eni/util.h>

using namespace eni;

TEST_CASE("erase_if() works for std::set", "[Util]") {
    std::set x{1, 2, 3, 4, 5};
    const auto r = erase_if(x, [](auto i) { return i > 3; });
    REQUIRE(r == 2);
}
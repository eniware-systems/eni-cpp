//
// Created by mvonkeil on 22.11.22.
//

#include <catch2/catch_all.hpp>

#include <eni/algorithm.h>

using namespace eni;

TEST_CASE("erase_pointer() works for std::set", "[Algorithm]") {
    std::vector x{new int(1), new int(2), new int(3), new int(4)};
    const auto r = erase_pointer(x, x[1]);
    REQUIRE(r == 1);
}

#pragma ide diagnostic ignored "cppcoreguidelines-owning-memory"
TEST_CASE("erase_pointer() works for std::vector", "[Algorithm]") {
    auto *two = new int(2);

    std::vector x{new int(1), two, new int(3), new int(4), two, two};
    const auto r = erase_pointer(x, two);
    REQUIRE(r == 3);
}

TEST_CASE("for_each_tuple() is working", "[Algorithm]") {// NOLINT(*-function-cognitive-complexity)
    std::tuple<int, std::string, char> tuple{42, "foo", 'x'};

    size_t index = 0;

    eni::for_each_tuple(tuple, [&](auto &&value) {
        using type = std::decay_t<decltype(value)>;

        if (index == 0) {
            REQUIRE(std::is_same_v<type, int>);
        }

        if (index == 1) {
            REQUIRE(std::is_same_v<type, std::string>);
        }

        if (index == 2) {
            REQUIRE(std::is_same_v<type, char>);
        }

        index++;
    });

    REQUIRE(index == 3);
}

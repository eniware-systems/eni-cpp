//
// Created by mvonkeil on 22.11.22.
//

#include <catch2/catch_all.hpp>

#include <eni/memory.h>

using namespace eni;

TEST_CASE("make_unique_vector() works", "[Memory]") {
    auto vec = eni::make_unique_vector(
            std::make_unique<int>(1),
            std::make_unique<int>(2),
            std::make_unique<int>(3));

    REQUIRE(vec.size() == 3);
    REQUIRE(*vec[1].get() == 2);
}

TEST_CASE("make_unique_set() works", "[Memory]") {
    auto set = eni::make_unique_set(std::make_unique<int>(1));

    REQUIRE(set.size() == 1);
    REQUIRE(*set.begin()->get() == 1);
}
//
// Created by mvonkeil on 10/18/24.
//

#include <catch2/catch_all.hpp>

#include <eni/concepts.h>

#include <map>
#include <set>
#include <string>
#include <vector>

using namespace eni;

// We only do this in a TEST_CASE to make the test framework happy
TEST_CASE("Static assertions", "[Concepts]") {
    static_assert(container_type<std::vector<unsigned char>>);
    static_assert(container_type<std::string>);
    static_assert(container_type<std::set<int>>);
    static_assert(container_type<std::map<int, int>>);
}

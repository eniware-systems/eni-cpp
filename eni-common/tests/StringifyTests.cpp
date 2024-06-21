//
// Created by mvonkeil on 6/21/24.
//

#include <catch2/catch_all.hpp>

#include <eni/stringify.h>

TEST_CASE("can stringify std::vector", "[Stringify]") {
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8};

    auto result = eni::to_string(nums);
    REQUIRE(result == "[1, 2, 3, 4, 5, 6, 7, 8]");
}

TEST_CASE("can stringify nested std::vector", "[Stringify]") {
    std::vector<std::vector<int>> nums{{1, 2, 3}, {4, 5, 6}, {7}, {8}};

    auto result = eni::to_string(nums);
    REQUIRE(result == "[[1, 2, 3], [4, 5, 6], [7], [8]]");
}

TEST_CASE("can stringify std::map", "[Stringify]") {
    std::map<int, int> map = {{1, 1001}, {2, 2002}, {3, 3003}};

    auto result = eni::to_string(map);
    REQUIRE(result == "{1: 1001, 2: 2002, 3: 3003}");
}

TEST_CASE("can stringify std::variant", "[Stringify]") {
    std::variant<int, std::string> variant = 12345;
    auto result = eni::to_string(variant);
    REQUIRE(result == "12345");
}
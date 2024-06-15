//
// Created by mvonkeil on 22.11.22.
//

#include <catch2/catch_all.hpp>

#include <eni/iterator.h>

using namespace eni;

TEST_CASE("transform iterator is working", "[Iterator]") {
    std::vector in = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto quad = [](const int &i) {
        return i * i;
    };

    TransformIterator<int, int> beg(&in.front(), quad);
    const TransformIterator<int, int> end(&in.back(), quad);

    auto i = 0;
    while (beg != end) {
        auto v = *(beg++);
        REQUIRE(quad(in[i++]) == v);
    }
}

TEST_CASE("dereference iterator is working", "[Iterator]") {
    auto src = std::make_unique<int>(42);
    const DereferenceIterator it(&src);

    const auto &value = *it;
    REQUIRE(value == *src);

    *src = 1000;
    REQUIRE(value == *src);
}

TEST_CASE("dereference range is working", "[Iterator]") {
    std::vector<std::unique_ptr<int>> in;
    for (int i = 0; i < 42; ++i) {
        in.emplace_back(std::make_unique<int>(i));
    }

    const auto range = make_range(DereferenceIterator(&*in.begin()), DereferenceIterator(&*in.end()));
    const auto& copiedRange = range;

    int i=0;
    for (const auto val : copiedRange) {
        REQUIRE(val == *in[i++]);
    }
}
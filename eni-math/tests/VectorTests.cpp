//
// Created by void on 5/5/24.
//


#include <catch2/catch_all.hpp>
#include <catch2/catch_approx.hpp>

#include <eni/math.h>
#include <eni/math/Vec2.h>
#include <eni/math/Vec3.h>
#include <eni/math/Vec4.h>

using namespace eni;
using namespace eni::math;

TEST_CASE("data() is returning correct values", "[Math][Vector]") {
    Vec2 v2{1, 2};
    Vec3 v3{1, 2, 3};
    Vec4 v4{1, 2, 3, 4};

    REQUIRE(v2.data()[0] == 1);// NOLINT(*-pro-bounds-pointer-arithmetic)
    REQUIRE(v2.data()[1] == 2);// NOLINT(*-pro-bounds-pointer-arithmetic)

    REQUIRE(v3.data()[0] == 1);// NOLINT(*-pro-bounds-pointer-arithmetic)
    REQUIRE(v3.data()[1] == 2);// NOLINT(*-pro-bounds-pointer-arithmetic)
    REQUIRE(v3.data()[2] == 3);// NOLINT(*-pro-bounds-pointer-arithmetic)

    REQUIRE(v4.data()[0] == 1);// NOLINT(*-pro-bounds-pointer-arithmetic)
    REQUIRE(v4.data()[1] == 2);// NOLINT(*-pro-bounds-pointer-arithmetic)
    REQUIRE(v4.data()[2] == 3);// NOLINT(*-pro-bounds-pointer-arithmetic)
    REQUIRE(v4.data()[3] == 4);// NOLINT(*-pro-bounds-pointer-arithmetic)
}
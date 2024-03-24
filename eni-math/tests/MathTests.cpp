#include <eni/build_config.h>

#include <catch2/catch_all.hpp>
#include <catch2/catch_approx.hpp>

#include <eni/math.h>

using namespace eni;

TEST_CASE("approximate equality check is working", "[Math]") {
    constexpr real a = 0.1f;
    constexpr real b = 0.01f;

    REQUIRE(math::is_equal_approx(a, b, 0.1f));
    REQUIRE(!math::is_equal_approx(a, b, 0.01f));
}

TEST_CASE("can convert between degrees and radians", "[Math]") {
    REQUIRE(math::deg2Rad(180.0f) == Catch::Approx(math::Pi));
    REQUIRE(math::rad2Deg(math::Pi) == Catch::Approx(180.0f));
}

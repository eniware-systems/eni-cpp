#include <catch2/catch_all.hpp>
#include <catch2/catch_approx.hpp>

#include <eni/math.h>
#include <eni/math/BoundingBox.h>

using namespace eni;
using namespace eni::math;

TEST_CASE("Can create BoundingBox", "[Math][BoundingBox]") {
    BoundingBoxi bbox{};

    bbox.setMinimum(50, 50, 50);
    bbox.setMaximum(100, 100, 100);
    auto expectedCenter = Vec3i(75, 75, 75);

    REQUIRE(bbox.getCenter() == expectedCenter);
}

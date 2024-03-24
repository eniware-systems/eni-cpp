#include <catch2/catch_all.hpp>
#include <catch2/catch_approx.hpp>

#include <eni/math.h>
#include <eni/math/Matrix4.h>

using namespace eni;
using namespace eni::math;

TEST_CASE("can convert from and to Euler coordinates", "[Math][Quaternion]") {
    {
        Quaternion q;
        q.setFromEulerAngles(0, 0, 0);
        Quaternion qr(0, 0, 0, 1);

        REQUIRE(qr == q);
    }

    {
        Quaternion q;
        q.setFromAxisAngle(Vec3r(1, 1, 0), math::deg2Rad(45));
        Quaternion qr(0.382683, 0.382683, 0, 0.92388);
        REQUIRE(qr == q);
    }

    {
        Quaternion q;
        real yaw = math::deg2Rad(-90);
        real pitch = math::deg2Rad(52);
        real roll = math::deg2Rad(34);
        q.setFromEulerAngles(yaw, pitch, roll);

        REQUIRE(q.getYaw() == Catch::Approx(yaw));
        REQUIRE(q.getPitch() == Catch::Approx(pitch));
        REQUIRE(q.getRoll() == Catch::Approx(roll));
    }
}

TEST_CASE("can convert to rotation matrix", "[Math][Quaternion]") {

    Quaternion q(1, 2, 3, 4);

    Matrix4 mat;
    Matrix4 rmat(
            -25, 28, -10, 0,
            -20, -19, 20, 0,
            22, 4, -9, 0,
            0, 0, 0, 1);

    q.toRotationMatrix(mat);

    REQUIRE(mat == rmat);
}

TEST_CASE("can get conjugated quaternion", "[Math][Quaternion]") {
    Quaternion q(1, 2, 3, 4);
    Quaternion eq(1, -2, -3, -4);
    Quaternion c = q.conjugated();

    REQUIRE(eq == c);
}

TEST_CASE("can get normalized quaternion", "[Math][Quaternion]") {
    Quaternion q(1, 4, 4, -4);
    REQUIRE(q.getLength() == Catch::Approx(7));
}

TEST_CASE("can get inverted quaternion", "[Math][Quaternion]") {
    Quaternion q(1, 2, 3, 4);
    Quaternion iq = q.inverted();
    Quaternion expected(-0.0333f, -0.0666f, -0.1f, 0.133f);

    REQUIRE(iq == expected);

    Quaternion iq2 = iq.inverted();

    REQUIRE(iq2 == q);
}

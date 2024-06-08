#include <eni/math.h>
#include <eni/math/Matrix4.h>
#include <eni/math/Quaternion.h>

namespace eni::math {

constexpr auto QuaternionEqualEpsilon = 0.1f;

Quaternion::Quaternion(real x, real y, real z, real w)
    : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(const Vec3r &xaxis, const Vec3r &yaxis,
                       const Vec3r &zaxis) {
    setFromAxes(xaxis, yaxis, zaxis);
}

void Quaternion::set(real x, real y, real z, real w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion &Quaternion::operator*=(const Quaternion &other) {
    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.

    const auto newX = w * other.x + x * other.w + y * other.z - z * other.y;
    const auto newY = w * other.y + y * other.w + z * other.x - x * other.z;
    const auto newZ = w * other.z + z * other.w + x * other.y - y * other.x;
    const auto newW = w * other.w - x * other.x - y * other.y - z * other.z;
    x = newX;
    y = newY;
    z = newZ;
    w = newW;

    return *this;
}

Quaternion &Quaternion::operator/=(real scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

Quaternion Quaternion::operator/(real scalar) const {
    Quaternion q(*this);
    q /= scalar;
    return q;
}

Quaternion Quaternion::operator*(const Quaternion &other) const {
    Quaternion q(*this);
    q *= other;
    return q;
}

void Quaternion::setToLookAt(const Vec3r &dir, const Vec3r &aup) {
    auto forward = dir.normalized();
    auto right = aup.cross(forward).normalize();
    auto up = forward.cross(right);

    const auto &m00 = right.x;
    const auto &m01 = right.y;
    const auto &m02 = right.z;
    const auto &m10 = up.x;
    const auto &m11 = up.y;
    const auto &m12 = up.z;
    const auto &m20 = forward.x;
    const auto &m21 = forward.y;
    const auto &m22 = forward.z;

    const auto num8 = (m00 + m11) + m22;
    Quaternion &quaternion = *this;
    if (num8 > 0.0f) {
        auto num = std::sqrt(num8 + 1.0f);
        quaternion.w = num * 0.5f;
        num = 0.5f / num;
        quaternion.x = (m12 - m21) * num;
        quaternion.y = (m20 - m02) * num;
        quaternion.z = (m01 - m10) * num;
        return;
    }
    if ((m00 >= m11) && (m00 >= m22)) {
        const auto num7 = std::sqrt(1.0f + m00 - m11 - m22);
        const auto num4 = 0.5f / num7;
        quaternion.x = 0.5f * num7;
        quaternion.y = (m01 + m10) * num4;
        quaternion.z = (m02 + m20) * num4;
        quaternion.w = (m12 - m21) * num4;
        return;
    }
    if (m11 > m22) {
        const auto num6 = std::sqrt(1.0f + m11 - m00 - m22);
        const auto num3 = 0.5f / num6;
        quaternion.x = (m10 + m01) * num3;
        quaternion.y = 0.5f * num6;
        quaternion.z = (m21 + m12) * num3;
        quaternion.w = (m20 - m02) * num3;
        return;
    }
    const auto num5 = std::sqrt(1.0f + m22 - m00 - m11);
    const auto num2 = 0.5f / num5;
    quaternion.x = (m20 + m02) * num2;
    quaternion.y = (m21 + m12) * num2;
    quaternion.z = 0.5f * num5;
    quaternion.w = (m01 - m10) * num2;
}

void Quaternion::setFromAxisAngle(const Vec3r &axis, real angle) {
    const auto halfAngle = angle * 0.5f;
    const auto s = std::sin(halfAngle);
    x = axis.x * s;
    y = axis.y * s;
    z = axis.z * s;
    w = std::cos(halfAngle);
}

void Quaternion::setFromRotationMatrix(const Matrix4 &matrix) {
    // Works!
    const auto trace = matrix[0][0] + matrix[1][1] +
                       matrix[2][2];

    if (trace > 0) {// I changed M_EPSILON to 0
        float s = 0.5f / sqrtf(trace + 1.0f);
        w = 0.25f / s;
        x = (matrix[1][2] - matrix[2][1]) * s;
        y = (matrix[2][0] - matrix[0][2]) * s;
        z = (matrix[0][1] - matrix[1][0]) * s;
    } else {
        if (matrix[0][0] > matrix[1][1] && matrix[0][0] > matrix[2][2]) {
            float s = 2.0f * sqrtf(1.0f + matrix[0][0] - matrix[1][1] - matrix[2][2]);
            w = (matrix[1][2] - matrix[2][1]) / s;
            x = 0.25f * s;
            y = (matrix[1][0] + matrix[0][1]) / s;
            z = (matrix[2][0] + matrix[0][2]) / s;
        } else if (matrix[1][1] > matrix[2][2]) {
            float s = 2.0f * sqrtf(1.0f + matrix[1][1] - matrix[0][0] - matrix[2][2]);
            w = (matrix[2][0] - matrix[0][2]) / s;
            x = (matrix[1][0] + matrix[0][1]) / s;
            y = 0.25f * s;
            z = (matrix[2][1] + matrix[1][2]) / s;
        } else {
            float s = 2.0f * sqrtf(1.0f + matrix[2][2] - matrix[0][0] - matrix[1][1]);
            w = (matrix[0][1] - matrix[1][0]) / s;
            x = (matrix[2][0] + matrix[0][2]) / s;
            y = (matrix[2][1] + matrix[1][2]) / s;
            z = 0.25f * s;
        }
    }
}

void Quaternion::setFromAxes(const Vec3r &a0, const Vec3r &a1, const Vec3r &a2) {
    Matrix4 mat;

    mat[0][0] = a0.x;
    mat[1][0] = a0.y;
    mat[2][0] = a0.z;

    mat[0][1] = a1.x;
    mat[1][1] = a1.y;
    mat[2][1] = a1.z;

    mat[0][2] = a2.x;
    mat[1][2] = a2.y;
    mat[2][2] = a2.z;

    setFromRotationMatrix(mat);
}

void Quaternion::toRotationMatrix(Matrix4 &mat) const {
    // source:
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
    // (first equation shown on page. Uses different signs!)

    // also:
    // https://www.fd.cvut.cz/personal/voracsar/GeometriePG/PGR020/matrix2quaternions.pdf
    // chp. 3

    const auto _2xx = 2 * x * x;
    const auto _2yy = 2 * y * y;
    const auto _2zz = 2 * z * z;

    const auto _2xy = 2 * x * y;
    const auto _2xz = 2 * x * z;
    const auto _2xw = 2 * x * w;
    const auto _2yw = 2 * y * w;
    const auto _2yz = 2 * y * z;
    const auto _2zw = 2 * z * w;

    auto *m = mat.data();

    m[0] = 1.0f - _2yy - _2zz;
    m[4] = _2xy + _2zw;
    m[8] = _2xz - _2yw;

    m[1] = _2xy - _2zw;
    m[5] = 1.0f - _2xx - _2zz;
    m[9] = _2yz + _2xw;

    m[2] = _2xz + _2yw;
    m[6] = _2yz - _2xw;
    m[10] = 1.0f - _2xx - _2yy;
}

Vec3r Quaternion::operator*(const Vec3r &other) const {
    // See
    // https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/
    auto tmp2 = conjugated();
    Quaternion tmp(other.x, other.y, other.z, 0);

    tmp2 = tmp * tmp2;
    tmp2 = *this * tmp2;

    return Vec3(tmp2.x, tmp2.y, tmp2.z);
}

void Quaternion::setFromEulerAngles(real yaw, real pitch, real roll) {
    // Expects radians.
    const auto hr = roll * 0.5f;
    const auto shr = std::sin(hr);
    const auto chr = std::cos(hr);
    const auto hp = pitch * 0.5f;
    const auto shp = std::sin(hp);
    const auto chp = std::cos(hp);
    const auto hy = yaw * 0.5f;
    const auto shy = std::sin(hy);
    const auto chy = std::cos(hy);
    const auto chyShp = chy * shp;
    const auto shyChp = shy * chp;
    const auto chyChp = chy * chp;
    const auto shyShp = shy * shp;

    x = (chyShp * chr) +
        (shyChp * shr);// cos(yaw/2) * sin(pitch/2) * cos(roll/2) + sin(yaw/2) *
                       // cos(pitch/2) * sin(roll/2)
    y = (shyChp * chr) -
        (chyShp * shr);// sin(yaw/2) * cos(pitch/2) * cos(roll/2) - cos(yaw/2) *
                       // sin(pitch/2) * sin(roll/2)
    z = (chyChp * shr) -
        (shyShp * chr);// cos(yaw/2) * cos(pitch/2) * sin(roll/2) - sin(yaw/2) *
                       // sin(pitch/2) * cos(roll/2)
    w = (chyChp * chr) +
        (shyShp * shr);// cos(yaw/2) * cos(pitch/2) * cos(roll/2) + sin(yaw/2) *
                       // sin(pitch/2) * sin(roll/2)
}

void Quaternion::toAxes(Vec3r &a0, Vec3r &a1, Vec3r &a2) const {
    Matrix4 rot;
    toRotationMatrix(rot);
    a0.x = rot[0][0];
    a0.y = rot[0][1];
    a0.z = rot[0][2];

    a0.x = rot[1][0];
    a0.y = rot[1][1];
    a0.z = rot[1][2];

    a0.x = rot[2][0];
    a0.y = rot[2][1];
    a0.z = rot[2][2];
}

Quaternion Quaternion::getRotationTo(const Vec3r &origin, const Vec3r &dest,
                                     const Vec3r &fallbackAxis) {
    // Based on Stan Melax's article in Game Programming Gems
    Quaternion q;
    // Copy, since cannot modify local
    const auto v0 = origin.normalized();
    const auto v1 = dest.normalized();

    const auto d = v0.dot(v1);
    // If dot == 1, vectors are the same
    if (d >= 1.0f) {
        return Identity;
    }

    if (d < (1e-6f - 1.0f)) {
        if (fallbackAxis != Vec3r::Zero) {
            // rotate 180 degrees about the fallback axis
            q.setFromAxisAngle(fallbackAxis, Pi);
        } else {
            // Generate an axis
            Vec3r axis = Vec3r::UnitX.cross(origin);
            if (axis.length() < Epsilon) {// pick another if colinear
                axis = Vec3r::UnitY.cross(origin);
            }
            axis.normalize();
            q.setFromAxisAngle(axis, Pi);
        }
    } else {
        const auto s = std::sqrt((1 + d) * 2);
        const auto invs = static_cast<real>(1.0 / s);
        const auto c = v0.cross(v1);

        q.x = c.x * invs;
        q.y = c.y * invs;
        q.z = c.z * invs;
        q.w = s * 0.5f;
        q.normalize();
    }
    return q;
}

void Quaternion::normalize() {
    const auto factor = static_cast<real>(1.0 / getLength());
    *this *= factor;
}

Quaternion Quaternion::normalized() const {
    Quaternion q(*this);
    q.normalize();
    return q;
}

void Quaternion::conjugate() {
    x = -x;
    y = -y;
    z = -z;
}

Quaternion Quaternion::conjugated() const {
    Quaternion q(*this);
    q.conjugate();
    return q;
}

void Quaternion::invert() {
    const auto d = x * x + y * y + z * z + w * w;
    set(-x / d, -y / d, -z / d, w / d);
}

Quaternion Quaternion::inverted() const {
    Quaternion q(*this);
    q.invert();
    return q;
}

real Quaternion::getLength() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

bool Quaternion::operator==(const Quaternion &other) const {
    return is_equal_approx(std::abs(x), std::abs(other.x),
                           QuaternionEqualEpsilon) &&
           is_equal_approx(std::abs(y), std::abs(other.y),
                           QuaternionEqualEpsilon) &&
           is_equal_approx(std::abs(z), std::abs(other.z),
                           QuaternionEqualEpsilon) &&
           is_equal_approx(std::abs(w), std::abs(other.w), QuaternionEqualEpsilon);
}

int8 Quaternion::getGimbalPole() const {
    const auto t = y * x + z * w;
    constexpr auto threshold = 0.499;

    if (t < -threshold) {
        return static_cast<int8>(t > threshold ? 1 : -1);
    }
    return static_cast<int8>(t > threshold ? 1 : 0);
}

real Quaternion::getYaw() const {
    return getGimbalPole() == 0
                   ? std::atan2(2.0f * (y * w + x * z), 1.0f - 2.0f * (y * y + x * x))
                   : 0.0f;
}

real Quaternion::getPitch() const {
    const auto pole = getGimbalPole();
    return pole == 0 ? std::asin(clamp(2.0f * (w * x - z * y), -1.0f, 1.0f))
                     : static_cast<real>(pole) * math::Pi * 0.5f;
}

real Quaternion::getRoll() const {
    const auto pole = getGimbalPole();
    return pole == 0
                   ? std::atan2(2.0f * (w * z + y * x), 1.0f - 2.0f * (x * x + z * z))
                   : static_cast<real>(pole) * 2.0f * std::atan2(y, w);
}

const Quaternion Quaternion::Identity(0, 0, 0, 1);

}// namespace eni::math

#include <cmath>
#include <ostream>

namespace eni::math {

std::ostream &operator<<(std::ostream &s, const Quaternion &v) {
    s << "Quaternion(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return s;
}

}// namespace eni::math
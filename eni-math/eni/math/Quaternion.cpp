#include <eni/math.h>
#include <eni/math/Matrix4.h>
#include <eni/math/Quaternion.h>

namespace eni::math {

#define QUATERNION_EQUAL_EPSILON 0.1f

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

    float newX = w * other.x + x * other.w + y * other.z - z * other.y;
    float newY = w * other.y + y * other.w + z * other.x - x * other.z;
    float newZ = w * other.z + z * other.w + x * other.y - y * other.x;
    float newW = w * other.w - x * other.x - y * other.y - z * other.z;
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
    Vec3r forward = dir.normalized();
    Vec3r right = aup.cross(forward).normalize();
    Vec3r up = forward.cross(right);

    float &m00 = right.x;
    float &m01 = right.y;
    float &m02 = right.z;
    float &m10 = up.x;
    float &m11 = up.y;
    float &m12 = up.z;
    float &m20 = forward.x;
    float &m21 = forward.y;
    float &m22 = forward.z;

    float num8 = (m00 + m11) + m22;
    Quaternion &quaternion = *this;
    if (num8 > 0.0f) {
        auto num = (float) std::sqrt(num8 + 1.0f);
        quaternion.w = num * 0.5f;
        num = 0.5f / num;
        quaternion.x = (m12 - m21) * num;
        quaternion.y = (m20 - m02) * num;
        quaternion.z = (m01 - m10) * num;
        return;
    }
    if ((m00 >= m11) && (m00 >= m22)) {
        auto num7 = (float) std::sqrt(((1.0f + m00) - m11) - m22);
        float num4 = 0.5f / num7;
        quaternion.x = 0.5f * num7;
        quaternion.y = (m01 + m10) * num4;
        quaternion.z = (m02 + m20) * num4;
        quaternion.w = (m12 - m21) * num4;
        return;
    }
    if (m11 > m22) {
        auto num6 = (float) std::sqrt(((1.0f + m11) - m00) - m22);
        float num3 = 0.5f / num6;
        quaternion.x = (m10 + m01) * num3;
        quaternion.y = 0.5f * num6;
        quaternion.z = (m21 + m12) * num3;
        quaternion.w = (m20 - m02) * num3;
        return;
    }
    auto num5 = (float) std::sqrt(((1.0f + m22) - m00) - m11);
    float num2 = 0.5f / num5;
    quaternion.x = (m20 + m02) * num2;
    quaternion.y = (m21 + m12) * num2;
    quaternion.z = 0.5f * num5;
    quaternion.w = (m01 - m10) * num2;
}

void Quaternion::setFromAxisAngle(const Vec3r &axis, real angle) {
    // Works!
    real halfAngle = angle * 0.5f;
    float s = std::sin(halfAngle);
    x = axis.x * s;
    y = axis.y * s;
    z = axis.z * s;
    w = std::cos(halfAngle);
}

void Quaternion::setFromRotationMatrix(const Matrix4 &a) {
    // Works!
    float trace = a[0][0] + a[1][1] +
                  a[2][2];// I removed + 1.0f; see discussion with Ethan

    if (trace > 0) {// I changed M_EPSILON to 0
        float s = 0.5f / sqrtf(trace + 1.0f);
        w = 0.25f / s;
        x = (a[1][2] - a[2][1]) * s;
        y = (a[2][0] - a[0][2]) * s;
        z = (a[0][1] - a[1][0]) * s;
    } else {
        if (a[0][0] > a[1][1] && a[0][0] > a[2][2]) {
            float s = 2.0f * sqrtf(1.0f + a[0][0] - a[1][1] - a[2][2]);
            w = (a[1][2] - a[2][1]) / s;
            x = 0.25f * s;
            y = (a[1][0] + a[0][1]) / s;
            z = (a[2][0] + a[0][2]) / s;
        } else if (a[1][1] > a[2][2]) {
            float s = 2.0f * sqrtf(1.0f + a[1][1] - a[0][0] - a[2][2]);
            w = (a[2][0] - a[0][2]) / s;
            x = (a[1][0] + a[0][1]) / s;
            y = 0.25f * s;
            z = (a[2][1] + a[1][2]) / s;
        } else {
            float s = 2.0f * sqrtf(1.0f + a[2][2] - a[0][0] - a[1][1]);
            w = (a[0][1] - a[1][0]) / s;
            x = (a[2][0] + a[0][2]) / s;
            y = (a[2][1] + a[1][2]) / s;
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

    // Works!

    // source:
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
    // (first equation shown on page. Uses different signs!)

    // also:
    // https://www.fd.cvut.cz/personal/voracsar/GeometriePG/PGR020/matrix2quaternions.pdf
    // chp. 3

    const real _2xx = 2 * x * x;
    const real _2yy = 2 * y * y;
    const real _2zz = 2 * z * z;

    const real _2xy = 2 * x * y;
    const real _2xz = 2 * x * z;
    const real _2xw = 2 * x * w;
    const real _2yw = 2 * y * w;
    const real _2yz = 2 * y * z;
    const real _2zw = 2 * z * w;

    real *m = mat.getRawPointer();

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
    Quaternion tmp2 = conjugated();
    Quaternion tmp(other.x, other.y, other.z, 0);

    tmp2 = tmp * tmp2;
    tmp2 = *this * tmp2;

    return Vec3(tmp2.x, tmp2.y, tmp2.z);
}

void Quaternion::setFromEulerAngles(real yaw, real pitch, real roll) {
    // Expects radians.
    real hr = roll * 0.5f;
    real shr = std::sin(hr);
    real chr = std::cos(hr);
    real hp = pitch * 0.5f;
    real shp = std::sin(hp);
    real chp = std::cos(hp);
    real hy = yaw * 0.5f;
    real shy = std::sin(hy);
    real chy = std::cos(hy);
    real chyShp = chy * shp;
    real shyChp = shy * chp;
    real chyChp = chy * chp;
    real shyShp = shy * shp;

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
    Vec3r v0 = origin;
    Vec3r v1 = dest;
    v0.normalize();
    v1.normalize();

    real d = v0.dot(v1);
    // If dot == 1, vectors are the same
    if (d >= 1.0f) {
        return Quaternion::IDENTITY;
    }

    if (d < (1e-6f - 1.0f)) {
        if (fallbackAxis != Vec3r::Zero) {
            // rotate 180 degrees about the fallback axis
            q.setFromAxisAngle(fallbackAxis, math::Pi);
        } else {
            // Generate an axis
            Vec3r axis = Vec3r::UnitX.cross(origin);
            if (axis.length() < math::Epsilon) {// pick another if colinear
                axis = Vec3r::UnitY.cross(origin);
}
            axis.normalize();
            q.setFromAxisAngle(axis, math::Pi);
        }
    } else {
        real s = static_cast<real>(std::sqrt((1 + d) * 2));
        real invs = static_cast<real>(1.0 / s);

        Vec3r c = v0.cross(v1);

        q.x = c.x * invs;
        q.y = c.y * invs;
        q.z = c.z * invs;
        q.w = s * 0.5f;
        q.normalize();
    }
    return q;
}

void Quaternion::normalize() {
    real factor = static_cast<real>(1.0 / getLength());
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
    real d = x * x + y * y + z * z + w * w;
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
    return math::is_equal_approx(std::abs(x), std::abs(other.x),
                        QUATERNION_EQUAL_EPSILON) &&
           math::is_equal_approx(std::abs(y), std::abs(other.y),
                        QUATERNION_EQUAL_EPSILON) &&
           math::is_equal_approx(std::abs(z), std::abs(other.z),
                        QUATERNION_EQUAL_EPSILON) &&
           math::is_equal_approx(std::abs(w), std::abs(other.w), QUATERNION_EQUAL_EPSILON);
}

int8 Quaternion::getGimbalPole() const {
    real t = y * x + z * w;
    return static_cast<int8>(t > 0.499 ? 1 : (t < -0.499 ? -1 : 0));
}

real Quaternion::getYaw() const {
    return getGimbalPole() == 0
                   ? std::atan2(2.0f * (y * w + x * z), 1.0f - 2.0f * (y * y + x * x))
                   : 0.0f;
}

real Quaternion::getPitch() const {
    int8 pole = getGimbalPole();
    return pole == 0 ? (float) std::asin(
                               math::clamp(2.0f * (w * x - z * y), -1.0f, 1.0f))
                     : static_cast<real>(pole) * math::Pi * 0.5f;
}

real Quaternion::getRoll() const {
    int8 pole = getGimbalPole();
    return pole == 0
                   ? std::atan2(2.0f * (w * z + y * x), 1.0f - 2.0f * (x * x + z * z))
                   : static_cast<real>(pole) * 2.0f * std::atan2(y, w);
}

const Quaternion Quaternion::IDENTITY(0, 0, 0, 1);

} // namespace eni::math

#include <cmath>
#include <ostream>

namespace eni::math {

std::ostream &operator<<(std::ostream &s, const Quaternion &v) {
    s << "Quaternion(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return s;
}

} // namespace eni::math
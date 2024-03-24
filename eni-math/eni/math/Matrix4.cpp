#include <eni/math.h>
#include <eni/math/Matrix4.h>

namespace eni::math {

Matrix4::Matrix4(real a00, real a10, real a20, real a30, real a01, real a11,
                 real a21, real a31, real a02, real a12, real a22, real a32,
                 real a03, real a13, real a23, real a33) {
    a[0] = a00;
    a[1] = a01;
    a[2] = a02;
    a[3] = a03;
    a[4] = a10;
    a[5] = a11;
    a[6] = a12;
    a[7] = a13;
    a[8] = a20;
    a[9] = a21;
    a[10] = a22;
    a[11] = a23;
    a[12] = a30;
    a[13] = a31;
    a[14] = a32;
    a[15] = a33;
}

Matrix4::Matrix4(const Vec4r &c0, const Vec4r &c1, const Vec4r &c2,
                 const Vec4r &c3) {
    a[0] = c0[0];
    a[1] = c0[1];
    a[2] = c0[2];
    a[3] = c0[3];
    a[4] = c1[0];
    a[5] = c1[1];
    a[6] = c1[2];
    a[7] = c1[3];
    a[8] = c2[0];
    a[9] = c2[1];
    a[10] = c2[2];
    a[11] = c2[3];
    a[12] = c3[0];
    a[13] = c3[1];
    a[14] = c3[2];
    a[15] = c3[3];
}

Matrix4::Matrix4(const Matrix4 &other) { this->operator=(other); }

Matrix4 &Matrix4::operator=(const Matrix4 &other) {
    std::copy(&other.a[0], &other.a[16], &a[0]);
    return *this;
}

real *Matrix4::operator[](size_t column) { return &a[column * 4]; }

const real *Matrix4::operator[](size_t column) const { return &a[column * 4]; }

real &Matrix4::at(size_t column, size_t row) { return a[column * 4 + row]; }

real Matrix4::at(size_t column, size_t row) const { return a[column * 4 + row]; }

void Matrix4::setToProjection(real near, real far, real fov, real aspectRatio) {
    this->operator=(Matrix4::ID);

    real fd = (real) (1.0f / std::tan((fov * (math::Pi / 180)) / 2.0f));
    real a1 = (near + far) / (near - far);
    real a2 = (2.0f * far * near) / (near - far);

    a[0 * 4 + 0] = fd / aspectRatio;
    a[0 * 4 + 1] = 0;
    a[0 * 4 + 2] = 0;
    a[0 * 4 + 3] = 0;
    a[1 * 4 + 0] = 0;
    a[1 * 4 + 1] = fd;
    a[1 * 4 + 2] = 0;
    a[1 * 4 + 3] = 0;
    a[2 * 4 + 0] = 0;
    a[2 * 4 + 1] = 0;
    a[2 * 4 + 2] = a1;
    a[2 * 4 + 3] = -1;
    a[3 * 4 + 0] = 0;
    a[3 * 4 + 1] = 0;
    a[3 * 4 + 2] = a2;
    a[3 * 4 + 3] = 0;
}

void Matrix4::setToOrtho(real left, real right, real bottom, real top,
                         real near, real far) {
    this->operator=(Matrix4::ID);

    real xOrth = 2.0f / (right - left);
    real yOrth = 2.0f / (top - bottom);
    real zOrth = -2.0f / (far - near);
    real tx = -(right + left) / (right - left);
    real ty = -(top + bottom) / (top - bottom);
    real tz = -(far + near) / (far - near);

    a[0 * 4 + 0] = xOrth;
    a[0 * 4 + 1] = 0;
    a[0 * 4 + 2] = 0;
    a[0 * 4 + 3] = 0;
    a[1 * 4 + 0] = 0;
    a[1 * 4 + 1] = yOrth;
    a[1 * 4 + 2] = 0;
    a[1 * 4 + 3] = 0;
    a[2 * 4 + 0] = 0;
    a[2 * 4 + 1] = 0;
    a[2 * 4 + 2] = zOrth;
    a[2 * 4 + 3] = 0;
    a[3 * 4 + 0] = tx;
    a[3 * 4 + 1] = ty;
    a[3 * 4 + 2] = tz;
    a[3 * 4 + 3] = 1;
}

void Matrix4::setToLookAt(const Vec3r &direction, const Vec3r &up) {

    this->operator=(Matrix4::ID);

    Vec3r z = direction.normalized();
    Vec3r x = z.cross(up).normalize();
    Vec3r y = x.cross(z);
    y.normalize();

    a[0 * 4 + 0] = x.x;
    a[1 * 4 + 0] = x.y;
    a[2 * 4 + 0] = x.z;
    a[0 * 4 + 1] = y.x;
    a[1 * 4 + 1] = y.y;
    a[2 * 4 + 1] = y.z;
    a[0 * 4 + 2] = -z.x;
    a[1 * 4 + 2] = -z.y;
    a[2 * 4 + 2] = -z.z;
}

Matrix4 Matrix4::operator*(const Matrix4 &other) const {
    Matrix4 result = Matrix4::ZERO;
    for (size_t r = 0; r < 4; r++) {
        for (size_t c = 0; c < 4; c++) {
            result.a[c * 4 + r] = a[static_cast<size_t>(0 * 4) + r] * other.a[c * 4 + 0] +
                                  a[static_cast<size_t>(1 * 4) + r] * other.a[c * 4 + 1] +
                                  a[static_cast<size_t>(2 * 4) + r] * other.a[c * 4 + 2] +
                                  a[static_cast<size_t>(3 * 4) + r] * other.a[c * 4 + 3];
        }
    }
    return result;
}

Matrix4 &Matrix4::operator*=(const Matrix4 &other) {
    this->operator=(*this * other);
    return *this;
}

void Matrix4::apply(Vec3r &v) const {
    real w = 1.0f / (v.x * a[0 * 4 + 3] + v.y * a[1 * 4 + 3] +
                     v.z * a[2 * 4 + 3] + a[3 * 4 + 3]);

    v.set((v.x * a[0 * 4 + 0] + v.y * a[1 * 4 + 0] + v.z * a[2 * 4 + 0] +
           a[3 * 4 + 0]) *
                  w,
          (v.x * a[0 * 4 + 1] + v.y * a[1 * 4 + 1] + v.z * a[2 * 4 + 1] +
           a[3 * 4 + 1]) *
                  w,
          (v.x * a[0 * 4 + 2] + v.y * a[1 * 4 + 2] + v.z * a[2 * 4 + 2] +
           a[3 * 4 + 2]) *
                  w);
}

void Matrix4::apply(Vec4r &v) const {
    v.set((v.x * a[0 * 4 + 0] + v.y * a[1 * 4 + 0] + v.z * a[2 * 4 + 0] +
           v.w * a[3 * 4 + 0]),
          (v.x * a[0 * 4 + 1] + v.y * a[1 * 4 + 1] + v.z * a[2 * 4 + 1] +
           v.w * a[3 * 4 + 1]),
          (v.x * a[0 * 4 + 2] + v.y * a[1 * 4 + 2] + v.z * a[2 * 4 + 2] +
           v.w * a[3 * 4 + 2]),
          (v.x * a[0 * 4 + 3] + v.y * a[1 * 4 + 3] + v.z * a[2 * 4 + 3] +
           v.w * a[3 * 4 + 3]));
}

bool Matrix4::operator==(const Matrix4 &other) const {
    for (uint8 i = 0; i < 16; ++i) {
        if (!math::is_equal_approx(a[i], other.a[i])) {
            return false;
        }
    }
    return true;
}

inline real getCofactor(real m0, real m1, real m2, real m3, real m4, real m5,
                        real m6, real m7, real m8) {
    return m0 * (m4 * m8 - m5 * m7) - m1 * (m3 * m8 - m5 * m6) +
           m2 * (m3 * m7 - m4 * m6);
}

Matrix4 &Matrix4::invert() {
    real *m = &a[0];

    // get cofactors of minor matrices
    real cofactor0 =
            getCofactor(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]);
    real cofactor1 =
            getCofactor(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]);
    real cofactor2 =
            getCofactor(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]);
    real cofactor3 =
            getCofactor(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);

    // get determinant
    real determinant = getDeterminant();

    if (math::is_equal_approx(determinant, 0, math::Epsilon)) {
        this->operator=(ID);
        return *this;
    }

    // get rest of cofactors for adj(M)
    real cofactor4 =
            getCofactor(m[1], m[2], m[3], m[9], m[10], m[11], m[13], m[14], m[15]);
    real cofactor5 =
            getCofactor(m[0], m[2], m[3], m[8], m[10], m[11], m[12], m[14], m[15]);
    real cofactor6 =
            getCofactor(m[0], m[1], m[3], m[8], m[9], m[11], m[12], m[13], m[15]);
    real cofactor7 =
            getCofactor(m[0], m[1], m[2], m[8], m[9], m[10], m[12], m[13], m[14]);

    real cofactor8 =
            getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[13], m[14], m[15]);
    real cofactor9 =
            getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[12], m[14], m[15]);
    real cofactor10 =
            getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[12], m[13], m[15]);
    real cofactor11 =
            getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[12], m[13], m[14]);

    real cofactor12 =
            getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[9], m[10], m[11]);
    real cofactor13 =
            getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[8], m[10], m[11]);
    real cofactor14 =
            getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[8], m[9], m[11]);
    real cofactor15 =
            getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);

    // build inverse matrix = adj(M) / det(M)
    // adjugate of M is the transpose of the cofactor matrix of M
    real invDeterminant = 1.0f / determinant;
    m[0] = invDeterminant * cofactor0;
    m[1] = -invDeterminant * cofactor4;
    m[2] = invDeterminant * cofactor8;
    m[3] = -invDeterminant * cofactor12;

    m[4] = -invDeterminant * cofactor1;
    m[5] = invDeterminant * cofactor5;
    m[6] = -invDeterminant * cofactor9;
    m[7] = invDeterminant * cofactor13;

    m[8] = invDeterminant * cofactor2;
    m[9] = -invDeterminant * cofactor6;
    m[10] = invDeterminant * cofactor10;
    m[11] = -invDeterminant * cofactor14;

    m[12] = -invDeterminant * cofactor3;
    m[13] = invDeterminant * cofactor7;
    m[14] = -invDeterminant * cofactor11;
    m[15] = invDeterminant * cofactor15;

    return *this;
}

real Matrix4::getDeterminant() const {
    return (a[3 * 4 + 2] * a[2 * 4 + 3] * a[1 * 4 + 0] * a[0 * 4 + 1]) -
           (a[2 * 4 + 2] * a[3 * 4 + 3] * a[1 * 4 + 0] * a[0 * 4 + 1]) -
           (a[3 * 4 + 2] * a[1 * 4 + 3] * a[2 * 4 + 0] * a[0 * 4 + 1]) +
           (a[1 * 4 + 2] * a[3 * 4 + 3] * a[2 * 4 + 0] * a[0 * 4 + 1]) +
           (a[0 * 4 + 6] * a[1 * 4 + 3] * a[3 * 4 + 0] * a[0 * 4 + 1]) -
           (a[1 * 4 + 2] * a[2 * 4 + 3] * a[3 * 4 + 0] * a[0 * 4 + 1]) -
           (a[1 * 4 + 0] * a[3 * 4 + 2] * a[2 * 4 + 3] * a[1 * 4 + 1]) +
           (a[0 * 4 + 0] * a[2 * 4 + 2] * a[3 * 4 + 3] * a[1 * 4 + 1]) +
           (a[1 * 4 + 0] * a[0 * 4 + 3] * a[2 * 4 + 0] * a[1 * 4 + 1]) -
           (a[2 * 4 + 2] * a[0 * 4 + 3] * a[3 * 4 + 0] * a[1 * 4 + 1]) +
           (a[0 * 4 + 0] * a[3 * 4 + 2] * a[1 * 4 + 3] * a[2 * 4 + 1]) -
           (a[0 * 4 + 0] * a[1 * 4 + 2] * a[3 * 4 + 3] * a[2 * 4 + 1]) -
           (a[3 * 4 + 2] * a[0 * 4 + 3] * a[1 * 4 + 0] * a[2 * 4 + 1]) +
           (a[1 * 4 + 2] * a[0 * 4 + 3] * a[3 * 4 + 0] * a[2 * 4 + 1]) -
           (a[0 * 4 + 0] * a[2 * 4 + 2] * a[1 * 4 + 3] * a[3 * 4 + 1]) +
           (a[0 * 4 + 0] * a[1 * 4 + 2] * a[2 * 4 + 3] * a[3 * 4 + 1]) +
           (a[2 * 4 + 2] * a[0 * 4 + 3] * a[1 * 4 + 0] * a[3 * 4 + 1]) -
           (a[1 * 4 + 2] * a[0 * 4 + 3] * a[2 * 4 + 0] * a[3 * 4 + 1]) -
           (a[3 * 4 + 3] * a[2 * 4 + 0] * a[1 * 4 + 1] * a[0 * 4 + 2]) +
           (a[2 * 4 + 3] * a[3 * 4 + 0] * a[1 * 4 + 1] * a[0 * 4 + 2]) +
           (a[3 * 4 + 3] * a[1 * 4 + 0] * a[2 * 4 + 1] * a[0 * 4 + 2]) -
           (a[1 * 4 + 3] * a[3 * 4 + 0] * a[2 * 4 + 1] * a[0 * 4 + 2]) -
           (a[2 * 4 + 3] * a[1 * 4 + 0] * a[3 * 4 + 1] * a[0 * 4 + 2]) +
           (a[1 * 4 + 3] * a[2 * 4 + 0] * a[3 * 4 + 1] * a[0 * 4 + 2]);
}

Matrix4 &Matrix4::transpose() {
    for (uint8 i = 0; i < 4; i++) {
        for (uint8 j = 0; j < i; j++) {
            real tmp = a[i * 4 + j];
            a[i * 4 + j] = a[j * 4 + i];
            a[j * 4 + i] = tmp;
        }
    }

    return *this;
}

void Matrix4::setToTransform(const Vec3r &translation,
                             const Quaternion &orientation, const Vec3r &scale) {
    real xs = orientation.x * 2.0f;
    real ys = orientation.y * 2.0f;
    real zs = orientation.z * 2.0f;
    real wx = orientation.w * xs;
    real wy = orientation.w * ys;
    real wz = orientation.w * zs;
    real xx = orientation.x * xs;
    real xy = orientation.x * ys;
    real xz = orientation.x * zs;
    real yy = orientation.y * ys;
    real yz = orientation.y * zs;
    real zz = orientation.z * zs;

    a[0] = scale.x * (1.0f - (yy + zz));
    a[4] = scale.y * (xy - wz);
    a[8] = scale.z * (xz + wy);
    a[12] = translation.x;

    a[1] = scale.x * (xy + wz);
    a[5] = scale.y * (1.0f - (xx + zz));
    a[9] = scale.z * (yz - wx);
    a[13] = translation.y;

    a[2] = scale.x * (xz - wy);
    a[6] = scale.y * (yz + wx);
    a[10] = scale.z * (1.0f - (xx + yy));
    a[14] = translation.z;

    a[3] = 0.f;
    a[7] = 0.f;
    a[11] = 0.f;
    a[15] = 1.0f;
}

const Matrix4 Matrix4::ZERO =
        Matrix4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
const Matrix4 Matrix4::ID =
        Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

} // namespace eni::math

#include <cstddef>
#include <iomanip>

namespace eni::math {

std::ostream &operator<<(std::ostream &s, const Matrix4 &mat) {
    s << std::setprecision(3) << std::fixed;

    s << "Matrix4(";

    for (uint8 i = 0; i < 16; i++) {
        if (i > 0) {
            s << ",";
        }

        s << mat.getRawPointer()[i];
    }

    s << ")";
    return s;
}

} // namespace eni::math

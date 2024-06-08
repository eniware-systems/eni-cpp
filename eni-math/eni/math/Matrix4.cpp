#include <eni/math.h>
#include <eni/math/Matrix4.h>

namespace eni::math {

Matrix4::Matrix4(const real a00, const real a10, const real a20, const real a30, const real a01, const real a11,
                 const real a21, const real a31, const real a02, const real a12, const real a22, const real a32,
                 const real a03, const real a13, const real a23, const real a33) {
    _a.at(0) = a00;
    _a.at(1) = a01;
    _a.at(2) = a02;
    _a.at(3) = a03;
    _a.at(4) = a10;
    _a.at(5) = a11;
    _a.at(6) = a12;
    _a.at(7) = a13;
    _a.at(8) = a20;
    _a.at(9) = a21;
    _a.at(10) = a22;
    _a.at(11) = a23;
    _a.at(12) = a30;
    _a.at(13) = a31;
    _a.at(14) = a32;
    _a.at(15) = a33;
}

Matrix4::Matrix4(const Vec4r &c0, const Vec4r &c1, const Vec4r &c2,
                 const Vec4r &c3) {
    _a.at(0) = c0[0];
    _a.at(1) = c0[1];
    _a.at(2) = c0[2];
    _a.at(3) = c0[3];
    _a.at(4) = c1[0];
    _a.at(5) = c1[1];
    _a.at(6) = c1[2];
    _a.at(7) = c1[3];
    _a.at(8) = c2[0];
    _a.at(9) = c2[1];
    _a.at(10) = c2[2];
    _a.at(11) = c2[3];
    _a.at(12) = c3[0];
    _a.at(13) = c3[1];
    _a.at(14) = c3[2];
    _a.at(15) = c3[3];
}

Matrix4::Matrix4(const Matrix4 &other) { this->operator=(other); }

Matrix4 &Matrix4::operator=(const Matrix4 &other) {
    std::copy(other._a.begin(), other._a.end(), _a.begin());
    return *this;
}

real *Matrix4::operator[](const size_t column) { return &_a.at(column * 4); }

const real *Matrix4::operator[](const size_t column) const { return &_a.at(column * 4); }

real &Matrix4::at(const size_t column, const size_t row) { return _a.at(column * 4 + row); }

real Matrix4::at(const size_t column, const size_t row) const { return _a.at(column * 4 + row); }

void Matrix4::setToProjection(const real near, const real far, const real fov, const real aspectRatio) {
    this->operator=(ID);

    const real fd = 1.0f / std::tan(fov * (Pi / 180) / 2.0f);
    const real a1 = (near + far) / (near - far);
    const real a2 = (2.0f * far * near) / (near - far);

    _a.at(0 * 4 + 0) = fd / aspectRatio;
    _a.at(0 * 4 + 1) = 0;
    _a.at(0 * 4 + 2) = 0;
    _a.at(0 * 4 + 3) = 0;
    _a.at(1 * 4 + 0) = 0;
    _a.at(1 * 4 + 1) = fd;
    _a.at(1 * 4 + 2) = 0;
    _a.at(1 * 4 + 3) = 0;
    _a.at(2 * 4 + 0) = 0;
    _a.at(2 * 4 + 1) = 0;
    _a.at(2 * 4 + 2) = a1;
    _a.at(2 * 4 + 3) = -1;
    _a.at(3 * 4 + 0) = 0;
    _a.at(3 * 4 + 1) = 0;
    _a.at(3 * 4 + 2) = a2;
    _a.at(3 * 4 + 3) = 0;
}

void Matrix4::setToOrtho(const real left, const real right, const real bottom, const real top,
                         const real near, const real far) {
    this->operator=(ID);

    const real xOrth = 2.0f / (right - left);
    const real yOrth = 2.0f / (top - bottom);
    const real zOrth = -2.0f / (far - near);
    const real tx = -(right + left) / (right - left);
    const real ty = -(top + bottom) / (top - bottom);
    const real tz = -(far + near) / (far - near);

    _a.at(0 * 4 + 0) = xOrth;
    _a.at(0 * 4 + 1) = 0;
    _a.at(0 * 4 + 2) = 0;
    _a.at(0 * 4 + 3) = 0;
    _a.at(1 * 4 + 0) = 0;
    _a.at(1 * 4 + 1) = yOrth;
    _a.at(1 * 4 + 2) = 0;
    _a.at(1 * 4 + 3) = 0;
    _a.at(2 * 4 + 0) = 0;
    _a.at(2 * 4 + 1) = 0;
    _a.at(2 * 4 + 2) = zOrth;
    _a.at(2 * 4 + 3) = 0;
    _a.at(3 * 4 + 0) = tx;
    _a.at(3 * 4 + 1) = ty;
    _a.at(3 * 4 + 2) = tz;
    _a.at(3 * 4 + 3) = 1;
}

void Matrix4::setToLookAt(const Vec3r &direction, const Vec3r &up) {

    this->operator=(ID);

    const Vec3r z = direction.normalized();
    const Vec3r x = z.cross(up).normalize();
    Vec3r y = x.cross(z);
    y.normalize();

    _a.at(0 * 4 + 0) = x.x;
    _a.at(1 * 4 + 0) = x.y;
    _a.at(2 * 4 + 0) = x.z;
    _a.at(0 * 4 + 1) = y.x;
    _a.at(1 * 4 + 1) = y.y;
    _a.at(2 * 4 + 1) = y.z;
    _a.at(0 * 4 + 2) = -z.x;
    _a.at(1 * 4 + 2) = -z.y;
    _a.at(2 * 4 + 2) = -z.z;
}

Matrix4 Matrix4::operator*(const Matrix4 &other) const {
    Matrix4 result = ZERO;
    for (size_t r = 0; r < 4; r++) {
        for (size_t c = 0; c < 4; c++) {
            result._a.at(c * 4 + r) = _a.at(static_cast<size_t>(0 * 4) + r) * other._a.at(c * 4 + 0) +
                                      _a.at(static_cast<size_t>(1 * 4) + r) * other._a.at(c * 4 + 1) +
                                      _a.at(static_cast<size_t>(2 * 4) + r) * other._a.at(c * 4 + 2) +
                                      _a.at(static_cast<size_t>(3 * 4) + r) * other._a.at(c * 4 + 3);
        }
    }
    return result;
}

Matrix4 &Matrix4::operator*=(const Matrix4 &other) {
    this->operator=(*this * other);
    return *this;
}

void Matrix4::apply(Vec3r &vector) const {
    const real w = 1.0f / (vector.x * _a.at(0 * 4 + 3) + vector.y * _a.at(1 * 4 + 3) +
                           vector.z * _a.at(2 * 4 + 3) + _a.at(3 * 4 + 3));

    vector.set((vector.x * _a.at(0 * 4 + 0) + vector.y * _a.at(1 * 4 + 0) + vector.z * _a.at(2 * 4 + 0) +
                _a.at(3 * 4 + 0)) *
                       w,
               (vector.x * _a.at(0 * 4 + 1) + vector.y * _a.at(1 * 4 + 1) + vector.z * _a.at(2 * 4 + 1) +
                _a.at(3 * 4 + 1)) *
                       w,
               (vector.x * _a.at(0 * 4 + 2) + vector.y * _a.at(1 * 4 + 2) + vector.z * _a.at(2 * 4 + 2) +
                _a.at(3 * 4 + 2)) *
                       w);
}

void Matrix4::apply(Vec4r &vector) const {
    vector.set((vector.x * _a.at(0 * 4 + 0) + vector.y * _a.at(1 * 4 + 0) + vector.z * _a.at(2 * 4 + 0) +
                vector.w * _a.at(3 * 4 + 0)),
               (vector.x * _a.at(0 * 4 + 1) + vector.y * _a.at(1 * 4 + 1) + vector.z * _a.at(2 * 4 + 1) +
                vector.w * _a.at(3 * 4 + 1)),
               (vector.x * _a.at(0 * 4 + 2) + vector.y * _a.at(1 * 4 + 2) + vector.z * _a.at(2 * 4 + 2) +
                vector.w * _a.at(3 * 4 + 2)),
               (vector.x * _a.at(0 * 4 + 3) + vector.y * _a.at(1 * 4 + 3) + vector.z * _a.at(2 * 4 + 3) +
                vector.w * _a.at(3 * 4 + 3)));
}

bool Matrix4::operator==(const Matrix4 &other) const {
    for (uint8 i = 0; i < 16; ++i) {
        if (!is_equal_approx(_a.at(i), other._a.at(i))) {
            return false;
        }
    }
    return true;
}

inline real getCofactor(const real m0, const real m1, const real m2, const real m3, const real m4, const real m5,
                        const real m6, const real m7, const real m8) {
    return m0 * (m4 * m8 - m5 * m7) - m1 * (m3 * m8 - m5 * m6) +
           m2 * (m3 * m7 - m4 * m6);
}

Matrix4 &Matrix4::invert() {
    auto &m = _a;

    // get cofactors of minor matrices
    const real cofactor0 =
            getCofactor(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]);
    const real cofactor1 =
            getCofactor(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]);
    const real cofactor2 =
            getCofactor(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]);
    const real cofactor3 =
            getCofactor(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);

    // get determinant
    const real determinant = getDeterminant();

    if (is_equal_approx(determinant, 0, Epsilon)) {
        this->operator=(ID);
        return *this;
    }

    // get rest of cofactors for adj(M)
    const real cofactor4 =
            getCofactor(m[1], m[2], m[3], m[9], m[10], m[11], m[13], m[14], m[15]);
    const real cofactor5 =
            getCofactor(m[0], m[2], m[3], m[8], m[10], m[11], m[12], m[14], m[15]);
    const real cofactor6 =
            getCofactor(m[0], m[1], m[3], m[8], m[9], m[11], m[12], m[13], m[15]);
    const real cofactor7 =
            getCofactor(m[0], m[1], m[2], m[8], m[9], m[10], m[12], m[13], m[14]);

    const real cofactor8 =
            getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[13], m[14], m[15]);
    const real cofactor9 =
            getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[12], m[14], m[15]);
    const real cofactor10 =
            getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[12], m[13], m[15]);
    const real cofactor11 =
            getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[12], m[13], m[14]);

    const real cofactor12 =
            getCofactor(m[1], m[2], m[3], m[5], m[6], m[7], m[9], m[10], m[11]);
    const real cofactor13 =
            getCofactor(m[0], m[2], m[3], m[4], m[6], m[7], m[8], m[10], m[11]);
    const real cofactor14 =
            getCofactor(m[0], m[1], m[3], m[4], m[5], m[7], m[8], m[9], m[11]);
    const real cofactor15 =
            getCofactor(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);

    // build inverse matrix = adj(M) / det(M)
    // adjugate of M is the transpose of the cofactor matrix of M
    const real invDeterminant = 1.0f / determinant;
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
    return (_a.at(3 * 4 + 2) * _a.at(2 * 4 + 3) * _a.at(1 * 4 + 0) * _a.at(0 * 4 + 1)) -
           (_a.at(2 * 4 + 2) * _a.at(3 * 4 + 3) * _a.at(1 * 4 + 0) * _a.at(0 * 4 + 1)) -
           (_a.at(3 * 4 + 2) * _a.at(1 * 4 + 3) * _a.at(2 * 4 + 0) * _a.at(0 * 4 + 1)) +
           (_a.at(1 * 4 + 2) * _a.at(3 * 4 + 3) * _a.at(2 * 4 + 0) * _a.at(0 * 4 + 1)) +
           (_a.at(0 * 4 + 6) * _a.at(1 * 4 + 3) * _a.at(3 * 4 + 0) * _a.at(0 * 4 + 1)) -
           (_a.at(1 * 4 + 2) * _a.at(2 * 4 + 3) * _a.at(3 * 4 + 0) * _a.at(0 * 4 + 1)) -
           (_a.at(1 * 4 + 0) * _a.at(3 * 4 + 2) * _a.at(2 * 4 + 3) * _a.at(1 * 4 + 1)) +
           (_a.at(0 * 4 + 0) * _a.at(2 * 4 + 2) * _a.at(3 * 4 + 3) * _a.at(1 * 4 + 1)) +
           (_a.at(1 * 4 + 0) * _a.at(0 * 4 + 3) * _a.at(2 * 4 + 0) * _a.at(1 * 4 + 1)) -
           (_a.at(2 * 4 + 2) * _a.at(0 * 4 + 3) * _a.at(3 * 4 + 0) * _a.at(1 * 4 + 1)) +
           (_a.at(0 * 4 + 0) * _a.at(3 * 4 + 2) * _a.at(1 * 4 + 3) * _a.at(2 * 4 + 1)) -
           (_a.at(0 * 4 + 0) * _a.at(1 * 4 + 2) * _a.at(3 * 4 + 3) * _a.at(2 * 4 + 1)) -
           (_a.at(3 * 4 + 2) * _a.at(0 * 4 + 3) * _a.at(1 * 4 + 0) * _a.at(2 * 4 + 1)) +
           (_a.at(1 * 4 + 2) * _a.at(0 * 4 + 3) * _a.at(3 * 4 + 0) * _a.at(2 * 4 + 1)) -
           (_a.at(0 * 4 + 0) * _a.at(2 * 4 + 2) * _a.at(1 * 4 + 3) * _a.at(3 * 4 + 1)) +
           (_a.at(0 * 4 + 0) * _a.at(1 * 4 + 2) * _a.at(2 * 4 + 3) * _a.at(3 * 4 + 1)) +
           (_a.at(2 * 4 + 2) * _a.at(0 * 4 + 3) * _a.at(1 * 4 + 0) * _a.at(3 * 4 + 1)) -
           (_a.at(1 * 4 + 2) * _a.at(0 * 4 + 3) * _a.at(2 * 4 + 0) * _a.at(3 * 4 + 1)) -
           (_a.at(3 * 4 + 3) * _a.at(2 * 4 + 0) * _a.at(1 * 4 + 1) * _a.at(0 * 4 + 2)) +
           (_a.at(2 * 4 + 3) * _a.at(3 * 4 + 0) * _a.at(1 * 4 + 1) * _a.at(0 * 4 + 2)) +
           (_a.at(3 * 4 + 3) * _a.at(1 * 4 + 0) * _a.at(2 * 4 + 1) * _a.at(0 * 4 + 2)) -
           (_a.at(1 * 4 + 3) * _a.at(3 * 4 + 0) * _a.at(2 * 4 + 1) * _a.at(0 * 4 + 2)) -
           (_a.at(2 * 4 + 3) * _a.at(1 * 4 + 0) * _a.at(3 * 4 + 1) * _a.at(0 * 4 + 2)) +
           (_a.at(1 * 4 + 3) * _a.at(2 * 4 + 0) * _a.at(3 * 4 + 1) * _a.at(0 * 4 + 2));
}

Matrix4 &Matrix4::transpose() {
    for (uint8 i = 0; i < 4; i++) {
        for (uint8 j = 0; j < i; j++) {
            const real tmp = _a.at(i * 4 + j);
            _a.at(i * 4 + j) = _a.at(j * 4 + i);
            _a.at(j * 4 + i) = tmp;
        }
    }

    return *this;
}

void Matrix4::setToTransform(const Vec3r &translation,
                             const Quaternion &orientation, const Vec3r &scale) {
    const real xs = orientation.x * 2.0f;
    const real ys = orientation.y * 2.0f;
    const real zs = orientation.z * 2.0f;
    const real wx = orientation.w * xs;
    const real wy = orientation.w * ys;
    const real wz = orientation.w * zs;
    const real xx = orientation.x * xs;
    const real xy = orientation.x * ys;
    const real xz = orientation.x * zs;
    const real yy = orientation.y * ys;
    const real yz = orientation.y * zs;
    const real zz = orientation.z * zs;

    _a.at(0) = scale.x * (1.0f - (yy + zz));
    _a.at(4) = scale.y * (xy - wz);
    _a.at(8) = scale.z * (xz + wy);
    _a.at(12) = translation.x;

    _a.at(1) = scale.x * (xy + wz);
    _a.at(5) = scale.y * (1.0f - (xx + zz));
    _a.at(9) = scale.z * (yz - wx);
    _a.at(13) = translation.y;

    _a.at(2) = scale.x * (xz - wy);
    _a.at(6) = scale.y * (yz + wx);
    _a.at(10) = scale.z * (1.0f - (xx + yy));
    _a.at(14) = translation.z;

    _a.at(3) = 0.f;
    _a.at(7) = 0.f;
    _a.at(11) = 0.f;
    _a.at(15) = 1.0f;
}

const Matrix4 Matrix4::ZERO =
        Matrix4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
const Matrix4 Matrix4::ID =
        Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

}// namespace eni::math

#include <cstddef>
#include <iomanip>

namespace eni::math {

std::ostream &operator<<(std::ostream &stream, const Matrix4 &matrix) {
    stream << std::setprecision(3) << std::fixed;

    stream << "Matrix4(";

    for (uint8 y = 0; y < 4; ++y) {
        for (uint8 x = 0; x < 4; x++) {
            if (x > 0 || y > 0) {
                stream << ",";
            }

            stream << matrix.at(x, y);
        }
    }

    stream << ")";
    return stream;
}

}// namespace eni::math

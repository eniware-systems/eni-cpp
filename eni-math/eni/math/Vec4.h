#ifndef ENI_MATH_VEC4_H
#define ENI_MATH_VEC4_H

#include <eni/build_config.h>
#include <eni/math.h>

#include <ostream>

namespace eni::math {

template<typename T>
class Vec4 {
public:
    using value_type = T;

    value_type
            x,//< The x component
            y,//< The y component
            z,//< The z component
            w;//< The w component

public:
    /**
     * Creates a new vector from component values
     * @param x The x axis value
     * @param y The y axis value
     * @param z The z axis value
     * @param w The w axis value
     */
    explicit Vec4(value_type x = 0, value_type y = 0, value_type z = 0, value_type w = 0);

    /**
     * Copies a vector
     * @param other The vector to copy
     */
    Vec4(const Vec4 &other) = default;

    /**
     * Sets the vector component values
     * @param x The x axis value
     * @param y The y axis value
     * @param z The z axis value
     * @param w The w axis value
     */
    void set(value_type x, value_type y, value_type z, value_type w);

    /**
 	 * @param nth The component number
 	 * @return the nth component value from this vector
 	 */
    value_type &operator[](size_t nth) {
        return *(&x + nth);
    }

    /**
      * @param nth The component number
      * @return the nth component value from this vector
      */
    value_type operator[](size_t nth) const {
        return *(&x + nth);
    }

public:
    /**
     * Adds another vector
     * @param other The vector to add
     * @return The vector sum of both vectors
     */
    Vec4 operator+(const Vec4 &other) const;

    /**
     * Subtracts another vector
     * @param other The vector to subtract
     * @return The subtracted vector
     */
    Vec4 operator-(const Vec4 &other) const;

    /**
     * Multiplies this by a scalar
     * @param scalar The scalar value
     * @return A new scaled vector
     */
    Vec4 operator*(const real &scalar) const;

    /**
     * Divides this by a scalar
     * @param scalar The scalar value
     * @return A new scaled vector
     */
    Vec4 operator/(const real &scalar) const;

    /**
     * Sets this vector to the values of another vector
     * @param other The vector to copy the component values
     * @return This vector for chaining
     */
    Vec4 &operator=(const Vec4 &other);

    /**
     * Adds another vector
     * @param other The vector to add
     * @return This vector for chaining
     */
    Vec4 &operator+=(const Vec4 &other);

    /**
     * Subtracts another vector
     * @param other The vector to subtract
     * @return This vector for chaining
     */
    Vec4 &operator-=(const Vec4 &other);

    /**
     * Multiplies this by a scalar
     * @param scalar The scalar value
     * @return This vector for chaining
     */
    Vec4 &operator*=(const real &scalar);

    /**
     * Divides this by a scalar
     * @param scalar The scalar value
     * @return This vector for chaining
     */
    Vec4 &operator/=(const real &scalar);

    /*
     * @return The negative vector
     */
    Vec4 operator-() const;

    /**
     * Compares two vectors
     * @param other The vector to compare this with
     * @return Whether both vectors are equal
     */
    bool operator==(const Vec4 &other) const;

    /**
     * Compares two vectors
     * @param other The vector to compare this with
     * @return Whether both vectors are unequal
     */
    bool operator!=(const Vec4 &other) const;

    /**
     * @return The length of this vector
     */
    [[nodiscard]] real length() const;

    /**
     * @return The squared length of this vector
     */
    [[nodiscard]] real squaredLength() const;

    /**
	 * Calculates the dot product of two vectors
	 * @param other The vector to calculate the dot product with
	 * @return The dot product of both vectors
	 */
    [[nodiscard]] real dot(const Vec4 &other) const;

    /**
     * @return A normalized copy of this vector
     */
    [[nodiscard]] Vec4 normalized() const;

    /**
     * Normalizes the vector
     * @return This vector for chaining
     */
    Vec4 &normalize();

    /**
     * Calculates the euclidean distance between two vectors
     * @param other The vector to calculate the distance with
     * @return The distance between this and other
     */
    [[nodiscard]] real distance(const Vec4 &other) const;

    /**
     * @return Whether all dimensions of this vector are finite.
     */
    [[nodiscard]] bool isFinite() const;

    /**
     * @return a raw pointer to the vector components.
     */
    [[nodiscard]] const T *data() const;

public:
    static const Vec4 Zero;         //< The zero vector (0,0,0,0)
    static const Vec4 Unit;         //< The neutral vector (1,1,1,1)
    static const Vec4 Infinite;     //< The vector representing infinity
    static const Vec4 UnitX;        //< The x unit vector (1,0,0,0)
    static const Vec4 UnitY;        //< The y unit vector (0,1,0,0)
    static const Vec4 UnitZ;        //< The z unit vector (0,0,1,0)
    static const Vec4 UnitW;        //< The w unit vector (0,0,0,1)
    static const Vec4 NegativeUnitX;// The negative x unit vector (-1,0,0,0).
    static const Vec4 NegativeUnitY;// The negative y unit vector (0,-1,0,0).
    static const Vec4 NegativeUnitZ;// The negative z unit vector (0,0,-1,0).
    static const Vec4 NegativeUnitW;// The negative w unit vector (0,0,0,-1).
};

/**
 * Stream implementation
 * @param stream The stream
 * @param vector The vector to write into the stream
 * @return The stream for chaining
 */
template<typename T>
std::ostream &operator<<(std::ostream &stream, const Vec4<T> &vector);

using Vec4i = Vec4<int32>;
using Vec4r = Vec4<real>;

// Implementation

template<typename T>
Vec4<T>::Vec4(value_type x, value_type y, value_type z, value_type w) : x(x), y(y), z(z), w(w) {}

template<typename T>
void Vec4<T>::set(const value_type nx, value_type ny, value_type nz, value_type nw) {
    x = nx;
    y = ny;
    z = nz;
    w = nw;
}

template<typename T>
Vec4<T> Vec4<T>::operator+(const Vec4 &other) const {
    return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

template<typename T>
Vec4<T> Vec4<T>::operator-(const Vec4 &other) const {
    return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

template<typename T>
Vec4<T> Vec4<T>::operator*(const real &scalar) const {
    return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

template<typename T>
Vec4<T> Vec4<T>::operator/(const real &scalar) const {
    return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

template<typename T>
Vec4<T> &Vec4<T>::operator=(const Vec4 &other) = default;

template<typename T>
Vec4<T> &Vec4<T>::operator+=(const Vec4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

template<typename T>
Vec4<T> &Vec4<T>::operator-=(const Vec4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

template<typename T>
Vec4<T> &Vec4<T>::operator*=(const real &scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template<typename T>
Vec4<T> &Vec4<T>::operator/=(const real &scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

template<typename T>
Vec4<T> Vec4<T>::operator-() const {
    return Vec4(-x, -y, -z, -w);
}

template<typename T>
bool Vec4<T>::operator==(const Vec4 &other) const {
    return math::is_equal_approx(x, other.x) && math::is_equal_approx(y, other.y) && math::is_equal_approx(z, other.z) && math::is_equal_approx(w, other.w);
}

template<typename T>
bool Vec4<T>::operator!=(const Vec4 &other) const {
    return !operator==(other);
}

template<typename T>
real Vec4<T>::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

template<typename T>
real Vec4<T>::squaredLength() const {
    return x * x + y * y + z * z + w * w;
}

template<typename T>
real Vec4<T>::dot(const Vec4 &other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

template<typename T>
real Vec4<T>::distance(const Vec4 &other) const {
    real dX = (x - other.x);
    real dY = (y - other.y);
    real dZ = (z - other.z);

    return std::sqrt(dX * dX + dY * dY + dZ * dZ);
}

template<typename T>
Vec4<T> Vec4<T>::normalized() const {
    Vec4 v(*this);
    v.normalize();
    return v;
}

template<typename T>
Vec4<T> &Vec4<T>::normalize() {
    real len = length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
    return *this;
}

template<typename T>
bool Vec4<T>::isFinite() const {
    return !std::isinf(x) && !std::isinf(y) && !std::isinf(z) && !std::isinf(w);
}

template<typename T>
const T *Vec4<T>::data() const {
    return &x;
}

template<typename T>
const Vec4<T> Vec4<T>::Zero(0, 0, 0, 0);

template<typename T>
const Vec4<T> Vec4<T>::Unit(1, 1, 1, 1);

template<typename T>
const Vec4<T> Vec4<T>::Infinite(
        std::numeric_limits<real>::infinity(),
        std::numeric_limits<real>::infinity(),
        std::numeric_limits<real>::infinity(),
        std::numeric_limits<real>::infinity());

template<typename T>
const Vec4<T> Vec4<T>::UnitX(1, 0, 0, 0);
template<typename T>
const Vec4<T> Vec4<T>::UnitY(0, 1, 0, 0);
template<typename T>
const Vec4<T> Vec4<T>::UnitZ(0, 0, 1, 0);
template<typename T>
const Vec4<T> Vec4<T>::UnitW(0, 0, 0, 1);

template<typename T>
const Vec4<T> Vec4<T>::NegativeUnitX(-1, 0, 0, 0);
template<typename T>
const Vec4<T> Vec4<T>::NegativeUnitY(0, -1, 0, 0);
template<typename T>
const Vec4<T> Vec4<T>::NegativeUnitZ(0, 0, -1, 0);
template<typename T>
const Vec4<T> Vec4<T>::NegativeUnitW(0, 0, 0, -1);

}// namespace eni::math

namespace eni::math {

template<typename T>
std::ostream &operator<<(std::ostream &s, const Vec4<T> &v) {
    s << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return s;
}

}// namespace eni::math


#endif//ENI_MATH_VEC4_H

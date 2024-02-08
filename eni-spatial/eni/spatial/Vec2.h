#ifndef ENI_SPATIAL_VEC2_H
#define ENI_SPATIAL_VEC2_H

#include "eni/math.h"

#include <cmath>
#include <limits>
#include <ostream>

#include <eni/build_config.h>

namespace eni::spatial {

template<typename T>
class Vec2 {
public:
    using value_type = T;

    value_type
            x,//< The x component
            y;//< The y component

public:
    /**
     * Creates a new vector from component values
     * @param x The x axis value
     * @param y The y axis value
     */
    explicit Vec2(value_type x = 0, value_type y = 0);

    /**
      * Copies a vector
      * @param other The vector to copy
      */
    Vec2(const Vec2 &other) = default;

    /**
     * Sets the vector component values
     * @param x The x axis value
     * @param y The y axis value
     */
    void set(value_type x, value_type y);

    /**
      * @param nth The component number
      * @return the nth component value from this vector
      */
    inline value_type &operator[](size_t nth) {
        return *static_cast<value_type *>(&x + nth);
    }

    /**
      * @param nth The component number
      * @return the nth component value from this vector
      */
    value_type operator[](size_t nth) const {
        return *static_cast<const value_type *>(&x + nth);
    }

public:
    /**
     * Adds another vector
     * @param other The vector to add
     * @return The vector sum of both vectors
     */
    Vec2 operator+(const Vec2 &other) const;

    /**
     * Subtracts another vector
     * @param other The vector to subtract
     * @return The subtracted vector
     */
    Vec2 operator-(const Vec2 &other) const;

    /**
     * Multiplies this by a scalar
     * @param scalar The scalar value
     * @return A new scaled vector
     */
    Vec2 operator*(value_type scalar) const;

    /**
     * Divides this by a scalar
     * @param scalar The scalar value
     * @return A new scaled vector
     */
    Vec2 operator/(value_type scalar) const;

    /**
     * Sets this vector to the values of another vector
     * @param other The vector to copy the component values
     * @return This vector for chaining
     */
    Vec2 &operator=(const Vec2 &other);

    /**
     * Adds another vector
     * @param other The vector to add
     * @return This vector for chaining
     */
    Vec2 &operator+=(const Vec2 &other);

    /**
     * Subtracts another vector
     * @param other The vector to subtract
     * @return This vector for chaining
     */
    Vec2 &operator-=(const Vec2 &other);

    /**
     * Multiplies this by a scalar
     * @param scalar The scalar value
     * @return This vector for chaining
     */
    Vec2 &operator*=(value_type scalar);

    /**
     * Divides this by a scalar
     * @param scalar The scalar value
     * @return This vector for chaining
     */
    Vec2 &operator/=(value_type scalar);

    /*
     * @return The negative vector
     */
    Vec2 operator-() const;

    /**
     * Compares two vectors
     * @param other The vector to compare this with
     * @return Whether both vectors are equal
     */
    bool operator==(const Vec2 &other) const;

    /**
     * Compares two vectors
     * @param other The vector to compare this with
     * @return Whether both vectors are unequal
     */
    bool operator!=(const Vec2 &other) const;

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
    [[nodiscard]] real dot(const Vec2 &other) const;

    /**
     * @return A normalized copy of this vector
     */
    [[nodiscard]] Vec2 normalized() const;

    /**
     * Normalizes the vector
     * @return This vector for chaining
     */
    Vec2 &normalize();

    /**
     * Calculates the euclidean distance between two vectors
     * @param other The vector to calculate the distance with
     * @return The distance between this and other
     */
    [[nodiscard]] real distance(const Vec2 &other) const;

public:
    static const Vec2 Zero;         //< The zero vector (0,0)
    static const Vec2 Unit;         //< The neutral vector (1,1)
    static const Vec2 Infinite;     //< The vector representing infinity
    static const Vec2 UnitX;        //< The x unit vector (1,0)
    static const Vec2 UnitY;        //< The y unit vector (0,1)
    static const Vec2 NegativeUnitX;// The negative x unit vector (-1,0).
    static const Vec2 NegativeUnitY;// The negative y unit vector (0,-1).
};

/**
 * Stream implementation
 * @param stream The stream
 * @param vector The vector to write into the stream
 * @return The stream for chaining
 */
template<typename T>
std::ostream &operator<<(std::ostream &stream, const Vec2<T> &vector);

using Vec2i = Vec2<int32>;
using Vec2r = Vec2<real>;

// Implementation

template<typename T>
Vec2<T>::Vec2(value_type x, value_type y) : x(x), y(y) {
}

template<typename T>
void Vec2<T>::set(value_type _x, value_type _y) {
    x = _x;
    y = _y;
}

template<typename T>
Vec2<T> Vec2<T>::operator+(const Vec2 &other) const {
    return Vec2(x + other.x, y + other.y);
}

template<typename T>
Vec2<T> Vec2<T>::operator-(const Vec2 &other) const {
    return Vec2(x - other.x, y - other.y);
}

template<typename T>
Vec2<T> Vec2<T>::operator*(value_type scalar) const {
    return Vec2(x * scalar, y * scalar);
}

template<typename T>
Vec2<T> Vec2<T>::operator/(value_type scalar) const {
    return Vec2(x / scalar, y / scalar);
}

template<typename T>
Vec2<T> &Vec2<T>::operator=(const Vec2 &other) = default;

template<typename T>
Vec2<T> &Vec2<T>::operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator-=(const Vec2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator*=(value_type scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator/=(value_type scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator-() const {
    return Vec2(-x, -y);
}

template<typename T>
bool Vec2<T>::operator==(const Vec2 &other) const {
    return math::is_equal_approx(x, other.x) && math::is_equal_approx(y, other.y);
}

template<typename T>
bool Vec2<T>::operator!=(const Vec2 &other) const {
    return !operator==(other);
}

template<typename T>
real Vec2<T>::length() const {
    return std::sqrt(x * x + y * y);
}

template<typename T>
real Vec2<T>::squaredLength() const {
    return x * x + y * y;
}

template<typename T>
real Vec2<T>::dot(const Vec2 &other) const {
    return x * other.x + y * other.y;
}

template<typename T>
real Vec2<T>::distance(const Vec2 &other) const {
    real dX = (x - other.x);
    real dY = (y - other.y);

    return std::sqrt(dX * dX + dY * dY);
}

template<typename T>
Vec2<T> Vec2<T>::normalized() const {
    Vec2 v(*this);
    v.normalize();
    return v;
}

template<typename T>
Vec2<T> &Vec2<T>::normalize() {
    real len = length();
    x /= len;
    y /= len;
    return *this;
}

template<typename T>
const Vec2<T> Vec2<T>::Zero(0, 0);

template<typename T>
const Vec2<T> Vec2<T>::Unit(1, 1);

template<typename T>
const Vec2<T> Vec2<T>::Infinite(
        std::numeric_limits<real>::infinity(),
        std::numeric_limits<real>::infinity());

template<typename T>
const Vec2<T> Vec2<T>::UnitX(1, 0);
template<typename T>
const Vec2<T> Vec2<T>::UnitY(0, 1);

template<typename T>
const Vec2<T> Vec2<T>::NegativeUnitX(-1, 0);
template<typename T>
const Vec2<T> Vec2<T>::NegativeUnitY(0, -1);

}// namespace eni::spatial

namespace eni::spatial {
template<typename T>
std::ostream &operator<<(std::ostream &s, const Vec2<T> &v) {
    s << "(" << v.x << "," << v.y << ")";
    return s;
}
}// namespace eni::spatial

#endif//ENI_SPATIAL_VEC2_H

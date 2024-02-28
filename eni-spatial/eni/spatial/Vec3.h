#ifndef ENI_SPATIAL_VEC3_H
#define ENI_SPATIAL_VEC3_H

#include <eni/build_config.h>
#include <eni/math.h>

#include <ostream>

namespace eni::spatial {

template<typename T>
class Vec3 {
public:
    using value_type = T;

    value_type
            x,//< The x component
            y,//< The y component
            z;//< The z component

public:
    /**
     * Creates a new vector from component values
     * @param x The x axis value
     * @param y The y axis value
     * @param z The z axis value
     */
    explicit Vec3(value_type x = 0, value_type y = 0, value_type z = 0);

    /**
      * Copies a vector
      * @param other The vector to copy
      */
    Vec3(const Vec3 &other) = default;

    /**
     * Sets the vector component values
     * @param x The x axis value
     * @param y The y axis value
     * @param z The z axis value
     */
    void set(value_type x, value_type y, value_type z);

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
    Vec3 operator+(const Vec3 &other) const;

    /**
     * Subtracts another vector
     * @param other The vector to subtract
     * @return The subtracted vector
     */
    Vec3 operator-(const Vec3 &other) const;

    /**
     * Multiplies this by a scalar
     * @param scalar The scalar value
     * @return A new scaled vector
     */
    Vec3 operator*(value_type scalar) const;

    /**
     * Divides this by a scalar
     * @param scalar The scalar value
     * @return A new scaled vector
     */
    Vec3 operator/(value_type scalar) const;

    /**
     * Sets this vector to the values of another vector
     * @param other The vector to copy the component values
     * @return This vector for chaining
     */
    Vec3 &operator=(const Vec3 &other);

    /**
     * Adds another vector
     * @param other The vector to add
     * @return This vector for chaining
     */
    Vec3 &operator+=(const Vec3 &other);

    /**
     * Subtracts another vector
     * @param other The vector to subtract
     * @return This vector for chaining
     */
    Vec3 &operator-=(const Vec3 &other);

    /**
     * Multiplies this by a scalar
     * @param scalar The scalar value
     * @return This vector for chaining
     */
    Vec3 &operator*=(value_type scalar);

    /**
     * Divides this by a scalar
     * @param scalar The scalar value
     * @return This vector for chaining
     */
    Vec3 &operator/=(value_type scalar);

    /*
     * @return The negative vector
     */
    Vec3 operator-() const;

    /**
     * Compares two vectors
     * @param other The vector to compare this with
     * @return Whether both vectors are equal
     */
    bool operator==(const Vec3 &other) const;

    /**
     * Compares two vectors
     * @param other The vector to compare this with
     * @return Whether both vectors are unequal
     */
    bool operator!=(const Vec3 &other) const;

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
    [[nodiscard]] real dot(const Vec3 &other) const;

    /**
     * Calculates the cross product of two vectors
     * @param other The vector to calculate the cross product with
     * @return The cross product of both vectors
     */
    [[nodiscard]] Vec3 cross(const Vec3 &other) const;

    /**
     * @return A normalized copy of this vector
     */
    [[nodiscard]] Vec3 normalized() const;

    /**
     * Normalizes the vector
     * @return This vector for chaining
     */
    Vec3 &normalize();

    /**
     * Calculates the euclidean distance between two vectors
     * @param other The vector to calculate the distance with
     * @return The distance between this and other
     */
    [[nodiscard]] real distance(const Vec3 &other) const;

public:
    static const Vec3 Zero;         //< The zero vector (0,0,0)
    static const Vec3 Unit;         //< The neutral vector (1,1,1)
    static const Vec3 Infinite;     //< The vector representing infinity
    static const Vec3 UnitX;        //< The x unit vector (1,0,0)
    static const Vec3 UnitY;        //< The y unit vector (0,1,0)
    static const Vec3 UnitZ;        //< The z unit vector (0,0,1)
    static const Vec3 NegativeUnitX;// The negative x unit vector (-1,0,0).
    static const Vec3 NegativeUnitY;// The negative y unit vector (0,-1,0).
    static const Vec3 NegativeUnitZ;// The negative z unit vector (0,0,-1).
};

/**
 * Stream implementation
 * @param stream The stream
 * @param vector The vector to write into the stream
 * @return The stream for chaining
 */
template<typename T>
std::ostream &operator<<(std::ostream &stream, const Vec3<T> &vector);

using Vec3i = Vec3<int32>;
using Vec3r = Vec3<real>;

// Implementation

template<typename T>
Vec3<T>::Vec3(value_type x, value_type y, value_type z) : x(x), y(y), z(z) {
}

template<typename T>
void Vec3<T>::set(value_type _x, value_type _y, value_type _z) {
    x = _x;
    y = _y;
    z = _z;
}

template<typename T>
Vec3<T> Vec3<T>::operator+(const Vec3 &other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

template<typename T>
Vec3<T> Vec3<T>::operator-(const Vec3 &other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

template<typename T>
Vec3<T> Vec3<T>::operator*(value_type scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

template<typename T>
Vec3<T> Vec3<T>::operator/(value_type scalar) const {
    return Vec3(x / scalar, y / scalar, z / scalar);
}

template<typename T>
Vec3<T> &Vec3<T>::operator=(const Vec3 &other) = default;

template<typename T>
Vec3<T> &Vec3<T>::operator+=(const Vec3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template<typename T>
Vec3<T> &Vec3<T>::operator-=(const Vec3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template<typename T>
Vec3<T> &Vec3<T>::operator*=(value_type scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template<typename T>
Vec3<T> &Vec3<T>::operator/=(value_type scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator-() const {
    return Vec3(-x, -y, -z);
}

template<typename T>
bool Vec3<T>::operator==(const Vec3 &other) const {
    return math::is_equal_approx(x, other.x) && math::is_equal_approx(y, other.y) && math::is_equal_approx(z, other.z);
}

template<typename T>
bool Vec3<T>::operator!=(const Vec3 &other) const {
    return !operator==(other);
}

template<typename T>
real Vec3<T>::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

template<typename T>
real Vec3<T>::squaredLength() const {
    return x * x + y * y + z * z;
}

template<typename T>
real Vec3<T>::dot(const Vec3 &other) const {
    return x * other.x + y * other.y + z * other.z;
}

template<typename T>
Vec3<T> Vec3<T>::cross(const Vec3 &other) const {
    return Vec3(y * other.z - other.y * z, z * other.x - other.z * x, x * other.y - other.x * y);
}

template<typename T>
real Vec3<T>::distance(const Vec3 &other) const {
    real dX = (x - other.x);
    real dY = (y - other.y);
    real dZ = (z - other.z);

    return std::sqrt(dX * dX + dY * dY + dZ * dZ);
}

template<typename T>
Vec3<T> Vec3<T>::normalized() const {
    Vec3 v(*this);
    v.normalize();
    return v;
}

template<typename T>
Vec3<T> &Vec3<T>::normalize() {
    real len = length();
    x /= len;
    y /= len;
    z /= len;
    return *this;
}

template<typename T>
const Vec3<T> Vec3<T>::Zero(0, 0, 0);

template<typename T>
const Vec3<T> Vec3<T>::Unit(1, 1, 1);

template<typename T>
const Vec3<T> Vec3<T>::Infinite(
        std::numeric_limits<real>::infinity(),
        std::numeric_limits<real>::infinity(),
        std::numeric_limits<real>::infinity());

template<typename T>
const Vec3<T> Vec3<T>::UnitX(1, 0, 0);
template<typename T>
const Vec3<T> Vec3<T>::UnitY(0, 1, 0);
template<typename T>
const Vec3<T> Vec3<T>::UnitZ(0, 0, 1);

template<typename T>
const Vec3<T> Vec3<T>::NegativeUnitX(-1, 0, 0);
template<typename T>
const Vec3<T> Vec3<T>::NegativeUnitY(0, -1, 0);
template<typename T>
const Vec3<T> Vec3<T>::NegativeUnitZ(0, 0, -1);

template<typename T>
std::ostream &operator<<(std::ostream &stream, const Vec3<T> &v) {
    stream << "(" << v.x << "," << v.y << "," << v.z << ")";
    return stream;
}

}// namespace eni::spatial

#endif//ENI_SPATIAL_VEC3_H

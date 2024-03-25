#ifndef ENI_MATH_BOUNDINGBOX_H
#define ENI_MATH_BOUNDINGBOX_H

#include <eni/math/Matrix4.h>
#include <eni/math/Vec3.h>

#include <limits>

namespace eni::math {

/**
 * This class represents an axis aligned bounding box.
 * Typically, axis aligned bounding boxes can be used to check for intersections
 * with geometry on a very fast but rough level. For example, if you just need to
 * pick an object from the scene, an axis aligned bounding box might be perfectly
 * fine. If you want to pick certain sides of the object then you would need a
 * more advanced approach like ray queries.
 **/
template<typename T>
class BoundingBox {
public:
    /**
     * Corners of the bounding box. Lowercase literals mean upper/left/back sides,
     * uppercase literals mean lower/right/front sides.
     */
    enum class Corner : uint8 { xyz,// NOLINT(*-identifier-naming)
                                Xyz,
                                xYz,// NOLINT(*-identifier-naming)
                                xyZ,// NOLINT(*-identifier-naming)
                                XYz,
                                XyZ,
                                xYZ,// NOLINT(*-identifier-naming)
                                XYZ,
                                Invalid };

public:
    BoundingBox();
    BoundingBox(const Vec3<T> &min, const Vec3<T> &max);
    BoundingBox(const BoundingBox &other);

    /**
     * Arthmetic operations.
     */
    BoundingBox &operator=(const BoundingBox &other);
    BoundingBox &operator+=(const BoundingBox &other);
    BoundingBox operator+=(const Vec3<T> &point);
    BoundingBox operator+(const BoundingBox &other) const;
    BoundingBox operator+(const Vec3<T> &point) const;
    BoundingBox &operator*=(const Matrix4 &transform);
    BoundingBox operator*(const Matrix4 &transform) const;

    bool operator==(const BoundingBox &other) const;

    bool operator!=(const BoundingBox &other) const;

    /**
     * Sets the minimum (upper left back edge of the box).
     * @param min the new minimum value
     */
    void setMinimum(const Vec3<T> &min);

    void setMinimum(T x, T y, T z);

    /**
     * @return the minimum (upper left back edge of the box).
     */
    const Vec3<T> &getMinimum() const;

    /**
     * Sets the maximum (lower right front edge of the box).
     * @param max the new maximum value
     */
    void setMaximum(const Vec3<T> &max);

    void setMaximum(T x, T y, T z);

    /**
     * @return the maximum (lower right front edge of the box).
     */
    const Vec3<T> &getMaximum() const;

    /**
     * @param upperX true for right side, false for left side.
     * @param upperY true for lower side, false for upper side.
     * @param upperZ true for front side, false for back side.
     * @return the correct enum value described by the three arguments.
     */
    static Corner corner(bool upperX, bool upperY, bool upperZ);

    /**
     * @param corner one of the enum values describing the corner. A lowercase
     * letter indicates the dimensional minimum, uppercase means maximum
     * (left/right, top/bottom, back/front).
     * @return a point describing the exact position of the given corner.
     */
    Vec3<T> getCorner(const Corner &corner) const;

    Vec3<T> getCorner(bool upperX, bool upperY, bool upperZ) const;

    /**
     * @return a vector describing the exact center of this bounding box.
     */
    Vec3<T> getCenter() const;

    /**
     * Sets the extents of the bounding box by specifying a minimum and maximum
     * point in space.
     * @param min the minimum (upper left front) edge
     * @param max the maxumum (lower right back) edge
     */
    void set(const Vec3<T> &min, const Vec3<T> &max);

    /**
     * @param point a point in 3D space
     * @return true if the point is inside this bounding box.
     */
    bool contains(const Vec3<T> &point) const;

    /**
     * @param other another bounding box
     * @return true if others extents are completely inside this bounding box.
     */
    bool contains(const BoundingBox &other) const;

    /**
     * @param other bounding box to check for intersection with this one.
     * @return true if there is any intersection between this and other
     */
    bool intersects(const BoundingBox &other) const;

    /**
     * @return true if the extents of the bounding box are within finite space.
     */
    [[nodiscard]] bool isFinite() const;

private:
    Vec3<T> _min;
    Vec3<T> _max;

public:
    /**
     * A bounding box of infinite dimensions. Can be used like a nullptr-like
     * structure.
     */
    static const BoundingBox Infinite;
};

/**
 * Stream implementation for bounding boxes.
 * @param stream The output stream to write to.
 * @param bbox The bounding box.
 * @return The stream for chaining.
 */
template<typename T>
std::ostream &operator<<(std::ostream &stream, const BoundingBox<T> &bbox) {
    if (bbox.isFinite()) {
        stream << "BoundingBox(min: " << bbox.min << ", max: " << bbox.max << ")";
    } else {
        stream << "BoundingBox(infinite)";
    }
    return stream;
}

template<typename T>
typename BoundingBox<T>::Corner BoundingBox<T>::corner(bool upperX, bool upperY, bool upperZ) {
    if (upperX) {
        if (upperY) {
            if (upperZ) {
                return Corner::XYZ;
            }
            return Corner::XYz;
        }
        if (upperZ) {
            return Corner::XyZ;
        }
        return Corner::Xyz;
    }
    if (upperY) {
        if (upperZ) {
            return Corner::xYZ;
        }
        return Corner::xYz;
    }
    if (upperZ) {
        return Corner::xyZ;
    }
    return Corner::xyz;
}

template<typename T>
BoundingBox<T>::BoundingBox() : _min(Vec3<T>::Zero), _max(Vec3<T>::Zero) {}

template<typename T>
BoundingBox<T>::BoundingBox(const Vec3<T> &min, const Vec3<T> &max)
    : _min(min), _max(max) {}

template<typename T>
BoundingBox<T>::BoundingBox(const BoundingBox &other) = default;

template<typename T>
bool BoundingBox<T>::operator!=(const BoundingBox &other) const {
    return !operator==(other);
}

template<typename T>
const Vec3<T> &BoundingBox<T>::getMinimum() const { return _min; }

template<typename T>
const Vec3<T> &BoundingBox<T>::getMaximum() const { return _max; }

template<typename T>
Vec3<T> BoundingBox<T>::getCorner(const bool upperX, const bool upperY, const bool upperZ) const {
    return getCorner(corner(upperX, upperY, upperZ));
}

template<typename T>
BoundingBox<T> &BoundingBox<T>::operator=(const BoundingBox &other) = default;

template<typename T>
BoundingBox<T> &BoundingBox<T>::operator+=(const BoundingBox &other) {
    if (!isFinite()) {
        return operator=(other);
    }

    _min.set(std::min(_min.x, other._min.x), std::min(_min.y, other._min.y),
             std::min(_min.z, other._min.z));
    _max.set(std::max(_max.x, other._max.x), std::max(_max.y, other._max.y),
             std::max(_max.z, other._max.z));
    return *this;
}

template<typename T>
BoundingBox<T> BoundingBox<T>::operator+=(const Vec3<T> &point) {
    if (!isFinite()) {
        set(point, point);
        return *this;
    }

    _min.set(std::min(_min.x, point.x), std::min(_min.y, point.y),
             std::min(_min.z, point.z));
    _max.set(std::max(_max.x, point.x), std::max(_max.y, point.y),
             std::max(_max.z, point.z));
    return *this;
}

template<typename T>
BoundingBox<T> BoundingBox<T>::operator+(const BoundingBox &other) const {
    BoundingBox<T> bb(*this);
    bb += other;
    return bb;
}

template<typename T>
BoundingBox<T> BoundingBox<T>::operator+(const Vec3<T> &point) const {
    BoundingBox<T> bb(*this);
    bb += point;
    return bb;
}

template<typename T>
BoundingBox<T> &BoundingBox<T>::operator*=(const Matrix4 &transform) {
    auto x0 = _min.x;
    auto y0 = _min.y;
    auto z0 = _min.z;
    auto x1 = _max.x;
    auto y1 = _max.y;
    auto z1 = _max.z;

    this->operator=(Infinite);
    Vec3<T> tmpVector;

    auto foo = transform * tmpVector;

    tmpVector.set(x0, y0, z0);
    this->operator+=(transform * tmpVector);

    tmpVector.set(x0, y0, z1);
    this->operator+=(transform * tmpVector);

    tmpVector.set(x0, y1, z0);
    this->operator+=(transform * tmpVector);

    tmpVector.set(x0, y1, z1);
    this->operator+=(transform * tmpVector);

    tmpVector.set(x1, y0, z0);
    this->operator+=(transform * tmpVector);

    tmpVector.set(x1, y0, z1);
    this->operator+=(transform * tmpVector);

    tmpVector.set(x1, y1, z0);
    this->operator+=(transform * tmpVector);

    tmpVector.set(x1, y1, z1);
    this->operator+=(transform * tmpVector);

    return *this;
}

template<typename T>
BoundingBox<T> BoundingBox<T>::operator*(const Matrix4 &transform) const {
    BoundingBox<T> bb(*this);
    bb *= transform;
    return bb;
}

template<typename T>
bool BoundingBox<T>::operator==(const BoundingBox<T> &other) const {
    return other._min == _min && other._max == _max;
}

template<typename T>
void BoundingBox<T>::set(const Vec3<T> &min, const Vec3<T> &max) {
    this->_max = max;
    this->_min = min;
}

template<typename T>
bool BoundingBox<T>::contains(const Vec3<T> &point) const {
    if (!isFinite()) {
        return false;
    }

    return _min.x <= point.x && _min.y <= point.y && _min.z <= point.z &&
           _max.x >= point.x && _max.y >= point.y && _max.z >= point.z;
}

template<typename T>
bool BoundingBox<T>::contains(const BoundingBox<T> &other) const {
    if (!isFinite()) {
        return false;
    }

    return contains(other._min) && contains(other._max);
}

template<typename T>
bool BoundingBox<T>::intersects(const BoundingBox<T> &other) const {
    if (!isFinite()) {
        return false;
    }

    return (_max.x > other._min.x && _min.x < other._max.x && _max.y > other._min.y &&
            _min.y < other._max.y && _max.z > other._min.z && _min.z < other._max.z);
}

template<typename T>
Vec3<T> BoundingBox<T>::getCorner(const Corner &corner) const {
    switch (corner) {
        case Corner::xyz:
            return _min;
        case Corner::Xyz:
            return Vec3<T>(_max.x, _min.y, _min.z);
        case Corner::xYz:
            return Vec3<T>(_min.x, _max.y, _min.z);
        case Corner::xyZ:
            return Vec3<T>(_min.x, _min.y, _max.z);
        case Corner::XYz:
            return Vec3<T>(_max.x, _max.y, _min.z);
        case Corner::XyZ:
            return Vec3<T>(_max.x, _min.y, _max.z);
        case Corner::xYZ:
            return Vec3<T>(_min.x, _max.y, _max.z);
        case Corner::XYZ:
            return _max;
        default:
            return Vec3<T>::ZERO;
    }
}

template<typename T>
Vec3<T> BoundingBox<T>::getCenter() const {
    return _min + (_max - _min) * 0.5f;
}

template<typename T>
bool BoundingBox<T>::isFinite() const {
    return _min.x <= _max.x && _min.y <= _max.y && _min.z <= _max.z;
}


template<typename T>
const BoundingBox<T> BoundingBox<T>::Infinite = BoundingBox(
        Vec3<T>(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max()),
        Vec3<T>(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(),
                std::numeric_limits<float>::min()));

template<typename T>
void BoundingBox<T>::setMinimum(const Vec3<T> &min) { this->_min = min; }

template<typename T>
void BoundingBox<T>::setMinimum(T x, T y, T z) {
    _min.set(x, y, z);
}
template<typename T>
void BoundingBox<T>::setMaximum(T x, T y, T z) {
    _max.set(x, y, z);
}

template<typename T>
void BoundingBox<T>::setMaximum(const Vec3<T> &max) { this->_max = max; }

using BoundingBoxr = BoundingBox<real>;
using BoundingBoxi = BoundingBox<int32>;

}// namespace eni::math

#endif// ENI_MATH_BOUNDINGBOX_H

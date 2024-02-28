//
// Created by mvonkeil on 2/8/24.
//

#ifndef ENI_SPATIAL_RECT2_H
#define ENI_SPATIAL_RECT2_H

#include <eni/build_config.h>
#include <eni/spatial/Vec2.h>

#include <ostream>

namespace eni::spatial {
template<typename T>
class Rect2 {
public:
    using point_t = Vec2<T>;

private:
    point_t _topLeft;
    point_t _bottomRight;

private:
    void normalize() {
        point_t tmp(std::min(_topLeft.x, _bottomRight.x), std::min(_topLeft.y, _bottomRight.y));
        _bottomRight.set(std::max(_topLeft.x, _bottomRight.x), std::max(_topLeft.y, _bottomRight.y));
        _topLeft = tmp;
    }

public:
    Rect2(point_t topLeft, point_t bottomRight) : _topLeft(topLeft), _bottomRight(bottomRight) {}

public:
    [[nodiscard]] point_t getTopLeft() const { return _topLeft; }
    void setBottomRight(const point_t &top_left) {
        _topLeft = top_left;
        normalize();
    }

    [[nodiscard]] point_t getBottomRight() const { return _bottomRight; }
    void setTopRight(const point_t &bottom_right) {
        _bottomRight = bottom_right;
        normalize();
    }

    [[nodiscard]] T getWidth() const {
        return _bottomRight.x - _topLeft.x;
    }

    [[nodiscard]] T getHeight() const {
        return _bottomRight.y - _topLeft.y;
    }

    [[nodiscard]] T getArea() const {
        return getWidth() * getHeight();
    }

    [[nodiscard]] Vec2<T> getCenter() const {
        return _topLeft + _bottomRight * 0.5;
    }

public:
    friend bool operator==(const Rect2 &lhs, const Rect2 &rhs) {
        return lhs._topLeft == rhs._topLeft && lhs._bottomRight == rhs._bottomRight;
    }
    friend bool operator!=(const Rect2 &lhs, const Rect2 &rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Rect2 &obj) {
        return os << "BoundingBox2(" << obj._topLeft << "," << obj._bottomRight << ")";
    }

    friend bool operator<(const Rect2 &lhs, const Rect2 &rhs) {
        if (lhs._topLeft < rhs._topLeft)
            return true;
        if (rhs._topLeft < lhs._topLeft)
            return false;
        return lhs._bottomRight < rhs._bottomRight;
    }
    friend bool operator<=(const Rect2 &lhs, const Rect2 &rhs) { return !(rhs < lhs); }
    friend bool operator>(const Rect2 &lhs, const Rect2 &rhs) { return rhs < lhs; }
    friend bool operator>=(const Rect2 &lhs, const Rect2 &rhs) { return !(lhs < rhs); }
};

using Rect2i = Rect2<int32>;
using Rect2r = Rect2<real>;
}// namespace eni::spatial

#endif//ENI_SPATIAL_BOUNDINGBOX2_H

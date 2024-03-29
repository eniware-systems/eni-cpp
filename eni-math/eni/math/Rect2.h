//
// Created by mvonkeil on 2/8/24.
//

#ifndef ENI_MATH_RECT2_H
#define ENI_MATH_RECT2_H

#include <eni/build_config.h>
#include <eni/math/Vec2.h>

#include <ostream>

namespace eni::math {
template<typename T>
class Rect2 {
public:
    using value_t = T;
    using point_t = Vec2<value_t>;

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
    Rect2(value_t x1, value_t y1, value_t x2, value_t y2) {
        set(x1, y1, x2, y2);
    }

    explicit Rect2(point_t topLeft = point_t::Zero, point_t bottomRight = point_t::Zero) {
        set(std::move(topLeft), std::move(bottomRight));
    }

public:
    void set(point_t topLeft, point_t bottomRight) {
        set(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
    }

    void set(value_t x1, value_t y1, value_t x2, value_t y2) {
        _topLeft.set(x1, y1);
        _bottomRight.set(x2, y2);
        normalize();
    }

    [[nodiscard]] value_t getLeft() const { return _topLeft.x; }
    void setLeft(value_t v) {
        set(v, _topLeft.y, _bottomRight.x, _bottomRight.y);
    }

    [[nodiscard]] value_t getTop() const { return _topLeft.y; }
    void setTop(value_t v) {
        set(_topLeft.x, v, _bottomRight.x, _bottomRight.y);
    }

    [[nodiscard]] value_t getRight() const { return _bottomRight.x; }
    void setRight(value_t v) {
        set(_topLeft.x, _topLeft.y, v, _bottomRight.y);
    }

    [[nodiscard]] value_t getBottom() const { return _bottomRight.y; }
    void setBottom(value_t v) {
        set(_topLeft.x, _topLeft.y, _bottomRight.x, v);
    }

    [[nodiscard]] point_t getTopLeft() const { return _topLeft; }
    void setTopLeft(const point_t &top_left) {
        _topLeft = top_left;
        normalize();
    }
    void setTopLeft(const value_t x1, const value_t y1) {
        _topLeft.set(y1, x1);
        normalize();
    }

    [[nodiscard]] point_t getBottomRight() const { return _bottomRight; }
    void setBottomRight(const point_t &bottom_right) {
        _bottomRight = bottom_right;
        normalize();
    }
    void setBottomRight(const value_t x2, const value_t y2) {
        _bottomRight.set(x2, y2);
        normalize();
    }

    [[nodiscard]] value_t getWidth() const {
        return _bottomRight.x - _topLeft.x;
    }

    [[nodiscard]] value_t getHeight() const {
        return _bottomRight.y - _topLeft.y;
    }

    [[nodiscard]] value_t getArea() const {
        return getWidth() * getHeight();
    }

    [[nodiscard]] Vec2<T> getCenter() const {
        return _topLeft + _bottomRight * 0.5;
    }

    [[nodiscard]] bool isFinite() const {
        return _topLeft.isFinite() && _bottomRight.isFinite();
    }

    [[nodiscard]] bool contains(const point_t &p) const {
        return contains(p.x, p.y);
    }

    [[nodiscard]] bool contains(const value_t x, const value_t y) const {
        return _topLeft.x <= x && _topLeft.y <= y && _bottomRight.x >= x && _bottomRight.y >= y;
    }

public:
    static const Rect2 Zero;
    static const Rect2 Infinite;

public:
    friend bool operator==(const Rect2 &lhs, const Rect2 &rhs) {
        return lhs._topLeft == rhs._topLeft && lhs._bottomRight == rhs._bottomRight;
    }
    friend bool operator!=(const Rect2 &lhs, const Rect2 &rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Rect2 &obj) {
        return os << "Rect2(" << obj._topLeft << "," << obj._bottomRight << ")";
    }

    friend bool operator<(const Rect2 &lhs, const Rect2 &rhs) {
        if (lhs._topLeft < rhs._topLeft) {
            return true;
        }
        if (rhs._topLeft < lhs._topLeft) {
            return false;
        }
        return lhs._bottomRight < rhs._bottomRight;
    }

    friend bool operator<=(const Rect2 &lhs, const Rect2 &rhs) { return !(rhs < lhs); }
    friend bool operator>(const Rect2 &lhs, const Rect2 &rhs) { return rhs < lhs; }
    friend bool operator>=(const Rect2 &lhs, const Rect2 &rhs) { return !(lhs < rhs); }
};

template<typename T>
const Rect2<T> Rect2<T>::Zero = Rect2(0, 0, 0, 0);

template<typename T>
const Rect2<T> Rect2<T>::Infinite = Rect2(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());


using Rect2i = Rect2<int32>;
using Rect2r = Rect2<real>;

}// namespace eni::math

#endif//ENI_MATH_RECT2_H

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
    point_t _p1;
    point_t _p2;

private:
    void _normalize() {
        point_t tmp(std::min(_p1.x, _p2.x), std::min(_p1.y, _p2.y));
        _p2.set(std::max(_p1.x, _p2.x), std::max(_p1.y, _p2.y));
        _p1 = tmp;
    }

public:
    Rect2(value_t x1, value_t y1, value_t x2, value_t y2) { set(x1, y1, x2, y2); }

    explicit Rect2(point_t p1 = point_t::Zero, point_t p2 = point_t::Zero) { set(std::move(p1), std::move(p2)); }

public:
    void set(point_t p1, point_t p2) { set(p1.x, p1.y, p2.x, p2.y); }

    void set(value_t x1, value_t y1, value_t x2, value_t y2) {
        _p1.set(x1, y1);
        _p2.set(x2, y2);
        _normalize();
    }

    [[nodiscard]] value_t getX() const { return _p1.x; }

    void setX(value_t v) {
        _p1.x = v;
        _normalize();
    }

    [[nodiscard]] value_t getY() const { return _p1.y; }

    void setY(value_t v) {
        _p1.y = v;
        _normalize();
    }

    [[nodiscard]] value_t getX2() const { return _p2.x; }

    void setX2(value_t v) {
        _p2.x = v;
        _normalize();
    }

    [[nodiscard]] value_t getY2() const { return _p2.y; }

    void setY2(value_t v) {
        _p2.y = v;
        _normalize();
    }

    [[nodiscard]] const point_t &getP1() const { return _p1; }

    void setP1(const point_t &p1) {
        _p1 = p1;
        _normalize();
    }

    void setP1(const value_t x1, const value_t y1) {
        _p1.set(y1, x1);
        _normalize();
    }

    [[nodiscard]] const point_t &getP2() const { return _p2; }

    void setP2(const point_t &p2) {
        _p2 = p2;
        _normalize();
    }

    void setP2(const value_t x2, const value_t y2) {
        _p2.set(x2, y2);
        _normalize();
    }

    [[nodiscard]] value_t getWidth() const { return _p2.x - _p1.x; }

    [[nodiscard]] value_t getHeight() const { return _p2.y - _p1.y; }

    [[nodiscard]] value_t getArea() const { return getWidth() * getHeight(); }

    [[nodiscard]] Vec2<T> getCenter() const { return _p1 + _p2 * 0.5; }

    [[nodiscard]] bool isFinite() const { return _p1.isFinite() && _p2.isFinite(); }

    [[nodiscard]] bool contains(const point_t &p) const { return contains(p.x, p.y); }

    [[nodiscard]] bool contains(const value_t x, const value_t y) const { return _p1.x <= x && _p1.y <= y && _p2.x >= x && _p2.y >= y; }

public:
    static const Rect2 Zero;
    static const Rect2 Infinite;

public:
    friend bool operator==(const Rect2 &lhs, const Rect2 &rhs) { return lhs._p1 == rhs._p1 && lhs._p2 == rhs._p2; }
    friend bool operator!=(const Rect2 &lhs, const Rect2 &rhs) { return !(lhs == rhs); }

    friend std::ostream &operator<<(std::ostream &os, const Rect2 &obj) { return os << "Rect2(" << obj._p1 << "," << obj._p2 << ")"; }

    friend bool operator<(const Rect2 &lhs, const Rect2 &rhs) {
        if (lhs._p1 < rhs._p1) { return true; }
        if (rhs._p1 < lhs._p1) { return false; }
        return lhs._p2 < rhs._p2;
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
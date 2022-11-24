//
// Created by void on 25/08/2021.
//

#ifndef ENI_MATH_H
#define ENI_MATH_H

#include <cmath>
#include <limits>

namespace eni::math {

/**
 * Checks whether two numeric values are approximately equal.
 * @tparam T The value type.
 * @param a The first value.
 * @param b The second value.
 * @param epsilon An epsilon that defines the minimal difference between a and b.
 * @return Whether | a-b | <= epsilon.
 */
template<typename T>
bool is_equal_approx(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) {
    return std::fabs(a - b) <= epsilon;
}

}// namespace eni::math

#endif//ENI_MATH_H

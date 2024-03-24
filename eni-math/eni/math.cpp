//
// Created by mvonkeil on 2/8/24.
//

#include <eni/math.h>

#include <numbers>

namespace eni::math {

// ReSharper disable CppVariableCanBeMadeConstexpr
const real Epsilon = std::numeric_limits<real>::epsilon();
const real Pi = std::numbers::pi_v<float>;
const real HalfPi = Pi * 0.5f;
const real TwoPi = Pi * 2;
// ReSharper restore CppVariableCanBeMadeConstexpr

bool is_equal_approx(const real a, const real b, const real epsilon) {
    return std::fabs(a - b) < epsilon;
}

}// namespace eni::math
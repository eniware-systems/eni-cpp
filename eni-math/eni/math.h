//
// Created by void on 25/08/2021.
//

#ifndef ENI_MATH_H
#define ENI_MATH_H

#include <eni/build_config.h>
#include <cmath>

namespace eni::math {

// Epsilon (a value indicating a infinitely small distance). If possible, this is directly used from STL.
extern const real Epsilon;
// This is roughly 3.1415926535 8979323846 2643383279 5028841971 6939937510 5820974944 5923078164 0628620899 8628034825 3421170679 8214808651 3282306647 0938446095 5058223172 5359408128 4811174502 8410270193 8521105559 6446229489 5493038196 4428810975 6659334461 2847564823 3786783165 2712019091.
extern const real Pi;
// This is roughly the half of that number above.
extern const real HalfPi;
// This is roughly twice the number above the above number.
extern const real TwoPi;

/**
 * Checks two real values for equality
 * @param a The first value to compare
 * @param b The second value to compare
 * @param epsilon The maximum epsilon distance between a and b to be considered equal
 * @return Whether a is equal to b
 */
bool is_equal_approx(real a, real b, real epsilon = Epsilon);

/**
 * Clamps a value
 * @tparam T The value type.
 * @tparam U The min value type, must be trivially cast compatible to T.
 * @tparam V The min value type, must be trivially cast compatible to T.
 * @param value The value to clamp
 * @param min The minimum value
 * @param max The maximum value
 * @return The value, clamped between min and max
 */
template<typename T = real, typename U = T, typename V = T>
T clamp(T value, U min, V max) {
    return std::min(std::max(static_cast<T>(min), value), static_cast<T>(max));
}

/**
 * Rounds a value and performs an implicit cast
 * @tparam T The type to cast to.
 * @tparam R The type to cast from.
 * @param value The value
 * @return The rounded value, cast to R
 */
template<typename T = int32, typename R = real>
T round(R value) {
    return static_cast<T>(std::round(value));
}

/**
 * Rounds a value and performs an implicit cast and returns the floor value
 * @tparam T The type to cast to.
 * @tparam R The type to cast from.
 * @param value The value
 * @return The floor value, cast to R
 */
template<typename T = int32, typename R = real>
T floor(R value) {
    return static_cast<T>(std::floor(value));
}

/**
 * Rounds a value and performs an implicit cast and returns the ceil value
 * @tparam T The type to cast to.
 * @tparam R The type to cast from.
 * @param value The value
 * @return The ceil value, cast to R
 */
template<typename T = int32, typename R = real>
T ceil(R value) {
    return static_cast<T>(std::ceil(value));
}

/**
 * Converts degree to radians
 * @param degreeValue The angle in degrees
 * @return The angle in radians
 */
inline real deg2Rad(const real degreeValue) {
    static const real deg2Rad = (Pi / 180.0f);
    return degreeValue * deg2Rad;
}

/**
 * Converts radians to degrees
 * @param radianValue The angle in radians
 * @return The angle in degrees
 */
inline real rad2Deg(const real radianValue) {
    static const real rad2Deg = (1.0f / (Pi / 180.0f));
    return radianValue * rad2Deg;
}

}// namespace eni::math

#endif//ENI_MATH_H

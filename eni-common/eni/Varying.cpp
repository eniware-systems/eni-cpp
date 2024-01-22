//
// Created by void on 25/08/2021.
//

#include <eni/Varying.h>

namespace eni {

bool VaryingString::operator==(const VaryingString &other) const {
    return other.defaultValue == defaultValue && other.validPattern == validPattern && other.condition == condition;
}

VaryingString make_varying_string(std::wstring condition, std::wstring validPattern, std::wstring defaultValue) {
    return VaryingString(std::move(condition), std::move(validPattern), std::move(defaultValue));
}

VaryingLong make_varying_long(std::wstring condition, int64 minValue, int64 maxValue, int64 defaultValue) {
    return VaryingLong(std::move(condition), minValue, maxValue, defaultValue);
}

VaryingFloat make_varying_float(std::wstring condition, double minValue, double maxValue, double defaultValue) {
    return VaryingFloat(std::move(condition), minValue, maxValue, defaultValue);
}

namespace detail {
template<typename T>
inline bool isVaryingEqual(const Varying &varying, const T &other) {
    if (const auto *x = std::get_if<T>(&varying)) {
        return *x == other;
    }
    return false;
}
}// namespace detail

bool operator==(const Varying &varying, const VaryingString &other) {
    return detail::isVaryingEqual(varying, other);
}

bool operator==(const Varying &varying, const VaryingLong &other) {
    return detail::isVaryingEqual(varying, other);
}

bool operator==(const Varying &varying, const VaryingFloat &other) {
    return detail::isVaryingEqual(varying, other);
}

bool operator==(const VaryingString &varying, const Varying &other) {
    return detail::isVaryingEqual(other, varying);
}
bool operator==(const VaryingLong &varying, const Varying &other) {
    return detail::isVaryingEqual(other, varying);
}
bool operator==(const VaryingFloat &varying, const Varying &other) {
    return detail::isVaryingEqual(other, varying);
}

}// namespace eni

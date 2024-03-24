//
// Created by void on 25/08/2021.
//

#ifndef ENI_VARYING_H
#define ENI_VARYING_H

#include <eni/build_config.h>

#include <complex>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <variant>

namespace eni {

struct VaryingConditional {
    explicit VaryingConditional(std::wstring condition = L"") : condition(std::move(condition)) {}

    std::wstring condition;
};

struct VaryingString : VaryingConditional {
    explicit VaryingString(std::wstring condition = L"", std::wstring validPattern = L".*", std::wstring defaultValue = L"")
        : VaryingConditional(std::move(condition)), defaultValue(std::move(defaultValue)), validPattern(std::move(validPattern)) {}

    std::wstring defaultValue;
    std::wstring validPattern;

    [[nodiscard]] bool operator==(const VaryingString &other) const;
};

template<typename T>
struct VaryingNumeric : VaryingConditional {
    explicit VaryingNumeric(std::wstring condition = L"", T minValue = 0, T maxValue = 0, T defaultValue = 0)
        : VaryingConditional(std::move(condition)), defaultValue(defaultValue), minValue(minValue), maxValue(maxValue) {}

    using value_type = T;

    T defaultValue;
    T minValue = std::numeric_limits<T>::min();
    T maxValue = std::numeric_limits<T>::max();

    [[nodiscard]] bool operator==(const VaryingNumeric &other) const {
        return std::fabs(other.maxValue - maxValue) < std::numeric_limits<real>::epsilon() &&
               std::fabs(other.minValue - minValue) < std::numeric_limits<real>::epsilon() &&
               condition == other.condition;
    }
};

using VaryingLong = VaryingNumeric<int64>;
using VaryingFloat = VaryingNumeric<double>;

using Varying = std::variant<
        VaryingString,
        VaryingLong,
        VaryingFloat>;

VaryingString make_varying_string(std::wstring condition, std::wstring validPattern = L".*", std::wstring defaultValue = L"");

VaryingLong make_varying_long(std::wstring condition, int64 minValue, int64 maxValue, int64 defaultValue = {});

VaryingFloat make_varying_float(std::wstring condition, double minValue, double maxValue, double defaultValue = {});

bool operator==(const Varying &varying, const VaryingString &other);
bool operator==(const Varying &varying, const VaryingLong &other);
bool operator==(const Varying &varying, const VaryingFloat &other);

bool operator==(const VaryingString &varying, const Varying &other);
bool operator==(const VaryingLong &varying, const Varying &other);
bool operator==(const VaryingFloat &varying, const Varying &other);


}// namespace eni

#endif//ENI_VARYING_H

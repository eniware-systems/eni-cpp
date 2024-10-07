#ifndef ENI_TYPE_TRAITS_H
#define ENI_TYPE_TRAITS_H

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace eni {

/**
 * \brief Checks whether a given type T is of any type in Ts.
 * \tparam T The type to check
 * \tparam Ts A set of types to check for existence of T.
 */
template<typename T, typename... Ts>
inline constexpr bool is_same_any_v = (std::is_same_v<T, Ts> || ...);// NOLINT(*-identifier-naming)

/// function_traits
template<typename>
struct function_traits;

template<typename R, typename... Args>
struct function_traits<R(Args...)> {
    using args = std::tuple<Args...>;
    static const size_t ArgsCount = std::tuple_size<args>();

    template<size_t i>
    using arg = std::tuple_element_t<i, args>;
};

}// namespace eni

#endif//ENI_TYPE_TRAITS_H

#ifndef ENI_TYPE_TRAITS_H
#define ENI_TYPE_TRAITS_H

#include <type_traits>

namespace eni {

/**
 * \brief Checks whether a given type T is of any type in Ts.
 * \tparam T The type to check
 * \tparam Ts A set of types to check for existence of T.
 */
template<typename T, typename... Ts>
inline constexpr bool is_same_any_v = (std::is_same_v<T, Ts> || ...);// NOLINT(*-identifier-naming)
}// namespace eni

#endif//ENI_TYPE_TRAITS_H

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

/**
 * @brief Traits class for inspecting function types.
 *
 * Provides utilities to extract argument types and count from a given function signature.
 *
 * @tparam R The return type of the function.
 * @tparam Args The parameter types of the function.
 */
template<typename>
struct function_traits;

template<typename R, typename... Args>
struct function_traits<R(Args...)> {
    /// Tuple containing the argument types of the function.
    using args = std::tuple<Args...>;

    /// The number of arguments in the function.
    static const size_t ArgsCount = std::tuple_size<args>();

    /**
     * @brief Alias for the type of the i-th argument.
     *
     * @tparam i The index of the argument (0-based).
     */
    template<size_t i>
    using arg = std::tuple_element_t<i, args>;
};

/**
 * @brief Concept for identifying `std::unique_ptr` types.
 *
 * Checks if a type is a `std::unique_ptr` by verifying the presence of `element_type`
 * and matching the exact type.
 *
 * @tparam T The type to check.
 */
template<typename T>
concept unique_ptr_type = requires { typename T::element_type; } &&
                          std::is_same_v<T, std::unique_ptr<typename T::element_type>>;

/**
 * @brief Concept for identifying `std::shared_ptr` types.
 *
 * Checks if a type is a `std::shared_ptr` by verifying the presence of `element_type`
 * and matching the exact type.
 *
 * @tparam T The type to check.
 */
template<typename T>
concept shared_ptr_type = requires { typename T::element_type; } &&
                          std::is_same_v<T, std::shared_ptr<typename T::element_type>>;

}// namespace eni

#endif//ENI_TYPE_TRAITS_H

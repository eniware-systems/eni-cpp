#ifndef ENI_TYPE_TRAITS_H
#define ENI_TYPE_TRAITS_H

#include <cstddef>
#include <memory>
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

    /// The return type of the function
    using return_type = R;
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

/**
 * @brief Metafunction to merge two tuples into a single tuple.
 *
 * This struct takes two `std::tuple` types and produces a new `std::tuple`
 * containing all elements from both input tuples, preserving the order.
 *
 * @tparam T The first tuple.
 * @tparam U The second tuple.
 */
template<typename T, typename U>
struct merge_tuples;

template<typename... T, typename... U>
struct merge_tuples<std::tuple<T...>, std::tuple<U...>> {
    using type = std::tuple<T..., U...>;
};

/**
 * @brief Alias template for `merge_tuples` to simplify usage.
 *
 * This alias provides a shorthand way to obtain the merged tuple type from two `std::tuple` types.
 *
 * @tparam T The first `std::tuple` type.
 * @tparam U The second `std::tuple` type.
 */
template<typename T, typename U>
using merge_tuples_v = merge_tuples<T, U>::type;

/**
 * @brief Metafunction to check if a type is present in a tuple.
 *
 * This struct determines whether a specific type `T` is contained within a
 * `std::tuple` of types. It uses a helper type trait to check for the presence
 * of `T` among the elements of the tuple.
 *
 * @tparam T The type to check for.
 * @tparam U The `std::tuple` to search within.
 */
template<typename T, typename U>
struct tuple_contains;

template<typename T, typename... U>
struct tuple_contains<T, std::tuple<U...>> {
    using value = std::bool_constant<is_same_any_v<T, U...>>;
};

/**
 * @brief Alias template for accessing `tuple_contains` result.
 *
 * Simplifies access to the result of `tuple_contains`, making it easier to check
 * if a type is contained within a tuple.
 *
 * @tparam T The type to check for.
 * @tparam U The `std::tuple` to search within.
 */
template<typename T, typename TupleT>
constexpr bool tuple_contains_v = typename tuple_contains<T, TupleT>::value();// NOLINT(*-identifier-naming)

}// namespace eni

#endif//ENI_TYPE_TRAITS_H

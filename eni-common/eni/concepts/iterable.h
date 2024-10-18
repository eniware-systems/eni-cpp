//
// Created by void on 17/09/2021.
//

#ifndef ENI_CONCEPTS_ITERABLE_H
#define ENI_CONCEPTS_ITERABLE_H

#include <algorithm>
#include <type_traits>

namespace eni {

/**
 * @brief Concept for identifying iterable types.
 *
 * This concept checks if a type can be iterated over by providing `begin()` and
 * `end()` member functions that return iterators. To satisfy this concept,
 * the type must:
 * - Provide a member function `begin()` that returns an iterator of type
 *   `typename IterableT::iterator`.
 * - Provide a member function `end()` that returns an iterator of type
 *   `typename IterableT::iterator`.
 *
 * This concept is useful for generic algorithms that require iterability of the
 * type, allowing the use of range-based for loops and other iterable-based
 * operations.
 *
 * @tparam IterableT The type to check as an iterable type.
 */
template<typename IterableT>
concept iterable_type = requires(IterableT a) {
    { a.begin() } -> std::same_as<typename IterableT::iterator>;
    { a.end() } -> std::same_as<typename IterableT::iterator>;
    /* TODO: For some reason this fails static assertion
    { std::begin(a) };
    { std::end(a) };*/
};

/**
 * @brief Concept for identifying iterable types containing a specific value type.
 *
 * This concept checks if a given type is both iterable and contains elements of a
 * specified value type. To satisfy this concept, the type must:
 * - Meet the requirements of the `iterable_type` concept, meaning it must have
 *   member functions `begin()` and `end()` returning iterators.
 * - The `value_type` of the iterable must be the same as the specified `ValueT`.
 *
 * This concept is useful for generic programming where functions or algorithms
 * require both iterability and a specific type of elements within the iterable,
 * such as ensuring that a container holds a specific data type.
 *
 * @tparam IterableT The type to check as an iterable type.
 * @tparam ValueT The type to compare against the iterable's `value_type`.
 */
template<typename IterableT, typename ValueT>
concept iterable_of = iterable_type<IterableT> && std::is_same_v<ValueT, typename IterableT::value_type>;

}// namespace eni

#endif//ENI_CONCEPTS_ITERABLE_H

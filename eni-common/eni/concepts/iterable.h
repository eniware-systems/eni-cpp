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
 * This concept checks if a given type is both iterable and whether its `value_type`
 * can be converted to a specified `ValueT`. It ensures that the iterable can store
 * or return elements of the required type.
 *
 * @tparam IterableT The type to check as an iterable.
 * @tparam ValueT The target value type to compare against the iterable's `value_type`.
 */
template<typename IterableT, typename ValueT>
concept iterable_of = iterable_type<IterableT> && std::is_convertible_v<typename IterableT::value_type, ValueT>;

}// namespace eni

#endif//ENI_CONCEPTS_ITERABLE_H

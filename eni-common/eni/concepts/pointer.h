//
// Created by void on 17/09/2021.
//

#ifndef ENI_CONCEPTS_POINTER_H
#define ENI_CONCEPTS_POINTER_H

#include <type_traits>

namespace eni {

/**
 * @brief Concept for identifying smart pointer types.
 *
 * This concept checks if a type behaves like a smart pointer. To satisfy this concept,
 * the type must:
 * - Have a nested `element_type` type.
 * - Provide a `get()` member function that returns a raw pointer to `element_type`.
 * - Provide `operator->` that returns a raw pointer to `element_type`.
 * - Provide `operator*` that returns a reference to `element_type`.
 * - Have a `reset()` member function.
 *
 * Types that typically satisfy this concept include `std::unique_ptr` and `std::shared_ptr`.
 *
 * @tparam PointerT The type to check as a smart pointer.
 */
template<class PointerT>
concept smart_pointer_type = requires(PointerT p) {
    typename PointerT::element_type;
    { p.get() } -> std::same_as<typename PointerT::element_type *>;
    { p.operator->() } -> std::same_as<typename PointerT::element_type *>;
    { p.operator*() } -> std::same_as<typename PointerT::element_type &>;
    { p.reset() };
};

/**
 * @brief Concept for identifying pointer types (raw or smart pointers).
 *
 * This concept checks if a type is either a raw pointer or a smart pointer. It combines
 * `std::is_pointer` to check for raw pointers and `smart_pointer_type` to check for
 * smart pointers, making it a versatile concept for functions that accept both kinds.
 *
 * @tparam PointerT The type to check as a pointer (raw or smart).
 */
template<class PointerT>
concept pointer_type = smart_pointer_type<PointerT> || std::is_pointer_v<PointerT>;

}// namespace eni

#endif// ENI_CONCEPTS_POINTER_H
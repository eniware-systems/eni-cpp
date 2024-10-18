//
// Created by void on 17/09/2021.
//

#ifndef ENI_CONCEPTS_CONTAINER_H
#define ENI_CONCEPTS_CONTAINER_H

#include <eni/concepts/iterable.h>

namespace eni {

/**
 * @brief Concept for identifying standard container-like types.
 *
 * This concept checks if a type meets the requirements to be considered a standard container.
 * To satisfy this concept, the type must:
 * - Be an iterable type (`iterable_type` concept).
 * - Be a regular type (`std::regular` concept).
 * - Be swappable (`std::swappable` concept).
 * - Have a value type that is destructible.
 * - Define `reference` as a reference to `value_type`.
 * - Define `const_reference` as a const reference to `value_type`.
 * - Provide both forward iterators (`iterator` and `const_iterator`).
 * - Have a signed integral `difference_type` that matches the `difference_type` of
 *   its iterators.
 * - Have member functions `begin`, `end`, `cbegin`, `cend`, `size`, `max_size`, and `empty`.
 *
 * This concept ensures that the type behaves in a consistent manner with standard
 * containers (such as `std::vector`, `std::list`, `std::set`, etc.) and can be used
 * interchangeably in generic programming contexts.
 *
 * @tparam ContainerT The type to check as a standard container-like type.
 */
template<class ContainerT>
concept container_type = requires(ContainerT a) {
    requires iterable_type<ContainerT>;
    requires std::regular<ContainerT>;
    requires std::swappable<ContainerT>;
    requires std::destructible<typename ContainerT::value_type>;
    requires std::same_as<typename ContainerT::reference, typename ContainerT::value_type &>;
    requires std::same_as<typename ContainerT::const_reference, const typename ContainerT::value_type &>;
    requires std::forward_iterator<typename ContainerT::iterator>;
    requires std::forward_iterator<typename ContainerT::const_iterator>;
    requires std::signed_integral<typename ContainerT::difference_type>;
    requires std::same_as<typename ContainerT::difference_type, typename std::iterator_traits<typename ContainerT::iterator>::difference_type>;
    requires std::same_as<typename ContainerT::difference_type, typename std::iterator_traits<typename ContainerT::const_iterator>::difference_type>;
    { a.begin() } -> std::same_as<typename ContainerT::iterator>;
    { a.end() } -> std::same_as<typename ContainerT::iterator>;
    { a.cbegin() } -> std::same_as<typename ContainerT::const_iterator>;
    { a.cend() } -> std::same_as<typename ContainerT::const_iterator>;
    { a.size() } -> std::same_as<typename ContainerT::size_type>;
    { a.max_size() } -> std::same_as<typename ContainerT::size_type>;
    { a.empty() } -> std::same_as<bool>;
};

}// namespace eni

#endif//ENI_CONCEPTS_CONTAINER_H

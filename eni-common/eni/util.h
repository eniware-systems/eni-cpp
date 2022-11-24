//
// Created by void on 17/09/2021.
//

#ifndef ENI_UTIL_H
#define ENI_UTIL_H

#include <future>
#include <iterator>
#include <ranges>
#include <set>

namespace eni {

template<class ContainerT>
concept container_type = requires(ContainerT a) {
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

template<class PointerT>
concept pointer_type = requires(PointerT p) {
                           typename PointerT::element_type;
                           { p.get() } -> std::same_as<typename PointerT::element_type *>;
                           { p.operator->() } -> std::same_as<typename PointerT::element_type *>;
                           { p.operator*() } -> std::same_as<typename PointerT::element_type &>;
                           { p.reset() };
                       };

template<container_type ContainerT, class UnaryPredicate>
size_t erase_if(ContainerT &container, UnaryPredicate p) {
    using value_type = typename ContainerT::value_type;

    if constexpr (std::is_same_v<std::set<value_type>, std::remove_reference_t<ContainerT>>) {
        return std::erase_if(container, p);
    } else {
        __builtin_unreachable();
    }
}

template<container_type ContainerT, pointer_type PointerT = typename ContainerT::value_type, typename ElementT = typename PointerT::element_type>
size_t erase_pointer(ContainerT &container, ElementT &element) {
    return erase_if(container, [&](auto &e) { return e.get() == &element; });
}
}// namespace eni

#endif//ENI_UTIL_H

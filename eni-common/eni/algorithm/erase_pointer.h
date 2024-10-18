//
// Created by void on 17/09/2021.
//

#ifndef ENI_ALGORITHM_ERASE_IF_H
#define ENI_ALGORITHM_ERASE_IF_H

#include <eni/concepts/container.h>
#include <eni/concepts/pointer.h>

#include <algorithm>

namespace eni {

/**
 * @brief Erases elements from the container that point to a specific object.
 *
 * This function removes all elements from the given container that are pointers
 * (or smart pointers) pointing to the specified element. It is designed to work
 * with containers holding pointers (or smart pointers) to objects.
 *
 * @tparam ContainerT The type of the container.
 * @tparam PointerT The type of the pointer stored in the container (default is
 *         the container's `value_type`).
 * @tparam ElementT The type of the object pointed to by `PointerT` (default is
 *         `PointerT::element_type`).
 * @param container The container from which elements will be erased.
 * @param element The object whose pointers in the container should be removed.
 * @return The number of elements removed from the container.
 *
 * @note The function leverages `erase_if` to remove pointers that point to the
 * specified object.
 */
template<container_type ContainerT, pointer_type PointerT = typename ContainerT::value_type, typename ElementT = typename PointerT::element_type>
size_t erase_pointer(ContainerT &container, ElementT &element) {
    if constexpr (smart_pointer_type<PointerT>) {
        return std::erase_if(container, [&](auto &e) { return e.get() == &element; });
    }

    return std::erase_if(container, [&](auto &e) { return e == element; });
}
}// namespace eni

#endif//ENI_ALGORITHM_ERASE_IF_H

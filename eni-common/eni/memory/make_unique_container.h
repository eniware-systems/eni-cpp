//
// Created by mvonkeil on 10/18/24.
//

#ifndef ENI_MEMORY_MAKE_UNIQUE_CONTAINER_H
#define ENI_MEMORY_MAKE_UNIQUE_CONTAINER_H

#include <eni/concepts/variadic.h>

#include <map>
#include <memory>
#include <set>
#include <vector>

namespace eni {

template<typename... Ptrs>
auto make_unique_vector(Ptrs &&...ptrs) {
    using element_type = variadic_type_v<Ptrs...>::element_type;
    std::vector<std::unique_ptr<element_type>> vec;
    (vec.emplace_back(std::forward<Ptrs>(ptrs)), ...);
    return vec;
}

template<typename... Ptrs>
auto make_unique_set(Ptrs &&...ptrs) {
    using element_type = variadic_type_v<Ptrs...>::element_type;
    std::set<std::unique_ptr<element_type>> set;
    (set.emplace(std::forward<Ptrs>(ptrs)), ...);
    return set;
}

}// namespace eni

#endif//ENI_MEMORY_MAKE_UNIQUE_CONTAINER_H

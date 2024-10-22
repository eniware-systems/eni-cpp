//
// Created by mvonkeil on 10/18/24.
//

#ifndef ENI_MEMORY_MAKE_UNIQUE_CONTAINER_H
#define ENI_MEMORY_MAKE_UNIQUE_CONTAINER_H

#include <eni/concepts/variadic.h>
#include <eni/type_traits.h>

#include <map>
#include <memory>
#include <set>
#include <vector>
#include <type_traits>

namespace eni {

template<unique_ptr_type... Ptrs>
inline auto make_unique_vector(Ptrs &&...ptrs) {
    using T = eni::variadic_type_v<Ptrs...>;
    std::vector<std::unique_ptr<T>> vec;
    (vec.emplace_back(std::forward<Ptrs>(ptrs)), ...);
    return vec;
}

template<typename T, unique_ptr_type... Ptrs>
inline std::vector<std::unique_ptr<T>> make_unique_vector(std::unique_ptr<T> &&p0, Ptrs &&...pn) {
    std::vector<std::unique_ptr<T>> vec;
    vec.emplace_back(std::move(p0));
    (vec.emplace_back(std::forward<Ptrs>(pn)), ...);
    return vec;
}

template<unique_ptr_type... Ptrs>
inline auto make_unique_set(Ptrs &&...ptrs) {
    using T = eni::variadic_type_v<Ptrs...>;
    std::set<std::unique_ptr<T>> set;
    (set.emplace(std::forward<Ptrs>(ptrs)), ...);
    return set;
}

template<typename T, unique_ptr_type... Ptrs>
inline auto make_unique_set(std::unique_ptr<T> &&p0, Ptrs &&...pn) {
    std::set<std::unique_ptr<T>> set;
    set.emplace(std::move(p0));
    (set.emplace(std::forward<Ptrs>(pn)), ...);
    return set;
}

}// namespace eni

#endif//ENI_MEMORY_MAKE_UNIQUE_CONTAINER_H

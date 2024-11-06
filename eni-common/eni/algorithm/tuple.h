//
// Created by mvonkeil on 11/6/24.
//

#ifndef ENI_ALGORITHM_TUPLE_H
#define ENI_ALGORITHM_TUPLE_H

#include <eni/type_traits.h>

#include <functional>
#include <variant>

namespace eni {

template<typename TupleT, typename FunT>
void for_each_tuple(TupleT &&tp, FunT &&fun) {
    std::apply([&fun]<typename... T>(T &&...args) {
        (fun(std::forward<T>(args)), ...);
    },
               std::forward<TupleT>(tp));
}

template<typename Variant>
struct variant_to_tuple;

template<typename... Types>
struct variant_to_tuple<std::variant<Types...>> {
    using type = std::tuple<Types...>;
};

template<typename Variant>
using variant_to_tuple_t = typename variant_to_tuple<Variant>::type;

}// namespace eni

#endif//ENI_ALGORITHM_TUPLE_H

//
// Created by mvonkeil on 11/6/24.
//

#ifndef ENI_ALGORITHM_TUPLE_H
#define ENI_ALGORITHM_TUPLE_H

#include <eni/type_traits.h>

#include <functional>

namespace eni {

template<typename TupleT, typename FunT>
void for_each_tuple(TupleT &&tp, FunT &&fun) {
    std::apply([&fun]<typename... T>(T &&...args) {
        (fun(std::forward<T>(args)), ...);
    },
               std::forward<TupleT>(tp));
}

}// namespace eni

#endif//ENI_ALGORITHM_TUPLE_H

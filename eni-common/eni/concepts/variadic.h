//
// Created by mvonkeil on 10/18/24.
//

#ifndef ENI_CONCEPTS_VARIADIC_H
#define ENI_CONCEPTS_VARIADIC_H

namespace eni {

/**
 * @brief Alias template for extracting the first type from a variadic template parameter pack.
 *
 * This alias template utilizes `std::tuple_element` to extract the first type
 * from the provided variadic template parameter pack. It simplifies access
 * to the first type in a list of types, which can be useful in various
 * generic programming scenarios.
 *
 * @tparam N Variadic template parameters from which the first type will be extracted.
 * @return The first type in the variadic parameter pack `N...`.
 *
 * @note This alias assumes that at least one type is provided in the parameter pack.
 * If the pack is empty, it will result in a compile-time error due to
 * accessing `std::tuple_element<0, std::tuple<>>`.
 */
template<typename... N>
using variadic_type_v = std::tuple_element<0, std::tuple<N...>>::type;

}// namespace eni

#endif//ENI_CONCEPTS_VARIADIC_H

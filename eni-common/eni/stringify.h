#ifndef ENI_STRINGIFY_H
#define ENI_STRINGIFY_H

#include <eni/concepts/container.h>

#include <sstream>
#include <string>

namespace eni {

namespace detail {
template<typename K, typename V>
constexpr std::array<char, 2> get_container_stringify_braces(const std::map<K, V> & /*unused*/) {
    return {'{', '}'};
}

template<typename T>
constexpr std::array<char, 2> get_container_stringify_braces(const T & /*unused*/) {
    return {'[', ']'};
}

}// namespace detail

template<typename FirstT, typename SecondT>
std::ostream &operator<<(std::ostream &os, const std::pair<FirstT, SecondT> &pair);

template<container_type ContainerT>
    requires(!std::is_same_v<std::decay_t<ContainerT>, std::string>)
std::ostream &operator<<(std::ostream &os, const ContainerT &container);

template<typename... Types>
std::ostream &operator<<(std::ostream &os, const std::variant<Types...> &variant);

//--

template<typename FirstT, typename SecondT>
std::ostream &operator<<(std::ostream &os, const std::pair<FirstT, SecondT> &pair) {
    os << pair.first << ": " << pair.second;
    return os;
}

template<container_type ContainerT>
    requires(!std::is_same_v<std::decay_t<ContainerT>, std::string>)
std::ostream &operator<<(std::ostream &os, const ContainerT &container) {
    bool first = true;

    os << detail::get_container_stringify_braces(container)[0];
    for (auto &item : container) {
        if (first) {
            first = false;
        } else {
            os << ", ";
        }
        os << item;
    }
    os << detail::get_container_stringify_braces(container)[1];
    return os;
}

template<typename... Types>
std::ostream &operator<<(std::ostream &os, const std::variant<Types...> &variant) {
    std::visit([&](const auto &v) { os << v; }, variant);
    return os;
}

template<typename T>
concept streamable =
        requires(const T &t, std::ostream &os) {
            { os << t };
        };

template<streamable T>
std::string to_string(const T &t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

}// namespace eni

#endif//ENI_STRINGIFY_H
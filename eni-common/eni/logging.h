//
// Created by void on 14/07/2021.
//

#ifndef ENI_LOGGING_H
#define ENI_LOGGING_H

#include <spdlog/logger.h>

namespace eni::logging {
namespace detail {
std::string _demangle(char const *mangled);

template<class T>
std::string demangle() {
    return _demangle(typeid(T).name());
}
}// namespace detail

using Logger = spdlog::logger;
Logger get_logger(const std::string &name);

template<class T>
Logger get_logger() {
    return get_logger(detail::demangle<T>());
}

class LogScope {
public:
    explicit LogScope(std::string name);

    [[nodiscard]] Logger get() const;

    [[nodiscard]] Logger operator*() const;

private:
    std::string _name;
};

template<class T>
LogScope get() {
    return LogScope(detail::demangle<T>());
}

LogScope get(const std::string &name);

}// namespace eni::logging

#endif//ENI_LOGGING_H

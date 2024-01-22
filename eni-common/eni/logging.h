//
// Created by void on 10/1/23.
//

#ifndef ENI_LOGGING_H
#define ENI_LOGGING_H

#include <spdlog/spdlog.h>

// ReSharper disable once CppUnusedIncludeDirective
#include <source_location>

namespace eni {
using logger = spdlog::logger;

logger &get_logger(const std::string &name);

namespace detail {
std::string _get_logger_from_function_name(const std::string &function_name);
}// namespace detail

#define ENI_LOGGER_FOR_THIS \
    ::eni::get_logger(::eni::detail::_get_logger_from_function_name(std::source_location::current().function_name()))
}// namespace eni


#endif//ENI_LOGGING_H

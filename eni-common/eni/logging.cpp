//
// Created by void on 10/1/23.
//

#include "logging.h"

#include <regex>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace eni {
logger &get_logger(const std::string &name) {
    auto logger = spdlog::get(name);

    if (!logger) {
        logger = spdlog::stdout_color_mt(name);
    }

    return *logger;
}

namespace detail {
std::string _get_logger_from_function_name(const std::string &function_name) {
    static const std::regex classPattern(R"((\w+::)*(\w+)::\w+\(.*)", std::regex_constants::icase);
    static const std::regex funcPattern(R"((\w+)\(.*)", std::regex_constants::icase);

    std::smatch match;
    if (std::regex_search(function_name, match, classPattern)) {
        const auto sm = match[std::distance(match.begin(), match.end()) - 1];
        return sm.str();
    }

    if (std::regex_search(function_name, match, classPattern)) {
        return match[0].str();
    }

    return function_name;
}
}// namespace detail
}// namespace eni

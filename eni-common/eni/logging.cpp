//
// Created by void on 14/07/2021.
//

#include "logging.h"

#include <cxxabi.h>
#include <utility>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace eni::logging {

namespace detail {
std::string _demangle(const char *mangled) {
    auto ptr = std::unique_ptr<char, decltype(&std::free)>{
            abi::__cxa_demangle(mangled, nullptr, nullptr, nullptr),
            std::free};
    std::string result = {ptr.get()};

    auto p = result.find_last_of("::");
    if (p != std::string::npos) {
        return result.substr(p + 1);
    }

    return result;
}
}// namespace detail

LogScope::LogScope(std::string name) : _name(std::move(name)) {}

Logger LogScope::get() const {
    return get_logger(_name);
}
Logger LogScope::operator*() const {
    return get();
}

Logger get_logger(const std::string &name) {
    static spdlog::sink_ptr defaultSink{};

    if (!defaultSink) {
        defaultSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        defaultSink->set_level(spdlog::level::debug);
        defaultSink->set_pattern("(%l) [%n] %v");
    }

    return spdlog::logger(name, {defaultSink});
}

LogScope get(const std::string &name) {
    return LogScope(name);
}

}// namespace eni::logging
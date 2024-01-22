//
// Created by void on 04/09/2021.
//

#ifndef ENI_DEBUG_H
#define ENI_DEBUG_H

#include <experimental/source_location>
#include <fmt/format.h>

namespace eni::debug {

struct Tracer {
    std::experimental::source_location location;

    explicit Tracer(std::experimental::source_location location) : location(location) {}

    void trace(const std::string &message = "tracepoint") const;

    void operator()(const std::string &message = "tracepoint") const;

    template<typename... Args>
    void operator()(const Args &...args) {
        trace(fmt::format(args...));
    }
};

#ifdef ENI_DEBUG
/**
 * Prints a trace point for debugging
 */
#define ENI_DEBUG_TRACE(...) ::eni::debug::Tracer(::std::experimental::source_location::current())(__VA_ARGS__);
#else
#define ENI_DEBUG_TRACE(...)
#endif

}// namespace eni::debug

#endif//ENI_DEBUG_H

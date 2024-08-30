//
// Created by void on 04/09/2021.
//


#include <eni/debug.h>

#ifndef ENI_NO_DEBUG

#include <iostream>
#include <thread>

namespace eni::debug {

void Tracer::trace(const std::string &message) const {
    static const std::string rootDir = ENI_SOURCE_DIR;
    auto filename = std::string(location.file_name()).substr(rootDir.size() + 1);
    auto thread = std::hash<std::thread::id>{}(std::this_thread::get_id());

    const auto formatted = fmt::format("[{} {}:{}@{}:{}] {}", thread, filename, location.function_name(),
                                       location.line(), location.column(), message);

    std::cout << formatted << "\n"
              << std::flush;
}

void Tracer::operator()(const std::string &message) const {
    trace(message);
}

}// namespace eni::debug

#endif
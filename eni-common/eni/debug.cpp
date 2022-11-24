//
// Created by void on 04/09/2021.
//

#include <eni/debug.h>

#include <iostream>
#include <thread>

namespace eni::debug {

void Tracer::operator()(const std::string &message) const {
    static const std::string RootDir = ENI_SOURCE_DIR;
    auto filename = std::string(location.file_name()).substr(RootDir.size() + 1);
    auto thread = std::hash<std::thread::id>{}(std::this_thread::get_id());

    auto formatted = fmt::format("[{} {}:{}@{}:{}] {}", thread, filename, location.function_name(), location.line(), location.column(), message);

    std::cout << formatted << std::endl
              << std::flush;
}

}// namespace eni::debug
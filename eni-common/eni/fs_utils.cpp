//
// Created by mvonkeil on 2/8/24.
//

#include "fs_utils.h"
#include <glob.h>

namespace eni {
std::vector<std::filesystem::path> fs::glob(const std::filesystem::path& path) {
    glob_t globResult{};
    glob(path.c_str(),GLOB_TILDE,NULL, &globResult);
    std::vector<std::filesystem::path> items;
    for (unsigned int i = 0; i < globResult.gl_pathc; ++i) {
        items.emplace_back(globResult.gl_pathv[i]); // NOLINT(*-pro-bounds-pointer-arithmetic)
    }
    globfree(&globResult);

    return items;
}
} // eni

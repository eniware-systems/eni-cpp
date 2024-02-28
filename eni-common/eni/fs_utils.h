//
// Created by mvonkeil on 2/8/24.
//

#ifndef ENI_FS_UTILS_H
#define ENI_FS_UTILS_H

#include <filesystem>
#include <vector>

namespace eni::fs {
std::vector<std::filesystem::path> glob(const std::filesystem::path& path);
} // namespace eni::fs

#endif //ENI_FS_UTILS_H

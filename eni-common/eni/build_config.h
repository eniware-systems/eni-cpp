//
// Created by void on 1/22/24.
//

#ifndef ENI_BUILD_CONFIG_H
#define ENI_BUILD_CONFIG_H

namespace eni {

// Define the target platform
enum class TargetPlatform : char {
    Linux,
};

#if defined(__linux__)
#define ENI_TARGET_PLATFORM_LINUX
constexpr auto CurrentTargetPlatform = TargetPlatform::Linux;
#else
#error "Target platform is not supported"
#endif

// Define the platform types

struct PlatformTypesGeneric {
public:
    PlatformTypesGeneric() = delete;

    using uint8 = unsigned char;
    using uint16 = unsigned short;
    using uint32 = unsigned int;
    using uint64 = unsigned long long;
    using int8 = signed char;
    using int16 = short;
    using int32 = int;
    using int64 = long long;
    using real = float;
};

#if defined(ENI_TARGET_PLATFORM_LINUX)
using PlatformTypes = PlatformTypesGeneric;
#endif

using uint8 = PlatformTypes::uint8;
using uint16 = PlatformTypes::uint16;
using uint32 = PlatformTypes::uint32;
using uint64 = PlatformTypes::uint64;
using int8 = PlatformTypes::int8;
using int16 = PlatformTypes::int16;
using int32 = PlatformTypes::int32;
using int64 = PlatformTypes::int64;
using real = PlatformTypes::real;

}// namespace eni

#endif//ENI_BUILD_CONFIG_H

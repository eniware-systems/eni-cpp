//
// Created by mvonkeil on 2/9/24.
//

#ifndef ENI_SPATIAL_ASPECTRATIO_H
#define ENI_SPATIAL_ASPECTRATIO_H

#include <eni/build_config.h>
#include <eni/spatial/Vec2.h>

namespace eni::spatial {

enum class AspectRatio : uint8 {
    Horizontal,
    Vertical
};

template<typename T>
AspectRatio get_aspect_ratio(const Vec2<T> &p) {
    return p.x > p.y ? AspectRatio::Horizontal : AspectRatio::Vertical;
}

}// namespace eni::spatial

#endif//ENI_SPATIAL_ASPECTRATIO_H

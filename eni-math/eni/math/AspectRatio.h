//
// Created by mvonkeil on 2/9/24.
//

#ifndef ENI_MATH_ASPECTRATIO_H
#define ENI_MATH_ASPECTRATIO_H

#include <eni/build_config.h>
#include <eni/math/Vec2.h>

namespace eni::math {

enum class AspectRatio : uint8 {
    Horizontal,
    Vertical
};

template<typename T>
AspectRatio get_aspect_ratio(const Vec2<T> &p) {
    return p.x > p.y ? AspectRatio::Horizontal : AspectRatio::Vertical;
}

}// namespace eni::math

#endif//ENI_MATH_ASPECTRATIO_H

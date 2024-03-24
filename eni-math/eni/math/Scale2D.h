#ifndef ENI_MATH_SCALE2D_H
#define ENI_MATH_SCALE2D_H

#include <eni/math/Vec2.h>

namespace eni::math {

/**
 * A utility class for scaling 2D vectors.
 */
class Scale2D {
public:
    Scale2D() = delete;

    /**
     * The available scaling types.
     */
    enum class Type {
        Fit,     //< Scale to fit the target while maintain the sources aspect ratio.
        Fill,    //< Scale to fill the target while maintain the sources aspect ratio.
        FillX,   //< Scale to fill the target _width while maintain the sources aspect
                 //ratio.
        FillY,   //< Scale to fill the target _height while maintain the sources aspect
                 //ratio.
        Stretch, //< Stretch the source to fill the whole target.
        StretchX,//< Stretch the source to fill the target _width.
        StretchY,//< Stretch the source to fill the target _height.
        None     //< Do not scale the source.
    };

public:
    /**
     * Applies a scaling on a source.
     * @param type The scaling type.
     * @param source The source to scale from.
     * @param target The target to scale to.
     * @return The scaled source vector.
     */
    static Vec2r apply(Scale2D::Type type, const Vec2r &source, const Vec2r &target);
};

} // namespace eni::math

#endif// ENI_MATH_SCALE2D_H

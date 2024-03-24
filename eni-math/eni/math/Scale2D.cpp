#include <eni/math/Scale2D.h>

namespace eni::math {

Vec2r Scale2D::apply(Scale2D::Type type,
                                const Vec2r &source,
                                const Vec2r &target) {
    Vec2r result;

    switch (type) {
        case Type::Fit: {
            real targetRatio = target.y / target.x;
            real sourceRatio = source.y / source.x;
            real scale =
                    targetRatio > sourceRatio ? target.x / source.x : target.y / source.y;

            result.set(source.x * scale, source.y * scale);

            break;
        }

        case Type::Fill: {
            real targetRatio = target.y / target.x;
            real sourceRatio = source.y / source.x;
            real scale =
                    targetRatio < sourceRatio ? target.x / source.x : target.y / source.y;

            result.set(source.x * scale, source.y * scale);

            break;
        }

        case Type::FillX: {
            real scale = target.x / source.x;

            result.set(source.x * scale, source.y * scale);

            break;
        }

        case Type::FillY: {
            real scale = target.y / source.y;

            result.set(source.x * scale, source.y * scale);

            break;
        }

        case Type::Stretch:
            result = target;
            break;

        case Type::StretchX:
            result.set(target.x, source.y);
            break;

        case Type::StretchY:
            result.set(source.x, target.y);
            break;

        case Type::None:
            result = source;
            break;
    }

    return result;
}
}// namespace eni::math
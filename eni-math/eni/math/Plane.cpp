#include <eni/math.h>
#include <eni/math/Plane.h>

namespace eni::math {

Plane::Plane() : normal(Vec3r::Zero) {}

Plane::Plane(const Plane &other)  = default;

Plane::Plane(const Vec3r &normal, real d) : normal(normal), d(d) {
    this->normal.normalize();
}

Plane::Plane(const Vec3r &normal, const Vec3r &point) : normal(normal), d(-normal.dot(point)) {
    this->normal.normalize();
}

Plane::Plane(const Vec3r &point1, const Vec3r &point2, const Vec3r &point3) {
    set(point1, point2, point3);
}

void Plane::set(const Plane &other) {
    normal = other.normal;
    d = other.d;
}

void Plane::set(const Vec3r &point1, const Vec3r &point2, const Vec3r &point3) {
    normal = (point1 - point2)
                     .cross(Vec3(point2.x - point3.x, point2.y - point3.y,
                                 point2.z - point3.z))
                     .normalize();
    d = -point1.dot(normal);
}

void Plane::set(real nx, real ny, real nz, real d) {
    normal.set(nx, ny, nz);
    normal.normalize();
    this->d = d;
}

void Plane::set(const Vec3r &point, const Vec3r &normal) {
    this->normal = normal;
    this->normal.normalize();
    d = -point.dot(normal);
}

Plane::PlaneSide Plane::getFacingSide(const Vec3r &point) const {
    real dist = normal.dot(point) + d;

    if (math::is_equal_approx(dist, 0)) {
        return PlaneSide::OnPlane;
    }
    if (dist < 0) {
        return PlaneSide::Back;
    }
    return PlaneSide::Front;
}

bool Plane::isFrontFacing(const Vec3r &direction) {
    real dot = normal.dot(direction);
    return dot <= 0;
}

} // namespace eni::math

#ifndef ENI_MATH_PLANE_H
#define ENI_MATH_PLANE_H

#include <eni/math/Vec3.h>

namespace eni::math {

/**
 * A class for handling planar operations.
 */
class Plane {
public:
    /**
     * Definitions of the plane alignment.
     */
    enum class PlaneSide {
        OnPlane,//!< The point lies on the plane.
        Back,   //!< The point lies behind the plane (behind means: on the opposite
                //!< direction the planes normal is pointing towards).
        Front,  //!< The point lies in front of the plane (in direction of the planes
                //!< normal).
    };

private:
    Vec3r normal;
    real d{};

public:
    /**
     * Constructs a new plane.
     */
    Plane();

    /**
     * Copy constructor.
     * @param other source plane to copy from.
     */
    Plane(const Plane &other);

    /**
     * Creates a new plane.
     * @param normal facing direction of the plane
     * @param d plane size
     */
    Plane(const Vec3r &normal, real d);

    /**
     * Creates a new plane from a normal and a point in space.
     * @param point The point from the origin.
     * @param normal The normal vector.
     */
    Plane(const Vec3r &normal, const Vec3r &point);

    /**
     * Creates a new plane from three points in space
     * @param point1 The first point.
     * @param point2 The second point.
     * @param point3 The third point.
     */
    Plane(const Vec3r &point1, const Vec3r &point2, const Vec3r &point3);

    /**
     * Sets this plane from another plane.
     * @param other The other plane to use as source.
     */
    void set(const Plane &other);

    /**
     * Sets this plane from three points in space.
     * @param point1 The first point.
     * @param point2 The second point.
     * @param point3 The third point.
     */
    void set(const Vec3r &point1, const Vec3r &point2, const Vec3r &point3);

    /**
     * Sets this plane from normal and distance.
     * @param nx The normal x axis.
     * @param ny The normal y axis.
     * @param nz The normal z axis.
     * @param d The distance from origin.
     */
    void set(real nx, real ny, real nz, real d);

    /**
     * Sets this plane from a point in space and a given normal vector.
     * @param point The point from the origin.
     * @param normal The normal vector.
     */
    void set(const Vec3r &point, const Vec3r &normal);

    /**
     * Sets this plane from a point in space and a given normal vector.
     * @param pointX The x position from origin.
     * @param pointY The y position from origin.
     * @param pointZ The z position from origin.
     * @param norX The normal x direction.
     * @param norY The normal y direction.
     * @param norZ The normal z direction.
     */
    inline void set(real pointX, real pointY, real pointZ, real norX, real norY,
                    real norZ) {
        set(Vec3(pointX, pointY, pointZ), Vec3(norX, norY, norZ));
    }

    /**
     * @param point a point to check.
     * @return the distance between the plane and the given point.
     */
    inline const real distance(const Vec3r &point) const {
        return normal.dot(point) + d;
    }

    /**
     * Gets the side that is facing toward the given point.
     * @param point the point to check.
     * @return the facing side of the plane. See PlaneSide for further
     * description.
     */
    PlaneSide getFacingSide(const Vec3r &point) const;

    /**
     * Gets the side that is facing toward the given point.
     * @param x x component of the point to check.
     * @param y y component of the point to check.
     * @param z z component of the point to check.
     * @return the facing side of the plane. See PlaneSide for further
     * description.
     */
    inline PlaneSide getFacingSide(real x, real y, real z) const {
        return getFacingSide(Vec3(x, y, z));
    }

    /**
     * @param direction an aligned directional vector.
     * @return true if the plane is facing the given direction
     */
    bool isFrontFacing(const Vec3r &direction);

    /**
     * @return the planes normal
     */
    inline const Vec3r &getNormal() const { return normal; }

    /**
     * @return The distance value of this plane.
     */
    inline real getDistance() const { return d; }
};

} // namespace eni::math

#endif /* ENI_MATH_PLANE_H */

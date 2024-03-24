#ifndef ENI_MATH_QUATERNION_H
#define ENI_MATH_QUATERNION_H

#include <eni/math/Vec3.h>

namespace eni::math {

class Matrix4;

/**
 * A class for handling quaternion math operations.
 */
class Quaternion {
public:
    real x; //< The x component of the quaternion.
    real y; //< The y component of the quaternion.
    real z; //< The z component of the quaternion.
    real w; //< The w component of the quaternion.

    /**
     * Creates a new quaternion.
     * @param x The x component of the new quaternion.
     * @param y The y component of the new quaternion.
     * @param z The z component of the new quaternion.
     * @param w The w component of the new quaternion.
     */
    Quaternion(real x = 0, real y = 0, real z = 0, real w = 0);

    /**
     * Creates a new quaternion from vectorial components.
     * @param xaxis The vectorial x component.
     * @param yaxis The vectorial y component.
     * @param zaxis The vectorial z component.
     */
    Quaternion(const Vec3r &xaxis, const Vec3r &yaxis, const Vec3r &zaxis);

    /**
     * Sets this quaternion.
     * @param newX The new value of the x component.
     * @param newY The new value of the y component.
     * @param newZ The new value of the z component.
     * @param newW The new value of the w component.
     */
    void set(real newX, real newY, real newZ, real newW);

    /**
     * Multiplies two quaternions.
     * @param other The other quaternion to multiply with.
     * @return This quaternion after the multiplication.
     */
    Quaternion &operator*=(const Quaternion &other);

    /**
     * Multiplies two quaternions.
     * @param other The other quaternion to multiply with.
     * @return A new quaternion with the result of the operation.
     */
    Quaternion operator*(const Quaternion &other) const;

    /**
     * Multiplies with a 3-dimensional vector.
     * @param other The vector to multipli with.
     * @return A new vector containing the result of the operation.
     */
    Vec3r operator*(const Vec3r &other) const;

    /**
     * Divides this quaternion.
     * @param scalar The division factor.
     * @return This quaternion after the division.
     */
    Quaternion &operator/=(real scalar);

    /**
     * Divides this quaternion.
     * @param scalar The division faftor.
     * @return A new quaternion with the result of the operation.
     */
    Quaternion operator/(real scalar) const;

    /**
     * Calculates the rotation between two points.
     * @param origin The position of the origin.
     * @param destination The position of the destination.
     * @param fallbackAxis The fallback axis to use if dest is near the inverse of origin. The axis will be
     *                     auto-generated if this argument is set to Vec3::ZERO.
     * @return A new quaternion describing the rotation from origin to dest.
     */
    static Quaternion getRotationTo(const Vec3r &origin, const Vec3r &destination, const Vec3r &fallbackAxis = Vec3r::Zero);

    /**
     * Sets this quaternion from an euler axis vector and an angle.
     * @param axis The euler axis vector.
     * @param angle The angle to rotate the quaternion around the axis.
     */
    void setFromAxisAngle(const Vec3r &axis, real angle);

    /**
     * Sets this quaternion from a transform matrix.
     * @param matrix The transform matrix to derive the direction from.
     */
    void setFromRotationMatrix(const Matrix4 &a);

    /**
     * Sets this quaternion to look at a direction.
     * @param direction The eye direction.
     * @param up The up vector of the eye.
     */
    void setToLookAt(const Vec3r &direction, const Vec3r &up = Vec3r::UnitY);

    /**
     * Sets this quaternion from directional vectors.
     * @param a0 The first vectorial component.
     * @param a1 The second vectorial component.
     * @param a2 The third vectorial component.
     */
    void setFromAxes(const Vec3r &a0, const Vec3r &a1, const Vec3r &a2);

    /**
     * Sets this quaternion from euler angles.
     * @param yaw The yaw component.
     * @param pitch The pitch component.
     * @param roll The roll component.
     */
    void setFromEulerAngles(real yaw, real pitch, real roll);

    /**
     * Normalizes the quaternion.
     */
    void normalize();

    /**
     * @return A normalized version of this quaternion.
     */
    Quaternion normalized() const;

    /**
     * Conjugates the quaternion.
     */
    void conjugate();

    /**
     * @return A new conjugated version of this quaternion.
     */
    Quaternion conjugated() const;

    /**
     * Inverts this quaternion.
     */
    void invert();

    /**
     * @return An inverted version of this quaternion.
     */
    Quaternion inverted() const;

    /**
     * @return The length of this quaternion.
     */
    real getLength() const;

    /**
     * Converts this quaternion to a rotation mation.
     * @param matrix The target matrix to apply this rotation to.
     */
    void toRotationMatrix(Matrix4 &matrix) const;

    /**
     * Extracts the axes of this quaternon.
     * @param a0 The target vector for the first axis.
     * @param a1 The target vector for the second axis.
     * @param a2 The target vector for the third axis.
     */
    void toAxes(Vec3r &a0, Vec3r &a1, Vec3r &a2) const;

    /**
     * Compares two quaternions for equality.
     * @param other The other quaternion to perform the operation with.
     * @return Whether this quaternion is equal to other.
     */
    bool operator==(const Quaternion &other) const;

    /**
     * Returns the gimbal pole, if existing.
     * @return -1 for south pole, 1 for north pole, 0 if not existing.
     */
    int8 getGimbalPole() const;

    /**
     * @return The yaw component of the quaternion in euler angles.
     */
    real getYaw() const;

    /**
     * @return The pitch component of the quaternion in euler angles.
     */
    real getPitch() const;

    /**
     * @return The roll component of the quaternion in euler angles.
     */
    real getRoll() const;

public:
    /**
     * The quaternion identity.
     */
    static const Quaternion IDENTITY;
};

/**
 * Stream implementation for quaternions.
 * @param stream The target stream.
 * @param quaternion The quaternion.
 * @return The stream for chaining.
 */
std::ostream &operator<<(std::ostream &stream, const Quaternion &v);

} // namespace eni::math

#endif //ENI_MATH_QUATERNION_H

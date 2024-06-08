#ifndef ENI_MATH_MATRIX4_H
#define ENI_MATH_MATRIX4_H

#include <eni/math/Quaternion.h>
#include <eni/math/Vec3.h>
#include <eni/math/Vec4.h>

#include <array>

namespace eni::math {

/**
 * This class represents a 4x4 matrix.
 */
class Matrix4 {
public:
    /**
     * Creates a new matrix.
     * @param a00 The cell at [0,0].
     * @param a10 The cell at [1,0].
     * @param a20 The cell at [2,0].
     * @param a30 The cell at [3,0].
     * @param a01 The cell at [0,1].
     * @param a11 The cell at [1,1].
     * @param a21 The cell at [2,1].
     * @param a31 The cell at [3,1].
     * @param a02 The cell at [0,2].
     * @param a12 The cell at [1,2].
     * @param a22 The cell at [2,2].
     * @param a32 The cell at [3,2].
     * @param a03 The cell at [0,3].
     * @param a13 The cell at [1,3].
     * @param a23 The cell at [2,3].
     * @param a33 The cell at [3,3].
     */
    Matrix4(real a00, real a10, real a20, real a30, real a01, real a11, real a21,
            real a31, real a02, real a12, real a22, real a32, real a03, real a13,
            real a23, real a33);

    /**
     * Creates a new matrix from four column vectors.
     * @param c0 The first column.
     * @param c1 The second column.
     * @param c2 The third column.
     * @param c3 The fourth column.
     */
    Matrix4(const Vec4r &c0, const Vec4r &c1, const Vec4r &c2,
            const Vec4r &c3);

    /**
     * Creates a copy of another matrix.
     * @param other The matrix to copy.
     */
    Matrix4(const Matrix4 &other = Matrix4::ID);

public:
    /**
     * Accesses a column.
     * @param column The column to return.
     * @return The raw data at the given column.
     */
    real *operator[](size_t column);

    /**
     * Accesses a column.
     * @param column The column to return.
     * @return The raw data at the given column.
     */
    const real *operator[](size_t column) const;

    /**
     * @return A raw pointer to the data.
     */
    [[nodiscard]] real *data() { return _a.data(); }

    /**
     * @return A raw pointer to the data.
     */
    [[nodiscard]] const real *data() const { return _a.data(); }

    /**
     * A reference to a value.
     * @param column The column of the value.
     * @param row The row of the value.
     * @return The value at the given cell.
     */
    [[nodiscard]] real &at(size_t column, size_t row);

    /**
     * A reference to a value.
     * @param column The column of the value.
     * @param row The row of the value.
     * @return The value at the given cell.
     */
    [[nodiscard]] real at(size_t column, size_t row) const;

public:
    /**
     * @return The determinant of this matrix.
     */
    [[nodiscard]] real getDeterminant() const;

    /**
     * Inverts this matrix.
     * @return This matrix for chaining.
     */
    Matrix4 &invert();

    /**
     * @return An inverted copy of this matrix.
     */
    [[nodiscard]] Matrix4 getInverted() const {
        Matrix4 m(*this);
        m.invert();
        return m;
    }

    /**
     * Transposes this matrix.
     * @return This matrix for chaining.
     */
    Matrix4 &transpose();

    /**
     * @return A transposed copy of this matrix.
     */
    [[nodiscard]] Matrix4 getTransposed() const {
        Matrix4 m(*this);
        m.transpose();
        return m;
    }

public:
    /**
     * Compares another matrix with this one.
     * @param other The matrix to compare.
     * @return Whether both matrices are equal.
     */
    [[nodiscard]] bool operator==(const Matrix4 &other) const;

    /**
     * Compares another matrix with this one.
     * @param other The matrix to compare.
     * @return Whether both matrices are unequal.
     */
    [[nodiscard]] bool operator!=(const Matrix4 &other) const {
        return !operator==(other);
    }

    /**
     * Performs a multiplication where this matrix is the left-handed value of the
     * operation.
     * @param other The matrix to multiply with.
     * @return The result of the multiplication.
     */
    [[nodiscard]] Matrix4 operator*(const Matrix4 &other) const;

    /**
     * Performs an multiplication where this matrix is the left-handed value of
     * the operation. The result of the multiplication will be assigned to this
     * matrix.
     * @param other The matrix to multiply with.
     * @return This matrix for chaining.
     */
    Matrix4 &operator*=(const Matrix4 &other);

    /**
     * Multiplies a vector with this matrix.
     * @param vector The vector to multiply.
     */
    void apply(Vec3r &vector) const;

    /**
     * Multiplies a vector with this matrix.
     * @param other The vector to multiply.
     * @return The multiplied result.
     */
    [[nodiscard]] Vec3r operator*(const Vec3r &other) const {
        Vec3r result(other);
        apply(result);
        return result;
    }

    /**
     * Multiplies a vector with this matrix.
     * @param vector The vector to multiply.
     */
    void apply(Vec4r &vector) const;

    /**
     * Multiplies a vector with this matrix.
     * @param other The vector to multiply.
     * @return The multiplied result.
     */
    [[nodiscard]] Vec4r operator*(const Vec4r &other) const {
        Vec4r result(other);
        apply(result);
        return result;
    }

public:
    /**
     * Set the values from another matrix.
     * @param other The matrix to copy the values from.
     */
    Matrix4 &operator=(const Matrix4 &other);

    /**
     * Sets this to a projection matrix.
     * @param near The near clipping plane distance.
     * @param far The far clipping plane distance.
     * @param fov The field of view.
     * @param aspectRatio The cameras aspect ratio.
     */
    void setToProjection(real near, real far, real fov, real aspectRatio);

    /**
     * Sets this to a orthographics projection matrix.
     * @param left The left offset of the viewport.
     * @param right The right offset of the viewport.
     * @param bottom The bottom offset of the viewport.
     * @param top The top offset of the viewport.
     * @param near The near clipping plane distance.
     * @param far The far clipping plane distance.
     */
    void setToOrtho(real left, real right, real bottom, real top, real near,
                    real far);

    /**
     * Sets this to a look-at matrix.
     * @param direction The direction to look at.
     * @param up The up vector of the camera.
     */
    void setToLookAt(const Vec3r &direction, const Vec3r &up);

    /**
     * Sets this to a transform matrix.
     * @param translation The translation component.
     * @param orientation The orientation component.
     * @param scale The scale component.
     */
    void setToTransform(const Vec3r &translation, const Quaternion &orientation,
                        const Vec3r &scale);

private:
    alignas(16) std::array<real, 16> _a{};

public:
    static const Matrix4 ZERO;//< The zero matrix.
    static const Matrix4 ID;  //< The identity matrix.
};

/**
 * Stream implementation.
 * @param stream The stream.
 * @param matrix The vector to write into the stream.
 * @return The stream for chaining.
 */
std::ostream &operator<<(std::ostream &stream, const Matrix4 &matrix);

}// namespace eni::math

#endif /* ENI_MATH_MATRIX4_H */

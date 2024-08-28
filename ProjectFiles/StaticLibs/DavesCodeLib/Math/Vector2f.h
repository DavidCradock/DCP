/// \file Vector2f.h
/// \brief 2D Vector
///
/// Detailed description text goes here.

#ifndef VECTOR2F_H
#define VECTOR2F_H

namespace DCL
{
	/// \brief Vector class, using 2 floats
	class CVector2f
	{
	public:
		/// \brief Constructor, sets all values to zero
		CVector2f();

		/// \brief Constructor, sets all values to the ones given
		///
		/// \param fX X value
		/// \param fY Y value
		CVector2f(float fX, float fY);

		/// \brief Addition operator which adds two vectors together
		///
		/// \param vec The other vector in the operation
		/// \return The result
		/// 
		/// Vector addition is commutative. (v1 + v2 == v2 + v1) is always true.
		/// Triangle law of vector addition states that when two vectors are represented as two sides of the
		/// triangle with the order of magnitude and direction, then the third side of the triangle represents
		/// the magnitude and direction of the resultant vector.
		/// Example:
		/// CVector2r vOne(1.0f, 1.0f);
		/// CVector2r vTwo(2.0f, 2.0f);
		/// CVector2r vThree = vOne + vTwo;
		CVector2f operator +(const CVector2f& vec) const;

		/// \brief Addition operator which adds two vectors together
		///
		/// \param vec The other vector in the operation
		/// \return The result
		/// 
		/// Vector addition is commutative. (v1 + v2 == v2 + v1) is always true.
		/// Triangle law of vector addition states that when two vectors are represented as two sides of the
		/// triangle with the order of magnitude and direction, then the third side of the triangle represents
		/// the magnitude and direction of the resultant vector.
		/// Example:
		/// CVector2r vOne(1.0f, 1.0f);
		/// CVector2r vThree(2.0f, 2.0f);
		/// vThree += vOne;
		CVector2f& operator +=(const CVector2f& vec);

		/// \brief Subtraction operator 
		///
		/// \param vec The other vector in the operation
		/// \return The result
		/// 
		/// Vector subtraction is not commutative. (v1 - v2 == v2 - v1) is only true when v1 is same as v2.
		/// Example:
		/// CVector2r vOne(1.0f, 1.0f);
		/// CVector2r vTwo(2.0f, 2.0f);
		/// CVector2r vMinusOne = vOne - vTwo;
		CVector2f operator -(const CVector2f& vec) const;

		/// \brief Subtraction operator 
		///
		/// \param vec The other vector in the operation
		/// \return The result
		/// 
		/// Vector subtraction is not commutative. (v1 - v2 == v2 - v1) is only true when v1 is same as v2.
		/// Example:
		/// CVector2r vMinusOne(1.0f, 1.0f);
		/// CVector2r vTwo(2.0f, 2.0f);
		/// vMinusOne -= vTwo;
		CVector2f& operator -=(const CVector2f& vec);

		/// \brief Multiplication by scalar
		///
		/// \param f The float value to multiply each of this vector's components by
		/// \return The result
		/// 
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed)
		/// Example:
		/// CVector2r vTwo(2.0f, 2.0f);
		/// CVector2r vOne = vTwo * 0.5f;
		const CVector2f operator *(const float f) const;

		/// \brief Multiplication by scalar
		///
		/// \param f The scalar value which to multiply each of this vector's components by
		/// 
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed) 
		/// Example:
		/// CVector2r vOne(2.0f, 2.0f, 2.0f);
		/// vOne *= 0.5f; 
		void operator *=(const float f);

		/// \brief Check for equality
		///
		/// \param vec The other vector
		/// \return True if both vectors are the same
		bool operator ==(const CVector2f& vec) const;

		/// \brief Check for inequality
		///
		/// \param vec The other vector
		/// \return True if both vectors are not the same
		bool operator !=(const CVector2f& vec) const;

		/// \brief Divides both components by the given scalar value
		///
		/// \param fScaler The value to divide both components by
		/// 
		/// If scalar given is less than 0.0000001, an exception occurs
		void divide(float fScaler);

		/// \brief Multiplies both elements by the given scalar value
		///
		/// \param fScaler The value to multiply both components by
		/// 
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed) 
		void multiply(float fScaler);

		/// \brief Sets each element to the values given
		///
		/// \param fX The X component
		/// \param fY The Y component
		void set(float fX, float fY);

		/// \brief Sets each element within the vector's set to zero.
		///
		/// A zero vector is a special case. It does not have a direction, and it's magnitude is zero. 
		void setZero(void);

		/// \brief Determines whether the vector is a zero vector.
		///
		/// \return True if the vector is a zero vector.
		bool isZero(void) const;

		/// \brief Negates the vector.
		///
		/// A negated vector has the same magnitude as before, however direction is reversed. 
		void negate(void);

		/// \brief Computes and returns the vector's magnitude
		///
		/// \return The magnitude or length or norm of the vector
		/// 
		/// A vector's magnitude is also know as "the length" or norm of the vector.
		/// Uses sqrtf() so it's quite expensive.
		float getMagnitude(void) const;

		/// \brief Normalises this vector so that it becomes a unit vector (Has a magnitude of 1)
		///
		/// Uses sqrtf() so it's quite expensive.
		/// If the vector has zero length(magnitude), then it is not modified.
		void normalise(void);

		/// \brief Computes distance between this vector and the one given, treating each vector as a point in 2D space.
		///
		/// \param vec The other vector, as a position in 2D space
		/// \return The computed distance between this and the given vector
		float getDistance(const CVector2f& vec) const;

		/// \brief Computes distance squared between this vector and the one given, treating each vector as a point in 2D space.
		///
		/// \param vec The other vector, as a position in 2D space
		/// \return The computed squared distance between this and the given vector
		/// 
		/// This is faster than the getDistance() method, as no expensive square root is used.
		/// This is useful if you have many vectors/points and need to find the closest out of them all.
		/// After finding the closest, then you can squareroot the return value from this method or use getDistance() to obtain the true distance. 
		float getDistanceSquared(const CVector2f& vec) const;

		/// \brief Returns 1.0f if vOther is clockwise, else -1.0f if vOther is anticlockwise
		///
		/// \param vOther The other vector
		/// \return 1.0f if vOther is clockwise, else -1.0f if vOther is anticlockwise
		float getSign(const CVector2f& vOther) const;

		/// \brief Computes the dot product (also known as inner product) between this vector and the one given.
		///
		/// \param vec The other vector
		/// \return The dot product
		/// 
		/// Dot product is commutative (v1.getDot(v2) == v2.getDot(v1)) == always true.
		/// If returned dot product is...
		/// > 0		vectors are pointing roughly in same direction (upto 90 degrees apart)
		/// = 0		vectors are perpendicular to one another (90 degrees)
		/// < 0		vectors are pointing in opposite directions (+90 degrees to 180 degrees)	
		float getDot(const CVector2f& vec) const;

		/// \brief Returns angle (in radians between this and parsed vector (unsigned result)
		///
		/// \param vOther The other vector
		/// \return The angle (in radians) between the two vectors. (unsigned result)
		float getAngleRadiansUnsigned(const CVector2f& vOther) const;

		/// \brief Returns signed angle (in radians) between this vector and one parsed
		///
		/// \param vOther The other vector
		/// \return The signed angle (in radians) between the two vectors.
		/// 
		/// If given vector is clockwise of this vector, the angle (in radians) will be positive, else negative
		float getAngleRadiansSigned(const CVector2f& vOther) const;

		/// \brief Returns signed angle (in degrees) between this vector and one parsed
		///
		/// \param vOther The other vector
		/// \return Signed angle (in degrees) between the two vectors
		/// 
		/// If given vector is clockwise of this vector, the angle (in degrees) will be positive, else negative
		float getAngleDegreesSigned(const CVector2f& vOther) const;

		/// \brief Returns angle in degrees that this vector is from north (CVector2f(0,1)) in the range of 0-360
		///
		/// \return Angle in degrees which this vector is from north (CVector2f(0,1)) in the range of 0-360
		float getAngleDegrees360(void) const;

		/// \brief If this vector represents a position, rotate it clockwise by the given number of degrees
		///
		/// \param fDegrees The angle in degrees in which to rotate this vector when it represents a position
		void rotate(float fDegrees);

		/// \brief Limits the length of this vector so that is equal to or below the parsed value
		///
		/// \param fMaxLength The maximum length to limit this vector to.
		/// 
		/// If the length of this vector does not exceed the one given, it remains unchanged.
		void limitLength(float fMaxLength);

		/// \brief Returns a vector which is at right angle / 90 degrees / perpendicular to this one
		///
		/// \return The perpendicular vector
		CVector2f getPerpendicular(void) const;

		/// \brief Determines a point between two specified points.
		///
		/// \param v1 The first vector which represents a point.
		/// \param v2 The second vector which represents a point.
		/// \param f Distance between v1 and v2. Range = 0.0 to 1.0
		/// \return The newly computed, interpolated point.
		/// 
		/// The parameter f determines where the new interpolated point is located relative to the two end points specified by parameters v1 and v2.
		/// The closer the value of the parameter f is to 1.0, the closer the interpolated point is to the first point (parameter v1).
		/// The closer the value of the parameter f is to 0, the closer the interpolated point is to the second point (parameter v2). 
		/// Returns the new interpolated point
		CVector2f interpolate(const CVector2f& v1, const CVector2f& v2, float f) const;

		/// \brief Returns x and y as an array of floats
		///
		/// \param pArray A pointer to an array of at least size 2 which will hold both component values of the vector
		/// 
		/// Example:
		/// \code
		/// float array[2];
		/// vector.getAsArray(array);
		/// \endcode
		void getAsArray(float* pArray) const;

		float x;	///< The x component of the vector
		float y;	///< The y component of the vector
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
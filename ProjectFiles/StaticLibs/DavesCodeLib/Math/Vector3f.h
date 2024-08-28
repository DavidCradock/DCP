/// \file Vector3f.h
/// \brief A three component floating point vector
///
/// Detailed description text goes here.

#ifndef VECTOR3F_H
#define VECTOR3F_H

namespace DCL
{

	/// \brief Vector class, using 3 floats
	class CVector3f
	{
	public:
		/// \brief Constructor, sets all values to zero
		CVector3f();

		/// \brief Constructor, sets all values to the ones given
		///
		/// \param fX X value
		/// \param fY Y value
		/// \param fZ Z value
		CVector3f(float fX, float fY, float fZ);

		/// \brief Constructor, sets all values from the given CVector3f
		///
		/// \param vector The vector to set this vector's values from
		CVector3f(const CVector3f& vector);

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
		/// CVector3f vOne(1.0f, 1.0f, 1.0f);
		/// CVector3f vTwo(2.0f, 2.0f, 2.0f);
		/// CVector3f vThree = vOne + vTwo;
		CVector3f operator +(const CVector3f& vec) const;

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
		/// CVector3f vOne(1.0f, 1.0f, 1.0f);
		/// CVector3f vThree(2.0f, 2.0f, 2.0f);
		/// vThree += vOne;
		CVector3f& operator +=(const CVector3f& vec);

		/// \brief Subtraction operator 
		///
		/// \param vec The other vector in the operation
		/// \return The result
		/// 
		/// Vector subtraction is not commutative. (v1 - v2 == v2 - v1) is only true when v1 is same as v2.
		/// Example:
		/// CVector3f vOne(1.0f, 1.0f, 1.0f);
		/// CVector3f vTwo(2.0f, 2.0f, 2.0f);
		/// CVector3f vMinusOne = vOne - vTwo;
		CVector3f operator -(const CVector3f& vec) const;

		/// \brief Subtraction operator 
		///
		/// \param vec The other vector in the operation
		/// \return The result
		///
		/// Vector subtraction is not commutative. (v1 - v2 == v2 - v1) is only true when v1 is same as v2.
		/// Example:
		/// CVector3f vMinusOne(1.0f, 1.0f, 1.0f);
		/// CVector3f vTwo(2.0f, 2.0f, 2.0f);
		//// vMinusOne -= vTwo;
		CVector3f& operator -=(const CVector3f& vec);

		/// \brief Multiplication by scalar
		///
		/// \param f The float value to multiply each of this vector's components by
		/// \return The result
		///
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed)
		/// Example:
		/// CVector3f vTwo(2.0f, 2.0f, 2.0f);
		/// CVector3f vOne = vTwo * 0.5f;
		const CVector3f operator *(const float f) const;

		/// \brief Multiplication by scalar
		///
		/// \param f The scalar value which to multiply each of this vector's components by
		///
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed) 
		/// Example:
		/// CVector3f vOne(2.0f, 2.0f, 2.0f);
		/// vOne *= 0.5f; 
		CVector3f& operator *=(const float f);

		/// \brief Check for equality
		///
		/// \param vec The other vector
		/// \return True if both vectors are the same
		bool operator ==(const CVector3f& vec) const;

		/// \brief Check for inequality
		///
		/// \param vec The other vector
		/// \return True if both vectors are not the same
		bool operator !=(const CVector3f& vec) const;

		/// \brief Sets each element to the values given
		///
		/// \param fX The x component's new value
		/// \param fY The y component's new value
		/// \param fZ The z component's new value
		void set(float fX, float fY, float fZ);

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
		float getDot(const CVector3f& vec) const;

		/// \brief Computes the cross product between this vector and the one given.
		///
		/// \param vec The other vector to use in the calculation
		/// \return The cross product
		/// 
		/// The cross product is a vector which is perpendicular to the two vectors it was calculated from. 
		CVector3f getCross(const CVector3f& vec) const;

		/// \brief Computes the angle (in radians) between two UNIT VECTORS (Length of 1)
		///
		/// \param vec The other vector
		/// \return The angle in radians between the two vectors
		/// 
		/// No checking of vectors are unit length here. 
		float getAngle(const CVector3f& vec) const;

		/// \brief Computes distance between this vector and the one given, treating each vector as a point in 3D space.
		///
		/// \param vec The other vector, as a position in 3D space
		/// \return The computed distance between this and the given vector
		float getDistance(const CVector3f& vec) const;

		/// \brief Computes distance squared between this vector and the one given, treating each vector as a point in 3D space.
		///
		/// \param vec The other vector, as a position in 3D space
		/// \return The computed squared distance between this and the given vector
		/// 
		/// This is faster than the getDistance() method, as no expensive square root is used.
		/// This is useful if you have many vectors/points and need to find the closest out of them all.
		/// After finding the closest, then you can squareroot the return value from this method or use getDistance() to obtain the true distance. 
		float getDistanceSquared(const CVector3f& vec) const;

		/// \brief Returns x, y and z as an array of floats
		///
		/// \param pArray A pointer to an array of at least size 3 which will hold the component values of the vector
		/// 
		/// Example:
		/// \code
		/// float array[3];
		/// vector.getAsArray(array);
		/// \endcode
		void getAsArray(float* pArray) const;

		/// \brief Multiplies this vector by the given scalar value
		///
		/// \param f The value to multiply the vector by
		/// 
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed) 
		void multiply(float f);

		/// \brief Computes a new position projected from the origin position, along the given direction vector by the given float amount and stores the result in this vector.
		///
		/// \param vOriginPosition The position in 3D space where the origin is
		/// \param vDirection The direction from the origin to project from the origin
		/// \param fProjectionAmount The amount along vDirection to move to the final computed position
		/// 
		/// vDirection doesn't have to be normalized, but it'd probably make more sense if it is.
		/// Use negative fProjectionAmount values to compute the projected position in the opposite direction
		/// Example...
		/// \code
		/// CVector3f vOrigin(0.0f, 0.0f, 0.0f);
		/// CVector3f vDirection(1.0f, 1.0f, 1.0f);
		/// CVector3f vProjectedPosition;
		/// vProjectedPosition.project(vOrigin, vDirection, 2.0f);	// Would result in vProjectedPosition being 2.0f, 2.0f, 2.0f
		/// \endcode
		void project(const CVector3f& vOriginPosition, const CVector3f& vDirection, float fProjectionAmount);
		
		float x;	///< The x component of the vector
		float y;	///< The y component of the vector
		float z;	///< The z component of the vector
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H

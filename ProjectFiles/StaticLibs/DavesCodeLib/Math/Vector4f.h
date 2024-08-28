/// \file Vector4f.h
/// \brief A four component floating point vector
///
/// Detailed description text goes here.

#ifndef VECTOR4F_H
#define VECTOR4F_H

namespace DCL
{
	/// \brief Vector class, using 4 floats
	class CVector4f
	{
	public:
		/// \brief Constructor, sets all values to zero
		CVector4f();

		/// \brief Constructor, sets all values to the ones given
		///
		/// \param fX X value
		/// \param fY Y value
		/// \param fZ Z value
		/// \param fW W value
		CVector4f(float fX, float fY, float fZ, float fW);

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
		/// CVector4f vOne(1.0f, 1.0f, 1.0f, 1.0f);
		/// CVector4f vTwo(2.0f, 2.0f, 2.0f, 2.0f);
		/// CVector4f vThree = vOne + vTwo;
		CVector4f operator +(const CVector4f& vec) const;

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
		/// CVector4f vOne(1.0f, 1.0f, 1.0f, 1.0f);
		/// CVector4f vThree(2.0f, 2.0f, 2.0f, 2.0f);
		/// vThree += vOne;
		CVector4f& operator +=(const CVector4f& vec);

		/// \brief Subtraction operator 
		///
		/// \param vec The other vector in the operation
		/// \return The result
		/// 
		/// Vector subtraction is not commutative. (v1 - v2 == v2 - v1) is only true when v1 is same as v2.
		/// Example:
		/// CVector4f vOne(1.0f, 1.0f, 1.0f, 1.0f);
		/// CVector4f vTwo(2.0f, 2.0f, 2.0f, 2.0f);
		/// CVector4f vMinusOne = vOne - vTwo;
		CVector4f operator -(const CVector4f& vec) const;

		/// \brief Subtraction operator 
		///
		/// \param vec The other vector in the operation
		/// \return The result
		/// 
		/// Vector subtraction is not commutative. (v1 - v2 == v2 - v1) is only true when v1 is same as v2.
		/// Example:
		/// CVector4f vMinusOne(1.0f, 1.0f, 1.0f, 1.0f);
		/// CVector4f vTwo(2.0f, 2.0f, 2.0f, 2.0f);
		/// vMinusOne -= vTwo;
		CVector4f& operator -=(const CVector4f& vec);

		/// \brief Multiplication by scalar
		///
		/// \param f The float value to multiply each of this vector's components by
		/// \return The result
		/// 
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed)
		/// Example:
		/// CVector4f vTwo(2.0f, 2.0f, 2.0f, 2.0f);
		/// CVector4f vOne = vTwo * 0.5f;
		const CVector4f operator *(const float f) const;

		/// \brief Multiplication by scalar
		///
		/// \param f The scalar value which to multiply each of this vector's components by
		/// 
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed) 
		/// Example:
		/// CVector4f vOne(2.0f, 2.0f, 2.0f, 2.0f);
		/// vOne *= 0.5f; 
		void operator *=(const float f);

		/// \brief Multiplication by another vector
		///
		/// \param v The other vector in the operation
		/// \return The result
		/// 
		/// Example:
		/// CVector4f vOne(3.0f, 3.0f, 3.0f, 3.0f);
		/// CVector4f vTwo(2.0f, 2.0f, 2.0f, 2.0f);
		/// CVector4f vResult = vOne * vTwo;
		const CVector4f operator *(const CVector4f& v) const;

		/// \brief Check for equality
		///
		/// \param vec The other vector
		/// \return True if both vectors are the same
		bool operator ==(const CVector4f& vec) const;

		/// \brief Check for inequality
		///
		/// \param vec The other vector
		/// \return True if both vectors are not the same
		bool operator !=(const CVector4f& vec) const;

		/// \brief Sets each element to the values given
		///
		/// \param fX The x component's new value
		/// \param fY The y component's new value
		/// \param fZ The z component's new value
		/// \param fW The w component's new value
		void set(float fX, float fY, float fZ, float fW);

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

		/// \brief Returns x, y,z and w as an array of floats
		///
		/// \param pArray A pointer to an array of at least size 4 which will hold the component values of the vector
		/// 
		/// Example:
		/// \code
		/// float array[4];
		/// vector.getAsArray(array);
		/// \endcode
		void getAsArray(float* pArray) const;

		/// \brief Multiplies this vector by the given scalar value
		///
		/// \param f The value to multiply the vector by
		/// 
		/// Adjusts the magnitude of a vector, keeping the direction the same (Unless the scalar is negative, in which case the direction is reversed) 
		void multiply(float f);

		float x;	///< The x component of the vector
		float y;	///< The y component of the vector
		float z;	///< The z component of the vector
		float w;	///< The w component of the vector
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H

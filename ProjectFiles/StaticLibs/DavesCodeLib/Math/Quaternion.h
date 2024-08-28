/// \file Quaternion.h
/// \brief Quaternions
///
/// Detailed description text goes here.

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3f.h"

namespace DCL
{
	class CMatrix;	// Declare CMatrix class here so we don't have to include the Matrix.h header

	/// \brief Quaternion class to represent rotations
	class CQuaternion
	{
	public:
		/// \brief Default constructor, sets quaternion to identity (0, 0, 0, 1)
		CQuaternion();

		/// \brief Sets quaternion from given values
		///
		/// \param fX The X component
		/// \param fY The Y component
		/// \param fZ The Z component
		/// \param fW The W component
		CQuaternion(float fX, float fY, float fZ, float fW);

		/// \brief Sets quaternion from given quaternion
		///
		/// \param quaternion The source quaternion to set this one's values to.
		CQuaternion(const CQuaternion& quaternion);

		/// \brief Access each element
		float& operator[] (const int iIndex);

		/// \brief Multiply this quaternion by another and return result
		const CQuaternion operator * (const CQuaternion& quaternion) const;

		/// \brief Multiply this quaternion by another
		const void operator *= (const CQuaternion& quaternion);

		/// \brief Add two quaternions, return result
		const CQuaternion operator+(const CQuaternion& quat) const;

		/// \brief Subtract two quaternions, return result
		const CQuaternion operator-(const CQuaternion& quat) const;

		/// \brief Multiply by scalar, return result
		const CQuaternion operator*(const float fScalar) const;

		/// \brief Divide by scalar, return result
		const CQuaternion operator/(const float fScalar) const;

		/// \brief Multiply a vector, return result
		CVector3f operator *(const CVector3f& vec) const;

		/// \brief Set this quaternion to the one on the right of the operator
		const void operator = (const CQuaternion& quat);

		/// \brief Comparison operator
		const bool operator == (const CQuaternion& quat) const;

		/// \brief Comparison operator
		const bool operator != (const CQuaternion& quat) const;

		/// \brief Sets quaternion to identity (0, 0, 0, 1)
		void setIdentity(void);

		/// \brief Gets magnitude of the quaternion
		///
		/// \return The magnitude or length of the quaternion
		float getMagnitude(void) const;

		/// \brief Normalizes the quaternion
		void normalise(void);

		/// \brief Returns a quaternion with this quaternion's first three components negated.
		///
		/// \return A CQuaternion with the first three components negated
		CQuaternion getConjugate(void) const;

		/// \brief Returns a quaternion with all of this quaternion's components negated.
		///
		/// \return A CQuaternion with all four components negated
		CQuaternion getNegative(void) const;

		/// \brief Sets this quaternion from an axis and an angle
		///
		/// \param vAxis The axis to form the rotation around
		/// \param fAngleRadians The amount in radians to be rotated around the given axis
		/// 
		/// This does not normalize the given axis
		void setFromAxisAngle(const CVector3f& vAxis, float fAngleRadians);

		/// \brief Returns this quaternion's axis
		///
		/// \return A CVector3f holding the axis
		CVector3f getAxis(void) const;

		/// \brief Returns this quaternion's angle in radians
		///
		/// \return The angle in radians the rotation is around it's axis
		float getAngle(void) const;

		/// \brief Sets this quaternion from Euler angles
		///
		/// \param fAngleRadiansX The angle in radians along the euler X axis
		/// \param fAngleRadiansY The angle in radians along the euler Y axis
		/// \param fAngleRadiansZ The angle in radians along the euler Z axis
		void setFromEuler(float fAngleRadiansX, float fAngleRadiansY, float fAngleRadiansZ);

		/// \brief Returns a vector containing the amount of rotation around each local axis
		///
		/// \return A CVector3f containing the amount of rotation around each local axis
		CVector3f getEuler(void) const;

		/// \brief Sets quaternion from given CMatrix
		///
		/// \param matrix A CMatrix which we take it's stored rotation from
		void setFromMatrix(const CMatrix& matrix);

		/// \brief Rotate this quaternion by another
		///
		/// \param quat The other quaternion
		void rotate(const CQuaternion& quat);

		/// \brief Return a quaternion which is interpolated between this quat and the one given using smooth SLERP
		///
		/// \param quaternion The other quaternion
		/// \param fInterval The interval
		/// \return The resulting quaternion
		CQuaternion getSLERP(const CQuaternion& quaternion, float fInterval) const;

		/// \brief Return a quaternion which is interpolated between this quat and the one given using linear interpolation
		/// \param quaternion The other quaternion
		/// \param fInterval The interval
		/// \return The resulting quaternion
		CQuaternion getLERP(const CQuaternion& quaternion, float fInterval) const;

		float q[4];	///< x, y, z and w
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
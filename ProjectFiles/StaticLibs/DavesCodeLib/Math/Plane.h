#ifndef PLANE_H
#define PLANE_H

#include "Vector3f.h"

namespace DCL
{
	/// \brief A representation of a plane in 3D space.
	///
	/// A plane is defined by two things.
	/// 1. Distance to the origin
	/// 2. A normal vector
	class CPlane
	{
	public:
		/// \brief Constructor, sets plane's normal to (0,1,0) and distance to 0
		CPlane();

		/// \brief Constructor, sets the plane's normal and distance to given values
		CPlane(const CVector3f& vNormal, float fDistanceToOrigin);

		/// \brief Sets plane to given values
		///
		/// \param vNormal The normal of the plane
		/// \param fDistanceToOrigin The distance from the origin
		void set(const CVector3f& vNormal, float fDistanceToOrigin);

		/// \brief Returns normal of plane
		///
		/// \return A CVector3f holding the normal of the plane
		CVector3f getNormal(void) const;

		/// \brief Returns distance from origin
		///
		/// \return The plane's distance from the origin
		float getDistanceToOrigin(void) const;

		/// \brief Uses to dot product to compute the distance of a point from the plane.
		///
		/// \param vPoint The point to test which side of the plane it is upon
		/// \return A positive value if the given point is on the side the plane's normal is pointing, else a negative value.
		/// 
		/// If the given point is on the side of the plane it's normal is pointing,
		/// a positive value is returned, else negative.
		float getDistanceFromPlane(const CVector3f& vPoint) const;

	private:
		CVector3f _mvNormal;
		float _mfDistanceToOrigin;
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
/// \file Frustum.h
/// \brief Frustum
///
/// Detailed description text goes here.

#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "AABB.h"
#include "Matrix.h"
#include "Plane.h"

namespace DCL
{
	/// \brief A frustum which is defined by six planes.
	///
	/// It can be used to determine whether various geometric shapes and points are inside of it
	class CFrustum
	{
	public:
		/// \brief Default constructor, does nothing
		CFrustum();

		/// \brief Sets this frustum's planes from the given matrices which are from a camera's view and projection matrices.
		/// 
		/// \param cameraViewMatrix A CMatrix representing the camera's view matrix
		/// \param cameraProjectionMatrix A CMatrix representing the camera's projection matrix
		/// \todo Check this
		void computeFromViewProjection(const CMatrix& cameraViewMatrix, const CMatrix& cameraProjectionMatrix);

		/// \brief Returns true if the given position is inside the frustum, else false.
		///
		/// \param vPosition The position to check againt this frustum
		/// \return True if the given position is within this frustum, else false
		/// \todo Check this
		bool isPointInside(const CVector3f& vPosition) const;

		/// \brief Returns true if the given Axis Aligned Bounding Box is intersecting this frustum, else false.
		/// 
		/// \param aabb The Axis Aligned Bounding Box to check
		/// \return True if the given AABB is intersecting this frustum, else false.
		/// \todo Check this
		bool isAABBIntersecting(const CAABB& aabb) const;

		CPlane mPlaneNear;		///< This frustum's near plane
		CPlane mPlaneFar;		///< This frustum's far plane
		CPlane mPlaneLeft;		///< This frustum's left plane
		CPlane mPlaneRight;		///< This frustum's right plane
		CPlane mPlaneTop;		///< This frustum's top plane
		CPlane mPlaneBottom;	///< This frustum's bottom plane
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
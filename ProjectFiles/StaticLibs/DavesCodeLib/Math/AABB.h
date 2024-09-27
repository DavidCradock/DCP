#ifndef AABB_H
#define AABB_H

#include "Vector3f.h"

namespace DCL
{
	/// \brief An Axis Aligned Bounding Box
	///
	/// An AABB is simply a box with it's axis aligned to the world.
	/// It is similar to the 2D CRect class, but in 3D and is used for culling with the COctTree class
	class CAABB
	{
	public:
		/// \brief Default constructor, sets to a 1x1x1 cube centered at origin
		CAABB();

		/// \brief Sets the axis aligned bouding box with given values
		///
		/// \param vMin The minimum extents of the bounding box
		/// \param vMax The maximum extents of the bounding box
		CAABB(const CVector3f& vMin, const CVector3f& vMax);

		/// \brief Sets box position and dims with given values
		///
		/// \param vMin The minimum extents of the bounding box
		/// \param vMax The maximum extents of the bounding box
		void setMinMax(const CVector3f& vMin, const CVector3f& vMax);

		/// \brief Sets box position and dims with given values
		///
		/// \param vPosition The centre position of the box
		/// \param vDimensions The total width and height of the box
		void setPosDims(const CVector3f& vPosition, const CVector3f& vDimensions);

		/// \brief Sets position of box, leaving dimensions alone
		///
		/// \param vNewPosition The new position of the AABB
		void setPosition(const CVector3f& vNewPosition);

		/// \brief Sets dimensions of box, leaving position alone
		///
		/// \param vNewDimensions The new dimensions of the AABB
		void setDimensions(const CVector3f& vNewDimensions);

		/// \brief Returns dimensions of the box
		///
		/// \return A CVector3f holding the dimensions of the AABB
		CVector3f getDimensions(void) const;

		/// \brief Returns half dimensions of the box
		///
		/// \return A CVector3f holding the half dimensions of the AABB
		CVector3f getHalfDimensions(void) const;

		/// \brief Returns position of the box
		///
		/// \return A CVector3f holding the centre position of the AABB
		CVector3f getPosition(void) const;

		/// \brief Returns true if the given point is inside of this box
		///
		/// \param vPoint The point the check
		/// \return True if the given point is inside ths AABB, else false
		bool getPointIsInside(const CVector3f& vPoint) const;

		/// \brief Returns true if the given AABB intersects with this one
		///
		/// \param aabb The other AABB to test for intersection against this one
		/// \return True if the given AABB intersects this one, else false
		/// \todo test this
		bool getAABBintersects(const CAABB& aabb) const;

		/// \brief Resizes the area so that it's dimensions are multiplied by the given float
		///
		/// \param fMultiplier The amount to adjust the size of the AABB
		/// \todo Test this
		/// 
		/// Example:
		/// If mvMin = (0,0) and mvMax = (10,10) (total dims of (10,10)) and the given float is 2 then the new values would be
		/// mvMin = (-5,-5) and mvMax = (15,15) (total dims of (20, 20))
		void resizeArea(float fMultiplier);

		/// \brief Returns _mvMin, the minimum positions of the corners of the box
		///
		/// \return A CVector3f holding the minimum positions of the corners of the box
		CVector3f getMin(void) const;

		/// \brief Returns _mvMax, the maximum positions of the corners of the box
		///
		/// \return A CVector3f holding the maximum positions of the corners of the box
		CVector3f getMax(void) const;
	private:
		CVector3f _mvMin;	///< Minimum positions of the corners of the box
		CVector3f _mvMax;	///< Maximum positions of the corners of the box
	};


}	// namespace DCL

#endif	// #ifndef FILENAME_H
/// \file Ray.h
/// \brief Holds a ray class for ray tracing
///
/// Detailed description text goes here.

#ifndef RAY_H
#define RAY_H

#include "../Math/Vector3f.h"

namespace DCL
{
	/// \brief A ray class used to represent a ray
	///
	/// <pre>
	/// All ray tracers need rays!
	/// This class represents one.
	/// A ray tracer sends rays through pixels and computes the colour seen by these rays.
	/// Here's the steps involved...
	/// Step 1: Compute a ray from the eye, through a pixel
	/// Step 2: Compute which objects if any that the ray intersects with
	/// Step 3: Compute the colour for the closest intersection position.
	/// 
	/// 
	/// </pre>
	class CRay
	{
	public:
		/// \brief Constructor, does nothing.
		///
		/// Initial values of vOrigin and vDirection are both zero upon their construction
		CRay();

		/// \brief Given the value t, returns a CVector3f which represents a point along a ray
		/// 
		/// \param t The amount along the ray from it's origin which we wish to "project" along and find the position.
		/// \return The computed position along the ray
		/// 
		/// <pre>
		/// Here's an equation I borrowed from somewhere...
		/// P(t) = A + tb
		/// P is a 3D position along a line/ray
		/// A is the ray's origin position
		/// b is the ray direction
		/// t is a float or double which represents the position along the ray
		///	So for example...
		/// if t was 0.0, then the position would be at the ray's origin
		/// if t was 1.0, then the position would be from the ray's origin, along it's direction by 1 unit
		/// if t was -1.0, then the position would be from the ray's origin, "behind" the origin by 1 unit
		/// Doxygen to the rescue again, here's an image I badly drew on the Wacom tablet...
		/// </pre>
		/// \image html ray_01.png "P(t) = A + tb"
		CVector3f at(float t) const;

		CVector3f vOrigin;			///< The origin position of the ray
		CVector3f vDirection;		///< The direction of the ray
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
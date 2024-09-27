#ifndef RECT_H
#define RECT_H

#include "Vector2f.h"

namespace DCL
{
	/// \brief Represents a non-uniform cube aka a rectangle
	/// 
	/// Used to compute whether two rects intersect one another
	class CRect
	{
	public:
		/// \brief Default constructor, sets everything to zero
		CRect();

		/// \brief Construct the rectangle, setting to passed values
		///
		/// \param iMinX The minimum value of the rectangle along X
		/// \param iMinY The minimum value of the rectangle along Y
		/// \param iMaxX The maximum value of the rectangle along X
		/// \param iMaxY The maximum value of the rectangle along Y
		CRect(int iMinX, int iMinY, int iMaxX, int iMaxY);

		/// \brief Sets this rect using given values
		///
		/// \param iMinX The minimum value of the rectangle along X
		/// \param iMinY The minimum value of the rectangle along Y
		/// \param iMaxX The maximum value of the rectangle along X
		/// \param iMaxY The maximum value of the rectangle along Y
		void set(int iMinX, int iMinY, int iMaxX, int iMaxY);

		/// \brief Returns true if the passed CRect intersects with this one
		///
		/// \param other The other CRest to test for intersection with this one
		/// \return True if an intersection would happen, else false.
		bool intersects(const CRect& other) const;

		/// \brief Resizes the rect so that it's dimensions are multiplied by the given int.
		///
		/// \param iMultiplier The multiplier
		/// 
		/// Example:
		/// If mvMin = (0,0) and mvMax = (10,10) (total dims of (10,10)) and the given int is 2 then the new values would be
		/// mvMin = (-5,-5) and mvMax = (15,15) (total dims of (20, 20))
		void resizeArea(int iMultiplier);

		/// \brief Given a position, returns whether it fits within this rect or not
		///
		/// \param iPosX The position along X to check if it fits within this rect or not
		/// \param iPosY The position along X to check if it fits within this rect or not
		/// \return True if the given position fits within this rect.
		bool doesPositionFitWithin(int iPosX, int iPosY);

		/// \brief Given a position, returns whether it fits within this rect or not
		///
		/// \param vPos The position to check if it fits within this rect or not
		/// \return True if the given position fits within this rect.
		bool doesPositionFitWithin(const CVector2f& vPos);

		/// \brief Returns the centre position of the rect
		///
		/// \param iCentreX Will hold the position of this rect for the X axis
		/// \param iCentreY Will hold the position of this rect for the Y axis
		void getCentre(int& iCentreX, int& iCentreY);

		int miMinX;		///< The minimum position of this rectangle along X
		int miMinY;		///< The minimum position of this rectangle along Y
		int miMaxX;		///< The maximum position of this rectangle along X
		int miMaxY;		///< The maximum position of this rectangle along Y
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
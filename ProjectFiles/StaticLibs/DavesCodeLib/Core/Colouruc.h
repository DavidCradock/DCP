/// \file Colouruc.h
/// \brief Contains the CColouruc class for representing a colour using an unsigned char for each colour component RGBA, totalling 4 bytes (1 byte per unsigned char * 4 components)
///
/// Gives less range for the colour with less memory usage

#ifndef COLOURUC_H
#define COLOURUC_H

namespace DCL
{
	/// \brief Used to represent a colour using an unsigned char for each colour component RGBA, totalling 4 bytes (1 byte per unsigned char * 4 components)
	class CColouruc
	{
	public:
		/// \brief Constructor, sets to default values (white with full alpha)
		CColouruc();

		/// \brief Constructor, sets to parsed values
		/// 
		/// \param ucRed A value between 0 and 255 representing the intensity of the red component of this colour.
		/// \param ucGreen A value between 0 and 255 representing the intensity of the green component of this colour.
		/// \param ucBlue A value between 0 and 255 representing the intensity of the blue component of this colour.
		/// \param ucAlpha A value between 0 and 255 representing the intensity of the alpha component of this colour.
		CColouruc(unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue, unsigned char ucAlpha);

		/// \brief Sets the colour to the given values.
		///
		/// \param ucRed A value between 0 and 255 representing the intensity of the red component of this colour.
		/// \param ucGreen A value between 0 and 255 representing the intensity of the green component of this colour.
		/// \param ucBlue A value between 0 and 255 representing the intensity of the blue component of this colour.
		/// \param ucAlpha A value between 0 and 255 representing the intensity of the alpha component of this colour.
		void set(unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue, unsigned char ucAlpha);

		/// \brief Sets this colour to RGB using the given the HSB (Hue, Saturation and Brightness) values.
		///
		/// \param fHueAmount A value between 0.0f and 1.0f representing the hue.
		/// \param fSaturation A value between 0.0f and 1.0f representing the saturation.
		/// \param fBrightness A value between 0.0f and 1.0f representing the brightness.
		/// 
		/// Leaves the alpha value alone
		/// Hue value should be between 0 and 1 (Although it is clamped)
		/// Saturation value should be between 0 and 1 (Although it is clamped)
		/// Brightness value should be between 0 and 1 (Although it is clamped)
		void setFromHSB(float fHueAmount, float fSaturation = 1.0f, float fBrightness = 1.0f);

		/// \brief From this colour in RGBA format, computes and sets the passed variables to hold the HSB (Hue, saturation and brightness values)
		///
		/// \param fHue A value between 0.0f and 1.0f representing the hue.
		/// \param fSaturation A value between 0.0f and 1.0f representing the saturation.
		/// \param fBrightness A value between 0.0f and 1.0f representing the brightness.
		void getHSB(float& fHue, float& fSaturation, float& fBrightness) const;

		/// \brief Interpolates between this colour and the one given by the given float and returns the new colour.
		///
		/// \param other The other colour to interpolate between this one.
		/// \param fValue The interpolation value between this and the other colour.
		/// \return The resulting colours interpolated between.
		/// 
		/// If the float is 0.0f, the returned colour will be this colour.
		/// If the float is 0.5f, the returned colour will be half way between this colour and the one given.
		/// If the float is 1.0f, the returned colour will be the one given.
		CColouruc interpolate(const CColouruc other, float fValue) const;

		/// \brief Overload the == operator to compare colours.
		///
		/// \param col The other colour to compare with this one.
		bool operator == (const CColouruc& col)
		{
			if (red == col.red && green == col.green && blue == col.blue && alpha == col.alpha)
				return true;
			return false;
		}

		/// \brief Overload the * operator to multiply two colours together
		///
		/// \param other The other colour which is multiplied with this one.
		/// \return A CColourf object holding the resulting colour.
		CColouruc operator*(const CColouruc& other) const
		{
			return CColouruc(red * other.red, green * other.green, blue * other.blue, alpha * other.alpha);
		}

		unsigned char red;		///< Red colour between 0 and 255
		unsigned char green;	///< Green colour between 0 and 255
		unsigned char blue;		///< Blue colour between 0 and 255
		unsigned char alpha;	///< Alpha colour between 0 and 255
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
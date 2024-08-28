#include "Colouruc.h"
#include "Utilities.h"

#include <algorithm>

namespace DCL
{
	CColouruc::CColouruc()
	{
		set(255, 255, 255, 255);
	}

	CColouruc::CColouruc(unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue, unsigned char ucAlpha)
	{
		set(ucRed, ucGreen, ucBlue, ucAlpha);
	}

	void CColouruc::set(unsigned char ucRed, unsigned char ucGreen, unsigned char ucBlue, unsigned char ucAlpha)
	{
		red = ucRed;
		green = ucGreen;
		blue = ucBlue;
		alpha = ucAlpha;
	}

	void CColouruc::setFromHSB(float fHueAmount, float fSaturation, float fBrightness)
	{
		// Clamp each passed value
		clamp(fHueAmount, 0.0f, 1.0f);
		clamp(fSaturation, 0.0f, 1.0f);
		clamp(fBrightness, 0.0f, 1.0f);

		// Compute colour
		fHueAmount *= 360.0f;
		float fReciprical60 = 1.0f / 60.0f;
		float fRed, fGreen, fBlue;
		if (fHueAmount <= 60.0f)	// Inc green
		{
			fRed = 1.0f;
			fGreen = fHueAmount * fReciprical60;
			fBlue = 0.0f;
		}
		else if (fHueAmount <= 120.0f)	// Dec red
		{
			fRed = 1.0f - ((fHueAmount - 60.0f) * fReciprical60);
			fGreen = 1.0f;
			fBlue = 0.0f;
		}
		else if (fHueAmount <= 180.0f)	// Inc blue
		{
			fRed = 0.0f;
			fGreen = 1.0f;
			fBlue = (fHueAmount - 120.0f) * fReciprical60;
		}
		else if (fHueAmount <= 240.0f)	// Dec green
		{
			fRed = 0.0f;
			fGreen = 1.0f - ((fHueAmount - 180.0f) * fReciprical60);
			fBlue = 1.0f;
		}
		else if (fHueAmount <= 300.0f)	// Inc red
		{
			fRed = (fHueAmount - 240.0f) * fReciprical60;
			fGreen = 0.0f;
			fBlue = 1.0f;
		}
		else // dec blue
		{
			fRed = 1.0f;
			fGreen = 0.0f;
			fBlue = 1.0f - ((fHueAmount - 300.0f) * fReciprical60);
		}

		// Now RGB is set, apply saturation
		float fSaturationScaleR = 1.0f - fRed;
		float fSaturationScaleG = 1.0f - fGreen;
		float fSaturationScaleB = 1.0f - fBlue;
		fRed += fSaturationScaleR * fSaturation;
		fGreen += fSaturationScaleG * fSaturation;
		fBlue += fSaturationScaleB * fSaturation;
		clamp(fRed, 0.0f, 1.0f);
		clamp(fGreen, 0.0f, 1.0f);
		clamp(fBlue, 0.0f, 1.0f);

		// Now saturation is added, apply brightness
		float fBrightnessInv = 1.0f - fBrightness;
		fRed -= fBrightnessInv;
		fGreen -= fBrightnessInv;
		fBlue -= fBrightnessInv;
		clamp(fRed, 0.0f, 1.0f);
		clamp(fGreen, 0.0f, 1.0f);
		clamp(fBlue, 0.0f, 1.0f);

		// Convert float to unsigned char
		red = unsigned char(fRed * 255);
		green = unsigned char(fGreen * 255);
		blue = unsigned char(fBlue * 255);
	}

	void CColouruc::getHSB(float& fHue, float& fSaturation, float& fBrightness) const
	{
		// Convert unsigned char to float
		float fOneOver255 = 1.0f / 255.0f;
		float fRed = float(red) * fOneOver255;
		float fGreen = float(green) * fOneOver255;
		float fBlue = float(blue) * fOneOver255;

		// Get maximum and minimum values of current RGB values
		float cmax = std::max(fRed, std::max(fGreen, fBlue));
		float cmin = std::min(fRed, std::min(fGreen, fBlue));
		float diff = cmax - cmin; // diff of cmax and cmin.
		fHue = -1, fSaturation = -1;

		// If cmax and cmax are equal then fHue = 0
		if (cmax == cmin)
			fHue = 0;

		// If cmax equal r then compute fHue
		else if (cmax == fRed)
			fHue = float(fmod(60 * ((fGreen - fBlue) / diff) + 360, 360));

		// If cmax equal g then compute fHue
		else if (cmax == green)
			fHue = float(fmod(60 * ((fBlue - fRed) / diff) + 120, 360));

		// If cmax equal b then compute fHue
		else if (cmax == blue)
			fHue = float(fmod(60 * ((fRed - fGreen) / diff) + 240, 360));

		fHue /= 360.0f;

		// If cmax equal zero
		if (cmax == 0)
			fSaturation = 0;
		else
			fSaturation = (diff / cmax);// *100;

		// Compute fBrightness
		fBrightness = cmax;// *100;
	}

	CColouruc CColouruc::interpolate(const CColouruc other, float fValue) const
	{
		clamp(fValue, 0.0f, 1.0f);

		CColouruc colour;
		int iDiff = red - other.red;	// In range of -255 to 255
		colour.red = red + unsigned char(float(iDiff) * -fValue);

		iDiff = green - other.green;
		colour.green = green + unsigned char(float(iDiff) * -fValue);

		iDiff = blue - other.blue;
		colour.blue = blue + unsigned char(float(iDiff) * -fValue);

		iDiff = alpha - other.alpha;
		colour.alpha = alpha + unsigned char(float(iDiff) * -fValue);
		
		return colour;
	}
}
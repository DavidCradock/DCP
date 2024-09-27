#include "Dimensions.h"

namespace DCL
{
	CDimension2D::CDimension2D(void)
	{
		width = height = 0;
	}

	CDimension2D::CDimension2D(unsigned int uiWidth, unsigned int uiHeight)
	{
		width = uiWidth;
		height = uiHeight;
	}

	CDimension3D::CDimension3D(void)
	{
		width = height = depth = 0;
	}

	CDimension3D::CDimension3D(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiDepth)
	{
		width = uiWidth;
		height = uiHeight;
		depth = uiDepth;
	}

}	// namespace DCL
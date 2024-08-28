#include "Ray.h"

namespace DCL
{
	CRay::CRay()
	{

	}

	CVector3f CRay::at(float t) const
	{
		return vOrigin + (vDirection * t);
	}

}	// namespace DCL
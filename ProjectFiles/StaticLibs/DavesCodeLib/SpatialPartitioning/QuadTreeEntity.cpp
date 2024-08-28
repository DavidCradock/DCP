#include "QuadTreeEntity.h"
#include "QuadTreeNode.h"

namespace DCL
{
	CQuadTreeEntity::CQuadTreeEntity(const std::string& strName, int iPosX, int iPosY, CQuadTreeNode* pNodeOwner, int iUserData, void* pUserData)
	{
		_mstrName = strName;
		_miPosX = iPosX;
		_miPosY = iPosY;
		_mpNodeOwner = pNodeOwner;

		// Store user data
		miUserData = iUserData;
		mpUserData = pUserData;
	}

	/*
	void CQuadTreeEntity::debugSetColour(CColour& colour)
	{
		_mColDebug = colour;
	}
	*/

	CVector2f CQuadTreeEntity::getPosition(void)
	{
		CVector2f v;
		v.x = float(_miPosX);
		v.y = float(_miPosY);
		return v;
	}

	std::string CQuadTreeEntity::getName(void)
	{
		return _mstrName;
	}

}	// namespace DCL
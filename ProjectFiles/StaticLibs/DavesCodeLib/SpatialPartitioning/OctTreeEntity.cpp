#include "OctTreeEntity.h"
#include "OctTreeNode.h"

namespace DCL
{
	COctTreeEntity::COctTreeEntity(const std::string& strName, const CVector3f& vPosition, COctTreeNode* pNodeOwner, int iUserData, void* pUserData)
	{
		_mstrName = strName;
		_mvPosition = vPosition;
		_mpNodeOwner = pNodeOwner;

		// Store user data
		miUserData = iUserData;
		mpUserData = pUserData;
	}

	/*
	void COctTreeEntity::debugSetColour(CColour& colour)
	{
		_mColDebug = colour;
	}
	*/

	CVector3f COctTreeEntity::getPosition(void)
	{
		return _mvPosition;;
	}

	std::string COctTreeEntity::getName(void)
	{
		return _mstrName;
	}

}	// namespace DCL
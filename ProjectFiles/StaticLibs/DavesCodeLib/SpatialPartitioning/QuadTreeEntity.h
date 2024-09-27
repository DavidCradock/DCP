#ifndef QUADTREEENTITY_H
#define QUADTREEENTITY_H

#include "../Math/Vector2f.h"
#include "../Core/Colourf.h"

#include <string>

namespace DCL
{
	class CQuadTreeNode;

	/// \brief An entity which is assigned into a CQuadTreeNode
	///
	/// It contains it's unique name, it's position within the world and the node it belongs to.
	class CQuadTreeEntity
	{
		friend class CQuadTree;
		friend class CQuadTreeNode;
	public:
		/// \brief Constructor.
		///
		/// \param strName is the unique name given to this entity.
		/// \param iPosX is this entity's position within the world along X axis
		/// \param iPosY is this entity's position within the world along Y axis
		/// \param pNodeOwner A pointer to this entity's owning node.
		/// \param iUserData Optional integer which you can use for anything.
		/// \param pUserData A void pointer to anything you wish to associate with this entity.
		CQuadTreeEntity(const std::string& strName, int iPosX, int iPosY, CQuadTreeNode* pNodeOwner, int iUserData = 0, void *pUserData = 0);

		/// \brief Set the debug colour of the entity
//		void debugSetColour(CColour& colour);

		/// \brief Returns position of entity
		///
		/// \return A CVector2f containing the entity's position.
		CVector2f getPosition(void);

		/// \brief Returns the name of the entity
		///
		/// \return A string holding the entity's name
		std::string getName(void);

		// Below are members which may be set to store various information.
		// They have nothing to do with the quad tree itself.
		int miUserData;			///< Can store a value for use by you for any required reason
		void* mpUserData;		///< Can store a void pointer for use by you for any required reason

	private:
		std::string _mstrName;			///< Unique name of this entity
		int _miPosX;					///< Position of this entity along X axis
		int _miPosY;					///< Position of this entity along Y axis
		CQuadTreeNode* _mpNodeOwner;	///< The node this entity is in
//		CColour _mColDebug;				///< The colour used when debug rendering this entity
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H

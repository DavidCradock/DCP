/// \file OctTreeEntity.h
/// \brief Brief description for the file goes here.
///
/// Detailed description text goes here.

#ifndef OCTTREEENTITY_H
#define OCTTREEENTITY_H

#include "../Math/Vector3f.h"
#include "../Core/Colourf.h"

#include <string>

namespace DCL
{
	class COctTreeNode;

	/// \brief An entity which is assigned into an COctTreeNode
	///
	/// It contains it's unique name, it's position within the world and the node it belongs to.
	class COctTreeEntity
	{
		friend class COctTree;
		friend class COctTreeNode;
	public:
		/// \brief Constructor.
		///
		/// \param strName is the unique name given to this entity.
		/// \param vPosition is this entity's position within the world
		/// \param pNodeOwner A pointer to this entity's owning node.
		/// \param iUserData Optional integer which you can use for anything.
		/// \param pUserData A void pointer to anything you wish to associate with this entity.
		COctTreeEntity(const std::string& strName, const CVector3f& vPosition, COctTreeNode* pNodeOwner, int iUserData = 0, void* pUserData = 0);

		/// \brief Set the debug colour of the entity
//		void debugSetColour(CColour& colour);

		/// \brief Returns position of entity
		///
		/// \return A CVector3f containing the entity's position.
		CVector3f getPosition(void);

		/// \brief Returns the name of the entity
		///
		/// \return A string holding the entity's name
		std::string getName(void);

		// Below are members which may be set to store various information.
		// They have nothing to do with the oct tree itself.
		int miUserData;			///< Optional user data
		void* mpUserData;		///< Optional user data

	private:
		std::string _mstrName;			///< Unique name of this entity
		CVector3f _mvPosition;			///< Position of this entity
		COctTreeNode* _mpNodeOwner;		///< The node this entity is in
//		CColour _mColDebug;				///< The colour used when debug rendering this entity
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H

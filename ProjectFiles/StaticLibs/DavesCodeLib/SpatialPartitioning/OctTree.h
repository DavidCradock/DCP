#ifndef OCTTREE_H
#define OCTTREE_H

#include "OctTreeNode.h"
//#include "SMCamera.h"
#include "../Math/Frustum.h"

namespace DCL
{
	/// \brief 3D spatial partitioning class.
	///
	/// For 2D spatial partitioning, see the CQuadTree class
	/// 
	/// An oct tree gives us fast retrieval of entities which are within a specified
	/// range of a given position aswell as fast retrieval of entities which are within a given area of space.
	/// This is great for rendering only visible entities and also for getting a list of entities which
	/// can be used to perform collision detection only upon entities which are closeby, instead of having
	/// to perform collision for ALL entities within a world.
	/// 
	/// An oct tree begins with an initial root 3D space (node) with which to insert uniquely named entities 
	/// into, specifying their position.
	/// The oct tree has a maximum number of entities which can be inserted into a node and once this number
	/// is reached, the node is split into one or more (up to eight) child nodes and the entities are removed
	/// from the parent node and into the child nodes.
	/// The position of entities determines which child nodes need to be created and then the entity inserted into.
	/// Each of the child nodes have half the dimensions of their parent node and there are eight of them.
	///
	/// This is a recursive process, so smaller and smaller child nodes of child nodes and so on are created until
	/// a "max node depth" value is reached, then what happens is the child nodes no longer get any more child nodes
	/// and the entities inserted, ignore the maximum number of entities per node value.
	/// The max node depth is computed upon the tree's construction based upon it's dimensions and then again if the 
	/// root node of the tree gets resized (due to insertion of an entity outside of the root node's region).
	/// The reason we have a max node depth is because, as the nodes get divided, their dimensions get smaller and 
	/// smaller, until they reach a dimension of 1x1x1 and if they were to become zero dimensions, no entities would
	/// fit in them and the algorithm would enter an infinite recursive loop, forever creating useless zero sized
	/// child nodes and cause a stack overflow.
	///
	/// The intial region is set to -8, +8 along each axis. 
	class COctTree
	{
		friend class COctTreeNode;
		friend class COctTreeEntity;
	public:
		/// \brief Constructor
		///
		/// \param iMaxEntitiesPerNode The maximum number of entities able to be stored
		/// within a node before that node will be subdivided again into child nodes.
		/// This must be at least 1, otherwise an exception occurs.
		/// If we add an entity which is outside of the root node's initial region
		/// then the tree is rebuilt.
		/// 
		/// \param fSizeIncreaseMultiplier is used when the tree is rebuilt. It is the
		/// amount to increase the root node's dimensions by until the new entity's
		/// position fits. A value of 2 would double the new root node's dimensions
		/// each time. It must be at least 2 otherwise an exception occurs.
		COctTree(int iMaxEntitiesPerNode = 10, float fSizeIncreaseMultiplier = 2.0f);

		/// \brief Destructor
		/// 
		/// Deletes the root node, which will delete all children and their children and so on.
		~COctTree();

		/// \brief Initialise the oct tree using the new given settings.
		///
		/// This will free the existing tree and any entities.
		/// 
		/// \param iMaxEntitiesPerNode is the maximum number of entities able to be stored
		/// within a node before that node will be subdivided again into child nodes.
		/// This must be at least 1, otherwise an exception occurs.
		/// If we add an entity which is outside of the root node's initial region
		/// then the tree is rebuilt.
		/// 
		/// \param fSizeIncreaseMultiplier is used when the tree is rebuilt. It is the
		/// amount to increase the root node's dimensions by until the new entity's
		/// position fits. A value of 2 would double the new root node's dimensions
		/// each time. It must be at least 2 otherwise an exception occurs.
		void init(int iMaxEntitiesPerNode = 10, float fSizeIncreaseMultiplier = 2.0f);

		/// \brief Deletes the root node and in turn all of it's children and all entities
		void free(void);

		/*
		// Debug rendering of the oct tree's nodes
		void debugRender(CSMCamera& camera) const;
		
		// For debug rendering, sets the named entity's rendered colour
		// If the named entity doesn't exist, an exception occurs.
		void debugSetEntityColour(const std::string& strName, CColour& colour);

		// For debug rendering, sets all entities' rendered colour to the one given
		void debugSetAllEntitiesColour(CColour& colour);
		*/

		/// \brief Add entity to the oct tree.
		///
		/// \param strName The name to be given to the new entity within the tree. It must be unique, if it already exists, an exception occurs.
		/// \param vPosition The position of the new entity.
		/// \param iUserData Optional integer which you can use for anything.
		/// \param pUserData A void pointer to anything you wish to associate with this entity.
		/// 
		/// Each entity needs a unique name, if the name given already exists, an exception occurs.
		/// If the specified position is outside of the tree's region, the tree is rebuilt
		void addEntity(const std::string& strName, const CVector3f& vPosition, int iUserData = 0, void* pUserData = 0);

		/// \brief Removes the named entity from the tree.
		///
		/// \param strName The name of the entity within the tree. If it doesn't exist, an exception occurs.
		/// To determine whether the entity exists, use getEntityExists()
		void removeEntity(const std::string& strName);

		/// \brief Returns whether the named entity exists or not
		///
		/// \param strName The name of the entity within the tree.
		/// \return True if the named entity exists, else false.
		bool getEntityExists(const std::string& strName) const;

		/// \brief Removes all entities from the tree and depending upon the passed bool, resets the tree to contain just the root node.
		///
		/// \param bResetTree Whether to reset the tree whist we're here.
		void removeAllEntities(bool bResetTree = false);

		/// \brief Set an existing entity's position to the one given, moving to the correct node if needed.
		///
		/// \param strName The name of the entity within the tree. If the named entity doesn't exist, an exception occurs.
		/// \param vNewPosition The new position of the entity.
		void setEntityPosition(const std::string& strName, const CVector3f& vNewPosition);

		/// \brief Sets the given vector to the named entity's position.
		///
		/// \param strName The name of the entity within the tree. If the named entity doesn't exist, an exception occurs.
		/// \param[out] vPosition Will hold the current position of the named entity.
		void getEntityPosition(const std::string& strName, CVector3f &vPosition) const;

		/// \brief Returns a vector of COctTreeNodes which holds all nodes which have entities in them
		///
		/// \return A vector of COctTreeNodes which holds all nodes which have entities in them
		std::vector<COctTreeNode*> getNodesWithEntities(void) const;

		/// \brief Returns a vector of COctTreeNodes which holds all nodes which intersect with the given AABB and have entities
		///
		/// \param aabb The axis aligned bounding box which to use for the intersection test.
		/// \return a vector of COctTreeNode* which have entities in them and intersect with the given AABB
		std::vector<COctTreeNode*> getNodesWithEntitiesWhichIntersect(const CAABB& aabb) const;

		/// \brief Returns a vector of COctTreeNodes which holds all nodes which intersect with the given CFrustum and have entities
		///
		/// \param frustum The frustum to use for the intersection test.
		/// \return a vector of COctTreeNode* which have entities in them and intersect with the given frustum
		std::vector<COctTreeNode*> getNodesWithEntitiesWhichIntersect(const CFrustum& frustum) const;

		/// \brief Returns a vector of entities which are within range of the given position.
		///
		/// \param vPosition The position in 3D space
		/// \param fRange The range from the given position with which any entities within this range will be returned.
		/// \return A vector of COctTreeEntity* which are within range of the given position and range.
		/// 
		/// This may return some entities which are outside of the range, as the test to see
		/// whether the entities aren't in range isn't 100% accurate.
		std::vector<COctTreeEntity*> getEntitiesWithinRange(const CVector3f& vPosition, float fRange) const;

		/// \brief Returns a vector of entities which are within the given CAABB
		///
		/// \param aabb The axis aligned bounding box which to use for the test.
		/// \return A vector of COctTreeEntity* which are within the given AABB
		/// 
		/// This may return some entities which are outside of the range, as the test to see
		/// whether the entities aren't in range isn't 100% accurate.
		std::vector<COctTreeEntity*> getEntitiesWithinAABB(const CAABB& aabb) const;

		/// \brief Returns a vector of entities which are within the given CFrustum
		///
		/// \param frustum The frustum to use for the test
		/// \return A vector of COctTreeEntity* which are within the given frustum
		/// \todo check this
		std::vector<COctTreeEntity*> getEntitiesWithinFrustum(const CFrustum& frustum) const;

		/// \brief Returns current node depth stat
		///
		/// \return The current node depth
		/// 
		/// If there are no child nodes, this would be zero.
		/// It's used by the debug rendering code to colour the nodes accordingly.
		/// It's also used to determine if the tree has reached the maximum child
		/// division depth, in which case, additionally added entities no longer
		/// subdivide a node into children and instead simply add the new entity
		/// into the node, ignoring the _miMaxEntitiesPerNode value.
		unsigned int getNodeDepthCurrent(void);

		/// \brief Returns max node depth stat
		///
		/// \return The max node depth stat
		/// 
		/// If adding an entity into a node, that node's depth is equal to this value,
		/// then _miMaxEntitiesPerNode is ignored and the new entity is simply added
		/// to the node, instead of trying to sub-divide the node further.
		/// This is to prevent node dimensions of less than 1x1 which would cause
		/// infinite sub-division of nodes and cause a stack overflow.
		/// This value is computed upon construction and whenever the root node's
		/// dimensions are increased.
		unsigned int getNodeDepthMax(void) const;

	private:
		COctTreeNode* _mpRootNode;		///< Root node of the tree which holds all child nodes and their entities

		/// \brief Maximum number of entities able to be stored within a node before that node will
		/// be subdivided again into child nodes.
		/// Set during construction
		int _miMaxEntitiesPerNode;

		/// \brief When adding a new entity and it's position doesn't fit within the root
		/// node's area, the area is increased by this amount until the new
		/// entity's position fits. A value of 2 would double the new root node's
		/// dimensions each time.
		/// Set during construction
		float _mfSizeIncreaseMultiplier;

		/// \brief Hashmap holding pointers to each of the added entities
		///
		/// This is used for fast retrieval or removal of single entities
		mutable std::map<std::string, COctTreeEntity*> _mmapEntities;

		/// \brief Holds the current maximum depth of the nodes.
		///
		/// If there are no child nodes, this would be zero.
		/// It's used by the debug rendering code to colour the nodes accordingly.
		/// It's also used to determine if the tree has reached the maximum child
		/// division depth, in which case, additionally added entities no longer
		/// subdivide a node into children and instead simply add the new entity
		/// into the node, ignoring the _miMaxEntitiesPerNode value.
		unsigned int _muiCurrentMaxNodeDepth;

		/// \brief Holds the maximum depth of child nodes.
		/// 
		/// If adding an entity into a node, that node's depth is equal to this value,
		/// then _miMaxEntitiesPerNode is ignored and the new entity is simply added
		/// to the node, instead of trying to sub-divide the node further.
		/// This is to prevent node dimensions of less than 1x1 which would cause
		/// infinite sub-division of nodes and cause a stack overflow.
		/// This value is computed upon construction and whenever the root node's
		/// dimensions are increased.
		unsigned int _muiMaxNodeDepth;

		/// \brief Based upon _mpRootNode->_mRegion, computes the maximum allowable node depth and sets _muiMaxNodeDepth.
		void _computeMaxNodeDepth(void);
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
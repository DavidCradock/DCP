#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include "../Math/Rect.h"
#include "QuadTreeEntity.h"
//#include "resourceManager.h"

#include <map>
#include <vector>

namespace DCL
{
	class CQuadTree;

	/// \brief A node used by the CQuadTree class
	class CQuadTreeNode
	{
		friend class CQuadTree;
	public:
		/// \brief Used for accessing child nodes based upon their location
		enum ChildNode
		{
			BL,	///< Bottom left child node
			BR,	///< Bottom right child node
			TL,	///< Top left child node
			TR,	///< Top right child node
			NONE
		};

		/// \brief Constructor.
		///
		/// \param rectRegion The 2D area/region which this node represents.
		/// \param pParentNode A pointer to this node's parent node. However, if this node is to represent the root node, this will be 0.
		/// \param pQuadTree The quad tree which owns this node
		/// 
		/// Sets up the node to represent the given region within the 2D world, with no child nodes.
		/// pParentNode is a pointer to this node's parent node. However, if this node is to represent
		/// the root node, this will be 0.
		CQuadTreeNode(const CRect& rectRegion, CQuadTreeNode* pParentNode, CQuadTree* pQuadTree);

		/// \brief Destructor
		///
		/// Removes all child nodes
		/// Although this obviously removes the entities from the nodes, because the nodes themselves
		/// no longer exist, this does NOT delete the entity pointers. They are stored in the CQuadTree's
		/// _mmapEntities hashmap.
		~CQuadTreeNode();

		/// \brief Debug renders this node and it's child nodes', node boundaries
		///
		/// pLine is the CResourceLine object which is being used to add vertices to be rendered
		/// vertex is the vertex object we're using to add vertices using the pLine object.
//		void debugRenderNodes(CResourceVertexBufferLine* pLine, CResourceVertexBufferLine::Vertex& vertex, CColour colour) const;

		/// \brief Debug renders this node and it's child nodes' entities
		///
		/// pLine is the CResourceLine object which is being used to add vertices to be rendered
//		void debugRenderEntities(CResourceVertexBufferLine* pLine, int iCircleRadius, unsigned int uiCircleNumSegments) const;

		/// \brief Returns true if this node has the specified child node
		///
		/// \param childNode A ChildNode
		/// \return True if this node has the specified child node, else false.
		bool hasChildNode(ChildNode childNode) const;

		/// \brief Returns whether this node has any child nodes
		///
		/// \return Whether this node has any child nodes
		bool hasAnyChildNodes(void) const;

		/// \brief Returns whether this node and all it's children have any entities within
		///
		/// \return Whether this node and all it's children have any entities within
		bool hasEntitiesInThisAndAllChildren(void) const;

		/// \brief Creates the specified child node
		///
		/// \param childNode A ChildNode
		/// 
		/// If the node already exists, this does nothing.
		void createChildNode(ChildNode childNode);

		/// \brief Calculates and returns a child's region.
		///
		/// \param childNode A ChildNode
		/// \return A CRect representing the node's region.
		CRect computeChildNodeRegion(ChildNode childNode) const;

		/// \brief Adds an entity into this node, or it's children
		///
		/// \param pEntity A pointer to the entity to add
		void addEntity(CQuadTreeEntity* pEntity);

		/// \brief Removes an entity from this node
		///
		/// \param pEntity A pointer to the entity to remove
		/// 
		/// If the entity couldn't be found, an exception occurs
		void removeEntity(CQuadTreeEntity* pEntity);

		/// \brief Adds nodes to a vector of CQuadTreeNodes which have entities in them
		///
		/// \param vecNodes A vector of CQuadTreeNode pointers which have entities within them
		void getNodesWithEntities(std::vector<CQuadTreeNode*>& vecNodes);

		/// \brief Adds nodes to a vector of CQuadTreeNodes which intersect with the given CRect and have entities
		///
		/// \param vecNodes A vector of CQuadTreeNode pointers which have entities within them and intersect with the given AABB
		/// \param rect The CRect to use for the test.
		void getNodesWithEntitiesWhichIntersect(std::vector<CQuadTreeNode*>& vecNodes, const CRect& rect);

		/// \brief Go through all children and if their depth is greater, increases given uiMaxNodeDepth
		/// 
		/// \param uiMaxNodeDepth Will hold maximum node depth
		void getMaxNodeDepth(unsigned int& uiMaxNodeDepth);
	private:
		/// \brief Holds the region which this node covers
		/// Must be a multiple of 2, otherwise child nodes' regions will not cover all space.
		CRect _mRectRegion;

		// \brief Pointer to the parent of this node. May be 0 if this is the root node
		CQuadTreeNode* _mpParentNode;

		// \brief Pointer to the four possible child nodes.
		// A pointer may be 0 for no child node allocated yet.
		// Use the ChildNode enum with this array to access the correct child node.
		CQuadTreeNode* _mpChildNode[4];

		// \brief The quad tree which owns this node, this is passed to the constructor
		CQuadTree* _mpQuadTree;

		/// \brief Depth of this node.
		///
		/// How many nodes there are above this node.
		unsigned int _muiNodeDepth;

		// \brief Hashmap holding pointers to each of the added entities, until
		// this node has children, in which case this would be empty as 
		// the child nodes now own the entities (or their siblings)
		mutable std::map<std::string, CQuadTreeEntity*> _mmapEntities;
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H

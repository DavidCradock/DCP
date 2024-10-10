#include "ResourceVertexBuffer.h"
#include "../../Core/Exceptions.h"
#include "../OpenGL/RendererOpenGLExtensions.h"

namespace DCL
{
	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Base
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	CResourceVertexBufferBase::CResourceVertexBufferBase()
	{
		eVertexBufferType = CResourceVertexBufferBase::EVertexBufferDataType::POS;
	}

	void CResourceVertexBufferBase::setDataType(CResourceVertexBufferBase::EVertexBufferDataType vertexBufferDataType)
	{
		eVertexBufferType = vertexBufferDataType;
	}

	void CResourceVertexBufferBase::computeTangentsAndBinormals(void)
	{
		// Make sure correct vertex data type is set
		ThrowIfFalse(EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL == eVertexBufferType, "Unable to compute TBN as vertex buffer data type is not set to correct type.");

		// Make sure data exists
		ThrowIfFalse(_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.size(), "Unable to compute TBN as vertex buffer data is empty.");

		// Make sure indicies exist
		ThrowIfFalse(_mvecIndices.size(), "Unable to compute TBN as there are no vertex indicies.");

		// For each face
		for (unsigned int iIndex = 0; iIndex < _mvecIndices.size(); iIndex += 3)
		{
			// Calculate the face's edges and delta UV coordinates
			CVector3f edge1 = _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex + 1]].position - _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].position;
			CVector3f edge2 = _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex + 2]].position - _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].position;
			CVector2f deltaUV1 = _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex + 1]].texCoord - _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].texCoord;
			CVector2f deltaUV2 = _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex + 2]].texCoord - _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].texCoord;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].binormal.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].binormal.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].binormal.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		}
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position)
	{
		ThrowIfFalse(CResourceVertexBufferBase::EVertexBufferDataType::POS == eVertexBufferType, "Vertex buffer type not correctly set to EVertexBufferDataType::POS");
		Vertex_POS vertex;
		vertex.position = position;
		_mvecVertexData_POS.push_back(vertex);
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position, const CColourf& colour)
	{
		ThrowIfFalse(CResourceVertexBufferBase::EVertexBufferDataType::POS_COL == eVertexBufferType, "Vertex buffer type not correctly set to EVertexBufferDataType::POS_COL");
		Vertex_POS_COL vertex;
		vertex.colour = colour;
		vertex.position = position;
		_mvecVertexData_POS_COL.push_back(vertex);
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position, const CColourf& colour, CVector2f& texcoord)
	{
		if (CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_TEXCOORD != eVertexBufferType)
		{
			if (CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL != eVertexBufferType)
			{
				Throw("Vertex buffer type not correctly set to EVertexBufferDataType::POS_COL_TEXCOORD or EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL");
			}
		}

		Vertex_POS_COL_TEXCOORD vertex;
		vertex.colour = colour;
		vertex.position = position;
		vertex.texCoord = texcoord;
		_mvecVertexData_POS_COL_TEXCOORD.push_back(vertex);
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position, const CColourf& colour, const CVector3f& normal, CVector2f& texcoord)
	{
		ThrowIfFalse(CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD == eVertexBufferType, "Vertex buffer type not correctly set to EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD");
		Vertex_POS_COL_NORMAL_TEXCOORD vertex;
		vertex.colour = colour;
		vertex.normal = normal;
		vertex.position = position;
		vertex.texCoord = texcoord;
		_mvecVertexData_POS_COL_NORMAL_TEXCOORD.push_back(vertex);
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position, const CColourf& colour, const CVector3f& normal, CVector2f& texcoord0, CVector2f& texcoord1)
	{
		ThrowIfFalse(CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2 == eVertexBufferType, "Vertex buffer type not correctly set to EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2");
		Vertex_POS_COL_NORMAL_TEXCOORDx2 vertex;
		vertex.colour = colour;
		vertex.normal = normal;
		vertex.position = position;
		vertex.texCoord0 = texcoord0;
		vertex.texCoord1 = texcoord1;
		_mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.push_back(vertex);
	}

	void CResourceVertexBufferBase::freeVertexData(void)
	{
		_mvecVertexData_POS.clear();
		_mvecVertexData_POS_COL.clear();
		_mvecVertexData_POS_COL_TEXCOORD.clear();
		_mvecVertexData_POS_COL_NORMAL_TEXCOORD.clear();
		_mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.clear();
		_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.clear();
	}

	void CResourceVertexBufferBase::freeVertexIndicies(void)
	{
		_mvecIndices.clear();
	}

	void CResourceVertexBufferBase::freeAll(void)
	{
		freeVertexData();
		freeVertexIndicies();
	}

	void CResourceVertexBufferBase::addIndex(int newIndex)
	{
		_mvecIndices.push_back(newIndex);
	}

	size_t CResourceVertexBufferBase::getNumVertices(void) const
	{
		switch (eVertexBufferType)
		{
		case CResourceVertexBufferBase::EVertexBufferDataType::POS:
			return _mvecVertexData_POS.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL:
			return _mvecVertexData_POS_COL.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD:
			return _mvecVertexData_POS_COL_NORMAL_TEXCOORD.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2:
			return _mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL:
			return _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_TEXCOORD:
			return _mvecVertexData_POS_COL_TEXCOORD.size();
			break;
		default:
			Throw("Invalid geometry data type set.");
			break;
		}
	}

	size_t CResourceVertexBufferBase::getNumIndicies(void) const
	{
		return _mvecIndices.size();
	}

	void CResourceVertexBufferBase::convertObj(const std::string filename) const
	{

	}

	void CResourceVertexBufferBase::addFromFile(const std::string& strGeometryFilename)
	{

	}

	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* OpenGL
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceVertexBufferOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceVertexBufferOpenGL::CPrim
	{
	public:
		CPrim();
	};

	CResourceVertexBufferOpenGL::CPrim::CPrim()
	{
	}

	CResourceVertexBufferOpenGL::CResourceVertexBufferOpenGL()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceVertexBufferOpenGL::~CResourceVertexBufferOpenGL()
	{
		LOG("Destructor called.");
		freeGPU();
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceVertexBufferOpenGL::uploadGPU(void)
	{

	}

	void CResourceVertexBufferOpenGL::freeGPU(void)
	{

	}

	void CResourceVertexBufferOpenGL::render(bool bWireframeMode) const
	{

	}

	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Vulkan
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceVertexBufferVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceVertexBufferVulkan::CPrim
	{
	public:
		CPrim();
	};

	CResourceVertexBufferVulkan::CPrim::CPrim()
	{

	}

	CResourceVertexBufferVulkan::CResourceVertexBufferVulkan()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceVertexBufferVulkan::~CResourceVertexBufferVulkan()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceVertexBufferVulkan::uploadGPU(void)
	{

	}

	void CResourceVertexBufferVulkan::freeGPU(void)
	{

	}

	void CResourceVertexBufferVulkan::render(bool bWireframeMode) const
	{

	}
}	// namespace DCL
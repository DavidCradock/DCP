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
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
		free();
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceVertexBufferOpenGL::upload(void)
	{

	}

	void CResourceVertexBufferOpenGL::free(void)
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

	void CResourceVertexBufferVulkan::upload(void)
	{

	}

	void CResourceVertexBufferVulkan::free(void)
	{

	}

}	// namespace DCL
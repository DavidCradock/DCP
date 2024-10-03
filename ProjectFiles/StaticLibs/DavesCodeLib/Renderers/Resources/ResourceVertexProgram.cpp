#include "ResourceVertexProgram.h"
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

	/// \brief Private implementation for CResourceVertexProgramOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceVertexProgramOpenGL::CPrim
	{
	public:
		CPrim();
	};

	CResourceVertexProgramOpenGL::CPrim::CPrim()
	{
	}

	CResourceVertexProgramOpenGL::CResourceVertexProgramOpenGL()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceVertexProgramOpenGL::~CResourceVertexProgramOpenGL()
	{
		LOG("Destructor called.");

		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Vulkan
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceVertexProgramVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceVertexProgramVulkan::CPrim
	{
	public:
		CPrim();
	};

	CResourceVertexProgramVulkan::CPrim::CPrim()
	{
	}

	CResourceVertexProgramVulkan::CResourceVertexProgramVulkan()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceVertexProgramVulkan::~CResourceVertexProgramVulkan()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

}	// namespace DCL
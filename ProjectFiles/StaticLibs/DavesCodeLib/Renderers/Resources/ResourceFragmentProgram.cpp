#include "ResourceFragmentProgram.h"
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

	/// \brief Private implementation for CResourceFragmentProgramOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceFragmentProgramOpenGL::CPrim
	{
	public:
		CPrim();
	};

	CResourceFragmentProgramOpenGL::CPrim::CPrim()
	{
	}

	CResourceFragmentProgramOpenGL::CResourceFragmentProgramOpenGL()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceFragmentProgramOpenGL::~CResourceFragmentProgramOpenGL()
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

	/// \brief Private implementation for CResourceFragmentProgramVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceFragmentProgramVulkan::CPrim
	{
	public:
		CPrim();
	};

	CResourceFragmentProgramVulkan::CPrim::CPrim()
	{
	}

	CResourceFragmentProgramVulkan::CResourceFragmentProgramVulkan()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceFragmentProgramVulkan::~CResourceFragmentProgramVulkan()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

}	// namespace DCL
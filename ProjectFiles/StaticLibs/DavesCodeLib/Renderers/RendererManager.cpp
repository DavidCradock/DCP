#include "RendererManager.h"
#include "../Core/Exceptions.h"
#include "../Core/StringUtils.h"

namespace DCL
{
	CRendererManager::CRendererManager()
	{
		_mpRenderer = 0;
	}

	CRendererManager::~CRendererManager()
	{

	}

	CRendererBase* CRendererManager::init(const std::string& strRendererName)
	{
		std::string strRendererNameLowercase = strRendererName;
		StringUtils::stringToLowercase(strRendererNameLowercase);

		ThrowIfTrue(_mpRenderer, "CRendererManager::init() failed. Renderer already initialised.");

		if ("opengl" == strRendererName)
			_mpRenderer = new CRendererOpenGL;
		else if ("vulkan" == strRendererName)
			_mpRenderer = new CRendererVulkan;
		else
			Throw("CRendererManager::init() failed. The given renderer name of " + strRendererName + " was not recognised. Please use either opengl or vulkan.");

		ThrowIfMemoryNotAllocated(_mpRenderer);
		return _mpRenderer;
	}

	CRendererBase* CRendererManager::get(void)
	{
		ThrowIfFalse(_mpRenderer, "CRendererManager::get() failed. Renderer is not initialised.");
		return _mpRenderer;
	}

}	// namespace DCL
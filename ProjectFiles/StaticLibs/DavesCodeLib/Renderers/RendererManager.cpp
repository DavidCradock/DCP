#include "RendererManager.h"
#include "../Core/Exceptions.h"

namespace DCL
{
	CRendererManager::CRendererManager()
	{
		_mpRenderer = 0;
	}

	CRendererManager::~CRendererManager()
	{

	}

	CRendererBase* CRendererManager::initOpenGL(void)
	{
		ThrowIfTrue(_mpRenderer, "CRendererManager::initOpenGL() failed. Renderer already initialised.");
		_mpRenderer = new CRendererOpenGL;
		ThrowIfMemoryNotAllocated(_mpRenderer);
		return _mpRenderer;
	}

	CRendererBase* CRendererManager::initVulkan(void)
	{
		ThrowIfTrue(_mpRenderer, "CRendererManager::initVulkan() failed. Renderer already initialised.");
		_mpRenderer = new CRendererVulkan;
		ThrowIfMemoryNotAllocated(_mpRenderer);
		return _mpRenderer;
	}
	CRendererBase* CRendererManager::get(void)
	{
		ThrowIfFalse(_mpRenderer, "CRendererManager::get() failed. Renderer is not initialised.");
		return _mpRenderer;
	}

}	// namespace DCL
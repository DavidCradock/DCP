#include "RendererVulkan.h"
#include "../../Core/Exceptions.h"

#include <Windows.h>

// Vulkan

// SDL
#include "../../../../DynamicLibs/SDL-release-2.30.6/include/SDL.h"

namespace DCL
{
	/// \brief Private implementation for CRendererVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files including CRenderer's header file
	class CRendererVulkan::CPrim
	{
	public:
		/// \brief Constructor for private members. Sets to initial values
		CPrim();

		bool bVsyncEnabled;				///< Vsync enabled or not. Set during call to initialise()
		bool bWindowFullscreen;			///< Fullscreen or windowed. Set during call to initialise()
		CColourf clearColour;			///< The clear colour. Set during call to initialise()
		HINSTANCE hInstance;			///< Application instance handle. Set during call to initialise()
		std::string strWindowTitle;		///< Window's title text. Set during call to initialise()
		unsigned int uiWindowWidth;		///< Width of window. Set during call to initialise()
		unsigned int uiWindowHeight;	///< Height of window. Set during call to initialise()

		SDL_Window* pSDLWindow;			///< SDL Window object pointer
		SDL_GLContext SDLOpenGLContext;	///< SDL OpenGL context
	private:

	};

	CRendererVulkan::CPrim::CPrim()
	{
		pSDLWindow = NULL;
	}

	CRendererVulkan::CRendererVulkan()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CRendererVulkan::~CRendererVulkan()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CRendererVulkan::initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen, bool bVSyncEnabled, CColourf clearColour)
	{
		prim->bVsyncEnabled = bVSyncEnabled;
		prim->bWindowFullscreen = bFullscreen;
		prim->clearColour = clearColour;
		prim->hInstance = NULL;
		prim->strWindowTitle = strWindowTitle;
		prim->uiWindowHeight = iWindowHeight;
		prim->uiWindowWidth = iWindowWidth;
	}

	void CRendererVulkan::shutdown(void)
	{

	}

	void CRendererVulkan::updateWindow(bool& bWindowResized, bool& bWindowMinimized, bool& bWindowHasBeenAskedToClose)
	{

	}

	void CRendererVulkan::beginFrame(void)
	{

	}

	void CRendererVulkan::endFrame(void)
	{

	}

	void CRendererVulkan::setBackbufferClearColour(float fRed, float fGreen, float fBlue, float fAlpha)
	{

	}

	void CRendererVulkan::setVSync(bool bVSyncOn)
	{
		if (NULL != prim->pSDLWindow)
		{
			SDL_GL_SetSwapInterval(int(bVSyncOn));
		}
	}

	void CRendererVulkan::blendDisable(void)
	{

	}

	void CRendererVulkan::blendEnable(void)
	{

	}

	void CRendererVulkan::blendFunction_SrcAlpha_One(void)
	{

	}

	void CRendererVulkan::blendFunction_SrcAlpha_OneMinusSrcAlpha(void)
	{

	}

	void CRendererVulkan::cullFaceAntiClockwise(void)
	{

	}

	void CRendererVulkan::cullFaceClockwise(void)
	{

	}

	void CRendererVulkan::cullFaceDisable(void)
	{

	}

	void CRendererVulkan::cullFaceEnable(void)
	{

	}

	void CRendererVulkan::depthTestDisable(void)
	{

	}

	void CRendererVulkan::depthTestEnable(void)
	{

	}

	void CRendererVulkan::pixelsRead(int iPositionX, int iPositionY, int iWidth, int iHeight, void* pixels)
	{

	}

	void CRendererVulkan::pixelsWrite(int iPositionX, int iPositionY, int iWidth, int iHeight, void* pixels)
	{

	}

	void CRendererVulkan::scissorTest(int iPositionX, int iPositionY, int iWidth, int iHeight)
	{

	}

	void CRendererVulkan::scissorTestEnable(void)
	{

	}

	void CRendererVulkan::scissorTestDisable(void)
	{

	}

	CResourceGPUProgramsBase* CRendererVulkan::addGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return 0;
	}

	CResourceGPUProgramsBase* CRendererVulkan::getGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return 0;
	}

	bool CRendererVulkan::getGPUProgramsExists(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return false;
	}

	void CRendererVulkan::removeGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber)
	{

	}

	void CRendererVulkan::removeGPUProgramsAll(unsigned int uiGroupNumber)
	{

	}

	CResourceTexture2DBase* CRendererVulkan::addTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return 0;
	}

	CResourceTexture2DBase* CRendererVulkan::getTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return 0;
	}

	bool CRendererVulkan::getTexture2DExists(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return false;
	}

	void CRendererVulkan::removeTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber)
	{

	}

	void CRendererVulkan::removeTexture2DAll(unsigned int uiGroupNumber)
	{

	}

	CResourceVertexBufferBase* CRendererVulkan::addVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return 0;
	}

	CResourceVertexBufferBase* CRendererVulkan::getVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return 0;
	}

	bool CRendererVulkan::getVertexBufferExists(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		return false;
	}

	void CRendererVulkan::removeVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber)
	{

	}

	void CRendererVulkan::removeVertexBufferAll(unsigned int uiGroupNumber)
	{

	}
}	// namespace DCL
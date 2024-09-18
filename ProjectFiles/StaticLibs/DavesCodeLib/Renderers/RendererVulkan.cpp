#include "RendererVulkan.h"
#include "../Core/Exceptions.h"

#include <Windows.h>

// Vulkan

// SDL
#include "../../../DynamicLibs/SDL-release-2.30.6/include/SDL.h"

namespace DCL
{
	/// \brief Private implementation for CRendererVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files including CRenderer's header file
	class CRendererVulkan::CPimpl
	{
	public:
		/// \brief Constructor for private members. Sets to initial values
		CPimpl();

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

	CRendererVulkan::CPimpl::CPimpl()
	{
		pSDLWindow = NULL;
	}

	CRendererVulkan::CRendererVulkan()
	{
		LOG("Constructor called.");
		_mpPimpl = new CPimpl;
		ThrowIfMemoryNotAllocated(_mpPimpl);
	}

	CRendererVulkan::~CRendererVulkan()
	{
		LOG("Destructor called.");
		if (_mpPimpl)
		{
			delete _mpPimpl;
			_mpPimpl = 0;
		}
	}

	void CRendererVulkan::initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen, bool bVSyncEnabled, CColourf clearColour)
	{
		_mpPimpl->bVsyncEnabled = bVSyncEnabled;
		_mpPimpl->bWindowFullscreen = bFullscreen;
		_mpPimpl->clearColour = clearColour;
		_mpPimpl->hInstance = NULL;
		_mpPimpl->strWindowTitle = strWindowTitle;
		_mpPimpl->uiWindowHeight = iWindowHeight;
		_mpPimpl->uiWindowWidth = iWindowWidth;
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

}	// namespace DCL
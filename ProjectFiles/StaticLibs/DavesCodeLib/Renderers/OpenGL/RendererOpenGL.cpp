#include "RendererOpenGL.h"
#include "../../Core/Colourf.h"

#include "RendererOpenGLExtensions.h"

// SDL
#include "../../../../DynamicLibs/SDL-release-2.30.6/include/SDL.h"
#include "../../../../DynamicLibs/SDL-release-2.30.6/include/SDL_opengl.h"

namespace DCL
{

	/// \brief Private implementation for CRendererOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files including CRenderer's header file
	class CRendererOpenGL::CPrim
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

	CRendererOpenGL::CPrim::CPrim()
	{
		pSDLWindow = NULL;
	}

	CRendererOpenGL::CRendererOpenGL()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CRendererOpenGL::~CRendererOpenGL()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CRendererOpenGL::initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen, bool bVSyncEnabled, CColourf clearColour)
	{
		prim->bVsyncEnabled = bVSyncEnabled;
		prim->bWindowFullscreen = bFullscreen;
		prim->clearColour = clearColour;
		prim->hInstance = NULL;
		prim->strWindowTitle = strWindowTitle;
		prim->uiWindowHeight = iWindowHeight;
		prim->uiWindowWidth = iWindowWidth;

		if (0 != SDL_Init(SDL_INIT_VIDEO))
		{
			std::string strError("CRendererOpenGL::initialise() failed during call to SDL_Init(SDL_INIT_VIDEO)\n");
			strError += "SDL_GetError() string: ";
			strError += SDL_GetError();
			Throw(strError);
		}

		// Use OpenGL 3.1 core (Will probably increase as we'll probably require computation features)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Create application window
		/* Info copied from SDL docs at https://wiki.libsdl.org/SDL2/SDL_CreateWindow
		If the window is created with the SDL_WINDOW_ALLOW_HIGHDPI flag, its size in pixels may differ from its size in screen coordinates on platforms with high-DPI support (e.g. iOS and macOS).
		Use SDL_GetWindowSize() to query the client area's size in screen coordinates, and SDL_GL_GetDrawableSize() or SDL_GetRendererOutputSize() to query the drawable size in pixels.
		Note that when this flag is set, the drawable size can vary after the window is created and should be queried after major window events such as when the window is resized or moved between displays.
		If the window is set fullscreen, the width and height parameters w and h will not be used. However, invalid size parameters (e.g. too large) may still fail.
		Window size is actually limited to 16384 x 16384 for all platforms at window creation.
		If the window is created with any of the SDL_WINDOW_OPENGL or SDL_WINDOW_VULKAN flags, then the corresponding LoadLibrary function (SDL_GL_LoadLibrary or SDL_Vulkan_LoadLibrary) is
		called and the corresponding UnloadLibrary function is called by SDL_DestroyWindow().
		If SDL_WINDOW_VULKAN is specified and there isn't a working Vulkan driver, SDL_CreateWindow() will fail because SDL_Vulkan_LoadLibrary() will fail.
		*/
		int iWindowFlags;
		if (bFullscreen)
			iWindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP;
		else
			iWindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		prim->pSDLWindow = SDL_CreateWindow(
			strWindowTitle.c_str(),		// Window title text
			SDL_WINDOWPOS_UNDEFINED,	// X position of window. Can be either SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED
			SDL_WINDOWPOS_UNDEFINED,	// Y position of window. Can be either SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED
			iWindowWidth,				// Window width
			iWindowHeight,				// Window height
			iWindowFlags);				// OR'd flags. Can be...
													// SDL_WINDOW_FULLSCREEN: fullscreen window
													// SDL_WINDOW_FULLSCREEN_DESKTOP : fullscreen window at desktop resolution
													// SDL_WINDOW_OPENGL : window usable with an OpenGL context
													// SDL_WINDOW_VULKAN : window usable with a Vulkan instance
													// SDL_WINDOW_METAL : window usable with a Metal instance
													// SDL_WINDOW_HIDDEN : window is not visible
													// SDL_WINDOW_BORDERLESS : no window decoration
													// SDL_WINDOW_RESIZABLE : window can be resized
													// SDL_WINDOW_MINIMIZED : window is minimized
													// SDL_WINDOW_MAXIMIZED : window is maximized
													// SDL_WINDOW_INPUT_GRABBED : window has grabbed input focus
													// SDL_WINDOW_ALLOW_HIGHDPI : window should be created in high - DPI mode if supported(>= SDL 2.0.1)

		if (NULL == prim->pSDLWindow)
		{
			std::string strError("CRendererOpenGL::initialise() failed during call to SDL_CreateWindow()\n");
			strError += "SDL_GetError() string: ";
			strError += SDL_GetError();
			Throw(strError);
		}

		prim->SDLOpenGLContext = SDL_GL_CreateContext(prim->pSDLWindow);
		if (NULL == prim->SDLOpenGLContext)
		{
			std::string strError("CRendererOpenGL::initialise() failed during call to SDL_GL_CreateContext()\n");
			strError += "SDL_GetError() string: ";
			strError += SDL_GetError();
			Throw(strError);
		}

		if (SDL_GL_SetSwapInterval((int)bVSyncEnabled) < 0)
		{
			std::string strError("CRendererOpenGL::initialise() failed during call to SDL_GL_SetSwapInterval()\n");
			strError += "SDL_GetError() string: ";
			strError += SDL_GetError();
			Throw(strError);
		}

		// Detect OpenGL extensions and obtain function pointers
		setupOpenGLExtensions(true);
	}

	void CRendererOpenGL::shutdown(void)
	{
		SDL_DestroyWindow(prim->pSDLWindow);
		prim->pSDLWindow = NULL;
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}

	void CRendererOpenGL::updateWindow(bool& bWindowResized, bool& bWindowMinimized, bool& bWindowHasBeenAskedToClose)
	{
		bWindowResized = false;
		bWindowMinimized = false;
		bWindowHasBeenAskedToClose = false;

		//Event handler
		SDL_Event e;

		//Enable text input
		SDL_StartTextInput();

		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				bWindowHasBeenAskedToClose = true;
			}
			//Handle keypress with current mouse position
			else if (e.type == SDL_TEXTINPUT)
			{
	//			int x = 0, y = 0;
	//			SDL_GetMouseState(&x, &y);
	//			handleKeys(e.text.text[0], x, y);
			}
		}

		// Update screen
	//	SDL_GL_SwapWindow(gWindow);

		// Disable text input
		SDL_StopTextInput();
	}

	void CRendererOpenGL::beginFrame(void)
	{
		glClearColor(prim->clearColour.red, prim->clearColour.green, prim->clearColour.blue, prim->clearColour.alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void CRendererOpenGL::endFrame(void)
	{
		SDL_GL_SwapWindow(prim->pSDLWindow);
	}

	void CRendererOpenGL::setBackbufferClearColour(float fRed, float fGreen, float fBlue, float fAlpha)
	{
		prim->clearColour.set(fRed, fGreen, fBlue, fAlpha);
	}

	void CRendererOpenGL::setVSync(bool bVSyncOn)
	{
		if (NULL != prim->pSDLWindow)
		{
			SDL_GL_SetSwapInterval(int(bVSyncOn));
		}
	}

	void CRendererOpenGL::blendDisable(void)
	{
		glDisable(GL_BLEND);
	}

	void CRendererOpenGL::blendEnable(void)
	{
		glEnable(GL_BLEND);
	}

	void CRendererOpenGL::blendFunction_SrcAlpha_One(void)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	void CRendererOpenGL::blendFunction_SrcAlpha_OneMinusSrcAlpha(void)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void CRendererOpenGL::cullFaceAntiClockwise(void)
	{

	}

	void CRendererOpenGL::cullFaceClockwise(void)
	{

	}

	void CRendererOpenGL::cullFaceDisable(void)
	{

	}

	void CRendererOpenGL::cullFaceEnable(void)
	{

	}

	void CRendererOpenGL::depthTestDisable(void)
	{
		glDisable(GL_DEPTH_TEST);
	}

	void CRendererOpenGL::depthTestEnable(void)
	{
		glEnable(GL_DEPTH_TEST);
	}

	void CRendererOpenGL::pixelsRead(int iPositionX, int iPositionY, int iWidth, int iHeight, void* pixels)
	{

	}

	void CRendererOpenGL::pixelsWrite(int iPositionX, int iPositionY, int iWidth, int iHeight, void* pixels)
	{

	}

	void CRendererOpenGL::scissorTest(int iPositionX, int iPositionY, int iWidth, int iHeight)
	{
		glScissor(iPositionX, iPositionY, iWidth, iHeight);
	}

	void CRendererOpenGL::scissorTestEnable(void)
	{
		glEnable(GL_SCISSOR_TEST);
	}

	void CRendererOpenGL::scissorTestDisable(void)
	{
		glDisable(GL_SCISSOR_TEST);
	}

	CResourceTexture2DBase* CRendererOpenGL::addTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		// Make sure valid group number is given
		ThrowIfTrue(uiGroupNumber > 7, "CRendererOpenGL::addTexture2D() failed. Invalid group number of " + std::to_string(uiGroupNumber) + " was given. Should be in range of 0 to 7");

		// If resource already exists
		auto itResource = _mmapResTexture2DGroups[uiGroupNumber].find(strResourceName);
		if (itResource != _mmapResTexture2DGroups[uiGroupNumber].end())
		{
			itResource->second.uiCount++;
			return itResource->second.pResource;
		}
		// Resource doesn't exist, create it
		SResourceTexture2D newRes;
		newRes.uiCount = 1;
		newRes.pResource = new CResourceTexture2DOpenGL;
		ThrowIfFalse(newRes.pResource, "CRendererOpenGL::addTexture2D(" + strResourceName + ") failed to allocate memory for new resource.");
		_mmapResTexture2DGroups[uiGroupNumber][strResourceName] = newRes;
		return newRes.pResource;
	}

	CResourceTexture2DBase* CRendererOpenGL::getTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		// Make sure valid group number is given
		ThrowIfTrue(uiGroupNumber > 7, "CRendererOpenGL::getTexture2De() failed. Invalid group number of " + std::to_string(uiGroupNumber) + " was given. Should be in range of 0 to 7");

		auto itResource = _mmapResTexture2DGroups[uiGroupNumber].find(strResourceName);
		ThrowIfTrue(itResource == _mmapResTexture2DGroups[uiGroupNumber].end(), "CRendererOpenGL::getTexture2D(" + strResourceName + ") failed. Named resource doesn't exist.");
		return itResource->second.pResource;
	}

	bool CRendererOpenGL::getTexture2DExists(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		// Make sure valid group number is given
		ThrowIfTrue(uiGroupNumber > 7, "CRendererOpenGL::getTexture2DExists() failed. Invalid group number of " + std::to_string(uiGroupNumber) + " was given. Should be in range of 0 to 7");

		return _mmapResTexture2DGroups[uiGroupNumber].find(strResourceName) != _mmapResTexture2DGroups[uiGroupNumber].end();
	}

	void CRendererOpenGL::removeTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber)
	{
		// Make sure valid group number is given
		ThrowIfTrue(uiGroupNumber > 7, "CRendererOpenGL::removeTexture2D() failed. Invalid group number of " + std::to_string(uiGroupNumber) + " was given. Should be in range of 0 to 7");

		auto itResource = _mmapResTexture2DGroups[uiGroupNumber].find(strResourceName);
		if (itResource == _mmapResTexture2DGroups[uiGroupNumber].end())
			return;	// Doesn't exist.
		if (itResource->second.uiCount > 1)
		{
			itResource->second.uiCount--;
			return;
		}
		delete itResource->second.pResource;
		_mmapResTexture2DGroups[uiGroupNumber].erase(itResource);
	}

	void CRendererOpenGL::removeAllTexture2D(unsigned int uiGroupNumber)
	{
		// Make sure valid group number is given
		ThrowIfTrue(uiGroupNumber > 7, "CRendererOpenGL::removeAllTexture2D() failed. Invalid group number of " + std::to_string(uiGroupNumber) + " was given. Should be in range of 0 to 7");

		auto itResource = _mmapResTexture2DGroups[uiGroupNumber].begin();
		while (itResource != _mmapResTexture2DGroups[uiGroupNumber].end())
		{
			delete itResource->second.pResource;
			_mmapResTexture2DGroups[uiGroupNumber].erase(itResource);
			itResource = _mmapResTexture2DGroups[uiGroupNumber].begin();
		}

	}

}	// namespace DCL
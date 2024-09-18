#include "RendererOpenGL.h"
#include "../Core/Colourf.h"
#include "../Core/Exceptions.h"

#include <Windows.h>

// OpenGL
#include <gl\gl.h>                                // Header File For The OpenGL32 Library
#include <gl\glu.h>                               // Header File For The GLu32 Library
#include "OpenGL/glcorearb.h"
#include "OpenGL/glext.h"
#include "OpenGL/khrplatform.h"
#include "OpenGL/wgl.h"
#include "OpenGL/wglext.h"
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

// SDL
#include "../../../DynamicLibs/SDL-release-2.30.6/include/SDL.h"
#include "../../../DynamicLibs/SDL-release-2.30.6/include/SDL_opengl.h"

namespace DCL
{

	/// \brief Private implementation for CRendererOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files including CRenderer's header file
	class CRendererOpenGL::CPimpl
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

	CRendererOpenGL::CPimpl::CPimpl()
	{
		pSDLWindow = NULL;
	}

	CRendererOpenGL::CRendererOpenGL()
	{
		LOG("Constructor called.");
		_mpPimpl = new CPimpl;
		ThrowIfMemoryNotAllocated(_mpPimpl);
	}

	CRendererOpenGL::~CRendererOpenGL()
	{
		LOG("Destructor called.");
		if (_mpPimpl)
		{
			delete _mpPimpl;
			_mpPimpl = 0;
		}
	}

	void CRendererOpenGL::initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen, bool bVSyncEnabled, CColourf clearColour)
	{
		_mpPimpl->bVsyncEnabled = bVSyncEnabled;
		_mpPimpl->bWindowFullscreen = bFullscreen;
		_mpPimpl->clearColour = clearColour;
		_mpPimpl->hInstance = NULL;
		_mpPimpl->strWindowTitle = strWindowTitle;
		_mpPimpl->uiWindowHeight = iWindowHeight;
		_mpPimpl->uiWindowWidth = iWindowWidth;

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

		_mpPimpl->pSDLWindow = SDL_CreateWindow(
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

		if (NULL == _mpPimpl->pSDLWindow)
		{
			std::string strError("CRendererOpenGL::initialise() failed during call to SDL_CreateWindow()\n");
			strError += "SDL_GetError() string: ";
			strError += SDL_GetError();
			Throw(strError);
		}

		_mpPimpl->SDLOpenGLContext = SDL_GL_CreateContext(_mpPimpl->pSDLWindow);
		if (NULL == _mpPimpl->SDLOpenGLContext)
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
	}

	void CRendererOpenGL::shutdown(void)
	{
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
		glClearColor(_mpPimpl->clearColour.red, _mpPimpl->clearColour.green, _mpPimpl->clearColour.blue, _mpPimpl->clearColour.alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void CRendererOpenGL::endFrame(void)
	{
		SDL_GL_SwapWindow(_mpPimpl->pSDLWindow);
	}

	void CRendererOpenGL::setBackbufferClearColour(float fRed, float fGreen, float fBlue, float fAlpha)
	{
		_mpPimpl->clearColour.set(fRed, fGreen, fBlue, fAlpha);
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

}	// namespace DCL
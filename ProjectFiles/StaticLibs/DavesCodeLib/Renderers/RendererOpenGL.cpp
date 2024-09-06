#include "RendererOpenGL.h"
#include "../Core/Colourf.h"
#include "../Core/Exceptions.h"

// OpenGL
#include <Windows.h>
#include <gl\gl.h>                                // Header File For The OpenGL32 Library
#include <gl\glu.h>                               // Header File For The GLu32 Library
#include "OpenGL/glcorearb.h"
#include "OpenGL/glext.h"
#include "OpenGL/khrplatform.h"
#include "OpenGL/wgl.h"
#include "OpenGL/wglext.h"
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")


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

		bool bVsyncEnabled;			///< Vsync enabled or not
		bool bWindowFullscreen;		///< Fullscreen or windowed
		CColourf clearColour;		///< The clear colour
		HINSTANCE hInstance;		///< Application instance handle
		std::string strWindowTitle;	///< Window's title text
		unsigned int uiWindowWidth;	///< Width of window
		unsigned int uiWindowHeight;///< Height of window

	private:

	};

	CRendererOpenGL::CPimpl::CPimpl()
	{
		
	}

	CRendererOpenGL::CRendererOpenGL()
	{
		_mpPimpl = new CPimpl;
		ThrowIfMemoryNotAllocated(_mpPimpl);
	}

	CRendererOpenGL::~CRendererOpenGL()
	{
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


	}

	void CRendererOpenGL::shutdown(void)
	{

	}

	void CRendererOpenGL::updateWindow(bool& bWindowResized, bool& bWindowMinimized, bool& bWindowHasBeenAskedToClose)
	{
		bWindowResized = false;
		bWindowMinimized = false;
		bWindowHasBeenAskedToClose = true;
		ThrowIfTrue(1, "This is a test exception. Nothing actually went wrong, this is just a test :)");
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
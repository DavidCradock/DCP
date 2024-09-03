#include "RendererOpenGL.h"

#include "../Core/Exceptions.h"

#include "RendererOpenGLPrivate.h"

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
	CRendererOpenGL::CRendererOpenGL()
	{
		_mpPrivate = new CPimpl;
		ThrowIfMemoryNotAllocated(_mpPrivate);
	}

	CRendererOpenGL::~CRendererOpenGL()
	{
		if (_mpPrivate)
		{
			delete _mpPrivate;
			_mpPrivate = 0;
		}
	}

	void CRendererOpenGL::initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen)
	{

	}

	void CRendererOpenGL::shutdown(void)
	{

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
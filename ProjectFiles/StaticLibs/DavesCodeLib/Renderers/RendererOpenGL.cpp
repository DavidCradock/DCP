#include "RendererOpenGL.h"

namespace DCL
{
	CRendererOpenGL::CRendererOpenGL()
	{
	}

	CRendererOpenGL::~CRendererOpenGL()
	{

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
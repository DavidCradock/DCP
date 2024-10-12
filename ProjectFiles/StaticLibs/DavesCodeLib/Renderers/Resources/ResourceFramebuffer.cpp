#include "ResourceFramebuffer.h"
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

	/// \brief Private implementation for CResourceFramebufferOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceFramebufferOpenGL::CPrim
	{
	public:
		CPrim();
		CDimension2D dimension;			///< Dimensions of the framebuffer
		unsigned int uiFramebufferID;	///< OpenGL ID for the framebuffer
		unsigned int uiTextureID;		///< OpenGL ID for the texture attached to the framebuffer
		unsigned int uiRenderbufferID;	///< OpenGL ID for the renderbuffer
	};

	CResourceFramebufferOpenGL::CPrim::CPrim()
	{
		dimension.set(32, 32);
		uiFramebufferID = 0;
		uiTextureID = 0;
		uiRenderbufferID = 0;
	}

	CResourceFramebufferOpenGL::CResourceFramebufferOpenGL()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceFramebufferOpenGL::~CResourceFramebufferOpenGL()
	{
		LOG("Destructor called.");
		free();
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceFramebufferOpenGL::upload(void)
	{
		// Create the framebuffer object and bind it
		glGenFramebuffers(1, &prim->uiFramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, prim->uiFramebufferID);

		// Create a texture which will be attached to the framebuffer object for colour information
		glGenTextures(1, &prim->uiTextureID);
		glBindTexture(GL_TEXTURE_2D, prim->uiTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, prim->dimension.width, prim->dimension.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, prim->uiTextureID, 0);

		// Create renderbuffer object for depth and stencil
		glGenRenderbuffers(1, &prim->uiRenderbufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, prim->uiRenderbufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, prim->dimension.width, prim->dimension.height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, prim->uiRenderbufferID);

		ThrowIfTrue(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "CResourceFramebufferOpenGL::upload() failed to create a complete framebuffer.");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void CResourceFramebufferOpenGL::free(void)
	{
		if (0 != prim->uiTextureID)
		{
			glDeleteTextures(1, &prim->uiTextureID);
			prim->uiTextureID = 0;
		}
		if (0 != prim->uiRenderbufferID)
		{
			glDeleteRenderbuffers(1, &prim->uiRenderbufferID);
			prim->uiRenderbufferID = 0;
		}
		if (0 != prim->uiFramebufferID)
		{
			glDeleteFramebuffers(1, &prim->uiFramebufferID);
			prim->uiFramebufferID = 0;
		}
	}

	void CResourceFramebufferOpenGL::bindAsRenderTarget(bool bClearbuffer, const CColourf& backgroundClearColour)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, prim->uiFramebufferID);

		if (bClearbuffer)
		{
			glClearColor(backgroundClearColour.red, backgroundClearColour.green, backgroundClearColour.blue, backgroundClearColour.alpha);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
		glViewport(0, 0, prim->dimension.width, prim->dimension.height);
	}

	void CResourceFramebufferOpenGL::unbindAsRenderTarget(void) const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glFlush();
//		glFinish();
	}

	void CResourceFramebufferOpenGL::bindAsTexture(unsigned int uiTextureUnit) const
	{
		switch (uiTextureUnit)
		{
		case 0:
			glActiveTexture(GL_TEXTURE0);
			break;
		case 1:
			glActiveTexture(GL_TEXTURE1);
			break;
		case 2:
			glActiveTexture(GL_TEXTURE2);
			break;
		case 3:
			glActiveTexture(GL_TEXTURE3);
			break;
		case 4:
			glActiveTexture(GL_TEXTURE4);
			break;
		case 5:
			glActiveTexture(GL_TEXTURE5);
			break;
		case 6:
			glActiveTexture(GL_TEXTURE6);
			break;
		case 7:
			glActiveTexture(GL_TEXTURE7);
			break;
		}
		glBindTexture(GL_TEXTURE_2D, prim->uiTextureID);
	}

	void CResourceFramebufferOpenGL::unbindTexture(unsigned int uiTextureUnit) const
	{
		switch (uiTextureUnit)
		{
		case 0:
			glActiveTexture(GL_TEXTURE0);
			break;
		case 1:
			glActiveTexture(GL_TEXTURE1);
			break;
		case 2:
			glActiveTexture(GL_TEXTURE2);
			break;
		case 3:
			glActiveTexture(GL_TEXTURE3);
			break;
		case 4:
			glActiveTexture(GL_TEXTURE4);
			break;
		case 5:
			glActiveTexture(GL_TEXTURE5);
			break;
		case 6:
			glActiveTexture(GL_TEXTURE6);
			break;
		case 7:
			glActiveTexture(GL_TEXTURE7);
			break;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int CResourceFramebufferOpenGL::getWidth(void) const
	{
		return prim->dimension.width;
	}

	unsigned int CResourceFramebufferOpenGL::getHeight(void) const
	{
		return prim->dimension.height;
	}

	CDimension2D CResourceFramebufferOpenGL::getDimensions(void) const
	{
		return prim->dimension;
	}

	void CResourceFramebufferOpenGL::resize(unsigned int uiNewWidth, unsigned int uiNewHeight)
	{
		CDimension2D newDims(uiNewWidth, uiNewHeight);
		resize(newDims);
	}

	void CResourceFramebufferOpenGL::resize(CDimension2D& newDimensions)
	{
		// If the framebuffer is already the newly specified size, do nother
		if (newDimensions == prim->dimension)
			return;

		ThrowIfTrue(newDimensions.width == 0 || newDimensions.height == 0, "CResourceFramebufferOpenGL::resize() given a dimension of size zero.");
		free();
		prim->dimension = newDimensions;
		upload();
	}


	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Vulkan
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceFramebufferVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceFramebufferVulkan::CPrim
	{
	public:
		CPrim();

		CDimension2D dimension;			///< Dimensions of the framebuffer
	};

	CResourceFramebufferVulkan::CPrim::CPrim()
	{
		dimension.set(32, 32);
	}

	CResourceFramebufferVulkan::CResourceFramebufferVulkan()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceFramebufferVulkan::~CResourceFramebufferVulkan()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceFramebufferVulkan::upload(void)
	{

	}

	void CResourceFramebufferVulkan::free(void)
	{

	}

	void CResourceFramebufferVulkan::bindAsRenderTarget(bool bClearbuffer, const CColourf& backgroundClearColour)
	{

	}

	void CResourceFramebufferVulkan::unbindAsRenderTarget(void) const
	{

	}

	void CResourceFramebufferVulkan::bindAsTexture(unsigned int uiTextureUnit) const
	{

	}

	void CResourceFramebufferVulkan::unbindTexture(unsigned int uiTextureUnit) const
	{

	}

	unsigned int CResourceFramebufferVulkan::getWidth(void) const
	{
		return prim->dimension.width;
	}

	unsigned int CResourceFramebufferVulkan::getHeight(void) const
	{
		return prim->dimension.height;
	}

	CDimension2D CResourceFramebufferVulkan::getDimensions(void) const
	{
		return prim->dimension;
	}

	void CResourceFramebufferVulkan::resize(unsigned int uiNewWidth, unsigned int uiNewHeight)
	{
		CDimension2D newDims(uiNewWidth, uiNewHeight);
		resize(newDims);
	}

	void CResourceFramebufferVulkan::resize(CDimension2D& newDimensions)
	{

	}
}	// namespace DCL
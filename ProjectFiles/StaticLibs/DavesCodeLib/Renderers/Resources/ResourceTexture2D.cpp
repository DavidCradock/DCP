#include "ResourceTexture2D.h"
#include "../../Core/Exceptions.h"
#include "../OpenGL/RendererOpenGLExtensions.h"

namespace DCL
{
	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Base
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/


	void CResourceTexture2DBase::setImageData(const CImage& imageDataSource)
	{
		ThrowIfTrue(0 == imageDataSource.getDataSize(), "Given CImage object has zero data.");
		imageDataSource.copyTo(imageData);
	}

	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* OpenGL
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceTexture2DOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceTexture2DOpenGL::CPrim
	{
	public:
		CPrim();
		unsigned int uiTextureID;	///< OpenGL texture ID
	};

	CResourceTexture2DOpenGL::CPrim::CPrim()
	{
		uiTextureID = 0;
	}

	CResourceTexture2DOpenGL::CResourceTexture2DOpenGL()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceTexture2DOpenGL::~CResourceTexture2DOpenGL()
	{
		LOG("Destructor called.");
		free();
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceTexture2DOpenGL::upload(void)
	{
		CImage image;
		ThrowIfTrue(0 == imageData.getDataSize(), "CResourceTexture2DOpenGL::upload() failed. ImageData holds no data.");
		glGenTextures(1, &prim->uiTextureID);
		glBindTexture(GL_TEXTURE_2D, prim->uiTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (3 == image.getNumChannels())
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getData());
		else  // We'll assume 4
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void CResourceTexture2DOpenGL::free(void)
	{
		if (!prim->uiTextureID)
			return;
		glDeleteTextures(1, &prim->uiTextureID);
		prim->uiTextureID = 0;
	}

	void CResourceTexture2DOpenGL::bind(unsigned int uiTextureUnit) const
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

	void CResourceTexture2DOpenGL::unbind(unsigned int uiTextureUnit) const
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

	void CResourceTexture2DOpenGL::unbindAll(void) const
	{
		glActiveTexture(GL_TEXTURE7);	glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE6);	glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE5);	glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE4);	glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE3);	glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE2);	glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);	glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);	glBindTexture(GL_TEXTURE_2D, 0);
	}

	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Vulkan
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceTexture2DVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceTexture2DVulkan::CPrim
	{
	public:
		CPrim();
	};

	CResourceTexture2DVulkan::CPrim::CPrim()
	{

	}

	CResourceTexture2DVulkan::CResourceTexture2DVulkan()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceTexture2DVulkan::~CResourceTexture2DVulkan()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceTexture2DVulkan::upload(void)
	{

	}

	void CResourceTexture2DVulkan::free(void)
	{

	}

	void CResourceTexture2DVulkan::bind(unsigned int uiTextureUnit) const
	{

	}

	void CResourceTexture2DVulkan::unbind(unsigned int uiTextureUnit) const
	{

	}

	void CResourceTexture2DVulkan::unbindAll(void) const
	{

	}

}	// namespace DCL
#include "ResourceTexture2D.h"
#include "../../Core/Exceptions.h"
namespace DCL
{
	void CResourceTexture2DBase::setImageData(const CImage& imageDataSource)
	{
		ThrowIfTrue(0 == imageDataSource.getDataSize(), "Given CImage object has zero data.");
		imageDataSource.copyTo(imageData);
	}

	CResourceTexture2DOpenGL::CResourceTexture2DOpenGL()
	{

	}

	void CResourceTexture2DOpenGL::upload(void)
	{

	}

	void CResourceTexture2DOpenGL::free(void)
	{

	}

	void CResourceTexture2DOpenGL::bind(unsigned int uiTextureUnit) const
	{

	}

	void CResourceTexture2DOpenGL::unbind(unsigned int uiTextureUnit) const
	{

	}

	void CResourceTexture2DOpenGL::unbindAll(void) const
	{

	}

	CResourceTexture2DVulkan::CResourceTexture2DVulkan()
	{

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
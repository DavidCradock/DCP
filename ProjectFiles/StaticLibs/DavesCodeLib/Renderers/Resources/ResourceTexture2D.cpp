#include "ResourceTexture2D.h"
#include "../../Core/Exceptions.h"
namespace DCL
{
	void CResourceTexture2DBase::setImageData(const CImage& imageData)
	{
		ThrowIfTrue(0 == imageData.getDataSize(), "Given CImage object has zero data.");
		imageData.copyTo(_mImageData);
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

	CDimension2D CResourceTexture2DOpenGL::getDimension(void) const
	{
		CDimension2D r;
		return r;
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

	CDimension2D CResourceTexture2DVulkan::getDimension(void) const
	{
		CDimension2D r;
		return r;
	}

}	// namespace DCL
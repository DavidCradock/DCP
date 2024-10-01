#include "ResourceTexture2DFromCImage.h"
#include "../../Core/Exceptions.h"
namespace DCL
{
	void CResourceTexture2DFromCImageBase::setImageData(const CImage& imageData)
	{
		ThrowIfTrue(0 == imageData.getDataSize(), "Given CImage object has zero data.");
		imageData.copyTo(_mImageData);
	}

	CResourceTexture2DFromCImageOpenGL::CResourceTexture2DFromCImageOpenGL()
	{

	}

	void CResourceTexture2DFromCImageOpenGL::upload(void)
	{

	}

	void CResourceTexture2DFromCImageOpenGL::free(void)
	{

	}

	void CResourceTexture2DFromCImageOpenGL::bind(unsigned int uiTextureUnit) const
	{

	}

	void CResourceTexture2DFromCImageOpenGL::unbind(unsigned int uiTextureUnit) const
	{

	}

	void CResourceTexture2DFromCImageOpenGL::unbindAll(void) const
	{

	}

	CDimension2D CResourceTexture2DFromCImageOpenGL::getDimension(void)
	{
		CDimension2D r;
		return r;
	}

	CResourceTexture2DFromCImageVulkan::CResourceTexture2DFromCImageVulkan()
	{

	}

	void CResourceTexture2DFromCImageVulkan::upload(void)
	{

	}

	void CResourceTexture2DFromCImageVulkan::free(void)
	{

	}

	void CResourceTexture2DFromCImageVulkan::bind(unsigned int uiTextureUnit) const
	{

	}

	void CResourceTexture2DFromCImageVulkan::unbind(unsigned int uiTextureUnit) const
	{

	}

	void CResourceTexture2DFromCImageVulkan::unbindAll(void) const
	{

	}

	CDimension2D CResourceTexture2DFromCImageVulkan::getDimension(void)
	{
		CDimension2D r;
		return r;
	}

}	// namespace DCL
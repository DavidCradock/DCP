#ifndef RESOURCE_TEXTURE2D_FROM_CIMAGE_H
#define RESOURCE_TEXTURE2D_FROM_CIMAGE_H

#include "../../Image/Image.h"
#include "../../Core/Dimensions.h"
//#include <string>

namespace DCL
{
	/// \brief Base class for resource of type texture 2D created from a CImage object
	///
	/// We derive resource classes from this base class for each renderer type such as OpenGL and Vulkan.
	/// These classes are to be declared within this header file to reduce the number of files.
	/// Eww! I know right? Three class declarations insided a single header file, the madness!
	/// I know it's a little messy, but the alternative is to have six files for each resource type and as there are quite a few resources, this would've meant many files and that's even more messy.
	/// I know it means that the various renderers for the different graphics APIs are including stuff which isn't related to them, but that's a small price to pay for the reduced number of files we'd otherwise have to create.
	/// Within DCL, all code uses only a pointer to the base class and the implementation for each of the methods are implemented inside the derived classes and are insulated via private implementations.
	/// Each of the API's CRenderer classes which are derived from the CRendererBase class, are responsible for creating, accessing and freeing this resource type.
	/// 
	class CResourceTexture2DFromCImageBase
	{
	public:
		/// \brief Copies the image data from the given CImage object into this object.
		/// 
		/// \param imageData A CImage object which contains existing image data to be used by this object.
		/// 
		/// Once this method is called, the CImage object is no longer required and can be freed.
		/// If the given CImage object doesn't have any image data, an exception occurs.
		/// This does NOT upload the image data to the GPU.
		void setImageData(const CImage& imageData);

		/// \brief Uploads the image data stored in _mImageData into GPU memory, ready for use.
		///
		/// If the image data hasn't been set with setImageData(), an exception should occur.
		virtual void upload(void) = 0;

		/// \brief Frees the image data from the GPU memory.
		virtual void free(void) = 0;

		/// \brief Binds the texture to the given texture unit number, starting at zero
		/// \param uiTextureUnit The texture unit number to bind the texture data to. Should be between 0 and 7.
		virtual void bind(unsigned int uiTextureUnit = 0) const = 0;

		/// \brief Unbinds texturing for the specified texture unit
		/// \param uiTextureUnit The texture unit number to unbind texturing. Should be between 0 and 7.
		virtual void unbind(unsigned int uiTextureUnit = 0) const = 0;

		/// \brief Unbinds texturing from texture units 0 to 7.
		virtual void unbindAll(void) const = 0;

		/// \brief Returns the dimensions of the image stored used by this texture
		///
		/// Will return the correct dimensions once setImageFilename() has been called.
		virtual CDimension2D getDimension(void) = 0;

	private:
		CImage _mImageData;		///< CImage object which holds the image data this object uses.
	};

	/// \brief OpenGL class for resource of type texture 2D created from a CImage object
	///
	///
	class CResourceTexture2DFromCImageOpenGL : public CResourceTexture2DFromCImageBase
	{
	public:
		CResourceTexture2DFromCImageOpenGL();

		void upload(void);
		void free(void);
		void bind(unsigned int uiTextureUnit = 0) const;
		void unbind(unsigned int uiTextureUnit = 0) const;
		void unbindAll(void) const;
		CDimension2D getDimension(void);
	};

	/// \brief Vulkan class for resource of type texture 2D created from a CImage
	///
	///
	class CResourceTexture2DFromCImageVulkan : public CResourceTexture2DFromCImageBase
	{
	public:
		CResourceTexture2DFromCImageVulkan();

		void upload(void);
		void free(void);
		void bind(unsigned int uiTextureUnit = 0) const;
		void unbind(unsigned int uiTextureUnit = 0) const;
		void unbindAll(void) const;
		CDimension2D getDimension(void);
	};


}	// namespace DCL

#endif	// #ifndef FILENAME_H

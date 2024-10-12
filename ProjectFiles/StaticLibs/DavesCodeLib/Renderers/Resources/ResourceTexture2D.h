#ifndef RESOURCE_TEXTURE2D_H
#define RESOURCE_TEXTURE2D_H

#include "../../Image/Image.h"
#include "../../Core/Dimensions.h"
//#include <string>

namespace DCL
{
	/// \brief Base class for resource of type texture 2D created from a CImage object
	///
	/// \todo Add filtering methods.
	/// 
	/// We derive resource classes from this base class for each renderer type such as OpenGL and Vulkan.
	/// These classes are to be declared within this header file to reduce the number of files.
	/// Eww! I know right? Three class declarations insided a single header file, the madness!
	/// I know it's a little messy, but the alternative is to have six files for each resource type and as there are quite a few resources, this would've meant many files and that's even more messy.
	/// I know it means that the various renderers for the different graphics APIs are including stuff which isn't related to them, but that's a small price to pay for the reduced number of files we'd otherwise have to create.
	/// Within DCL, all code uses only a pointer to the base class and the implementation for each of the methods are implemented inside the derived classes and are insulated via private implementations.
	/// Each of the API's CRenderer classes which are derived from the CRendererBase class, are responsible for creating, accessing and freeing this resource type.
	/// Usage:
	/// \code
	/// CRendererBase* pRenderer = CRendererManager::get();	// Obtain pointer to a renderer
	/// CResoureTexture2DBase *pTexture = pRenderer->addTexture2D("MyTexture", 1);	// Add a new empty texture named "MyTexture" in group 1
	/// CImage imageData;	// An image object to load in the image data from a file
	/// imageData.load("myTexture.png");	// Load the image data into the CImage object from a file
	/// pTexture->setImageData(imageData);	// Set the new empty texture to use the image data stored in the CImage object. 
	/// // The imageData object is no longer required as setImageData copies it's contents into the texture object.
	/// pTexutre->upload();	// Upload the texture to the GPU memory, ready for use.
	/// // Insert rendering code here and just before rendering, bind the texture to a texture unit...
	/// pTexture->bind(0);	// Bind the texture to texture unit 0
	/// \endcode
	class CResourceTexture2DBase
	{
	public:
		/// \brief Copies the image data from the given CImage object into this object.
		/// 
		/// \param imageDataSource A CImage object which contains existing image data to be used by this object.
		/// 
		/// Once this method is called, the CImage object is no longer required and can be freed.
		/// If the given CImage object doesn't have any image data, an exception occurs.
		/// This does NOT upload the image data to the GPU.
		void setImageData(const CImage& imageDataSource);

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

		CImage imageData;		///< CImage object which holds the image data this object uses. We can access this object to get the image/texture dimensions.
	};

	/// \brief OpenGL class for resource of type texture 2D created from a CImage object
	///
	///
	class CResourceTexture2DOpenGL : public CResourceTexture2DBase
	{
	public:
		CResourceTexture2DOpenGL();
		~CResourceTexture2DOpenGL();

		void upload(void);
		void free(void);
		void bind(unsigned int uiTextureUnit = 0) const;
		void unbind(unsigned int uiTextureUnit = 0) const;
		void unbindAll(void) const;
	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};

	/// \brief Vulkan class for resource of type texture 2D created from a CImage
	///
	///
	class CResourceTexture2DVulkan : public CResourceTexture2DBase
	{
	public:
		CResourceTexture2DVulkan();
		~CResourceTexture2DVulkan();

		void upload(void);
		void free(void);
		void bind(unsigned int uiTextureUnit = 0) const;
		void unbind(unsigned int uiTextureUnit = 0) const;
		void unbindAll(void) const;
	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};


}	// namespace DCL

#endif	// #ifndef FILENAME_H

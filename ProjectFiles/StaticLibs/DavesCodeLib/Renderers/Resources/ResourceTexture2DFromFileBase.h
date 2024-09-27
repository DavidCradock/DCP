#ifndef RESOURCE_TEXTURE2D_FROM_FILE_BASE_H
#define RESOURCE_TEXTURE2D_FROM_FILE_BASE_H

#include "../../Core/Dimensions.h"
#include <string>

namespace DCL
{
	/// \brief Base class for resource of type texture 2D created from a file.
	///
	/// We derive resource classes from this base class for each renderer type such as OpenGL and Vulkan.
	/// These classes are to be located within the Resources sub folder of the Renderers folder.
	/// Within DCL, all code uses only a pointer to the base class and the implementation for each of the methods are implemented inside the derived classes and are insulated via private implementations.
	/// Each of the API's CRenderer classes which are derived from the CRendererBase class, are responsible for creating, accessing and freeing this resource type.
	class CResourceTexture2DFromFileBase
	{
	public:
		/// \brief Sets the filename of a file holding the image data used by this texture.
		/// 
		/// \param strImageFilename The filename of the file holding the image data this texture will use.
		/// 
		virtual void setImageFilename(const std::string& strImageFilename) = 0;

		/// \brief Initialises the resource so that the resource is ready for use
		///
		/// This is called to upload the resource to the GPU
		virtual void initialise(void) = 0;

		/// \brief Frees the resource
		///
		/// This is called when the graphics API's device context is lost (For example, when the window is destroyed)
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
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H

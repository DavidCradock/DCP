#ifndef RESOURCE_FRAMEBUFFER_H
#define RESOURCE_FRAMEBUFFER_H

#include "../../Image/Image.h"
#include "../../Core/Dimensions.h"
//#include <string>

namespace DCL
{
	/// \brief Base class for resource of type framebuffer
	///
	/// We derive resource classes from this base class for each renderer type such as OpenGL and Vulkan.
	/// These classes are to be declared within this header file to reduce the number of files.
	/// Eww! I know right? Three class declarations insided a single header file, the madness!
	/// I know it's a little messy, but the alternative is to have six files for each resource type and as there are quite a few resources, this would've meant many files and that's even more messy.
	/// I know it means that the various renderers for the different graphics APIs are including stuff which isn't related to them, but that's a small price to pay for the reduced number of files we'd otherwise have to create.
	/// Within DCL, all code uses only a pointer to the base class and the implementation for each of the methods are implemented inside the derived classes and are insulated via private implementations.
	/// Each of the API's CRenderer classes which are derived from the CRendererBase class, are responsible for creating, accessing and freeing this resource type.
	/// By default, the framebuffer's dimensions are set to 32x32. Call resize() to change this.
	class CResourceFramebufferBase
	{
	public:
		
		/// \brief Uploads into GPU memory, ready for use.
		virtual void upload(void) = 0;

		/// \brief Frees the framebuffer from the GPU memory.
		virtual void free(void) = 0;

		/// \brief Bind this framebuffer object so that all render operations use this as the target.
		///
		/// \param bClearbuffer Whether to clear the framebuffer or not
		/// \param backgroundClearColour If bClearbuffer is true, this is the colour used to clear it with.
		/// 
		/// Also clears the render target by default and sets viewport to match render target
		virtual void bindAsRenderTarget(bool bClearbuffer = true, const CColourf& backgroundClearColour = CColourf(0.0f, 0.0f, 0.0f, 0.0f)) = 0;

		/// \brief Unbind the framebuffer object so that all render operations use the window's backbuffer as the target.
		/// 
		/// Don't forget as now the backbuffer is set as the render target, we'll need (for OpenGL) to call glViewport(0, 0, Width, Height) to reset the viewport to the window dimensions.
		virtual void unbindAsRenderTarget(void) const = 0;

		/// \brief Bind this framebuffer's attached colour texture to a texture unit, to be used as a normal 2D texture.
		///
		/// \param uiTextureUnit The texture unit number to bind to. Should be between 0-7
		virtual void bindAsTexture(unsigned int uiTextureUnit) const = 0;

		/// \brief Unbinds texturing for the specified texture unit
		///
		/// \param uiTextureUnit Should be between 0-7
		virtual void unbindTexture(unsigned int uiTextureUnit = 0) const = 0;

		/// \brief Returns width of the frame buffer
		///
		/// \return The width of the frame buffer.
		virtual unsigned int getWidth(void) const = 0;

		/// \brief Returns height of the frame buffer
		///
		/// \return The height of the frame buffer.
		virtual unsigned int getHeight(void) const = 0;

		/// \brief Returns dimensions of the frame buffer
		///
		/// \return The dimensions of the framebuffer
		virtual CDimension2D getDimensions(void) const = 0;

		/// \brief Sets frame buffer to new dimensions
		/// 
		/// \param uiNewWidth The new width of the framebuffer
		/// \param uiNewHeight The new height of the framebuffer
		/// 
		/// If the new dimensions are the same as the current ones, this simply returns
		virtual void resize(unsigned int uiNewWidth, unsigned int uiNewHeight) = 0;

		/// \brief Sets frame buffer to new dimensions
		/// 
		/// \param newDimensions The new dimensions of the framebuffer
		/// 
		/// If the new dimensions are the same as the current ones, this simply returns
		virtual void resize(CDimension2D& newDimensions) = 0;

	};

	/// \brief OpenGL class for resource of type framebuffer
	///
	///
	class CResourceFramebufferOpenGL : public CResourceFramebufferBase
	{
	public:
		CResourceFramebufferOpenGL();
		~CResourceFramebufferOpenGL();

		void upload(void);
		void free(void);

		void bindAsRenderTarget(bool bClearbuffer = true, const CColourf& backgroundClearColour = CColourf(0.0f, 0.0f, 0.0f, 0.0f));
		void unbindAsRenderTarget(void) const;
		void bindAsTexture(unsigned int uiTextureUnit) const;
		void unbindTexture(unsigned int uiTextureUnit = 0) const;
		unsigned int getWidth(void) const;
		unsigned int getHeight(void) const;
		CDimension2D getDimensions(void) const;
		void resize(unsigned int uiNewWidth, unsigned int uiNewHeight);
		void resize(CDimension2D& newDimensions);

	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};

	/// \brief Vulkan class for resource of type framebuffer
	///
	///
	class CResourceFramebufferVulkan : public CResourceFramebufferBase
	{
	public:
		CResourceFramebufferVulkan();
		~CResourceFramebufferVulkan();

		void upload(void);
		void free(void);

		void bindAsRenderTarget(bool bClearbuffer = true, const CColourf& backgroundClearColour = CColourf(0.0f, 0.0f, 0.0f, 0.0f));
		void unbindAsRenderTarget(void) const;
		void bindAsTexture(unsigned int uiTextureUnit) const;
		void unbindTexture(unsigned int uiTextureUnit = 0) const;
		unsigned int getWidth(void) const;
		unsigned int getHeight(void) const;
		CDimension2D getDimensions(void) const;
		void resize(unsigned int uiNewWidth, unsigned int uiNewHeight);
		void resize(CDimension2D& newDimensions);
	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};


}	// namespace DCL

#endif	// #ifndef FILENAME_H

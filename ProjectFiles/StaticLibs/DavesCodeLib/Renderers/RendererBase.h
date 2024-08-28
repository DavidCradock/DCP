/// \file RendererBase.h
/// \brief Brief description for the file goes here.
///
/// Detailed description text goes here.

#ifndef RENDERER_H
#define RENDERER_H

#include <string>

namespace DCL
{
	/// \brief Base class for the various renderers
	///
	/// Base class which declares which methods need to be in a renderer class.
	/// No implementation here.
	/// Every method in here is pure virtual (The virtual keyword and the "= 0" at the end)
	/// All the various rendering classes (such as the user interface class for example) use the methods declared here to render stuff in a generic way.
	/// This allows us, to write all the rendering code in an API independent way, so if we wish to use a different API, we don't have to re-write all the rendering code.
	/// We implement multiple renderer classes which are based upon this class, then create a pointer to one of those classes and store that
	/// in a CRenderer pointer depending upon which renderer we wish to use (OpenGL, Vulkan, maybe software (at a later date)).
	/// The only disadvantage I can think of is more work.
	/// The advantages are plentiful! Being able to switch APIs is fun and good for a few reasons...
	/// If some end user piece of software is buggy and crashing when using the Vulkan API, I can just say "Try the more stable OpenGL renderer" as I'm a little uncertain what I'm doing
	/// with Vulkan and it gives me a nice user support feature :)
	/// It'll also be fun to compare performance between the different APIs.
	/// 
	/// We use Cheshire cat/pimpl for the derived renderer classes as we do not wish to expose/make the APIs visible to any code, otherwise we might be tempted to call the APIs and that'd make a huge mess!
	/// So all objects needed by the renderer classes go inside the private implementation instead of their header files.
	class CRendererBase
	{
	public:
		/// \brief Initialise a window with the graphics API all hooked up and ready to go
		virtual void initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen) = 0;

		/// \brief Shutdown and close the API and window
		virtual void shutdown(void) = 0;
	
		/// \brief 
		//virtual void beginFrame() = 0;
		//virtual void endFrame() = 0;
		//virtual void clear(const float r, const float g, const float b, const float a) = 0;

		// Primitive drawing
		//virtual void drawTriangles(const void* vertexData, size_t vertexCount, const void* indexData, size_t indexCount) = 0;
		//virtual void drawLines(const void* vertexData, size_t vertexCount) = 0;
		//virtual void drawPoints(const void* vertexData, size_t vertexCount) = 0;

		// Texture management
		//virtual Texture* createTexture(const void* data, int width, int height, TextureFormat format) = 0;
		//virtual void destroyTexture(Texture* texture) = 0;
		// Generate mipmaps : Generate mipmap levels for textures.
		// Set texture parameters : Set texture wrapping, filtering, and anisotropy.
		// Bind texture : Bind textures to texture units.

		// Shader management
		//virtual Shader* createShader(const char* vertexShaderSource, const char* fragmentShaderSource) = 0;
		//virtual void destroyShader(Shader* shader) = 0;

		// Material management (optional)
		//virtual Material* createMaterial(Shader* shader) = 0;
		//virtual void setMaterial(Material* material) = 0;
		//virtual void destroyMaterial(Material* material) = 0;

		// Other potential methods:
	// - Set viewport dimensions and position




		/// \brief Disable blending
		virtual void blendDisable(void) = 0;

		/// \brief Enable blending
		virtual void blendEnable(void) = 0;

		/// \brief Set blending mode to SourceAlpha, One
		virtual void blendFunction_SrcAlpha_One(void) = 0;

		/// \brief Set blending mode to SourceAlpha, OneMinusSrcAlpha
		virtual void blendFunction_SrcAlpha_OneMinusSrcAlpha(void) = 0;

		/// \brief Set culling of anti clockwise faces.
		virtual void cullFaceAntiClockwise(void) = 0;

		/// \brief Set culling of clockwise faces.
		virtual void cullFaceClockwise(void) = 0;

		/// \brief Disable culling of faces
		virtual void cullFaceDisable(void) = 0;

		/// \brief Enable culling of faces
		virtual void cullFaceEnable(void) = 0;

		/// \brief Disable depth testing
		virtual void depthTestDisable(void) = 0;

		/// \brief Enable depth testing
		virtual void depthTestEnable(void) = 0;

		/// \brief Read pixels from the currently set "back buffer"
		virtual void pixelsRead(int iPositionX, int iPositionY, int iWidth, int iHeight, void* pixels) = 0;

		/// \brief Write pixels from the currently set "back buffer"
		virtual void pixelsWrite(int iPositionX, int iPositionY, int iWidth, int iHeight, void* pixels) = 0;

		/// \brief Set parameters for scissor test
		virtual void scissorTest(int iPositionX, int iPositionY, int iWidth, int iHeight) = 0;

		/// \brief Disable scissor testing
		virtual void scissorTestDisable(void) = 0;

		/// \brief Enable scissor testing
		virtual void scissorTestEnable(void) = 0;


	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
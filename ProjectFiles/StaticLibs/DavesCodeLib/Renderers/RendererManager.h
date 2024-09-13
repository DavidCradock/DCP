/// \file RendererManager.h
/// \brief Brief description for the file goes here.
///
/// Detailed description text goes here.

#ifndef RENDERERMANAGER_H
#define RENDERERMANAGER_H

#include "rendererOpenGL.h"
#include "rendererVulkan.h"

namespace DCL
{
	/// \brief Renderer manager class for creating and holding a renderer
	class CRendererManager
	{
	public:
		CRendererManager();
		~CRendererManager();

		/// \brief Initialises the renderer by creating a window and hooking up the correct graphics API such as OpenGL or Vulkan, ready for use.
		///
		/// \param strRendererName The name of the renderer we wish to use. Can be OpenGL, Vulkan and maybe more in the future.
		///	The given string can be uppercase, lowercase or a mixture, as long as it is either opengl or vulkan
		/// If the given string holding the renderer name is not recognised, an exception occurs.
		/// 
		/// \return A pointer to a CRendererBase object which we use to perform all the rendering operations.
		/// 
		/// If the renderer is already initialised, an exception occurs
		CRendererBase* init(const std::string& strRendererName = "OpenGL");

		/// \brief Returns a pointer the a CRendererBase object if a call to the init method has previously been called.
		///
		/// \return A pointer to a CRendererBase object which we use to perform all the rendering operations if it has been initialised,
		///		otherwise, an exception will occur. A call to either initOpenGL() or initVulkan() or any of the other init methods will fix this exception from occurring.
		CRendererBase* get(void);
	private:
		CRendererBase* _mpRenderer;	///< A pointer holding the initialised renderer
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
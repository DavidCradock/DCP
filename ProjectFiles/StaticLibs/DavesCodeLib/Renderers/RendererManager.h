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

		/// \brief Initialises the renderer by creating a window and hooking up the OpenGL API ready for use.
		///
		/// \return A pointer to a CRendererBase object which we use to perform all the rendering operations.
		CRendererBase* initOpenGL(void);

		/// \brief Initialises the renderer by creating a window and hooking up the Vulkan API ready for use.
		///
		/// \return A pointer to a CRendererBase object which we use to perform all the rendering operations.
		CRendererBase* initVulkan(void);

		/// \brief Returns a pointer the a CRendererBase object if a call to one of the initAPINAME methods have previously been called.
		///
		/// \return A pointer to a CRendererBase object which we use to perform all the rendering operations if it has been initialised,
		///		otherwise, an exception will occur. A call to either initOpenGL() or initVulkan() or any of the other init methods will fix this exception from occurring.
		CRendererBase* get(void);
	private:
		CRendererBase* _mpRenderer;	///< A pointer holding the initialised renderer
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
#ifndef RENDERER_H
#define RENDERER_H

// Resources
#include "Resources/ResourceFramebuffer.h"
#include "Resources/ResourceGPUPrograms.h"
#include "Resources/ResourceTexture2D.h"
#include "Resources/ResourceVertexBuffer.h"

#include "../Core/Colourf.h"
#include <map>

namespace DCL
{
	/// \brief Base class for the various renderers
	///
	/// Base class which declares which methods need to be in a renderer class for each graphics API.
	/// No implementation here.
	/// Every method in here is pure virtual (The virtual keyword and the "= 0" at the end)
	/// All the various rendering classes (such as the user interface class for example) use the methods declared here to render stuff in a generic way.
	/// This allows us to write all the rendering code in an API independent way, so if we wish to use a different API, we don't have to re-write all the code which uses a renderer.
	/// We implement multiple renderer classes which are based upon this class, then create a pointer to one of those classes and store that
	/// in a CRendererBase pointer depending upon which renderer we wish to use (OpenGL, Vulkan, maybe software (at a later date)).
	/// The only disadvantage I can think of is more work.
	/// The advantages are plentiful! Being able to switch APIs is fun and good for a few reasons...
	/// If some end user piece of software is buggy and crashing when using the Vulkan API, I can just say "Try the more stable OpenGL renderer" as I'm a little uncertain what I'm doing
	/// with Vulkan and it gives me a nice user support feature :)
	/// It'll also be fun to compare performance between the different APIs.
	/// 
	/// We use Pimpl for the derived renderer classes as we do not wish to expose/make the APIs visible to any code, otherwise we might be tempted to call the APIs and that'd make a huge mess!
	/// So all objects needed by the renderer classes go inside the private implementation instead of their header files.
	/// 
	/// Although a renderer, regardless of API can render to a buffer without a window, we do not include such functionality here.
	/// Meaning, a window is required. This class is responsible for creating/checking messages/closing this window.
	/// 
	/// The derived classes have sets of methods which are responsible for creating/freeing/accessing various resources such as textures, vertex buffers/programs, etc.
	/// These methods, for each resource type are...
	/// addResourceType()			// Adds a new resource. Allocates an object of the derived class into a pointer of the base class for the resource type.
	/// getResourceType()			// Returns a pointer to the base class of the resource type
	/// getResourceTypeExists()		// Returns true if the named resource already exists in the numbered resource group
	/// removeResourceType()		// Removes, or reduces the reference count of the named resource.
	/// removeResourceTypeAll()		// Removes all resources in a group.
	/// 
	/// Each resource should have a unique name and they are held within a speccified resource group number.
	/// These resource group numbers are used so we can seperate resources into groups and allow more flexibility when calling the removeAllResourceType() method, for example.
	/// There are 8 resource groups, so valid group numbers are from 0 to 7.
	/// Group 0 is supposed to be reserved for resources which are used within DCL such as default textures, vertex/fragment programs etc.
	/// I say "supposed" as there's nothing preventing us from messing around with group 0.
	/// All methods accept a group number, which defaults to group 1.
	/// I decided to use group numbers instead of names for performance reasons. (Faster access to an array via index rather than using a hashmap lookup for a named group)
	///
	/// Each renderer derived from this base class, upon initialisation create some default GPU program pairs (vertex and fragment programs) which are stored as text inside the executable.
	/// These GPU programs are stored inside GPUProgramStrings.h/.cpp as strings.
	/// There is a function which needs calling to setup these strings called initGPUProgramStrings()
	/// Once the renderer is initialised, the programs are uploaded and ready for use.
	/// They are used throughout DCL for common, standard rendering.
	/// They are meant to be paired with ResourceVertexBuffer data types which are set with CResourceVertexBufferBase::setDataType()
	/// Regardless of renderer, they are named the same so that they can be accessed and used regardless of which renderer is being used.
	/// They simply match the available data types available in the vertex buffer resource.
	class CRendererBase
	{
	public:
		/// \brief Initialise a window with the graphics API all hooked up and ready to go
		virtual void initialise(unsigned int iWindowWidth = 320, unsigned int iWindowHeight = 240, const std::string& strWindowTitle = "DCP Dev App", bool bFullscreen = false, bool bVSyncEnabled = true, CColourf clearColour = CColourf(0.2f, 0.2f, 0.4f, 1.0f)) = 0;

		/// \brief Shutdown and close the API and window
		virtual void shutdown(void) = 0;
	
		/// \brief Should be called regularly, IE, each program loop to check any messages sent to the rendering window.
		/// 
		/// \param bWindowResized Will be true if the window has been resized
		/// The framebuffer should be resized within this method.
		/// 
		/// \param bWindowMinimized Will be true if the window has been minimized
		/// \param bWindowHasBeenAskedToClose Will be true if the window/application has been asked to be closed by the OS.
		/// We should check this value and end program execution if true
		/// 
		/// Windows created by the operating system have messages sent to them when certain events happen to the window.
		/// For example, when the window is minimized, resized, the close button has been pressed or the application has been asked to be closed.
		/// Within this method, we check for these messages and handle resizing(resize the framebuffer), minimizing (Maybe pause the app?) and closing
		virtual void updateWindow(bool& bWindowResized, bool& bWindowMinimized, bool& bWindowHasBeenAskedToClose) = 0;
		
		/// \brief Begin frame, clearing back buffer, ready for rendering
		virtual void beginFrame(void) = 0;
		 
		/// \brief End frame, flip back buffer to front
		virtual void endFrame(void) = 0;
	
		/// \brief Set the colour which the back buffer of the window is cleared to during the call to beginFrame()
		virtual void setBackbufferClearColour(float fRed, float fGreen, float fBlue, float fAlpha) = 0;

		/// \brief Toggles vertical syncronisation of flipping of the back buffer to the windows' front with the display device's refresh rate
		///
		/// Should be called after the window has been created, otherwise nothing will happen.
		/// 
		/// \param bVSyncOn Whether vsync should be on or off.
		virtual void setVSync(bool bVSyncOn) = 0;

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

		/// \brief Adds a new ResourceGPUPrograms object to be managed.
		///
		/// \param strResourceName The name of the new resource which we can use to refer to it with other methods.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the named resource already exists, it has a count value which is incremented and the pointer to the existing resource is returned.
		virtual CResourceGPUProgramsBase* addGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Returns a pointer to an existing resource
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the resource couldn't be found, an exception is thrown.
		virtual CResourceGPUProgramsBase* getGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Returns whether a named resource exists
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		virtual bool getGPUProgramsExists(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Removes a previously added resource from this manager
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the resource doesn't exist, this silently fails.
		/// If the resource has been added multiple times and it's count value is greater than 1, the value is reduced, but the resource remains.
		virtual void removeGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Removes all previously added resources from the given numbered group
		///
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		virtual void removeGPUProgramsAll(unsigned int uiGroupNumber = 1) = 0;

		/// \brief Adds a new ResourceTexture2D object to be managed.
		///
		/// \param strResourceName The name of the new resource which we can use to refer to it with other methods.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the named resource already exists, it has a count value which is incremented and the pointer to the existing resource is returned.
		virtual CResourceTexture2DBase* addTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Returns a pointer to an existing resource
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the resource couldn't be found, an exception is thrown.
		virtual CResourceTexture2DBase* getTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Returns whether a named resource exists
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		virtual bool getTexture2DExists(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Removes a previously added resource from this manager
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the resource doesn't exist, this silently fails.
		/// If the resource has been added multiple times and it's count value is greater than 1, the value is reduced, but the resource remains.
		virtual void removeTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Removes all previously added resources from the given numbered group
		///
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		virtual void removeTexture2DAll(unsigned int uiGroupNumber = 1) = 0;

		/// \brief Adds a new ResourceFramebuffer object to be managed.
		///
		/// \param strResourceName The name of the new resource which we can use to refer to it with other methods.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the named resource already exists, it has a count value which is incremented and the pointer to the existing resource is returned.
		virtual CResourceFramebufferBase* addFramebuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Returns a pointer to an existing resource
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the resource couldn't be found, an exception is thrown.
		virtual CResourceFramebufferBase* getFramebuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Returns whether a named resource exists
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		virtual bool getFramebufferExists(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Removes a previously added resource from this manager
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the resource doesn't exist, this silently fails.
		/// If the resource has been added multiple times and it's count value is greater than 1, the value is reduced, but the resource remains.
		virtual void removeFramebuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Removes all previously added resources from the given numbered group
		///
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		virtual void removeFramebufferAll(unsigned int uiGroupNumber = 1) = 0;

		/// \brief Adds a new ResourceVertexBuffer object to be managed.
		///
		/// \param strResourceName The name of the new resource which we can use to refer to it with other methods.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the named resource already exists, it has a count value which is incremented and the pointer to the existing resource is returned.
		virtual CResourceVertexBufferBase* addVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Returns a pointer to an existing resource
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the resource couldn't be found, an exception is thrown.
		virtual CResourceVertexBufferBase* getVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Returns whether a named resource exists
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		virtual bool getVertexBufferExists(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Removes a previously added resource from this manager
		///
		/// \param strResourceName The name of the resource.
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		/// 
		/// If the resource doesn't exist, this silently fails.
		/// If the resource has been added multiple times and it's count value is greater than 1, the value is reduced, but the resource remains.
		virtual void removeVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1) = 0;

		/// \brief Removes all previously added resources from the given numbered group
		///
		/// \param uiGroupNumber The resource group number which this resource is stored in. Can range from 0 to 7. Resource group 0 is reserved for resources used by DCL.
		virtual void removeVertexBufferAll(unsigned int uiGroupNumber = 1) = 0;

		// Primitive drawing
		//virtual void drawTriangles(const void* vertexData, size_t vertexCount, const void* indexData, size_t indexCount) = 0;
		//virtual void drawLines(const void* vertexData, size_t vertexCount) = 0;
		//virtual void drawPoints(const void* vertexData, size_t vertexCount) = 0;

		// Shader management
		//virtual Shader* createShader(const char* vertexShaderSource, const char* fragmentShaderSource) = 0;
		//virtual void destroyShader(Shader* shader) = 0;

		// Material management (optional)
		//virtual Material* createMaterial(Shader* shader) = 0;
		//virtual void setMaterial(Material* material) = 0;
		//virtual void destroyMaterial(Material* material) = 0;

		// Other potential methods:
	// - Set viewport dimensions and position
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
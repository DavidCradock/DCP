#ifndef RESOURCE_VERTEXBUFFER_H
#define RESOURCE_VERTEXBUFFER_H

namespace DCL
{
	/// \brief Base class for resource of type vertex buffer
	///
	/// We derive resource classes from this base class for each renderer type such as OpenGL and Vulkan.
	/// These classes are to be declared within this header file to reduce the number of files.
	/// Eww! I know right? Three class declarations insided a single header file, the madness!
	/// I know it's a little messy, but the alternative is to have six files for each resource type and as there are quite a few resources, this would've meant many files and that's even more messy.
	/// I know it means that the various renderers for the different graphics APIs are including stuff which isn't related to them, but that's a small price to pay for the reduced number of files we'd otherwise have to create.
	/// Within DCL, all code uses only a pointer to the base class and the implementation for each of the methods are implemented inside the derived classes and are insulated via private implementations.
	/// Each of the API's CRenderer classes which are derived from the CRendererBase class, are responsible for creating, accessing and freeing this resource type.
	class CResourceVertexBufferBase
	{
	public:
		/// \brief Uploads the vertex buffer data stored into GPU memory, ready for use.
		///
		virtual void upload(void) = 0;

		/// \brief Frees the data from the GPU memory.
		virtual void free(void) = 0;
	};

	/// \brief OpenGL class for resource of type vertex buffer
	///
	///
	class CResourceVertexBufferOpenGL : public CResourceVertexBufferBase
	{
	public:
		CResourceVertexBufferOpenGL();
		~CResourceVertexBufferOpenGL();

		void upload(void);
		void free(void);
	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};

	/// \brief Vulkan class for resource of type texture 2D created from a CImage
	///
	///
	class CResourceVertexBufferVulkan : public CResourceVertexBufferBase
	{
	public:
		CResourceVertexBufferVulkan();
		~CResourceVertexBufferVulkan();

		void upload(void);
		void free(void);
	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
		///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};


}	// namespace DCL

#endif	// #ifndef FILENAME_H

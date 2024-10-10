#ifndef RESOURCE_VERTEXBUFFER_H
#define RESOURCE_VERTEXBUFFER_H

#include "../../Core/Colourf.h"
#include "../../Math/Vector2f.h"
#include "../../Math/Vector3f.h"
#include <string>
#include <vector>

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
	/// A vertex buffer can consist of different types of data such as a vertex's position, colour, normals, texture coordinates as well as binormals and tangents.
	/// The type is set in eVertexBufferType using the CResourceVertexBufferBase::EVertexBufferDataType enumeration.
	/// By default, this is set to the CResourceVertexBufferBase::EVertexBufferDataType::POS type.
	/// Vertex data is stored in system memory and that data is used to upload/create the buffer on the GPU
	/// Before adding vertex data to the vertex buffer, we should set the desired type with a call to setDataType().
	/// This will remove all vertex data from memory as well as the GPU.
	/// When adding vertex data to this object with the various add??() methods, this data is added into system memory and it is that data which is copied to the GPU once upload() is called.
	/// Usage example:
	/// \code
	/// CRenderManager rm;
	/// CRendererBase *pRenderer = rm->init("OpenGL");	// Get a pointer to a renderer, of type OpenGL (Can be Vulkan and maybe others, see CRenderManager)
	/// 
	/// // Create a new empty vertex buffer.
	/// CResourceVertexBufferBase* vb = pRenderer->addVertexBuffer("MyFirstVertexBuffer");
	/// 
	/// // Set the type of the vertex buffer. Can be any of the EVertexBufferDataType enumerations.
	/// vb->setDataType(CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL);
	/// 
	/// // Add three vertices to represent a triangle...
	/// vb->addVertex(
	///		CVector3f(-1.0f, -1.0f, 0.0f),		// Position
	///		CColourf(1.0f, 0.0f, 0.0f, 0.5f),	// Colour
	///		CVector3f(0.0f, 0.0f, 1.0f),		// Normal
	///		CVector2f(0.0f, 0.0f));				// Texture coordinate
	/// // Pretend we have done this for the other two vertices
	/// // Please note, that as the vertex buffer data type is set to have tangent and binormals which are used for various things by shaders such as bump mapping,
	/// // we don't add these ourselves. Instead we add all the vertex data as shown above and then call a method to compute these for us with a call to...
	/// vb->computeTangentsAndBinormals();
	/// 
	/// // Now that the unique vertex data has been added, we add three vertex indicies.
	/// vb->addIndex(0); // The first vertex to be rendered, points to the first vertex data.
	/// vb->addIndex(1); // The second vertex to be rendered, points to the second vertex data.
	/// vb->addIndex(2); // The third vertex to be rendered, points to the third vertex data.
	/// 
	/// // Finally, upload the vertex buffer data and indicies to the GPU, ready to be sent and rendered...
	/// vb->uploadGPU();
	/// 
	/// // Now somewhere in our rendering loop, after binding textures, GPU programs and setting uniforms (Such as matricies) for those programs, send the vertex data to be rendered with...
	/// vb->render();
	/// \endcode
	class CResourceVertexBufferBase
	{
	public:
		CResourceVertexBufferBase();

		/// \brief Uploads the vertex buffer data stored into GPU memory, ready for use.
		///
		virtual void uploadGPU(void) = 0;

		/// \brief Frees the data from the GPU memory.
		virtual void freeGPU(void) = 0;

		/// \brief Vertex buffer data types that it holds.
		///
		/// Default type for a vertex buffer should be POS
		enum EVertexBufferDataType
		{
			POS,										///< Holds vertex position
			POS_COL,									///< Holds vertex position and colour
			POS_COL_TEXCOORD,							///< Holds vertex position, colour and texture coordinates
			POS_COL_NORMAL_TEXCOORD,					///< Holds vertex position, colour, normal and texture coordinates
			POS_COL_NORMAL_TEXCOORDx2,					///< Holds vertex position, colour, normal and two sets of texture coordinates
			POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL	///< Holds vertex position, colour, normal, texture coordinates, tangent and binormal vectors.
		};
		EVertexBufferDataType eVertexBufferType;	///< Which data types the vertex buffer holds.

		/// \brief A single vertex's data for the EVertexBufferDataType of POS
		struct Vertex_POS
		{
			CVector3f position;		///< Vertex position
		};

		/// \brief A single vertex's data for the EVertexBufferDataType of POS_COL
		struct Vertex_POS_COL
		{
			CVector3f position;		///< Vertex position
			CColourf colour;		///< Vertex colour
		};

		/// \brief A single vertex's data for the EVertexBufferDataType of POS_COL_TEXCOORD
		struct Vertex_POS_COL_TEXCOORD
		{
			CVector3f position;		///< Vertex position
			CColourf colour;		///< Vertex colour
			CVector2f texCoord;		///< Vertex texture coordinate
		};

		/// \brief A single vertex's data for the EVertexBufferDataType of POS_COL_NORMAL_TEXCOORD
		struct Vertex_POS_COL_NORMAL_TEXCOORD
		{
			CVector3f position;		///< Vertex position
			CColourf colour;		///< Vertex colour
			CVector3f normal;		///< Vertex normal
			CVector2f texCoord;		///< Vertex texture coordinate
		};

		/// \brief A single vertex's data for the EVertexBufferDataType of POS_COL_NORMAL_TEXCOORDx2
		struct Vertex_POS_COL_NORMAL_TEXCOORDx2
		{
			CVector3f position;		///< Vertex position
			CColourf colour;		///< Vertex colour
			CVector3f normal;		///< Vertex normal
			CVector2f texCoord0;	///< Vertex texture coordinate 0
			CVector2f texCoord1;	///< Vertex texture coordinate 1
		};

		/// \brief A single vertex's data for the EVertexBufferDataType of POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL
		struct Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL
		{
			CVector3f position;		///< Vertex position
			CColourf colour;		///< Vertex colour
			CVector2f texCoord;		///< Vertex texture coordinate
			CVector3f normal;		///< Vertex normal
			CVector3f tangent;		///< Tangent vector for bump/normal mapping
			CVector3f binormal;		///< Binormal vector for bump/normal mapping
		};
		
		/// \brief Sets the data types that this vertex buffer will hold/use.
		/// 
		/// Should be of enumeration CResourceVertexBufferBase::EVertexBufferDataType
		/// 
		/// This will both, remove all vertex data from memory as well as the GPU.
		void setDataType(CResourceVertexBufferBase::EVertexBufferDataType vertexBufferDataType = CResourceVertexBufferBase::EVertexBufferDataType::POS);

		std::vector<Vertex_POS> _mvecVertexData_POS;																			///< Vector holding each unique vertex's data for a specific vertex buffer data type
		std::vector<Vertex_POS_COL> _mvecVertexData_POS_COL;																	///< Vector holding each unique vertex's data for a specific vertex buffer data type
		std::vector<Vertex_POS_COL_TEXCOORD> _mvecVertexData_POS_COL_TEXCOORD;													///< Vector holding each unique vertex's data for a specific vertex buffer data type
		std::vector<Vertex_POS_COL_NORMAL_TEXCOORD> _mvecVertexData_POS_COL_NORMAL_TEXCOORD;									///< Vector holding each unique vertex's data for a specific vertex buffer data type
		std::vector<Vertex_POS_COL_NORMAL_TEXCOORDx2> _mvecVertexData_POS_COL_NORMAL_TEXCOORDx2;								///< Vector holding each unique vertex's data for a specific vertex buffer data type
		std::vector<Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL> _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL;	///< Vector holding each unique vertex's data for a specific vertex buffer data type

		std::vector<int> _mvecIndices;			///< Vector holding indicies to each unique vertex

		/// \brief Compute tangents and binormals from currently added geometry.
		///
		/// This only works if the data type of this vertex buffer is set to Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL, otherwise an exception occurs.
		/// If no data exists, an exception occurs.
		void computeTangentsAndBinormals(void);

		/// \brief Adds a new unique vertex's data to system memory
		///
		/// Used when the vertex data type is set to CResourceVertexBufferBase::EVertexBufferDataType::POS
		/// If the vertex buffer type is not set to CResourceVertexBufferBase::EVertexBufferDataType::POS, an exception occurs
		void addVertex(const CVector3f& position);

		/// \brief Adds a new unique vertex's data to system memory
		///
		/// Used when the vertex data type is set to CResourceVertexBufferBase::EVertexBufferDataType::POS_COL
		/// If the vertex buffer type is not set to CResourceVertexBufferBase::EVertexBufferDataType::POS_COL, an exception occurs
		void addVertex(const CVector3f& position, const CColourf& colour);

		/// \brief Adds a new unique vertex's data to system memory
		///
		/// Used when the vertex data type is set to CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_TEXCOORD or POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL
		/// If the vertex buffer type is not set to CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_TEXCOORD or POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL, an exception occurs
		/// After adding all the position, colour and texture coordinate data and the data type is set to POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL, we should call computeTangentsAndBinormals() to compute them.
		void addVertex(const CVector3f& position, const CColourf& colour, CVector2f& texcoord);

		/// \brief Adds a new unique vertex's data to system memory
		///
		/// Used when the vertex data type is set to CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD
		/// If the vertex buffer type is not set to CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD, an exception occurs
		void addVertex(const CVector3f& position, const CColourf& colour, const CVector3f& normal, CVector2f& texcoord);

		/// \brief Adds a new unique vertex's data to system memory
		///
		/// Used when the vertex data type is set to CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2
		/// If the vertex buffer type is not set to CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2, an exception occurs
		void addVertex(const CVector3f& position, const CColourf& colour, const CVector3f& normal, CVector2f& texcoord0, CVector2f& texcoord1);

		/// \brief Frees all previously added vertex data from system memory
		void freeVertexData(void);

		/// \brief Frees all vertex indicies from system memory
		void freeVertexIndicies(void);

		/// \brief Frees all vertex data and vertex indicies from system memory
		void freeAll(void);

		/// \brief Adds a new vertex index
		void addIndex(int newIndex);

		/// \brief Returns the number of vertices which have been added so far.
		///
		/// \return The number of vertices which have been added so far.
		size_t getNumVertices(void) const;

		/// \brief Returns nummber of indices which have been added so far.
		///
		/// \return The nummber of indices which have been added so far.
		size_t getNumIndicies(void) const;

		/// \brief Sends the vertex data to the GPU to be rendered.
		///
		/// If there's no vertex data, this silently fails.
		virtual void render(bool bWireframeMode = false) const = 0;

		/// \brief Converts an .obj file to our custom geometry file format and saves to disk
		///
		/// Does not touch any members of this class
		void convertObj(const std::string filename) const;

		/// \brief Adds vertex data and indicies from our custom file format which is created with convertObj()
		/// 
		/// Use the convertObj() method to generate a binary file from an .obj file exported from
		/// some 3D modelling package such as Blender.
		/// The method will load in, convert and save out the stored geometry information into an efficient to load file which we use here
		/// to load the vertex information into memory.
		void addFromFile(const std::string& strGeometryFilename);

	};

	
	/// \brief OpenGL class for resource of type vertex buffer
	class CResourceVertexBufferOpenGL : public CResourceVertexBufferBase
	{
	public:
		CResourceVertexBufferOpenGL();
		~CResourceVertexBufferOpenGL();

		void uploadGPU(void);
		void freeGPU(void);
		void render(bool bWireframeMode = false) const;
	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};

	/// \brief Vulkan class for resource of type vertex buffer
	///
	///
	class CResourceVertexBufferVulkan : public CResourceVertexBufferBase
	{
	public:
		CResourceVertexBufferVulkan();
		~CResourceVertexBufferVulkan();

		void uploadGPU(void);
		void freeGPU(void);
		void render(bool bWireframeMode = false) const;
	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
		///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};


}	// namespace DCL

#endif	// #ifndef FILENAME_H

/// \file GPUProgramStrings.h
/// \brief Contains GPU program source code for DCL default GPU programs
///
/// DCL has a few renderers such as OpenGL and Vulkan and those renderers have some default GPU programs which are used throughout DCL.
/// When the renderers are initialised, they create some default vertex and fragment program resources (ResourceGPUPrograms) from the GPU program source code found within this file as strings.
/// There is a function which needs calling to setup these strings called initGPUProgramStrings()
/// Once the renderer is initialised, the programs are uploaded and ready for use.
/// They are used throughout DCL for common, standard rendering.
/// They are meant to be paired with ResourceVertexBuffer data types which are set with CResourceVertexBufferBase::setDataType()
/// Regardless of renderer, they are named the same so that they can be accessed and used regardless of which renderer is being used.
/// Here are their names and a description of what each one is for...
/// gStrGPU_POS_COL,									// Vertex buffer data type which holds vertex position and colour
///	gStrGPU_POS_COL_TEXCOORD,							// Vertex buffer data type which holds vertex position, colour and texture coordinates
///	gStrGPU_POS_COL_NORMAL_TEXCOORD,					// Vertex buffer data type which holds vertex position, colour, normal and texture coordinates
///	gStrGPU_POS_COL_NORMAL_TEXCOORDx2,					// Vertex buffer data type which holds vertex position, colour, normal and two sets of texture coordinates
///	gStrGPU_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL	// Vertex buffer data type which holds vertex position, colour, normal, texture coordinates, tangent and binormal vectors.
/// They simply match the available data types available in the vertex buffer resource.
/// For each ResourceVertexBuffer data type, there is a pair of GPU program strings, array index 0 for the vertex shader and index 1 for the fragment shader code.
#ifndef GPU_PROGRAM_STRINGS_H
#define GPU_PROGRAM_STRINGS_H
#include <string>

namespace DCL
{
	/// \brief Sets up the various GPU program strings with their source code
	void initGPUProgramStrings(void);

	extern std::string strGPU_POS_COL[2];									// Vertex buffer data type which holds vertex position and colour
	extern std::string strGPU_POS_COL_TEXCOORD[2];							// Vertex buffer data type which holds vertex position, colour and texture coordinates
	extern std::string strGPU_POS_COL_NORMAL_TEXCOORD[2];					// Vertex buffer data type which holds vertex position, colour, normal and texture coordinates
	extern std::string strGPU_POS_COL_NORMAL_TEXCOORDx2[2];					// Vertex buffer data type which holds vertex position, colour, normal and two sets of texture coordinates
	extern std::string strGPU_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[2];	// Vertex buffer data type which holds vertex position, colour, normal, texture coordinates, tangent and binormal vectors.

}	// namespace DCL

#endif	// #ifndef FILENAME_H
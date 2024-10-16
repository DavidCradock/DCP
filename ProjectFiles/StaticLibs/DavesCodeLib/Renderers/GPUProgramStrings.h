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
/// DCL_POS_COL,									// Vertex buffer data type which holds vertex position and colour
///	DCL_POS_COL_TEXCOORD,							// Vertex buffer data type which holds vertex position, colour and texture coordinates
///
/// They simply match the available data types available in the vertex buffer resource.
#ifndef GPU_PROGRAM_STRINGS_H
#define GPU_PROGRAM_STRINGS_H
#include <string>
#include <vector>

namespace DCL
{
	/// \brief Sets up the various GPU program strings with their source code
	///
	/// Can be called multiple times as the strings are cleared before having the source code appended.
	void initGPUProgramStrings(void);

	/// \brief Structure to hold names and source code for each default ResourceGPUProgram
	struct SDefaultGPUPrograms
	{
		std::string strResourceName;			///< The name of the GPU program resource added to a renderer. This is used to access the GPU program
		std::string strVertexProgramSource;		///< Holds source code for the vertex program
		std::string strFragmentProgramSource;	///< Holds source code for the fragment program
	};
	extern std::vector<SDefaultGPUPrograms> gVecDefaultGPUPrograms;			///< A vector of SDefaultGPUPrograms structures holding each unique GPUProgram resource name and it's source code.

}	// namespace DCL

#endif	// #ifndef FILENAME_H
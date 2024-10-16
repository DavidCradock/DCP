#include "GPUProgramStrings.h"

namespace DCL
{
	// Vertex[0] and fragment[1] GPU shader program source code strings.
	std::string strGPU_POS_COL[2];
	std::string strGPU_POS_COL_TEXCOORD[2];
	std::string strGPU_POS_COL_NORMAL_TEXCOORD[2];
	std::string strGPU_POS_COL_NORMAL_TEXCOORDx2[2];
	std::string strGPU_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[2];

	void initGPUProgramStrings(void)
	{
		// Clear vector holding all structures of strings.
		gVecDefaultGPUPrograms.clear();
		SDefaultGPUPrograms prog;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Program name
		prog.strResourceName = "DCL_POS_COL";

		// Vertex program
		prog.strVertexProgramSource.clear();
		prog.strVertexProgramSource.append("#version 330 core\n");
		prog.strVertexProgramSource.append("layout(location = 0) in vec3 aPos;\n");
		prog.strVertexProgramSource.append("layout(location = 1) in vec4 aColour;\n");
		prog.strVertexProgramSource.append("out vec4 colour;\n");
		prog.strVertexProgramSource.append("uniform mat4 matrixWorld;\n");
		prog.strVertexProgramSource.append("uniform mat4 matrixView;\n");
		prog.strVertexProgramSource.append("uniform mat4 matrixProjection;\n");
		prog.strVertexProgramSource.append("void main()\n");
		prog.strVertexProgramSource.append("{\n");
		prog.strVertexProgramSource.append("		gl_Position = matrixProjection * matrixView * matrixWorld * vec4(aPos, 1.0f);\n");
		prog.strVertexProgramSource.append("		colour = aColour;\n");
		prog.strVertexProgramSource.append("}\n");

		// Fragment program
		prog.strFragmentProgramSource.clear();
		prog.strFragmentProgramSource.append("#version 330 core\n");
		prog.strFragmentProgramSource.append("out vec4 FragColour;\n");
		prog.strFragmentProgramSource.append("in vec4 colour;\n");
		prog.strFragmentProgramSource.append("void main()\n");
		prog.strFragmentProgramSource.append("{\n");
		prog.strFragmentProgramSource.append("		FragColour = colour;\n");
		prog.strFragmentProgramSource.append("}\n");
		gVecDefaultGPUPrograms.push_back(prog);	// Add GPU program resource details to the vector

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Program name
		prog.strResourceName = "DCL_POS_COL_TEXCOORD";

		// Vertex program
		prog.strVertexProgramSource.clear();
		prog.strVertexProgramSource.append("#version 330 core\n");
		prog.strVertexProgramSource.append("layout(location = 0) in vec3 aPos;\n");
		prog.strVertexProgramSource.append("layout(location = 1) in vec4 aColour;\n");
		prog.strVertexProgramSource.append("layout(location = 2) in vec2 aTexCoord;\n");
		prog.strVertexProgramSource.append("out vec4 colour;\n");
		prog.strVertexProgramSource.append("out vec2 texCoord;\n");
		prog.strVertexProgramSource.append("uniform mat4 matrixWorld;\n");
		prog.strVertexProgramSource.append("uniform mat4 matrixView;\n");
		prog.strVertexProgramSource.append("uniform mat4 matrixProjection;\n");
		prog.strVertexProgramSource.append("void main()\n");
		prog.strVertexProgramSource.append("{\n");
		prog.strVertexProgramSource.append("		gl_Position = matrixProjection * matrixView * matrixWorld * vec4(aPos, 1.0f);\n");
		prog.strVertexProgramSource.append("		colour = aColour;\n");
		prog.strVertexProgramSource.append("		texCoord = aTexCoord;\n");
		prog.strVertexProgramSource.append("}\n");

		// Fragment program
		prog.strFragmentProgramSource.clear();
		prog.strFragmentProgramSource.append("#version 330 core\n");
		prog.strFragmentProgramSource.append("out vec4 FragColour;\n");
		prog.strFragmentProgramSource.append("in vec4 colour;\n");
		prog.strFragmentProgramSource.append("in vec2 texCoord;\n");
		prog.strFragmentProgramSource.append("uniform sampler2D texture0;\n");
		prog.strFragmentProgramSource.append("void main()\n");
		prog.strFragmentProgramSource.append("{\n");
		prog.strFragmentProgramSource.append("		FragColour = texture(texture0, texCoord);\n");
		prog.strFragmentProgramSource.append("		FragColour *= colour;\n");
		prog.strFragmentProgramSource.append("}\n");
		gVecDefaultGPUPrograms.push_back(prog);	// Add GPU program resource details to the vector
	}

}	// namespace DCL
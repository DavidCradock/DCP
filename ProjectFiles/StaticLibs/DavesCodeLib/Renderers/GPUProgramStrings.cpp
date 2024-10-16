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
		// Vertex program
		strGPU_POS_COL[0].append("#version 330 core\n");
		strGPU_POS_COL[0].append("layout(location = 0) in vec3 aPos;\n");
		strGPU_POS_COL[0].append("layout(location = 1) in vec4 aColour;\n");
		strGPU_POS_COL[0].append("out vec4 colour;\n");
		strGPU_POS_COL[0].append("uniform mat4 matrixWorld;\n");
		strGPU_POS_COL[0].append("uniform mat4 matrixView;\n");
		strGPU_POS_COL[0].append("uniform mat4 matrixProjection;\n");
		strGPU_POS_COL[0].append("void main()\n");
		strGPU_POS_COL[0].append("{\n");
		strGPU_POS_COL[0].append("		gl_Position = matrixProjection * matrixView * matrixWorld * vec4(aPos, 1.0f);\n");
		strGPU_POS_COL[0].append("		colour = aColour;\n");
		strGPU_POS_COL[0].append("}\n");

		// Fragment program
		strGPU_POS_COL[1].clear();
		strGPU_POS_COL[1].append("#version 330 core\n");
		strGPU_POS_COL[1].append("out vec4 FragColour;\n");
		strGPU_POS_COL[1].append("in vec4 colour;\n");
		strGPU_POS_COL[1].append("void main()\n");
		strGPU_POS_COL[1].append("{\n");
		strGPU_POS_COL[1].append("		FragColour = colour;\n");
		strGPU_POS_COL[1].append("}\n");



		/*
		// Vertex program
		strGPU_POS_COL[0].clear();
		strGPU_POS_COL[0].append("#version 330 core\n");
		strGPU_POS_COL[0].append("layout(location = 0) in vec3 aPos;\n");
		strGPU_POS_COL[0].append("layout(location = 1) in vec4 aColour;\n");
		strGPU_POS_COL[0].append("layout(location = 2) in vec2 aTexCoord;\n");
		strGPU_POS_COL[0].append("layout(location = 3) in vec2 aTexCoord2;\n");
		strGPU_POS_COL[0].append("out vec4 colour;\n");
		strGPU_POS_COL[0].append("out vec2 texCoord;\n");
		strGPU_POS_COL[0].append("out vec2 texCoord2;\n");
		strGPU_POS_COL[0].append("uniform mat4 matrixWorld;\n");
		strGPU_POS_COL[0].append("uniform mat4 matrixView;\n");
		strGPU_POS_COL[0].append("uniform mat4 matrixProjection;\n");
		strGPU_POS_COL[0].append("void main()\n");
		strGPU_POS_COL[0].append("{\n");
		strGPU_POS_COL[0].append("		gl_Position = matrixProjection * matrixView * matrixWorld * vec4(aPos, 1.0f);\n");
		strGPU_POS_COL[0].append("		colour = aColour;\n");
		strGPU_POS_COL[0].append("		texCoord = aTexCoord;\n");
		strGPU_POS_COL[0].append("		texCoord2 = aTexCoord2;\n");
		strGPU_POS_COL[0].append("}\n");

		// Fragment program
		strGPU_POS_COL[1].clear();
		strGPU_POS_COL[1].append("#version 330 core\n");
		strGPU_POS_COL[1].append("out vec4 FragColour;\n");
		strGPU_POS_COL[1].append("in vec4 colour;\n");
		strGPU_POS_COL[1].append("in vec2 texCoord;\n");
		strGPU_POS_COL[1].append("in vec2 texCoord2;\n");
		strGPU_POS_COL[1].append("uniform sampler2D texture0;\n");
		strGPU_POS_COL[1].append("uniform sampler2D texture1;\n");
		// Amount of texture0 and texture1.
		// If 0.0f, texture0 has full contribution and texture1, none.
		// If 0.5f, texture0 and texture1 are added equally.
		// If 1.0f, texture1 has full contribution and texture0, none.
		strGPU_POS_COL[1].append("uniform float fTextureContribution;\n");
		strGPU_POS_COL[1].append("void main()\n");
		strGPU_POS_COL[1].append("{\n");
		strGPU_POS_COL[1].append("		FragColour = texture(texture0, texCoord) * fTextureContribution;\n");
		strGPU_POS_COL[1].append("		FragColour += texture(texture1, texCoord2) * (1.0 - fTextureContribution);\n");
		strGPU_POS_COL[1].append("		FragColour *= colour;\n");
		strGPU_POS_COL[1].append("}\n");
		*/
	}

}	// namespace DCL
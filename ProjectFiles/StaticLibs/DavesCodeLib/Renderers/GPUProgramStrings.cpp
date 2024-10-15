#include "GPUProgramStrings.h"

namespace DCL
{
	// Vertex[0] and fragment[1] GPU shader program source code strings.
	std::string gStrGPU_POS[2];
	std::string gStrGPU_POS_COL[2];
	std::string gStrGPU_POS_COL_TEXCOORD[2];
	std::string gStrGPU_POS_COL_NORMAL_TEXCOORD[2];
	std::string gStrGPU_POS_COL_NORMAL_TEXCOORDx2[2];
	std::string gStrGPU_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[2];

	void initGPUProgramStrings(void)
	{
		// Vertex program
		gStrGPU_POS[0].append("#version 330 core\n");
		gStrGPU_POS[0].append("layout(location = 0) in vec3 aPos;\n");
		gStrGPU_POS[0].append("uniform mat4 matrixWorld;\n");
		gStrGPU_POS[0].append("uniform mat4 matrixView;\n");
		gStrGPU_POS[0].append("uniform mat4 matrixProjection;\n");
		gStrGPU_POS[0].append("void main()\n");
		gStrGPU_POS[0].append("{\n");
		gStrGPU_POS[0].append("		gl_Position = matrixProjection * matrixView * matrixWorld * vec4(aPos, 1.0f);\n");
		gStrGPU_POS[0].append("}\n");

		// Fragment program
		gStrGPU_POS[1].clear();
		gStrGPU_POS[1].append("#version 330 core\n");
		gStrGPU_POS[1].append("out vec4 FragColour;\n");
		gStrGPU_POS[1].append("void main()\n");
		gStrGPU_POS[1].append("{\n");
		gStrGPU_POS[1].append("		FragColour = vec4(1.0, 1.0, 1.0, 1.0);\n");	// Not sure if this works
		gStrGPU_POS[1].append("}\n");



		/*
		// Vertex program
		gStrGPU_POS[0].append("#version 330 core\n");
		gStrGPU_POS[0].append("layout(location = 0) in vec3 aPos;\n");
		gStrGPU_POS[0].append("layout(location = 1) in vec4 aColour;\n");
		gStrGPU_POS[0].append("layout(location = 2) in vec2 aTexCoord;\n");
		gStrGPU_POS[0].append("layout(location = 3) in vec2 aTexCoord2;\n");
		gStrGPU_POS[0].append("out vec4 colour;\n");
		gStrGPU_POS[0].append("out vec2 texCoord;\n");
		gStrGPU_POS[0].append("out vec2 texCoord2;\n");
		gStrGPU_POS[0].append("uniform mat4 matrixWorld;\n");
		gStrGPU_POS[0].append("uniform mat4 matrixView;\n");
		gStrGPU_POS[0].append("uniform mat4 matrixProjection;\n");
		gStrGPU_POS[0].append("void main()\n");
		gStrGPU_POS[0].append("{\n");
		gStrGPU_POS[0].append("		gl_Position = matrixProjection * matrixView * matrixWorld * vec4(aPos, 1.0f);\n");
		gStrGPU_POS[0].append("		colour = aColour;\n");
		gStrGPU_POS[0].append("		texCoord = aTexCoord;\n");
		gStrGPU_POS[0].append("		texCoord2 = aTexCoord2;\n");
		gStrGPU_POS[0].append("}\n");

		// Fragment program
		gStrGPU_POS[1].clear();
		gStrGPU_POS[1].append("#version 330 core\n");
		gStrGPU_POS[1].append("out vec4 FragColour;\n");
		gStrGPU_POS[1].append("in vec4 colour;\n");
		gStrGPU_POS[1].append("in vec2 texCoord;\n");
		gStrGPU_POS[1].append("in vec2 texCoord2;\n");
		gStrGPU_POS[1].append("uniform sampler2D texture0;\n");
		gStrGPU_POS[1].append("uniform sampler2D texture1;\n");
		// Amount of texture0 and texture1.
		// If 0.0f, texture0 has full contribution and texture1, none.
		// If 0.5f, texture0 and texture1 are added equally.
		// If 1.0f, texture1 has full contribution and texture0, none.
		gStrGPU_POS[1].append("uniform float fTextureContribution;\n");
		gStrGPU_POS[1].append("void main()\n");
		gStrGPU_POS[1].append("{\n");
		gStrGPU_POS[1].append("		FragColour = texture(texture0, texCoord) * fTextureContribution;\n");
		gStrGPU_POS[1].append("		FragColour += texture(texture1, texCoord2) * (1.0 - fTextureContribution);\n");
		gStrGPU_POS[1].append("		FragColour *= colour;\n");
		gStrGPU_POS[1].append("}\n");
		*/
	}

}	// namespace DCL
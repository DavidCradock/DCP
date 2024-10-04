#include "ResourceGPUPrograms.h"
#include "../../Core/Exceptions.h"
#include "../OpenGL/RendererOpenGLExtensions.h"

namespace DCL
{
	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Base
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/


	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* OpenGL
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceGPUProgramsOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceGPUProgramsOpenGL::CPrim
	{
	public:
		CPrim();
		unsigned int uiProgramID;	///< Holds GPU program ID given to us by OpenGL
	};

	CResourceGPUProgramsOpenGL::CPrim::CPrim()
	{
		uiProgramID = 0;
	}

	CResourceGPUProgramsOpenGL::CResourceGPUProgramsOpenGL()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceGPUProgramsOpenGL::~CResourceGPUProgramsOpenGL()
	{
		LOG("Destructor called.");

		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceGPUProgramsOpenGL::setProgramSourceFromFile(const std::string& strVertexProgramSourceFilename, const std::string& strFragmentProgramSourceFilename)
	{
		// Load in source code
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(strVertexProgramSourceFilename);
			fShaderFile.open(strFragmentProgramSourceFilename);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			ThrowIfTrue(1, "CResourceGPUProgramsOpenGL::setProgramSourceFromFile() failed to read in program code for either " + strVertexProgramSourceFilename + " or " + strFragmentProgramSourceFilename);
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// Attempt to compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::string err("CResourceGPUProgramsOpenGL::setProgramSourceFromFile() failed. ");
			err.append(infoLog);
			ThrowIfTrue(1, err);
		};

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::string err("CResourceGPUProgramsOpenGL::setProgramSourceFromFile() failed. ");
			err.append(infoLog);
			ThrowIfTrue(1, err);
		};

		// Shader Program
		prim->uiProgramID = glCreateProgram();
		glAttachShader(prim->uiProgramID, vertex);
		glAttachShader(prim->uiProgramID, fragment);
		glLinkProgram(prim->uiProgramID);

		// Show linking errors if any
		glGetProgramiv(prim->uiProgramID, GL_LINK_STATUS, &success);
		if (!success)
		{
			std::string err("CResourceGPUProgramsOpenGL::setProgramSourceFromFile() failed. ");
			err.append(infoLog);
			ThrowIfTrue(1, err);
		}

		// Delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void CResourceGPUProgramsOpenGL::upload(void)
	{

	}

	void CResourceGPUProgramsOpenGL::free(void)
	{
		if (prim->uiProgramID)
		{
			glDeleteProgram(prim->uiProgramID);
			prim->uiProgramID = 0;
		}
	}

	void CResourceGPUProgramsOpenGL::bind(void) const
	{
		if (prim->uiProgramID)
			glUseProgram(prim->uiProgramID);
	}

	void CResourceGPUProgramsOpenGL::unbind(void) const
	{
		glUseProgram(0);
	}

	void CResourceGPUProgramsOpenGL::setUniformBool(const std::string& strUniformName, bool value) const
	{
		if (prim->uiProgramID)
			glUniform1i(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), (int)value);
	}

	void CResourceGPUProgramsOpenGL::setUniformInt(const std::string& strUniformName, int value) const
	{
		if (prim->uiProgramID)
			glUniform1i(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), value);
	}

	void CResourceGPUProgramsOpenGL::setUniformFloat(const std::string& strUniformName, float value) const
	{
		if (prim->uiProgramID)
			glUniform1f(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), value);
	}

	void CResourceGPUProgramsOpenGL::setUniformMat4(const std::string& strUniformName, const CMatrix& value) const
	{
		if (prim->uiProgramID)
			glUniformMatrix4fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, GL_FALSE, value.getFloat());
	}

	void CResourceGPUProgramsOpenGL::setUniformVec2(const std::string& strUniformName, const CVector2f& value) const
	{
		if (!prim->uiProgramID)
			return;
		float array[2];
		value.getAsArray(array);
		glUniform2fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, &array[0]);
	}

	void CResourceGPUProgramsOpenGL::setUniformVec3(const std::string& strUniformName, const CVector3f& value) const
	{
		if (!prim->uiProgramID)
			return;
		float array[3];
		value.getAsArray(array);
		glUniform3fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, &array[0]);
	}

	void CResourceGPUProgramsOpenGL::setUniformVec3(const std::string& strUniformName, const CColourf& value) const
	{
		if (!prim->uiProgramID)
			return;
		float array[3];
		array[0] = value.red;
		array[1] = value.green;
		array[2] = value.blue;
		glUniform3fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, &array[0]);
	}

	void CResourceGPUProgramsOpenGL::setUniformVec4(const std::string& strUniformName, const CColourf& value) const
	{
		if (!prim->uiProgramID)
			return;
		float array[4];
		array[0] = value.red;
		array[1] = value.green;
		array[2] = value.blue;
		array[3] = value.alpha;
		glUniform4fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, &array[0]);
	}

	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Vulkan
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceGPUProgramsVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceGPUProgramsVulkan::CPrim
	{
	public:
		CPrim();
	};

	CResourceGPUProgramsVulkan::CPrim::CPrim()
	{
	}

	CResourceGPUProgramsVulkan::CResourceGPUProgramsVulkan()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceGPUProgramsVulkan::~CResourceGPUProgramsVulkan()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceGPUProgramsVulkan::setProgramSourceFromFile(const std::string& strVertexProgramSourceFilename, const std::string& strFragmentProgramSourceFilename)
	{

	}

	void CResourceGPUProgramsVulkan::upload(void)
	{

	}

	void CResourceGPUProgramsVulkan::free(void)
	{

	}

	void CResourceGPUProgramsVulkan::bind(void) const
	{

	}

	void CResourceGPUProgramsVulkan::unbind(void) const
	{

	}

	void CResourceGPUProgramsVulkan::setUniformBool(const std::string& strUniformName, bool value) const
	{

	}

	void CResourceGPUProgramsVulkan::setUniformInt(const std::string& strUniformName, int value) const
	{

	}

	void CResourceGPUProgramsVulkan::setUniformFloat(const std::string& strUniformName, float value) const
	{

	}

	void CResourceGPUProgramsVulkan::setUniformMat4(const std::string& strUniformName, const CMatrix& value) const
	{

	}

	void CResourceGPUProgramsVulkan::setUniformVec2(const std::string& strUniformName, const CVector2f& value) const
	{

	}

	void CResourceGPUProgramsVulkan::setUniformVec3(const std::string& strUniformName, const CVector3f& value) const
	{

	}

	void CResourceGPUProgramsVulkan::setUniformVec3(const std::string& strUniformName, const CColourf& value) const
	{

	}

	void CResourceGPUProgramsVulkan::setUniformVec4(const std::string& strUniformName, const CColourf& value) const
	{

	}


}	// namespace DCL
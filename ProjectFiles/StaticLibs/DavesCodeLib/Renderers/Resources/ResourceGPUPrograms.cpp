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
		unsigned int uiProgramID;			///< Holds GPU program ID given to us by OpenGL
		std::string strVertexSourceCode;	///< Holds the vertex program source code as text
		std::string strFragmentSourceCode;	///< Holds the fragment program source code as text
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
		prim->strVertexSourceCode.clear();
		prim->strFragmentSourceCode.clear();
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
			prim->strVertexSourceCode = vShaderStream.str();
			prim->strFragmentSourceCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			ThrowIfTrue(1, "CResourceGPUProgramsOpenGL::setProgramSourceFromFile() failed to read in program code for either " + strVertexProgramSourceFilename + " or " + strFragmentProgramSourceFilename);
		}
		
	}

	void CResourceGPUProgramsOpenGL::setProgramSourceFromMemory(const std::string& strVertexProgramSourceCode, const std::string& strFragmentProgramSourceCode)
	{
		ThrowIfFalse(strVertexProgramSourceCode.length(), "CResourceGPUProgramsOpenGL::setProgramSourceFromMemory() failed. The given vertex program is of zero length.");
		ThrowIfFalse(strFragmentProgramSourceCode.length(), "CResourceGPUProgramsOpenGL::setProgramSourceFromMemory() failed. The given fragment program is of zero length.");

		// Copy the source code
		prim->strVertexSourceCode = strVertexProgramSourceCode;
		prim->strFragmentSourceCode = strFragmentProgramSourceCode;
	}

	void CResourceGPUProgramsOpenGL::upload(void)
	{
		// Make sure the source code as text exists
		ThrowIfTrue(0 == prim->strVertexSourceCode.length(), "CResourceGPUProgramsOpenGL::upload() failed. The vertex program's source code hasn't been set. Did you forget to call setProgramSourceFromFile()?");
		ThrowIfTrue(0 == prim->strFragmentSourceCode.length(), "CResourceGPUProgramsOpenGL::upload() failed. The fragment program's source code hasn't been set. Did you forget to call setProgramSourceFromFile()?");;

		// Free the linked shader programs if they already exist
		free();

		const char* vShaderCode = prim->strVertexSourceCode.c_str();
		const char* fShaderCode = prim->strFragmentSourceCode.c_str();

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
			std::string err("CResourceGPUProgramsOpenGL::upload() failed to compile the vertex program. ");
			err.append(infoLog);
			Throw(err);
		};

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::string err("CResourceGPUProgramsOpenGL::upload() failed to compile the fragment program. ");
			err.append(infoLog);
			Throw(err);
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
			std::string err("CResourceGPUProgramsOpenGL::upload() failed to link the programs. ");
			err.append(infoLog);
			Throw(err);
		}

		// Delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
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
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");
		glUseProgram(prim->uiProgramID);
	}

	void CResourceGPUProgramsOpenGL::unbind(void) const
	{
		glUseProgram(0);
	}

	void CResourceGPUProgramsOpenGL::setUniformBool(const std::string& strUniformName, bool value) const
	{
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");
		glUniform1i(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), (int)value);
	}

	void CResourceGPUProgramsOpenGL::setUniformInt(const std::string& strUniformName, int value) const
	{
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");
		glUniform1i(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), value);
	}

	void CResourceGPUProgramsOpenGL::setUniformFloat(const std::string& strUniformName, float value) const
	{
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");
		glUniform1f(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), value);
	}

	void CResourceGPUProgramsOpenGL::setUniformMat4(const std::string& strUniformName, const CMatrix& value) const
	{
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");
		glUniformMatrix4fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, GL_FALSE, value.getFloat());
	}

	void CResourceGPUProgramsOpenGL::setUniformVec2(const std::string& strUniformName, const CVector2f& value) const
	{
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");

		float array[2];
		value.getAsArray(array);
		glUniform2fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, &array[0]);
	}

	void CResourceGPUProgramsOpenGL::setUniformVec3(const std::string& strUniformName, const CVector3f& value) const
	{
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");
		float array[3];
		value.getAsArray(array);
		glUniform3fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, &array[0]);
	}

	void CResourceGPUProgramsOpenGL::setUniformVec3(const std::string& strUniformName, const CColourf& value) const
	{
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");
		float array[3];
		array[0] = value.red;
		array[1] = value.green;
		array[2] = value.blue;
		glUniform3fv(glGetUniformLocation(prim->uiProgramID, strUniformName.c_str()), 1, &array[0]);
	}

	void CResourceGPUProgramsOpenGL::setUniformVec4(const std::string& strUniformName, const CColourf& value) const
	{
		ThrowIfFalse(prim->uiProgramID, "Shader programs not compiled and uploaded to GPU.");
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

	void CResourceGPUProgramsVulkan::setProgramSourceFromMemory(const std::string& strVertexProgramSourceCode, const std::string& strFragmentProgramSourceCode)
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
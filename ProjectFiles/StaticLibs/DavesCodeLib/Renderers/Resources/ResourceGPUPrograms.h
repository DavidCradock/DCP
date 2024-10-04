#ifndef RESOURCE_GPUPROGRAMS_H
#define RESOURCE_GPUPROGRAMS_H

#include "../../Core/Colourf.h"
#include "../../Math/Matrix.h"
#include "../../Math/Vector2f.h"
#include "../../Math/Vector3f.h"
#include <string>

namespace DCL
{
	/// \brief Base class for resource of type GPU program for a pair of vertex/fragment shaders
	///
	/// We derive resource classes from this base class for each renderer type such as OpenGL and Vulkan.
	/// These classes are to be declared within this header file to reduce the number of files.
	/// Eww! I know right? Three class declarations insided a single header file, the madness!
	/// I know it's a little messy, but the alternative is to have six files for each resource type and as there are quite a few resources, this would've meant many files and that's even more messy.
	/// I know it means that the various renderers for the different graphics APIs are including stuff which isn't related to them, but that's a small price to pay for the reduced number of files we'd otherwise have to create.
	/// Within DCL, all code uses only a pointer to the base class and the implementation for each of the methods are implemented inside the derived classes and are insulated via private implementations.
	/// Each of the API's CRenderer classes which are derived from the CRendererBase class, are responsible for creating, accessing and freeing this resource type.
	/// We have a set of setUniform??? methods which set a variable for the GPU program which remains constant for all vertices/fragments sent to the GPU.
	class CResourceGPUProgramsBase
	{
	public:
		/// \brief Sets the GPU programs to use the source code found in the given filename.
		///
		/// \param strProgramSourceFilename The filename of the file holding the source code for this program
		virtual void setProgramSourceFromFile(const std::string& strVertexProgramSourceFilename, const std::string& strFragmentProgramSourceFilename) = 0;

		/// \brief Compiles and uploads the programs using the source code set with setProgramSourceFromFile(), into GPU memory, ready for use.
		///
		/// If the source code hasn't been set with setProgramSourceFromFile(), an exception should occur.
		virtual void upload(void) = 0;

		/// \brief Frees the programs from the GPU memory.
		virtual void free(void) = 0;

		/// \brief Binds the programs ready for use
		virtual void bind(void) const = 0;

		/// \brief Unbinds the prograsm from the GPU
		virtual void unbind(void) const = 0;

		/// \brief Set bool uniform. Call once the program is bound with bind().
		///
		/// \param strUniformName The name of the boolean uniform in the program source code
		/// \param value The value to set the uniform to.
		virtual void setUniformBool(const std::string& strUniformName, bool value) const = 0;

		/// \brief Set int uniform. Call once the program is bound with bind().
		///
		/// \param strUniformName The name of the int uniform in the program source code
		/// \param value The value to set the uniform to.
		/// 
		/// Usefull for telling the graphics API which sampler unit belongs to which uniform sampler2D name in the program
		/// Example...
		/// Tell GPU API, for each sampler, to which texture unit it belongs to
		/// pShader->setInt("texture0", 0);
		/// pShader->setInt("texture1", 1);
		virtual void setUniformInt(const std::string& strUniformName, int value) const = 0;

		/// \brief Set float uniform. Call once the program is bound with bind().
		///
		/// \param strUniformName The name of the float uniform in the program source code
		/// \param value The value to set the uniform to.
		virtual void setUniformFloat(const std::string& strUniformName, float value) const = 0;

		/// \brief Set matrix uniform. Call once the program is bound with bind().
		///
		/// \param strUniformName The name of the matrix uniform in the program source code
		/// \param value The value to set the uniform to.
		virtual void setUniformMat4(const std::string& strUniformName, const CMatrix& value) const = 0;

		/// \brief Set vec2 uniform. Call once the program is bound with bind().
		///
		/// \param strUniformName The name of the vector uniform in the program source code
		/// \param value The value to set the uniform to.
		virtual void setUniformVec2(const std::string& strUniformName, const CVector2f& value) const = 0;

		/// \brief Set vec3 uniform. Call once the program is bound with bind().
		///
		/// \param strUniformName The name of the vector uniform in the program source code
		/// \param value The value to set the uniform to.
		virtual void setUniformVec3(const std::string& strUniformName, const CVector3f& value) const = 0;

		/// \brief Set vec3 uniform. Call once the program is bound with bind().
		///
		/// \param strUniformName The name of the vector uniform in the program source code
		/// \param value The value to set the uniform to.
		virtual void setUniformVec3(const std::string& strUniformName, const CColourf& value) const = 0;

		/// \brief Set vec4 uniform. Call once the program is bound with bind().
		///
		/// \param strUniformName The name of the vector uniform in the program source code
		/// \param value The value to set the uniform to.
		virtual void setUniformVec4(const std::string& strUniformName, const CColourf& value) const = 0;

	};

	/// \brief OpenGL class for resource of type GPU programs
	///
	///
	class CResourceGPUProgramsOpenGL : public CResourceGPUProgramsBase
	{
	public:
		CResourceGPUProgramsOpenGL();
		~CResourceGPUProgramsOpenGL();

		void setProgramSourceFromFile(const std::string& strVertexProgramSourceFilename, const std::string& strFragmentProgramSourceFilename);
		void upload(void);
		void free(void);
		void bind(void) const;
		void unbind(void) const;
		void setUniformBool(const std::string& strUniformName, bool value) const;
		void setUniformInt(const std::string& strUniformName, int value) const;
		void setUniformFloat(const std::string& strUniformName, float value) const;
		void setUniformMat4(const std::string& strUniformName, const CMatrix& value) const;
		void setUniformVec2(const std::string& strUniformName, const CVector2f& value) const;
		void setUniformVec3(const std::string& strUniformName, const CVector3f& value) const;
		void setUniformVec3(const std::string& strUniformName, const CColourf& value) const;
		void setUniformVec4(const std::string& strUniformName, const CColourf& value) const;

	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};

	/// \brief Vulkan class for resource of type vertex program
	///
	///
	class CResourceGPUProgramsVulkan : public CResourceGPUProgramsBase
	{
	public:
		CResourceGPUProgramsVulkan();
		~CResourceGPUProgramsVulkan();

		void setProgramSourceFromFile(const std::string& strVertexProgramSourceFilename, const std::string& strFragmentProgramSourceFilename);
		void upload(void);
		void free(void);
		void bind(void) const;
		void unbind(void) const;
		void setUniformBool(const std::string& strUniformName, bool value) const;
		void setUniformInt(const std::string& strUniformName, int value) const;
		void setUniformFloat(const std::string& strUniformName, float value) const;
		void setUniformMat4(const std::string& strUniformName, const CMatrix& value) const;
		void setUniformVec2(const std::string& strUniformName, const CVector2f& value) const;
		void setUniformVec3(const std::string& strUniformName, const CVector3f& value) const;
		void setUniformVec3(const std::string& strUniformName, const CColourf& value) const;
		void setUniformVec4(const std::string& strUniformName, const CColourf& value) const;

	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
		///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};


}	// namespace DCL

#endif	// #ifndef FILENAME_H

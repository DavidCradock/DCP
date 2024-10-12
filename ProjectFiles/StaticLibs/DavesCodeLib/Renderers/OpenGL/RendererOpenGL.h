#ifndef RENDEREROPENGL_H
#define RENDEREROPENGL_H

#include "../RendererBase.h"

namespace DCL
{
	/// \brief Renderer class derived from CRenderBase class which uses OpenGL for the render API
	class CRendererOpenGL : public CRendererBase
	{
	public:
		CRendererOpenGL();
		~CRendererOpenGL();

		void initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen, bool bVSyncEnabled, CColourf clearColour);
		void shutdown(void);
		void updateWindow(bool& bWindowResized, bool& bWindowMinimized, bool& bWindowHasBeenAskedToClose);

		void beginFrame(void);
		void endFrame(void);

		void setBackbufferClearColour(float fRed, float fGreen, float fBlue, float fAlpha);

		void setVSync(bool bVSyncOn);

		void blendDisable(void);
		void blendEnable(void);
		void blendFunction_SrcAlpha_One(void);
		void blendFunction_SrcAlpha_OneMinusSrcAlpha(void);

		void cullFaceAntiClockwise(void);
		void cullFaceClockwise(void);
		void cullFaceDisable(void);
		void cullFaceEnable(void);

		void depthTestDisable(void);
		void depthTestEnable(void);

		void pixelsRead(int iPositionX, int iPositionY, int iWidth, int iHeight, void* pixels);
		void pixelsWrite(int iPositionX, int iPositionY, int iWidth, int iHeight, void* pixels);

		void scissorTest(int iPositionX, int iPositionY, int iWidth, int iHeight);
		void scissorTestDisable(void);
		void scissorTestEnable(void);

		CResourceGPUProgramsBase* addGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber);
		CResourceGPUProgramsBase* getGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber);
		bool getGPUProgramsExists(const std::string& strResourceName, unsigned int uiGroupNumber);
		void removeGPUPrograms(const std::string& strResourceName, unsigned int uiGroupNumber);
		void removeGPUProgramsAll(unsigned int uiGroupNumber);

		CResourceTexture2DBase* addTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber);
		CResourceTexture2DBase* getTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber);
		bool getTexture2DExists(const std::string& strResourceName, unsigned int uiGroupNumber);
		void removeTexture2D(const std::string& strResourceName, unsigned int uiGroupNumber);
		void removeTexture2DAll(unsigned int uiGroupNumber);

		CResourceFramebufferBase* addFramebuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1);
		CResourceFramebufferBase* getFramebuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1);
		bool getFramebufferExists(const std::string& strResourceName, unsigned int uiGroupNumber = 1);
		void removeFramebuffer(const std::string& strResourceName, unsigned int uiGroupNumber = 1);
		void removeFramebufferAll(unsigned int uiGroupNumber = 1);

		CResourceVertexBufferBase* addVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber);
		CResourceVertexBufferBase* getVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber);
		bool getVertexBufferExists(const std::string& strResourceName, unsigned int uiGroupNumber);
		void removeVertexBuffer(const std::string& strResourceName, unsigned int uiGroupNumber);
		void removeVertexBufferAll(unsigned int uiGroupNumber);

	private:
		/// \brief Struct to hold a resource for the GPUPrograms type.
		struct SResourceGPUPrograms
		{
			CResourceGPUProgramsBase* pResource;	///< Pointer to the resource
			unsigned int uiCount;					///< Number of times the resource has been added
		};
		std::map<std::string, SResourceGPUPrograms> _mmapResGPUProgramsGroups[8];	///< Each of the 8 groups holding resources for the resource type.

		/// \brief Struct to hold a resource for the Texture2D type.
		struct SResourceTexture2D
		{
			CResourceTexture2DBase* pResource;	///< Pointer to the resource
			unsigned int uiCount;				///< Number of times the resource has been added
		};
		std::map<std::string, SResourceTexture2D> _mmapResTexture2DGroups[8];	///< Each of the 8 groups holding resources for the resource type.

		/// \brief Struct to hold a resource for the Framebuffer type.
		struct SResourceFramebuffer
		{
			CResourceFramebufferBase* pResource;	///< Pointer to the resource
			unsigned int uiCount;					///< Number of times the resource has been added
		};
		std::map<std::string, SResourceFramebuffer> _mmapResFramebufferGroups[8];	///< Each of the 8 groups holding resources for the resource type.

		/// \brief Struct to hold a resource for the VertexBuffer type.
		struct SResourceVertexBuffer
		{
			CResourceVertexBufferBase* pResource;	///< Pointer to the resource
			unsigned int uiCount;					///< Number of times the resource has been added
		};
		std::map<std::string, SResourceVertexBuffer> _mmapResVertexBufferGroups[8];	///< Each of the 8 groups holding resources for the resource type.

	private:
		class CPrim;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPrim* prim;		///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
/// \file RendererVulkan.h
/// \brief Renderer class derived from CRenderBase class which uses Vulkan for the render API
///
/// Detailed description text goes here.

#ifndef RENDERERVULKAN_H
#define RENDERERVULKAN_H

#include "RendererBase.h"

namespace DCL
{
	class CRendererVulkan : public CRendererBase
	{
	public:
		CRendererVulkan();
		~CRendererVulkan();

		void initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen, bool bVSyncEnabled, CColourf clearColour);
		void shutdown(void);
		void updateWindow(bool& bWindowResized, bool& bWindowMinimized, bool& bWindowHasBeenAskedToClose);

		void beginFrame(void);
		void endFrame(void);

		void setBackbufferClearColour(float fRed, float fGreen, float fBlue, float fAlpha);

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

	private:
		class CPimpl;		///< Declaration of this class's private implementation holding things which we do not wish to expose when including this header file.
							///< We put this here so we can create the pointer below, without having to include the header file containing the actual code.
		CPimpl* _mpPimpl;	///< Pointer holding private implementation, new'd and delete'd in con/des tructors of this class.
	};
}	// namespace DCL

#endif	// #ifndef FILENAME_H
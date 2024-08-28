/// \file RendererVulkan.h
/// \brief Brief description for the file goes here.
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

		void initialise(unsigned int iWindowWidth, unsigned int iWindowHeight, const std::string& strWindowTitle, bool bFullscreen);
		void shutdown(void);

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

	};
}	// namespace DCL

#endif	// #ifndef FILENAME_H
#include "AudioSample.h"

#include "../Core/Exceptions.h"

namespace DCL
{
	CAudioSample::CAudioSample()
	{
		_mpSampleChunk = 0;
	}

	CAudioSample::~CAudioSample()
	{
		free();
	}

	void CAudioSample::load(const std::string& sampleFilename)
	{
		_mpSampleChunk = Mix_LoadWAV(sampleFilename.c_str());
		if (!_mpSampleChunk)
		{
			std::string strError("CAudioSample::load(\"");
			strError.append(sampleFilename);
			strError.append("\") failed. SDL::Mix_LoadWav() failed: ");
			strError.append(Mix_GetError());
			ThrowIfTrue(1, strError);
		}
	}

	void CAudioSample::play(int iWhichChannel, int iNumberOfLoops)
	{
		if (!_mpSampleChunk)
			return;
		Mix_PlayChannel(iWhichChannel, _mpSampleChunk, iNumberOfLoops);
	}

	void CAudioSample::free(void)
	{
		if (_mpSampleChunk)
		{
			Mix_FreeChunk(_mpSampleChunk);
			_mpSampleChunk = 0;
		}
	}

}	// namespace DCL
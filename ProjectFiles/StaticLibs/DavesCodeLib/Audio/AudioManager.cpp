#include "AudioManager.h"
#include "../Core/Exceptions.h"

namespace DCL
{
	CAudioManager::CAudioManager(int iFrequency, int iNumberOfChannels, int iChunkSizeInSamples)
	{
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			std::string strError("SDL could not initialize: ");
			strError.append(SDL_GetError());
			ThrowIfTrue(1, strError);
		}
		/*
		if (Mix_OpenAudio(iFrequency, MIX_DEFAULT_FORMAT, iNumberOfChannels, iChunkSizeInSamples) < 0)
		{
			std::string strError("SDL_mixer could not initialize: ");
			strError.append(Mix_GetError());
			ThrowIfTrue(1, strError);
		}
		*/
	}

	CAudioManager::~CAudioManager(void)
	{
		Mix_CloseAudio();
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
	}

	bool CAudioManager::isAudioPlaying(void)
	{
		if (Mix_Playing(-1) > 0)
			return true;
		return false;
	}
}	// namespace DCL
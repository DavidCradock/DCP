/// \file AudioManager.h
/// \brief Audio manager
///
/// Detailed description text goes here.

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "../../../DynamicLibs/SDL3/include/SDL3/SDL.h"
#include "../../../DynamicLibs/SDL3Mixer/include/SDL3_mixer/SDL_mixer.h"

namespace DCL
{
	/// \brief Brief description text goes here
	///
	/// Detailed description goes here
	/// \code
	/// int iSomeCode = 0;
	/// \endcode
	/// \todo Lots to add and check here.
	class CAudioManager
	{
	public:
		/// \brief Constructor, initializes the audio sub system using given params as options
		///
		/// If initialization failed, an exception occurs
		CAudioManager(int iFrequency = 44100, int iNumberOfChannels = 2, int iChunkSizeInSamples = 2048);
#
		/// \brief Destructor, cleans up SDL audio subsystem
		~CAudioManager(void);

		/// \brief Checks to see if audio is playing on any channels
		///
		/// \return True is anything on any channels is currently playing, else false.
		/// 
		/// Please note, that even if a channel is paused, it is still considered being played.
		bool isAudioPlaying(void);

	private:
	
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
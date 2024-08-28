/// \file AudioSample.h
/// \brief Brief description for the file goes here.
///
/// Detailed description text goes here.

#ifndef AUDIOSAMPLE_H
#define AUDIOSAMPLE_H

#include "../../../DynamicLibs/SDL3/include/SDL3/SDL.h"
#include "../../../DynamicLibs/SDL3Mixer/include/SDL3_mixer/SDL_mixer.h"

#include <string>

namespace DCL
{
	/// \brief Audio sample for playback with the CAudioManager class
	///
	/// These are meant for short audio sample playback for sound effects such as explosions and such.
	/// For longer audio, intended to be played as music, see CAudioMusic
	class CAudioSample
	{
	public:

		/// \brief Constructor, audio sample is intially empty
		CAudioSample();

		/// \brief Destructor, frees any memory
		~CAudioSample();

		/// \brief Attempts to load the audio sample's audio data from a file on storage device.
		///
		/// \param sampleFilename The filename of the sample's audio data. Can be .wav, .mp3 and .ogg
		/// 
		/// If an error occured, an exception occurs
		void load(const std::string& sampleFilename);

		/// \brief Plays the audio sample
		///
		/// \param iWhichChannel Which channel to play the sample on.
		///		If the specified channel is -1, play on the first free channel.
		///		If a specific channel was requested, and there is a sample already playing there,
		///		that sample will be halted and the new sample will take its place.
		/// \param iNumberOfLoops If this is greater than zero, loop the sound that many times.
		///		If this is - 1, loop "infinitely" (~65000 times)
		void play(int iWhichChannel = -1, int iNumberOfLoops = -1);

		/// \brief Frees the audio sample data
		///
		/// If the audio sample is currently playing on any channels they will be stopped.
		void free(void);

	private:
		Mix_Chunk* _mpSampleChunk;	///< A pointer to the sample data loaded via SDL's Mix_LoadWAV function
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
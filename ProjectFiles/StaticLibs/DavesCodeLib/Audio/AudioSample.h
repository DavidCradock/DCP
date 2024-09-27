#ifndef AUDIOSAMPLE_H
#define AUDIOSAMPLE_H

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


	private:

	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
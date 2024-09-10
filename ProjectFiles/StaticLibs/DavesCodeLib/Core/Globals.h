/// \file Globals.h
/// \brief Contains global objects used throughout DCL
///
/// "Globals are bad!" Ooooo! No they are great! :)
/// We have several global variables here which are used throughout DCL.
/// 

#ifndef GLOBALS_H
#define GLOBALS_H

#include "Logging.h"	// For access to logging

namespace DCL
{

	/// \brief Class holding all globals used by DCL
	class CGlobals
	{
	public:
		/// \brief Constructor which initialises all globals
		CGlobals();

		CLog mainLog;	/// \brief Main logging file for DCL
	};

	/// \brief Globals object of CGlobals class which holds all global objects used by DCL.
	extern CGlobals gGlobals;	

}	// namespace DCL

#endif	// #ifndef FILENAME_H
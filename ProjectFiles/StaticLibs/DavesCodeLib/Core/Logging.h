/// \file Logging.h
/// \brief Contains various logging code
/// 
/// 

#ifndef LOGGING_H
#define LOGGING_H

#include "Utilities.h"
#include "Timer.h"
//#include "vector3f.h"
//#include "openGLExtensions.h"

#include <fstream>
#include <string>
#include <vector>

#include <mutex>
#include <queue>
#include <thread>

namespace DCL
{
	/// \brief A Log entry object which holds information about a single log entry. Used by the CLog class
	/// 
	/// See CLog class for more information.
	class CLogEntry
	{
	public:
		CLogEntry();

		std::string strText;	///< A string holding the text for this log entry.
		float fTimeSeconds;		///< Time since start of log file creation that log entry was added (Seconds as clock)
		int iTimeMin;			///< Time since start of log file creation that log entry was added (Minutes as clock)
		int iTimeHours;			///< Time since start of log file creation that log entry was added (Hours as clock)
		int iTimeDays;			///< Time since start of log file creation that log entry was added (Days as clock)
		int iTimeWeeks;			///< Time since start of log file creation that log entry was added (Weeks as clock)
		std::string strTime;	///< Time since start of log file creation that log entry was added, formatted to a string
	};

	/// \brief Logging of text to a text file.
	///
	/// Logging of information to a text file
	/// The default filename used for the log file is "log.txt" but can be changed with the constructor of this class, passing the filename we wish to use
	/// Example...
	/// \code
	/// CLog myLog("myLog.txt");		// Create a logging object using the given filename.
	/// 
	/// // Add an entry to the log file...
	/// myLog.add("Some text");	// Text to be added to the log entry in the file.
	/// \endcode
	/// \todo Add html output
	class CLog
	{
	public:
		/// \brief Constructor
		///
		/// Upon construction, the passed filename is deleted.
		CLog(const std::string& strFilename = "log.txt");

		/// \brief Destructor
		~CLog();

		/// \brief Add text to the log file
		///
		/// \param string Holds the text for this new log entry.
		void add(const std::string& strText);
		
		/// \brief Test method to test logging
		///
		/// Writes some text to the filename log_run_test.txt
		void run_test(void);
	private:
		std::string _mstrFilename;					///< Holds the filename of the log file passed to the constructor
		std::queue<CLogEntry> _mQueueEntriesToAdd;	///< Queue of CLogEntry objects which have been added with a call to add() which the main logging thread checks to write to a file
		std::mutex _mQueueMutex;					///< Mutex to allow access to the _mQueueEntriesToAdd in a thread safe way
		std::thread _mMainThread;					///< Main logging thread which checks the _mQueueEntriesToAdd and writes to a file and pops them from the queue.
		bool _mStop;								///< Whether to stop the main thread this class uses.
		CTimer _timer;								///< For adding time to the beginning of each entry

		/// \brief Main loop which pops log entries from the queue and writes them to a file.
		void _mainThreadLoop(void);
	};
	
	extern CLog gLogMain;	/// \brief Main logging file for DCL

	/// \brief Macro to call gGlobals.mainLog.add() passing in __FUNCTION__, __FILE__ and __LINE__
///
/// Usage:
/// \code
/// LOG("Some log info text");
/// // Will add "Some log info text 
/// \endcode
#ifndef	LOG
#define LOG(x) {								\
		std::string strLogText = x;				\
		strLogText += " Func: ";				\
		strLogText += __FUNCTION__;				\
		strLogText += " at line: ";				\
		strLogText += std::to_string(__LINE__);	\
		strLogText += " in file: ";				\
		strLogText += __FILE__;					\
		gLogMain.add(strLogText);				\
	}
#endif

}	// namespace DCL

#endif // #ifndef FILENAME_H

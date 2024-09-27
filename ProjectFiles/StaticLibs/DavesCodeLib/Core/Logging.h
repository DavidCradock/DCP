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

		std::string strText;			///< A string holding the text for this log entry.
		std::string strFunctionName;	///< A string holding the function name. Obtained from preprocessor predefined macro __FUNCTION__
		std::string strSourceFilename;	///< A string holding the source code filename. Obtained from preprocessor predefined macro __FILE__
		std::string strSourceLineNumber;///< A string holding the source code line number. Obtained from preprocessor predefined macro std::to_string(__LINE__)
		float fTimeSeconds;				///< Time since start of log file creation that log entry was added (Seconds as clock)
		int iTimeMin;					///< Time since start of log file creation that log entry was added (Minutes as clock)
		int iTimeHours;					///< Time since start of log file creation that log entry was added (Hours as clock)
		int iTimeDays;					///< Time since start of log file creation that log entry was added (Days as clock)
		int iTimeWeeks;					///< Time since start of log file creation that log entry was added (Weeks as clock)
		std::string strTime;			///< Time since start of log file creation that log entry was added, formatted to a string
	};

	/// \brief Logging of text to a text file.
	///
	/// Logging of information to a text file
	/// The default filename used for the log file is "log.html" but can be changed with the constructor of this class, passing the filename we wish to use
	/// Example...
	/// \code
	/// CLog myLog("myLog.html");		// Create a logging object using the given filename.
	/// 
	/// // Add an entry to the log file...
	/// myLog.add("Some text");	// Text to be added to the log entry in the file.
	/// \endcode
	/// 
	/// There is a macro declared below called LOG() which accepts a string which should hold some descriptive text for the log entry.
	/// This macro adds not only the text, but also the function the LOG() function is called from as well as the line number and the source code file's name.
	/// Throughout DCL, this LOG macro is called instead of calling the gLogMain object's add() method as it reduces the amount of stuff we need to type.
	/// When an exception is thrown, the macro LOG() is called to log the exception to the file.
	/// When add() is called, regardless of either directly or from the macro LOG, the actual log object is written with threading in mind, so that the call to add()
	/// has minimal overhead. The object has a main thread loop which periodically checks to see if add() has been called and writes those log entries to a file in the seperate thread.
	/// \todo Add html output
	class CLog
	{
	public:
		/// \brief Constructor
		///
		/// Upon construction, the passed filename is deleted.
		CLog(const std::string& strFilename = "log.html");

		/// \brief Destructor
		~CLog();

		/// \brief Add text to the log file
		///
		/// \param strText String holding the text for this new log entry.
		/// \param strFunctionName String holding the function name. Obtained from preprocessor predefined macro __FUNCTION__
		/// \param strLineNumber String holding the source code line number. Obtained from preprocessor predefined macro std::to_string(__LINE__)
		/// \param strSourceFilename String holding the source code filename. Obtained from preprocessor predefined macro __FILE__
		/// 
		/// Instead of having to manually call something like the following, which can get quite tedious...
		/// \code
		/// clogObject.add("DescriptiveText", __FUNCTION__, std::to_string(__LINE__), __FILE__);
		/// \endcode
		/// We have a macro which accepts just the strText variable, so we can succinctly type...
		/// \code
		/// LOG("DescriptiveText");
		/// \endcode
		/// Much easier :) Most of DCL uses this macro.
		void add(const std::string& strText, const std::string& strFunctionName, const std::string& strLineNumber, const std::string& strSourceFilename);
		
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

		/// \brief Writes header to the log file
		///
		/// Also opens the log file with the std::ios::trunc flag so that the file is cleared
		void _writeLogHeader(void);

		/// \brief Writes out the end of the html file, closing body and html tags etc
		void _writeLogFooter(void);

		/// \brief Each element of this array holds the html text to add before adding the table cell's contents (text)
		///
		/// For example, element 0 holds the following html... 
		/// <tr><td width=\"1%\"><div align=\"center\">" and then the text would be added to the file after this to be contained within the first column of the table
		/// We have the html code stored in these so that when they are added from various methods, the width settings remain consistant and we only have to change them
		/// where these strings are setup (In the constructor of CLog)
		std::string _strTableColumnText[5];
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
#define LOG(x) {																\
		gLogMain.add(x, __FUNCTION__, std::to_string(__LINE__), __FILE__);		\
	}
#endif

}	// namespace DCL

#endif // #ifndef FILENAME_H

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
	/// Logging of information to a text file and storage of each added log entry into memory.
	/// The default filename used for the log file is "log.txt" but can be changed with setLogFileName()
	/// Example...
	/// \code
	/// CLog myLog;		// Create a logging object. It'll create an empty "log.txt" file ready for use.
	/// 
	/// // If we wish to use a different name for this log file, then...
	/// myLog.setLogFileName("MyNewLogFile.txt");
	/// // The above will delete the old "log.txt" file and then create a new file named "MyNewLogFile.txt", ready for use.
	/// // This is usefull if we wish to have different log files, say perhaps one for audio, one for graphics, one for AI etc.
	/// 
	/// // Add an entry to the log file...
	/// myLog.add("Some text");	// Text to be added to the log entry in the file and in memory
	/// 
	/// // All previously added entries with add() are stored in memory and can be accessed.
	/// // Only the text is stored, not whether a new line was added, nor the time it was added.
	/// // Example looping through these...
	/// for (size_t iEntry = 0; iEntry < myLog.getNumEntries(); iEntry++)
	/// {
	///		// Get the text for the indexed entry
	///		// If iEntry is out of bounds, an exception occurs.
	///		std::string strEntryText = myLog.getEntry(iEntry);
	/// 
	///		// Do something with the log entry text here.
	/// }
	/// \endcode
	class CLog
	{
	public:
		/// \brief Default constructor.
		///
		/// Sets the log file name to "log.txt" and clears the file.
		CLog();

		/// \brief Add text to the log file and entries in memory
		///
		/// \param string Holds the text for this new log entry.
		void add(const std::string& string);

		/// \brief Clear the log file and all log entries in memory
		void clear(void);

		/// \brief Deletes the current log file.
		///
		/// \return Whether deletion was successfull.
		/// 
		/// Whatever the currently set log file name is set to, attempts to delete that file.
		/// Returns true if the deletion was successfull, else false.
		bool deleteLogFile(void);

		/// \brief Sets the log file name of the log file.
		///
		/// \param strFilename The filename to use for the log file.
		/// 
		/// Will attempt to delete the current log file by calling deleteLogFile() before creating the newly named one.
		/// Also clears the newly named file.
		void setLogFileName(const std::string& strFilename = "log.txt");

		/// \brief Return number of entries added via add()
		///
		/// \return The current number of entries added via add()
		size_t getNumEntries(void) const;

		/// \brief Returns a log entry's text string.
		///
		/// \param entryIndex The index of the entry
		/// \return A string holding the entry's text.
		/// 
		/// If entryIndex is out of bounds, an exception occurs
		std::string getEntryText(size_t entryIndex) const;

		/// \brief Returns a log entry's time it was added since the log file was created as a formatted string
		/// 
		/// \param entryIndex The index of the entry
		/// \return A string which represents the time since the log file was created, which the entry was added.
		/// 
		/// If entryIndex is out of bounds, an exception occurs
		std::string getEntryTime(size_t entryIndex) const;

		/// \brief Stores a log entry's time it was added since the log file was created to the passed variables.
		/// 
		/// \param entryIndex
		/// \param[out] fSecondsOut Holds the number of seconds.
		/// \param[out] iMinutesOut Holds the number of minutes.
		/// \param[out] iHoursOut Holds the number of hours.
		/// \param[out] iDaysOut Holds the number of days.
		/// \param[out] iWeeksOut Holds the number of weeks.
		/// 
		/// If entryIndex is out of bounds, an exception occurs
		void getEntryTimes(size_t entryIndex, float &fSecondsOut, int &iMinutesOut, int &iHoursOut, int &iDaysOut, int &iWeeksOut) const;

		/// \brief Returns a log entry.
		///
		/// \param entryIndex The index of the entry
		/// \return The found log entry.
		/// 
		/// If entryIndex is out of bounds, an exception occurs
		CLogEntry getEntry(size_t entryIndex) const;

	private:
		std::string _mstrLogFilename;			///< Holds the filename used for the log file. By default, this is "log.txt"
		std::vector<CLogEntry> _mlogEntries;	///< A vector of CLogEntry objects, to hold each entry added by add() method
		CTimer _timer;							///< For adding time to the beginning of each entry
	};

}	// namespace DCL

#endif // #ifndef FILENAME_H
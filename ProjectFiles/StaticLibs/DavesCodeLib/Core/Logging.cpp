#include "Logging.h"
#include "Exceptions.h"
#include <filesystem>

namespace DCL
{
	CLogEntry::CLogEntry()
	{
		fTimeSeconds = 0.0f;
		iTimeMin = 0;
		iTimeHours = 0;
		iTimeDays = 0;
		iTimeWeeks = 0;

	}

	CLog::CLog()
	{
		_mstrLogFilename = "log.txt";
		clear();
	}

	void CLog::add(const std::string& string)
	{
		CLogEntry logEntry;
	
		std::fstream fs;
		fs.open(_mstrLogFilename, std::ios::out | std::ios::app);

		// Store the given string in the log entry
		logEntry.strText = string;

		// Store current runtime in the log entry
		_timer.update();
		_timer.getClock(logEntry.fTimeSeconds, logEntry.iTimeMin, logEntry.iTimeHours, logEntry.iTimeDays, logEntry.iTimeWeeks);

		// Create the current runtime as a string in the log entry
		logEntry.strTime += std::to_string(logEntry.iTimeWeeks) + "w:";
		logEntry.strTime += std::to_string(logEntry.iTimeDays) + "d:";
		logEntry.strTime += std::to_string(logEntry.iTimeHours) + "h:";
		logEntry.strTime += std::to_string(logEntry.iTimeMin) + "m:";
		if (logEntry.fTimeSeconds < 10.0f)
			logEntry.strTime += "0";
		logEntry.strTime += std::to_string(int(logEntry.fTimeSeconds)) + "s : ";

		// Output time string to file
		fs << logEntry.strTime.c_str();

		// Output the log entry's text to the file
		fs << string.c_str();
		fs << "\n";
		fs.close();

		// Store the log entry in memory for future access.
		_mlogEntries.push_back(logEntry);
	}

	void CLog::clear(void)
	{
		std::fstream fs;
		fs.open(_mstrLogFilename, std::ios::out | std::ios::trunc);
		fs.close();
		_mlogEntries.clear();
	}

	bool CLog::deleteLogFile(void)
	{
		const std::filesystem::path file_path(_mstrLogFilename);

		try
		{
			if (std::filesystem::exists(file_path))
			{
				std::filesystem::remove(file_path);
				//std::cout << "File deleted successfully." << std::endl;
			}
			else
			{
				//std::cerr << "File does not exist." << std::endl;
			}
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			//std::cerr << "Error deleting file: " << e.what() << std::endl;
			std::string strError = "Error deleting file: ";
			strError += e.what();
			add(strError);
			return false;
		}
		return true;
	}

	void CLog::setLogFileName(const std::string& strLogFileName)
	{
		deleteLogFile();

		_mstrLogFilename = strLogFileName;
		clear();
	}

	size_t CLog::getNumEntries(void) const
	{
		return _mlogEntries.size();
	}

	std::string CLog::getEntryText(size_t entryIndex) const
	{
		ThrowIfTrue(entryIndex >= _mlogEntries.size(), "CLog::getEntryText() with given index of " + std::to_string(entryIndex) + " failed as given index is invalid.");
		return _mlogEntries[entryIndex].strText;
	}

	std::string CLog::getEntryTime(size_t entryIndex) const
	{
		ThrowIfTrue(entryIndex >= _mlogEntries.size(), "CLog::getEntryTime() with given index of " + std::to_string(entryIndex) + " failed as given index is invalid.");
		return _mlogEntries[entryIndex].strTime;
	}

	void CLog::getEntryTimes(size_t entryIndex, float& fSecondsOut, int& iMinutesOut, int& iHoursOut, int& iDaysOut, int& iWeeksOut) const
	{
		ThrowIfTrue(entryIndex >= _mlogEntries.size(), "CLog::getEntryTimes() with given index of " + std::to_string(entryIndex) + " failed as given index is invalid.");
		fSecondsOut = _mlogEntries[entryIndex].fTimeSeconds;
		iMinutesOut = _mlogEntries[entryIndex].iTimeMin;
		iHoursOut = _mlogEntries[entryIndex].iTimeHours;
		iDaysOut = _mlogEntries[entryIndex].iTimeDays;
		iWeeksOut = _mlogEntries[entryIndex].iTimeWeeks;
	}

	CLogEntry CLog::getEntry(size_t entryIndex) const
	{
		ThrowIfTrue(entryIndex >= _mlogEntries.size(), "CLog::getEntry() with given index of " + std::to_string(entryIndex) + " failed as given index is invalid.");
		return _mlogEntries[entryIndex];
	}

}	// namespace DCL
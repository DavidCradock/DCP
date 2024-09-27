#include "Logging.h"
#include "Exceptions.h"
#include "StringUtils.h"
#include <filesystem>
#include "Utilities.h"

namespace DCL
{
	CLog gLogMain;	/// \brief Main logging file for DCL

	CLogEntry::CLogEntry()
	{
		fTimeSeconds = 0.0f;
		iTimeMin = 0;
		iTimeHours = 0;
		iTimeDays = 0;
		iTimeWeeks = 0;
	}

	CLog::CLog(const std::string& strFilename)
	{
		_mstrFilename = strFilename;
		_mStop = false;

		// Set private html code used when writing each column of each row in the table to the html file.
		// The contents of each cell in the table is written to the file after each one of these strings.
		_strTableColumnText[0] = "<tr><td width=\"1%\"><div align=\"center\">";
		_strTableColumnText[1] = "</div></td><td width=\"20%\"><div align=\"center\">";
		_strTableColumnText[2] = "</div></td><td width=\"20%\"><div align=\"center\">";
		_strTableColumnText[3] = "</div></td><td width=\"1%\"><div align=\"center\">";
		_strTableColumnText[4] = "</div></td><td width=\"20%\"><div align=\"center\">";

		_writeLogHeader();

		_mMainThread = std::thread(&CLog::_mainThreadLoop, this);

		std::string strEntryText = "CLog::CLog(\"";
		strEntryText += strFilename;
		strEntryText += "\") called.";
		LOG(strEntryText);
	}

	CLog::~CLog()
	{
		_mStop = true;
		_mMainThread.join();

		_writeLogFooter();
	}

	void CLog::add(const std::string& strText, const std::string& strFunctionName, const std::string& strLineNumber, const std::string& strSourceFilename)
	{
		_mQueueMutex.lock();

		CLogEntry entry;
		entry.strText = strText;
		entry.strFunctionName = strFunctionName;
		entry.strSourceFilename = strSourceFilename;
		entry.strSourceLineNumber = strLineNumber;

		// Compute time related stuff
		_timer.update();
		_timer.getClock(entry.fTimeSeconds, entry.iTimeMin, entry.iTimeHours, entry.iTimeDays, entry.iTimeWeeks);

		// Create the current runtime as a string in the log entry
		entry.strTime += std::to_string(entry.iTimeWeeks) + "w:";
		entry.strTime += std::to_string(entry.iTimeDays) + "d:";
		entry.strTime += std::to_string(entry.iTimeHours) + "h:";
		entry.strTime += std::to_string(entry.iTimeMin) + "m:";
		if (entry.fTimeSeconds < 10.0f)
			entry.strTime += "0";
		entry.strTime += std::to_string(float(entry.fTimeSeconds)) + "s";

		// Add entry to the queue
		_mQueueEntriesToAdd.push(entry);

		_mQueueMutex.unlock();
	}

	void CLog::_mainThreadLoop(void)
	{
		bool bLogToSave = false;
		CLogEntry logToSave;

		while (!_mStop)	// This gets set to true in the destructor
		{
			// Determine whether there's at least one log entry in the queue
			// If so, copy it ready to save to file.
			// We perform the minimal of stuff here to help prevent locking the mutex which could slow down calls to add()
			bLogToSave = false;
			_mQueueMutex.lock();
			if (!_mQueueEntriesToAdd.empty())
			{
				bLogToSave = true;
				logToSave = _mQueueEntriesToAdd.front();
				_mQueueEntriesToAdd.pop();
			}
			_mQueueMutex.unlock();

			// If there is a log entry, save it to file
			if (bLogToSave)
			{
				std::ofstream file(_mstrFilename, std::ios::app);
				if (file.is_open())
				{
					file << _strTableColumnText[0] << logToSave.strTime;
					file << _strTableColumnText[1] << logToSave.strText;
					file << _strTableColumnText[2] << logToSave.strFunctionName;
					file << _strTableColumnText[3] << logToSave.strSourceLineNumber;
					file << _strTableColumnText[4] << logToSave.strSourceFilename;
					file << "</div></td></tr>\n";
				}
				else
				{
				}
			}
			else
			{
				// If there wasn't a log entry to save, let's sleep for a bit.
				// Not sleeping due to there being a log entry makes it so that on the next
				// loop is fast and allows us to prevent entries from queueing up.
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}

	}

	void CLog::run_test(void)
	{
		CLog logger("log_run_test.txt");
		std::thread t1([&logger]()
			{
				for (int i = 0; i < 100; ++i) {
					logger.add("Thread 1: Message " + std::to_string(i), __FUNCTION__, std::to_string(__LINE__), __FILE__);
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			});

		std::thread t2([&logger]() {
			for (int i = 0; i < 100; ++i) {
				logger.add("Thread 2: Message " + std::to_string(i), __FUNCTION__, std::to_string(__LINE__), __FILE__);
				std::this_thread::sleep_for(std::chrono::milliseconds(15));
			}
			});

		t1.join();
		t2.join();
	}

	void CLog::_writeLogHeader(void)
	{
		// Clear file and add header
		std::ofstream file(_mstrFilename, std::ios::trunc);
		// Write styles and start body
		file << "<html>\n<head>\n<style>\n";
		file << "body {	background-color: rgba(50, 50, 50, 1.0); color: rgba(255, 255, 255, 1.0); }\n";
		file << "tr:nth-child(even) { background-color: rgba(100, 100, 100, 0.8); color: rgba(250, 250, 250, 1.0); }\n";
		file << "tr:nth-child(odd) { background-color: rgba(150, 150, 150, 0.8); color: rgba(250, 250, 250, 1.0); }\n";
		file << "</style>\n</head>\n<body>";
		
		// Write heading
		file << "<h1 style = \"text-align:center\">" << _mstrFilename << "</h1>\n";

		// Write system information after the heading, but before the main table begins
		// RAM usage of process
		SMemInfo memInfo;
		getMemInfo(memInfo);
		double dMBUsedByProcess = memInfo.proc.iWorkingSetSize / (1024.0 * 1024.0);
		file << "RAM used by process: " << std::to_string(dMBUsedByProcess) << "MB\n";

		file << "<br>\n";

		// Number of CPU logical cores
		file << "Number of logical CPU cores: " << std::to_string(getCPULogicalCores()) << "\n";

		// Write begin table and write first row with headings for each column
		file << "<table width=\"100%\" border=\"0\">\n";
		file << _strTableColumnText[0] << "TIME";
		file << _strTableColumnText[1] << "DESCRIPTION";
		file << _strTableColumnText[2] << "NAMESPACE:CLASS:METHOD";
		file << _strTableColumnText[3] << "LINE NUMBER";
		file << _strTableColumnText[4] << "SOURCE FILENAME";
		file << "</div></td></tr>\n";

		
	}

	void CLog::_writeLogFooter(void)
	{
		std::ofstream file(_mstrFilename, std::ios::app);
		// End table, body and html tags
		file << "</table>\n</body>\n</html>\n";
		file.close();
	}

	

}	// namespace DCL
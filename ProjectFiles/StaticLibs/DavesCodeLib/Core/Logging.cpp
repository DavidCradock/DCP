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

	CLog::CLog(const std::string& strFilename)
	{
		_mstrFilename = strFilename;
		_mStop = false;
		std::string strEntryText = "CLog::CLog(\"";
		strEntryText += strFilename;
		strEntryText += "\") called.";

		// Clear file
		std::fstream fs;
		fs.open(_mstrFilename, std::ios::out | std::ios::trunc);
		fs.close();

		add(strEntryText);
		_mMainThread = std::thread(&CLog::_mainThreadLoop, this);
	}

	CLog::~CLog()
	{
		_mStop = true;
		_mMainThread.join();
	}

	void CLog::add(const std::string& strText)
	{
		_mQueueMutex.lock();

		CLogEntry entry;
		entry.strText = strText;

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
		entry.strTime += std::to_string(float(entry.fTimeSeconds)) + "s : ";

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
					// Output time string to file
					file << logToSave.strTime.c_str();
					// Output the log entry's text to the file
					file << logToSave.strText.c_str() << std::endl;
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
				logger.add("Thread 1: Message " + std::to_string(i));
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			});

		std::thread t2([&logger]() {
			for (int i = 0; i < 100; ++i) {
				logger.add("Thread 2: Message " + std::to_string(i));
				std::this_thread::sleep_for(std::chrono::milliseconds(15));
			}
			});

		t1.join();
		t2.join();
	}

	CLog gLogMain;	/// \brief Main logging file for DCL

}	// namespace DCL
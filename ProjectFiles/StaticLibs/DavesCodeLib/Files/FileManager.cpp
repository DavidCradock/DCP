#include "FileManager.h"

namespace DCL
{
	/// \brief Global instance of CFileManager
	/// 
	/// I did originally set this class to be a singleton, but I try to avoid singletons where possible
	/// due to them limiting the class only being able to have one instance.
	/// So instead, I converted the class to a non-singleton and declared this global instance which is used
	/// in various places.
	CFileManager gFileManager;

	CFileManager::CFileManager()
	{
		LOG("Constructor called.");
	}

	void CFileManager::writeString(std::ofstream& file, std::string& strString) const
	{
		ThrowIfFalse(file.is_open(), "CFileManager::write() failed. The given ofstream is not open.");
		ThrowIfTrue(file.bad(), "CFileManager::write() failed. The given ofstream is bad.");

		// Write out length of string
		size_t stringLength = strString.size();
		file.write((char*)&stringLength, sizeof(size_t));

		// Write out characters
		file.write(strString.c_str(), stringLength);

		ThrowIfTrue(file.bad(), "CFileManager::write() failed. The given ofstream is bad.");
	}

	void CFileManager::readString(std::ifstream& file, std::string& strString) const
	{
		ThrowIfFalse(file.is_open(), "CFileManager::read() failed. The given ifstream is not open.");
		ThrowIfTrue(file.bad(), "CFileManager::read() failed. The given ifstream is bad.");

		// Read in length of string
		size_t stringLength;
		file.read((char*)&stringLength, sizeof(size_t));

		// Read in characters
		char* charTemp = new char[stringLength];
		ThrowIfFalse(charTemp, "CFileManager::read() failed. Temporary memory allocation failed.");
		file.read(charTemp, stringLength);
		ThrowIfTrue(file.bad(), "CFileManager::read() failed. The given ifstream is bad.");

		strString.clear();
		strString.append(charTemp);
		delete[] charTemp;
	}

	bool CFileManager::getFileExists(const std::string& strFilename) const
	{
		/*
		FILE* f;
		if (fopen_s(&f, strFilename.c_str(), "rb"))
			return false;
		fclose(f);
		return true;
		*/
		bool bExists = false;
		std::ifstream file(strFilename);
		if (file.is_open())
		{
			bExists = true;
			file.close();
		}
		return bExists;
	}

	bool CFileManager::deleteFile(const std::string& strFilenameToDelete) const
	{
		std::remove(strFilenameToDelete.c_str());
		return !getFileExists(strFilenameToDelete);
	}

	bool CFileManager::renameFile(const std::string& strOldFilename, const std::string& strNewFilename) const
	{
		if (0 == std::rename(strOldFilename.c_str(), strNewFilename.c_str()))
			return true;
		return false;
	}
}	// namespace DCL
/// \file FileManager.h
/// \brief Brief description for the file goes here.
///
/// Detailed description text goes here.

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../Core/Exceptions.h"
#include <string>
#include <fstream>

namespace DCL
{
	/// \brief File manager responsible for dealing with files.
	///
	/// Lots of file helper methods in here as well as managing compressed archive files.
	/// \todo Check and modify, lots to add here!
	class CFileManager
	{
	public:
		/// \brief Constructor, does nothing.
		CFileManager();

		/// \brief Helper method to write the given string to an already opened ofstream in binary mode.
		///
		/// \param file An already opened std::ofstream
		/// \param strString The string to write to the file.
		/// 
		/// If the given ofstream is not opened or an error occurred, an exception occurs
		void writeString(std::ofstream& file, std::string& strString) const;

		/// \brief Helper method to read a string from an already opened ifstream in binary mode.
		///
		/// \param file An already opened std::ifstream
		/// \param strString The string to read from the file.
		/// 
		/// If the given ifstream is not opened or an error occurred, an exception occurs
		/// The given string is cleared before being set.
		void readString(std::ifstream& file, std::string& strString) const;

		/// \brief Helper method. Returns true if the given filename exists on storage device
		///
		/// \param strFilename The filename to check for
		/// \return True if the named file exists, else false.
		bool getFileExists(const std::string& strFilename) const;

		/// \brief Read a type from an already opened ifstream in binary mode.
		///
		/// \param file An already opened std::ifstream
		/// \param data This will hold the data being read from the stream.
		/// 
		/// If the given ifstream is not opened or an error occurred, an exception occurs
		/// returns false if an error occurred.
		template <class Type> void read(std::ifstream& file, Type& data);

		/// \brief Write a type to an already opened ofstream in binary mode.
		/// 
		/// \param file An already opened std::ofstream
		/// \param data This is what will be written to the ofstream.
		/// 
		/// If the given ofstream is not opened or an error occurred, an exception occurs
		/// returns false if an error occurred.
		template <class Type> void write(std::ofstream& file, Type& data);

		/// \brief Attempts to delete the given file name.
		///
		/// \param strFilenameToDelete The filename to delete
		/// \return True if the file was deleted, else false.
		/// 
		/// If the file still exists after attempting to delete it, this method returns false, else true
		bool deleteFile(const std::string& strFilenameToDelete) const;

		/// \brief Attempts to rename the given file name to the new filename.
		/// 
		/// \param strOldFilename The current name of the file to rename
		/// \param strNewFilename The name to be given to the renamed file.
		/// \return Whether the operation was a success or not
		bool renameFile(const std::string& strOldFilename, const std::string& strNewFilename) const;
	};

	/// \brief Global instance of CFileManager
	/// 
	/// I did originally set this class to be a singleton, but I try to avoid singletons where possible
	/// due to them limiting the class only being able to have one instance.
	/// So instead, I converted the class to a non-singleton and declared this global instance which is used
	/// in various places.
	extern CFileManager gFileManager;

	template<class Type> void CFileManager::read(std::ifstream& file, Type& data)
	{
		ThrowIfFalse(file.is_open(), "CFileManager::read() failed. The given ifstream is not open.");
		ThrowIfTrue(file.bad(), "CFileManager::read() failed. The given ifstream is bad.");

		size_t stTypeSize = sizeof(Type);
		file.read((char*)&data, stTypeSize);
		ThrowIfTrue(file.bad(), "CFileManager::read() failed. The given ifstream is bad.");
	}

	template<class Type> void CFileManager::write(std::ofstream& file, Type& data)
	{
		ThrowIfFalse(file.is_open(), "CFileManager::write() failed. The given ofstream is not open.");
		ThrowIfTrue(file.bad(), "CFileManager::write() failed. The given ofstream is bad.");

		size_t stTypeSize = sizeof(Type);
		file.write((char*)&data, stTypeSize);
		ThrowIfTrue(file.bad(), "CFileManager::write() failed. The given ofstream is bad.");
	}

}	// namespace DCL

#endif	// #ifndef FILENAME_H

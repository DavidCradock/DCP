/// \file FileMemory.h
/// \brief Brief description for the file goes here.
///
/// Detailed description text goes here.

#ifndef FILEMEMORY_H
#define FILEMEMORY_H

//#include "../Core/Exceptions.h"
//#include "../Core/Singleton.h"
#include <string>
//#include <fstream>

namespace DCL
{
	/// \brief A FileMemory object holds the entirety of a file in memory
	class CFileMemory
	{
	public:
		/// \brief Constructor. Sets data to 0
		CFileMemory();

		/// \brief Destructor. Deletes data if there is any.
		~CFileMemory();

		/// \brief Frees all data and resets everything
		void free(void);

		/// \brief Loads data from a file stored on storage device into this object
		///
		/// \param strFilename The name of the filename to load into memory, inside this object.
		/// 
		/// If something went wrong, an exception occurs
		/// Use X::getFileExists() to determine whether the file exists prior to calling this
		void setFromFile(const std::string& strFilename);

		/// \brief Sets data from given pointer and size
		///
		/// \param pData A pointer to an array holding the data to copy to this object
		/// \param stDataLength The length of the data to copy from the given pointer.
		/// 
		// If something went wrong, an exception occurs
		void setFromMem(const char* pData, size_t stDataLength);

		/// \brief Attempts to save the contents of this object to a file on storage device
		///
		/// \param strFilename The file name to save the data of this object to.
		/// 
		/// If something went wrong, an exception occurs.
		/// The named file is overwritten.
		void saveToFile(const std::string& strFilename);

		/// \brief Attempts to append the contents of this object to an already opened file on storage device
		///
		/// \param file An already opened ofstream object.
		/// 
		// If something went wrong, an exception occurs.
		void appendToFile(std::ofstream& file);

		/// \brief Gets a pointer to the beginning of the file data stored in memory
		///
		/// \return A pointer to the data in this object.
		/// 
		/// May be 0 if no data exists in the object.
		char* getData(void);

		/// \brief Returns the size of the data stored in memory in bytes
		///
		/// \return The size of the data stored inside this object.
		/// 
		/// May be 0 if no data exists in the object.
		size_t getDataSize(void);

		/// \brief Set seek position to the start of the data stored in this object
		void seekBegin(void);

		/// \brief Set seek position to the end of the data stored in this object, the last byte.
		///
		/// So calling this and then calling seekGetPos() would return the size of the data minus 1.
		void seekEnd(void);

		/// \brief Sets seek position by the given offset from the start of this object's data.
		///
		/// \param stOffsetBytesFromStart The offset from the beginning of this object's data in bytes.
		/// \return False if the given offset goes past the end, else true.
		/// 
		/// If error occurred, sets _mbIsOK to false which can be checked with isOK() if the new seek position is invalid.
		bool seekToPos(size_t stOffsetBytesFromStart);

		/// \brief Offsets the current seek position from the current position by the specified amount in bytes.
		///
		/// \param stOffsetBytes The number of bytes to move the seek position in bytes.
		/// \return False if the given offset would move the new position past the end of the data of the object.
		/// 
		/// If error occurred, sets _mbIsOK to false which can be checked with isOK() if the new seek position is invalid.
		bool seekOffset(size_t stOffsetBytes);

		/// \brief Returns the current seek position in bytes.
		///
		/// \return The current seek position in bytes
		size_t seekGetPos(void);

		/// \brief Read a type from this object's data and move the seek position forward.
		///
		/// \param out This is a type that will hold the data being read from the file.
		/// \return False if the type could not be read.
		/// 
		/// If error occurred, sets _mbIsOK to false which can be checked with isOK().
		template <class Type> bool read(Type& out);

		/// \brief Returns whether an error occurred either due to seeking to an invalid position or read() failing
		///
		/// \return True if everything has been OK since construction or since last call to reset()
		bool isOK(void);

		/// \brief Resets any errors so isOK() will return true again and resets seek position to beginning by calling seekBegin().
		void reset(void);
	private:

		char* _mpchDataStart;		///< Bytes of data
		size_t _mstDataSizeBytes;	///< Size of data in bytes

		char* _mpchSeekData;		///< Pointer to data at current offset
		size_t _mstSeekPos;			///< Current offset in bytes

		bool _mbIsOK;				///< Has there been a failure? Either by seeking to incorrect position or read() failing
	};

	template<class Type> bool CFileMemory::read(Type& out)
	{
		size_t stTypeSize = sizeof(Type);

		// Past end of array?
		if (_mstSeekPos + stTypeSize > _mstDataSizeBytes)
		{
			_mbIsOK = false;
			return false;
		}

		// Store value
		out = *(Type*)_mpchSeekData;

		// Increment pointer and position
		_mpchSeekData += stTypeSize;
		_mstSeekPos += stTypeSize;
		return true;
	}

}	// namespace DCL

#endif	// #ifndef FILENAME_H

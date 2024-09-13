/// \file Exceptions.h
/// \brief Contains error handling code and macros to deal with errors, warnings and logging of information to a log file.
/// 
/// How we deal with error handling in Dave's Code Library.
/// 
/// We use exceptions. Although they introduce a slight performance penalty, they greatly simplify error handling.
/// We use various macros found in this file which are used throughout the codebase to log the status of things happening to a log file, and deal with unrecoverable, exceptional errors 
/// The macros in here log information using the CLog class found in Core/Logging.h
/// 
/// The macros reduce the amount of code we have to write everywhere and do stuff such as checking for critical errors, automatically shutting down the process and writing information to a log file.
///
/// Within our main program loop somewhere, we'd do the following...
/// \code
/// try
/// {
///		// Main loop would go here
/// }
/// catch (CException &exception)
/// {
///		// Deal with the exception somehow...
///		x->pLog->add(exception.mstrException, true);
///		std::wstring strw = StringUtils::stringToWide(exception.mstrException);
///		MessageBox(x->pWindow->getWindowHandle(), strw.c_str(), L"Sorry, an exception has been thrown...", MB_OK);
///		__debugbreak();
/// }
/// \endcode

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "Logging.h"

namespace DCL
{
	/// \brief An exception containing information about what went wrong.
	///
	/// Gets thrown via the ThrowIfFalse/True/ThrowIfMemoryNotAllocated macros below
	class CException
	{
	public:
		/// \brief Constructor accepting a string describing the exceptional circumstance why the unrecoverable error occurred and two additional
		/// parameters for the source code file name and line number where the exception is thrown. These can of course be added manually using __FILE__ and __LINE__,
		/// but it's easier to use the various macros which fill these in for us.
		/// 
		/// \param strExceptionText A string describing the exceptional circumstance why the unrecoverable error occurred.
		/// \param strFilename A string holding the filename in which the exception was constructed
		/// \param iLineNumber An int holding the line number in the source code in which the exception was constructed
		CException(const std::string& strText, const std::string& strFunctionName, const std::string& strLineNumber, const std::string& strSourceFilename)
		{
			mstrException = "Description: " + strText + "\n";
			mstrException += "Function: " + strFunctionName + "\n";
			mstrException += "Line number: " + strLineNumber + "\n";
			mstrException += "Source Filename: " + strSourceFilename + "\n";

			// Log the exception to the global log file
			std::string strLog("Exception Thrown! ");
			strLog += strText;
			gLogMain.add(strLog, strFunctionName, strLineNumber, strSourceFilename);
		}
		std::string mstrException;	///< String holding the complete text of the exception.
	};

#ifndef _DEBUG

#ifndef Throw
/// \brief Macro to throw an exception which adds filename, line number and the given text.
#define Throw(y)									\
		{											\
		throw CException(y, __FUNCTION__, std::to_string(__LINE__), __FILE__);	\
		}
#endif

#ifndef ThrowIfFalse
/// \brief Macro to check a bool and if false, throw an exception which adds filename, line number and the given text.
#define ThrowIfFalse(x, y)							\
		{											\
		if(!x){										\
		throw CException(y, __FUNCTION__, std::to_string(__LINE__), __FILE__);}	\
		}
#endif

#ifndef ThrowIfTrue
/// \brief Macro to check a bool and is true, throw an exception which adds filename, line number and the given text.
#define ThrowIfTrue(x, y)							\
		{											\
		if(x){										\
		throw CException(y, __FUNCTION__, std::to_string(__LINE__), __FILE__);}	\
		}
#endif

#ifndef ThrowIfMemoryNotAllocated
/// \brief Macro to check a pointer and if 0, throw an exception stating that the memory was not allocated with filename and line number.
#define ThrowIfMemoryNotAllocated(x)											\
			{																	\
			if(!x){																\
			throw CException("Memory allocation error.", __FUNCTION__, std::to_string(__LINE__), __FILE__);}	\
			}
#endif

#else
#ifndef Throw
/// \brief Macro to throw an exception which adds filename, line number and the given text.
#define Throw(y)									\
		{											\
		__debugbreak();								\
		throw CException(y, __FUNCTION__, std::to_string(__LINE__), __FILE__);	\
		}
#endif

#ifndef ThrowIfFalse
/// \brief Macro to check a bool and if false, throw an exception which adds filename, line number and the given text.
#define ThrowIfFalse(x, y)							\
		{											\
		if(!x){										\
 		__debugbreak();								\
		throw CException(y, __FUNCTION__, std::to_string(__LINE__), __FILE__);}	\
		}
#endif

#ifndef ThrowIfTrue
/// \brief Macro to check a bool and is true, throw an exception which adds filename, line number and the given text.
#define ThrowIfTrue(x, y)							\
		{											\
		if(x){										\
 		__debugbreak();								\
		throw CException(y, __FUNCTION__, std::to_string(__LINE__), __FILE__);}	\
		}
#endif

#ifndef ThrowIfMemoryNotAllocated
/// \brief Macro to check a pointer and if 0, throw an exception stating that the memory was not allocated with filename and line number.
#define ThrowIfMemoryNotAllocated(x)											\
			{																	\
			if(!x){																\
 			__debugbreak();														\
			throw CException("Memory allocation error.", __FUNCTION__, std::to_string(__LINE__), __FILE__);}	\
			}
#endif

#endif	// #ifndef _DEBUG


}   // namespace DCL

#endif // #ifndef FILENAME_H

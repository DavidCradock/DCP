/// \file NewFileTemplate.h
/// \brief Brief description for the file goes here.
///
/// Detailed description text goes here.
/// This file does nothing other than to demonstate how to document the code for the awesome app, Doxygen.
/// It's also quite useful as a header file template which we can copy and paste into a newly created header file to save us some time.

#ifndef NEWFILE_TEMPLATE_H
#define NEWFILE_TEMPLATE_H

namespace DCL
{
	/// \brief Brief description text goes here
	///
	/// Detailed description goes here
	/// \code
	/// int iSomeCode = 0;
	/// \endcode
	class CNewClassTemplate
	{
	public:
		/// \brief Brief description text goes here
		///
		/// \param paramName Description of parameter goes here
		/// \param[in, out] paramINOUT Specifies in or out, or both for a parameter that's either a pointer or a reference
		/// \return What the method returns, if anything.
		/// 
		/// Detailed description text goes here
		int someMethod(int paramName, int& paramINOUT)
		{
			return 0;
		}

		float fSomeMember;		///< \brief A public member

	private:
		float _mfSomePrivateMember;	///< \brief A private member

		/// \brief Some private method
		void _privateMethod(void);
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
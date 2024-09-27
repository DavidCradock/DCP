#ifndef SINGLETON_H
#define SINGLETON_H

namespace DCL
{
	/// \brief Singleton class to inherit from.
	///
	/// Usage:
	/// Create a class from this template class with something like...
	/// \code
	/// class MyClass : public CSingleton<MyClass>
	/// {
	///		// Rest of class declaration here
	/// }
	/// \endcode
	/// From then on, whenever we create an object of MyClass like normal, it only has one instance, all variables are shared.
	/// To create a pointer to the singleton...
	/// \code
	/// MyClass *pMyClass = MyClass::getPointer();
	/// // Then you can access all the public stuff with something like...
	/// pMyClass->someMethod();
	/// \endcode
	template <class T>
	class CSingleton
	{
	public:
		virtual ~CSingleton()
		{
			if (pInstance)
			{
				delete pInstance;
				pInstance = 0;
			}
		}

		/// \brief Obtain pointer to class object
		///
		/// \return A pointer to the single instance of the class.
		/// 
		/// If not yet created, the object will be created here and it's constructor called 
		static T* getPointer(void)
		{
			if (!pInstance)
			{
				pInstance = new T();
			}
			return pInstance;
		}

	protected:
		static T* pInstance;	///< A pointer holding the single instance
	};
	template <class T> T* CSingleton<T>::pInstance = 0;

}	// namespace DCL

#endif	// #ifndef FILENAME_H
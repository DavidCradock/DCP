/// \file Utilities.h
/// \brief Contains various utility functions.
/// 
/// 

#ifndef UTILITIES_H
#define UTILITIES_H

#include "Timer.h"

namespace DCL
{
	/// \brief Due to floating point errors, we use this to determine whether two floating points are roughly equal
	const float kfEpsilon = 0.0000001f;

	/// \brief Returns true if parsed values have a difference of less than kfEpsilon
	///
	/// \param A The first floating point value to compare
	/// \param B The second floating point value to compare
	/// \return Whether both given floating point values are roughly equal (To within kfEpsilon)
	inline bool areFloatsEqual(const float& A, const float& B)
	{
		return (fabsf(A - B) < kfEpsilon);
	}

	/// \brief Due to floating point errors with doubles, we use this to determine whether two doubles points are roughly equal
	const double kdEpsilon = 0.000000000000001f;
	
	/// \brief Returns true if parsed values have a difference of less than kdEpsilon
	/// 
	/// \param A The first double value to compare
	/// \param B The second double point value to compare
	/// \return Whether both given double values are roughly equal (To within kdEpsilon)
	inline bool areDoublesEqual(const double& A, const double& B)
	{
		return (abs(A - B) < kdEpsilon);
	}

	/// \brief Interpolate between two given values, given a position value between 0.0f and 1.0f
	///
	/// \param fValA The first value to interpolate between
	/// \param fValB The second value to interpolate between
	/// \param fPosition The position between fValA and fValB ranging from 0.0 and 1.0
	/// \return The interpolated value
	inline float interpolate(float fValA, float fValB, float fPosition)
	{
		float fDiff = fValA - fValB;
		fDiff *= -1.0f;
		return fValA + (fDiff * fPosition);
	}

	/// \brief Sigmoid function
	/// 
	/// \param dValue The value to position upon an S curve
	/// \param dResponse The shape of the S curve
	/// \return The computed value
	/// 
	/// Given a value, takes that and scales it so that the values lie upon an S curve.
	/// dResponse curve specified the shape of the curve.
	/// Higher values, flatten the curve, lower ones tighten it.
	/// A default value of 1 is usually used.
	/// Do not set it to zero, this'll create a divide by zero error.
	inline double sigmoid(double dValue, double dResponse = 1)
	{
		// The sigmoid function looks like this...
		// 1 / 1 + (e to the power of(-dValue / dResponse));
		// Where e is a math constant, which is roughly 2.7183
		// We use exp() to compute the exponential value of (-dValue / dResponse)
		return (1 / (1 + exp(-dValue / dResponse)));
	}

	/// \brief Sigmoid function
	///
	/// \param dValue The value to position upon an S curve
	/// \return The computed value
	/// 
	/// Given a value, takes that and scales it so that the values lie upon an S curve.
	/// This does not have the ability to set the shape of the S curve, but it is 
	/// slightly faster as there is no divide.
	inline double sigmoid(double dValue)
	{
		return 1 / (1 + exp(-dValue));
	}

	/// \brief  Returns true if the given disk filename exists.
	///
	/// \param strFilename The name of the file to determine whether it exists.
	/// \return Whether the file exists or not.
	bool getFileExists(const std::string& strFilename);

	/// \brief Converts the contents of a file into an array, stored inside a text header file, for inclusion of external files, inside the executable of a program
	///
	/// \param strFilename The name of the file we wish to convert.
	/// \param strArrayName The name the array variable will be given in the output file
	/// \param iNumElementsPerRow How many elements to fit on a line within the output file
	/// \return False if an error occurred such as the file not being able to be opened.
	bool convertFileToHeader(const std::string &strFilename, const std::string &strArrayName = "data", unsigned int iNumElementsPerRow = 20);

	/// \brief  Sets the given colour values based on given hue value (between zero and one)
	///
	/// \param fHueAmount Between zero and one, represents the hue of the desired colour.
	/// \param fRed Will hold the red colour intensity of the computed colour between 0.0 and 1.0
	/// \param fGreen Will hold the green colour intensity of the computed colour between 0.0 and 1.0
	/// \param fBlue Will hold the blue colour intensity of the computed colour between 0.0 and 1.0
	extern void getHueColour(float fHueAmount, float& fRed, float& fGreen, float& fBlue);

	const float kPi = 3.14159265f;										///< Pi constant
	const float k2Pi = kPi * 2.0f;										///< 2 * Pi (Radians in a circle)
	const float kPiOver2 = kPi / 2.0f;									///< Pi divided by 2 (90 degrees in radians)
	const float k1OverPi = 1.0f / kPi;									///< 1.0f divided by PI
	const float k1Over2Pi = 1.0f / k2Pi;								///< 1.0f divided by 2*PI
	const float kPiOver180 = kPi / 180.0f;								///< PI divided by 180.0f
	const float k180OverPi = 180.0f / kPi;								///< 180.0f divided by PI
	const double  kMaxDouble = (std::numeric_limits<double>::max)();	///< Maximum value for a double
	const double  kMinDouble = (std::numeric_limits<double>::min)();	///< Minimum value for a double
	const float   kMaxFloat = (std::numeric_limits<float>::max)();		///< Maximum value for a float
	const float   kMinFloat = (std::numeric_limits<float>::min)();		///< Minimum value for a float
	const int     kMaxInt = (std::numeric_limits<int>::max)();			///< Maximum value for an int

	/// \brief Comparing a variable when it becomes invalid always returns false.
	/// 
	/// \param type The variable we wish to determine whether is NAN.
	/// \return False if the given type is a number, else true
	/// 
	/// Nice easy way to check if I've done something stupid with a zero and a division somewhere
	template <typename Type>
	inline bool isNAN(Type type)
	{
		return type != type;
	}

	/// \brief Converts degrees to radians
	///
	/// \param fAngleDegrees The angle in degrees
	/// \return The computed angle in radians
	inline float deg2rad(float fAngleDegrees) { return fAngleDegrees * kPiOver180; }

	/// \brief Converts radians to degrees
	///
	/// \param fAngleRadians The angle in radians
	/// \return The computed angle in degrees
	inline float rad2deg(float fAngleRadians) { return fAngleRadians * k180OverPi; }

	/// \brief Clamps given value within the range of -1 to +1 then performs standard acos function
	///
	/// \param f The value to perform the calculation on.
	/// \return The computed acos of the given value.
	inline float acosClamped(float f)
	{
		if (f < -1.0f)
			return kPi;
		if (f > 1.0f)
			return 0.0f;
		return acosf(f);
	}

	/// \brief Computes both sin and cos of a scalar (Sometime faster to calculate both at same time)
	///
	/// \param outSin The sin of the fScalar
	/// \param outCos The cos of the fScalar
	/// \param fScalar The value which to compute sin and cos upon.
	inline void sincos(float& outSin, float& outCos, float fScalar)
	{
		outSin = sinf(fScalar);
		outCos = cosf(fScalar);
	}

	/// \brief Clamps a value within given range
	///
	/// \param valueToClamp The value we wish to clamp
	/// \param valueA The first value which sets one boundary of the range we wish to clamp the given value to.
	/// \param valueB The second value which sets one boundary of the range we wish to clamp the given value to.
	template <class type>
	inline void clamp(type& valueToClamp, type valueA, type valueB)
	{
		type min;
		type max;
		if (valueA < valueB)
		{
			min = valueA;
			max = valueB;
		}
		else
		{
			min = valueB;
			max = valueA;
		}
		if (valueToClamp < min)
			valueToClamp = min;
		else if (valueToClamp > max)
			valueToClamp = max;
	}

	/// \brief Sets given variable to absolute value
	///
	/// \param value The value we wish to max absolute (aka, positive)
	template <class type>
	inline void absolute(type& value)
	{
		if (value < 0)
			value *= -1;
	}

	/// \brief Computes the difference
	///
	/// \param valueA The first value used.
	/// \param valueB The second value used.
	/// \return The difference
	template <class type>
	inline type difference(type valueA, type valueB)
	{
		type result = valueA - valueB;
		absolute(result);
		return result;
	}

	/// \brief Returns a random integer between x and y
	///
	/// \param ix The first value
	/// \param iy The second value
	/// \return The random value
	inline int randInt(int ix, int iy) { return rand() % (iy - ix + 1) + ix; }

	/// \brief Returns a random float between zero and 1
	/// 
	/// \return The random value
	inline float randFloat() { return float(rand()) / float(RAND_MAX + 1.0f); }

	/// \brief Returns a random double between zero and 1
	///
	/// \return The random value
	inline double randDouble() { return double(rand()) / double(RAND_MAX + 1.0); }

	/// \brief Returns a random bool
	///
	/// \return The random value
	inline bool randBool()
	{
		if (randInt(0, 1)) return true;
		return false;
	}

	/// \brief Returns a random double in the range -1 < n < 1
	///
	/// \return The random value between -1 and 1
	inline double randomClamped() { return randDouble() - randDouble(); }

	/// \brief Returns a random float within the specified range
	///
	/// \param fMin The minimum float which species the low end of the range
	/// \param fMax The maximum float which species the high end of the range
	/// \return The computed random float which lies within the given range
	inline float randf(float fMin, float fMax)
	{
		float fZeroToOne = (float)rand() / float(RAND_MAX + 1.0);
		return fMin + (fMax - fMin) * fZeroToOne;
	}

/*
	// Given two vectors, returns the rotation quaternion needed to rotate v1 to match v2
//	glm::quat rotationBetweenVectors(glm::vec3 v1, glm::vec3 v2);
*/

	/// \brief Holds system memory information which is set by getMemInfo()
	struct SMemInfo
	{
		/// \brief Holds process memory usage 
		struct SMemProcess
		{
			unsigned int iPageFaultCount;				///< The number of page faults.
			unsigned int iPeakWorkingSetSize;			///< The peak working set size. 
			unsigned int iWorkingSetSize;				///< The current working set size. 
			unsigned int iQuotaPeakPagedPoolUsage;		///< The peak paged pool usage. 
			unsigned int iQuotaPagedPoolUsage;			///< The current paged pool usage. 
			unsigned int iQuotaPeakNonPagedPoolUsage;	///< The peak nonpaged pool usage. 
			unsigned int iQuotaNonPagedPoolUsage;		///< The current nonpaged pool usage. 
			unsigned int iPagefileUsage;				///< The current pagefile usage. 
			unsigned int iPeakPagefileUsage;			///< The peak pagefile usage.
			unsigned int iPrivateUsage;					///< Same as PagefileUsage. The Commit Charge value in bytes for this process. Commit Charge is the total amount of private memory that the memory manager has committed for a running process.
		};

		/// \brief Holds OS memory usage
		struct SMemOS
		{
			unsigned int iCommitTotal;			///< Total number of pages committed by the system. 
			unsigned int iCommitLimit;			///< Current maximum number of page commits that can be performed by the system. This number can change if memory is added or deleted, or if pagefiles have grown, shrunk, or been added. 
			unsigned int iCommitPeak;			///< Maximum number of page commit totals that have occurred since the last reboot. 
			unsigned int iPhysicalTotal;		///< Total amount, in pages, of physical memory. 
			unsigned int iPhysicalAvailable;	///< Amount, in pages, of physical memory available to user processes. 
			unsigned int iSystemCache;			///< Total amount, in pages, of system cache memory. 
			unsigned int iKernelTotal;			///< Total amount, in pages, of the sum of the paged and nonpaged kernel pools. 
			unsigned int iKernelPaged;			///< Total amount, in pages, of the paged kernel pool. 
			unsigned int iKernelNonpaged;		///< Total amount, in pages, of the nonpaged kernel pool. 
			unsigned int iPageSize;				///< Size, in bytes, of a page. 
			unsigned int iHandleCount;			///< Total number of open handles. 
			unsigned int iProcessCount;			///< Total number of processes. 
			unsigned int iThreadCount;			///< Total number of threads. 
		};

		SMemProcess proc;	///< Process information
		SMemOS os;			///< Operating system information
		
	};

	/// \brief Places memory information about the process and system into the given SMemInfo structure
	///
	/// \param memInfo Holds the result in an SMemInfo structure
	void getMemInfo(SMemInfo& memInfo);

	/// \brief Returns number of logical CPU cores
	///
	/// \return The number of logical CPU cores (If we have a single core CPU, with "hyperthreading", this would be 2.
	int getCPULogicalCores(void);

}	// Namespace DCL

#endif // #ifndef FILENAME_H

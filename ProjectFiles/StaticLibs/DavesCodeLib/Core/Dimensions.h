#ifndef DIMENSIONS_H
#define DIMENSIONS_H

namespace DCL
{
	/// \brief Holds 2D dimensions of something, maybe an image
	class CDimension2D
	{
	public:
		/// \brief Default constructor, sets dimensions to zero
		CDimension2D(void);

		/// \brief Constructor, sets to given dimensions
		CDimension2D(unsigned int uiWidth, unsigned int uiHeight);

		/// \brief Operator overload for comparison
		bool operator==(const CDimension2D& other) const {
			return (width == other.width && height == other.height);
		}

		/// \brief Set the dimensions to the given values
		///
		/// \param uiWidth The width of the dimension
		/// \param uiHeight The height of the dimension
		void set(unsigned int uiWidth, unsigned int uiHeight);

		unsigned int width;		///< Width for this dimension
		unsigned int height;	///< Height for this dimension
	};

	/// \brief Holds 3D dimensions of something, maybe an image
	class CDimension3D
	{
	public:
		/// \brief Default constructor, sets dimensions to zero
		CDimension3D(void);

		/// \brief Constructor, sets to given dimensions
		CDimension3D(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiDepth);

		/// \brief Operator overload for comparison
		bool operator==(const CDimension3D& other) const {
			return (width == other.width && height == other.height && depth == other.depth);
		}


		/// \brief Set the dimensions to the given values
		///
		/// \param uiWidth The width of the dimension
		/// \param uiHeight The height of the dimension
		/// \param uiDepth The depth of the dimension
		void set(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiDepth);

		unsigned int width;		///< Width for this dimension
		unsigned int height;	///< Height for this dimension
		unsigned int depth;		///< Depth for this dimension
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
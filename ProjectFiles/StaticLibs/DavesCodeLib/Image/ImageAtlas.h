#ifndef IMAGEATLAS_H
#define IMAGEATLAS_H

#include "Image.h"
#include "../Math/Vector2f.h"
#include <map>
#include <fstream>
#include <vector>

namespace DCL
{
	/// \brief Holds information about each packed image inside an atlas image
	class CImageAtlasDetails
	{
	public:
		/// \brief Holds texture coordinates for each of the four corners of an image.
		struct STexCoords
		{
			CVector2f vTL;	///< Top left texture coordinate
			CVector2f vTR;	///< Top right texture coordinate
			CVector2f vBL;	///< Bottom left texture coordinate
			CVector2f vBR;	///< Bottom right texture coordinate
		};
		// Stuff read/written to file

		STexCoords sTexCoords;	///< The texture coordinates within the atlas image of the image

		/// \brief The atlas image number which the image is located in.
		///
		/// If setting the maximum size of the atlas images to a small size,
		/// multiple atlas images may be created to accomodate all the images.
		unsigned int uiAtlasImage;

		bool bRotated;					///< Whether the image was rotated clockwise to fit better or not.
		CVector2f vDims;				///< The dimensions of the image in pixels
		std::string strImageFilename;	///< The filename which the image was created from.

		/// \brief Writes out this object's data to an already opened ofstream
		///
		/// \param file An already opened ofstream handle.
		/// 
		/// If an error occurs, so does an exception
		void write(std::ofstream& file);

		/// \brief Reads in this object's data from an already opened ifsream
		///
		/// \param file An already opened ifstream handle.
		/// 
		/// If an error occurs, so does an exception
		void read(std::ifstream& file);
	};

	/// \brief Image atlas class used to pack many smaller images into as few as possible larger atlas images.
	class CImageAtlasPacker
	{
	public:
		/// \brief Constructor, does nothing
		CImageAtlasPacker();

		/// \brief Destructor, calls reset() to free all data
		~CImageAtlasPacker();

		/// \brief This creates texture atlas images.
		///
		/// \param vstrImages A vector of strings holding each individual image's filename which to add to the atlas image/s
		/// \param uiMaxAtlasImageWidth The maximum allowed width of the created atlas image/s
		/// \param uiMaxAtlasImageHeight The maximum allowed height of the created atlas image/s
		/// \param bAllowRotationOfImages Whether to allow rotation of individual images to obtain greater packing efficiency or not.
		/// \param uiImageSpacing Amount of spacing between individual images.
		/// 
		/// We provide a vector of strings holding each individual image's filename.
		/// Each individual image can have different dimensions.
		/// We specify a maximum width and height that an individual atlas image may be.
		/// We specify whether to allow or disallow rotation of images to allow better fitting of the images.
		/// If rotation is enabled, the computed texture coordinates are rotated accordingly.
		/// After calling this, we can call the various other methods to get at the information
		/// If the vector of strings is empty, an exception occurs
		/// If an individual image's dimensions, including spacing is greater than the max atlas dimensions, an exception occurs.
		/// If all given images are the same dimensions, nothing is sorted.
		void createAtlasImages(
			const std::vector<std::string>& vstrImages,	// A vector of strings holding each individual image's filename which to add to the atlas image/s
			unsigned int uiMaxAtlasImageWidth,			// The maximum allowed width of the created atlas image/s
			unsigned int uiMaxAtlasImageHeight,			// The maximum allowed height of the created atlas image/s
			bool bAllowRotationOfImages,				// Whether to allow rotation of individual images to obtain greater packing efficiency or not.
			unsigned int uiImageSpacing = 1				// Amount of spacing between individual images.
		);

		/// \brief Resets everything, freeing computed data and atlas images.
		void reset(void);

		/// \brief Returns the number of generated atlas images holding the individual images
		///
		/// \return The number of generated atlas images holding the individual images
		/// 
		/// Call createAtlasImages() first.
		unsigned int getNumAtlases(void) const;

		/// \brief Returns a pointer to the atlas image at the specified index
		///
		/// \param uiIndex The index of the atlas image to return a pointer to.
		/// \return A pointer to the CImage holding the atlas image.
		/// 
		/// Call createAtlasImages() first.
		/// If an invalid index is given, or no atlases exist, an exception occurs
		CImage* getAtlasImage(unsigned int uiIndex) const;

		/// \brief Returns a vector of CImageAtlasDetails containing each image's details
		///
		/// \return A vector of CImageAtlasDetails which contain each image's details.
		/// 
		/// Call createAtlasImages() first.
		/// If no image data exists, an exception occurs.
		std::vector<CImageAtlasDetails> getAllImageDetails(void) const;

		/// \brief Returns a pointer to _mvImageDetails containing each image's details
		///
		/// \return A pointer to _mvImageDetails contained each image's details
		/// 
		/// Call createAtlasImages() first.
		/// If no image data exists, an exception occurs.
		/// Usage:
		/// \code
		/// std::vector<CImageAtlasDetails>* pviad = _mAtlases.getAllImageDetailsPointer();
		/// unsigned int uiLastImageIndex = pviad->size() - 1;
		/// unsigned int uiAtlasNumber = (*pviad)[uiLastImageIndex].uiAtlasImage;
		/// \endcode
		/// or
		/// \code
		/// unsigned int uiAtlasNumber = pviad->operator[](uiLastImageIndex).uiAtlasImage;
		/// \endcode
		/// or
		/// \code
		/// unsigned int uiAtlasNumber = pviad[0][uiLastImageIndex].uiAtlasImage;
		/// \endcode
		std::vector<CImageAtlasDetails>* getAllImageDetailsPointer(void);

		/// \brief Returns the total number of individual images added to all the atlases
		///
		/// \return The total number of individual images added to the atlases
		/// 
		/// Call createAtlasImages() first.
		unsigned int getNumIndividualImages(void) const;

		/// \brief Returns the named image's details
		///
		/// \param strImageName The previously added image's name.
		/// \return A CImageAtlasDetails holding the named image's details.
		/// 
		/// Call createAtlasImages() first.
		/// If an invalid image name is given, an exception occurs
		CImageAtlasDetails getImageDetails(const std::string& strImageName) const;

		/// \brief Returns a pointer to the named image's details
		///
		/// \param strImageName The name of an image which was previously added.
		/// \return CImageAtlasDetails A pointer to the image's details.
		/// 
		/// Call createAtlasImages() first.
		/// If an invalid image name is given, an exception occurs
		CImageAtlasDetails* getImageDetailsPointer(const std::string& strImageName) const;

		/// \brief Returns whether the named image exists or not
		///
		/// \param strImageName The name of the image we wish to determine whether it had been added or not.
		/// \return True if the image exists, else false.
		bool getImageExists(const std::string& strImageName) const;
	private:
		std::vector<CImage*> _mvAtlasImages;				///< Holds each atlas image which contain all the added images.
		std::vector<CImageAtlasDetails> _mvImageDetails;	///< Holds each image's details

		///< This is so we can lookup an image by name using getImageDetails()
		mutable std::map<std::string, CImageAtlasDetails> _mmapImageDetails;
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
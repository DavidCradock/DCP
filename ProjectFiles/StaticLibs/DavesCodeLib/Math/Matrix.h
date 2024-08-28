/// \file Matrix.h
/// \brief 3D Matrix class
///
/// Detailed description text goes here.

#ifndef MATRIX_H
#define MATRIX_H

#include "Quaternion.h"
#include "Vector3f.h"

namespace DCL
{
	/// \brief Matrix class
	/// 
	/// Here's the matrix class used for applying transformations to vectors in 3D space
	/// and projecting points to 2D.
	/// This is a column-major matrix, compatible with OpenGL.
	/// So the elements of the matrix are stored like this..
	/// [ 0  4  8 12 ]
	/// [ 1  5  9 13 ]
	/// [ 2  6 10 14 ]
	/// [ 3  7 11 15 ]
	/// 
	/// A matrix is a rectangular array of numbers layed out in rows and columns, like this...
	/// [1 0 0 0]
	/// [0 1 0 0]
	/// [0 0 1 0]
	/// [0 0 0 1]
	/// 
	/// The above is a special case of a matrix, known as an identity matrix where if multiplying
	/// a point/vector by it, will produce no translation, rotation or scale.
	///
	/// A translation in a matrix for x, y and z are stored in these values...
	/// [1 0 0 x]
	/// [0 1 0 y]
	/// [0 0 1 z]
	/// [0 0 0 1]
	///
	/// The scaling values are along the diagonal(scaling of x, y and z)...
	/// [x 0 0 0]
	/// [0 y 0 0]
	/// [0 0 z 0]
	/// [0 0 0 1]
	/// 
	/// The rotation part is more complicated since it uses cosine and sine functions and it
	/// changes depending on the axis...
	///		X - Axis Rotation			Y - Axis Rotation			Z - Axis Rotation
	/// [1	0			0		0]	[cos(θ)		0	-sin(θ)	0]	[cos(θ)		sin(θ)  0   0]
	/// [0	cos(θ)		sin(θ)	0]	[0			1   0		0]	[-sin(θ)	cos(θ)  0   0]
	/// [0	-sin(θ)		cos(θ)  0]	[sin(θ)		0   cos(θ)	0]	[0			0       1   0]
	/// [0	0			0		1]	[0			0   0		1]	[0			0       0   1]
	///
	/// The rotation matrices can be combined with the scale and translation matrix to create the final matrix.
	///
	/// Here's what a poor vertex has to go through to get to the screen...
	/// Vertex object coordinates x model matrix = world coordinates
	/// World coordinates x view matrix = eye coordinates
	/// Eye coordinates x projection matrix = clipping space coordinates
	/// Clipping space coordinates x perspective division = normalized device coordinates
	/// Normalized device coordinates x viewport transformation = screen coordinates
	///
	/// Vertex object coordinates are the vertex positions usually created in 3D modelling apps such as Blender.
	/// Model matrix is what translates, rotates and scales a vertex into the correct world position.
	/// View matrix is the camera position and created by the inverse of the camera position. We use the lookat()
	/// method to create a view matrix.
	/// Projection matrix is created using setProjectionOrtho() and setProjectionPerspective() depending
	/// upon how we wish the vertices to be transformed.
	/// The other stuff is performed in the vertex/fragment shaders.
	/// 
	/// Remember that the order of matrix multiplication is important and we go from right to left, like this in a shader...
	/// gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;
	class CMatrix
	{
	public:
		friend class CQuaternion;

		/// \brief Default constructor, sets to identity matrix
		CMatrix();

		/// \brief Sets this matrix to the one on the right
		const void operator = (const CMatrix& matrix);

		/// \brief Multiply this matrix by another and return the result
		const CMatrix operator * (const CMatrix& matrix) const;

		/// \brief Multiply this matrix by another
		const void operator *= (const CMatrix& matrix);

		/// \brief Compares whether this matrix and the one to the right of the == operator are equal.
		///
		/// This is an exact compare, no teeny epsilon value.
		bool operator==(const CMatrix& matrix) const;

		/// \brief Compares whether this matrix and the one to the right of the != operator are equal.
		///
		/// This is an exact compare, no teeny epsilon value.
		bool operator!=(const CMatrix& matrix) const;

		/// \brief Sets matrix to identity matrix
		void setIdentity(void);

		/// \brief Fills the matrix with zeros
		void setZero(void);

		/// \brief Sets this matrix from the given array of floats
		///
		/// \param src Array holding the values to set this matrix to.
		void set(const float src[16]);

		/// \brief Sets the matrix from the one given
		///
		/// \param src Matrix holding the values to set this matrix to.
		void set(const CMatrix& src);

		/// \brief Sets the matrix from the one given
//		void set(const glm::mat4& matrix);

		/// \brief Returns a matrix containing the contents of this matrix
		///
		/// \return A matrix which holds this matrix's data
		CMatrix get(void) const;

		/// \brief Returns a glm matrix constructed from this one
//		glm::mat4 getGLM(void) const;

		/// \brief Set the matrix to hold a translation transformation
		///
		/// \param fX X translation amount
		/// \param fY Y translation amount
		/// \param fZ Z translation amount
		void setTranslation(float fX, float fY, float fZ);

		/// \brief Set the matrix to hold a translation transformation
		///
		/// \param vTrans A CVector3f holding the translation to set
		void setTranslation(const CVector3f& vTrans);

		/// \brief Set the matrix to hold a scale transformation
		///
		/// \param fX The amount to scale along X
		/// \param fY The amount to scale along Y
		/// \param fZ The amount to scale along Z
		void setScale(float fX, float fY, float fZ);

		/// \brief Set the matrix to hold a scale transformation
		///
		/// \param vTrans A CVector3f holding the scaling amounts
		void setScale(const CVector3f& vTrans);

		/// \brief Sets the matrix to hold a rotation transformation
		///
		/// \param vAxis The axis with which to rotate around
		/// \param fAngleDegrees The amount in degrees in which to rotate around the given axis
		/// 
		/// The rotation is specified from the give amount of rotation in degrees around the given axis.
		/// Working with degrees is slightly slower than working in radians as when using degrees, deg2rad() is called.
		void setFromAxisAngleDegrees(const CVector3f& vAxis, float fAngleDegrees);

		/// \brief Sets the matrix to hold a rotation transformation
		/// 
		/// \param vAxis The axis with which to rotate around
		/// \param fAngleRadians The amount in radians in which to rotate around the given axis
		/// 
		/// The rotation is specified from the give amount of rotation in radians around the given axis.
		/// Working with radians is slightly faster than working in degress as when using degrees, deg2rad() is called.
		void setFromAxisAngleRadians(const CVector3f& vAxis, float fAngleRadians);

		/// \brief Sets the matrix to hold a rotation transformation from a quaternion
		///
		/// \param quaternion The quaternion holding a rotation
		void setFromQuaternion(const CQuaternion& quaternion);

		/// \brief Sets the given vector to hold this matrix's right vector/axis
		///
		/// \param vVec A CVector3f which will hold this matrix's right vector/axis
		/// 
		/// This is used to obtain the orientation of the current state of the matrix
		void getRightVector(CVector3f& vVec) const;

		/// \brief Sets the given vector to hold this matrix's up vector/axis
		///
		/// \param vVec A CVector3f which will hold this matrix's up vector/axis
		/// 
		/// This is used to obtain the orientation of the current state of the matrix
		void getUpVector(CVector3f& vVec) const;

		/// \brief Sets the given vector to hold this matrix's forward vector/axis
		///
		/// \param vVec A CVector3f which will hold this matrix's forward vector/axis
		/// 
		/// This is used to obtain the orientation of the current state of the matrix
		void getForwardVector(CVector3f& vVec) const;

		/// \brief Returns a matrix which is the transpose of this matrix
		///
		/// \return A CMatrix which is the transpose of this matrix
		/// 
		/// The transpose of a matrix is obtained by flipping the matrix over its diagonal.
		/// Which means the rows become columns and the columns become rows.
		/// The transpose of a matrix has some useful properties such as reversing the order
		/// of multiplication, preserving the trace and determinant, changing the orientation
		/// of vectors and converting matrixs between column major and row major.
		CMatrix transpose(void);

		/// \brief Returns a matrix which is the inverse of this matrix
		///
		/// \return A CMatrix which is the inverse of this matrix
		/// 
		/// The inverse of a matrix is a matrix that, when multiplied by the original matrix, gives the identity matrix.
		CMatrix inverse(void);

		/// \brief Multiplies this matrix by the one given and returns the resulting matrix
		///
		/// \param matrix A matrix to multiply this one by
		/// \return A CMatrix holding the result
		CMatrix multiply(const CMatrix& matrix);

		/// \brief Multiplies the given vector by this matrix and returns the resulting vector
		///
		/// \param vector A CVector3f to multiply by this matrix
		/// \return A CVector3f holding the result
		CVector3f multiply(const CVector3f& vector);

		/// \brief Multiplies each value in the matrix by the given scalar and returns the resulting matrix
		///
		/// \param fScalar The scalar value to multiply this matrix by
		/// \return The resulting matrix
		CMatrix multiply(const float fScalar);

		/// \brief Sets the matrix to represent a perspective projection matrix
		///
		/// \param fWidth The width of the backbuffer/screen to use when calculating the aspect ration if fAspectRatio is given a value of < 0.0
		/// \param fHeight The height of the backbuffer/screen to use when calculating the aspect ration if fAspectRatio is given a value of < 0.0
		/// \param fFieldOfViewInDegrees The desired field of view, in degrees
		/// \param fNearClippingPlaneDistance The near clipping plane distance
		/// \param fFarClippingPlaneDistance The far clipping plane distance
		/// \param fAspectRatio The aspect ratio, which if given a value < 0, will be computed from fWidth and fHeight
		/// 
		/// Passing in a value of 0.0f or less for fAspectRatio will compute this value for us from the given (width / height) parameters
		void setProjectionPerspective(
			float fWidth = 320.0f,
			float fHeight = 240.0f,
			float fFieldOfViewInDegrees = 55.0f,
			float fNearClippingPlaneDistance = 1.0f,
			float fFarClippingPlaneDistance = 1000.0f,
			float fAspectRatio = -1.0f);

		/// \brief Sets the matrix to represent an orthographic prjection matrix
		///
		/// \param fWidth If fRight or fBottom are given values < 0.0f, this is used for fRight
		/// \param fHeight If fRight or fBottom are given values < 0.0f, this is used for fBottom
		/// \param fLeft Typically 0.0f
		/// \param fRight Typically -1.0f
		/// \param fTop Typically 0.0f
		/// \param fBottom Typically -1.0f
		/// \param fNear Typically -1.0f
		/// \param fFar Typically 1.0f
		/// 
		/// Passing in a value of 0.0f or less for fRight or fBottom will use values from fWidth and fHeight
		void setProjectionOrthographic(
			float fWidth = 320.0f,
			float fHeight = 240.0f,
			float fLeft = 0.0f,
			float fRight = -1.0f,
			float fTop = 0.0f,
			float fBottom = -1.0f,
			float fNear = -1.0f,
			float fFar = 1.0f);

		/// \brief Sets the matrix to represent a view matrix based upon glLookat
		///
		/// \param vEyePos The eye position
		/// \param vTarget The target position
		/// \param vUp The up vector
		/// 
		/// vUp should be normalised
		void setViewLookat(const CVector3f& vEyePos, const CVector3f& vTarget, const CVector3f& vUp = CVector3f(0.0f, 1.0f, 0.0f));

		/// \brief Returns a pointer to the float array containing the matrix
		///
		/// \return a pointer to the float array containing the matrix values
		const float* getFloat(void) const;

		/// \brief Returns the current translation stored in the matrix as a CVector3f
		///
		/// \return A CVector3f holding the translation this matrix contains
		CVector3f getTranslation(void) const;
	private:
		float m[16];	///< The 16 values for the matrix
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
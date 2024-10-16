#include "ResourceVertexBuffer.h"
#include "../../Core/Exceptions.h"
#include "../OpenGL/RendererOpenGLExtensions.h"

namespace DCL
{
	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Base
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	CResourceVertexBufferBase::CResourceVertexBufferBase()
	{
		eVertexBufferType = CResourceVertexBufferBase::EVertexBufferDataType::POS_COL;
	}

	void CResourceVertexBufferBase::setDataType(CResourceVertexBufferBase::EVertexBufferDataType vertexBufferDataType)
	{
		eVertexBufferType = vertexBufferDataType;
	}

	void CResourceVertexBufferBase::computeTangentsAndBinormals(void)
	{
		// Make sure correct vertex data type is set
		ThrowIfFalse(EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL == eVertexBufferType, "Unable to compute TBN as vertex buffer data type is not set to correct type.");

		// Make sure data exists
		ThrowIfFalse(_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.size(), "Unable to compute TBN as vertex buffer data is empty.");

		// Make sure indicies exist
		ThrowIfFalse(_mvecIndices.size(), "Unable to compute TBN as there are no vertex indicies.");

		// For each face
		for (unsigned int iIndex = 0; iIndex < _mvecIndices.size(); iIndex += 3)
		{
			// Calculate the face's edges and delta UV coordinates
			CVector3f edge1 = _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex + 1]].position - _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].position;
			CVector3f edge2 = _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex + 2]].position - _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].position;
			CVector2f deltaUV1 = _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex + 1]].texCoord - _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].texCoord;
			CVector2f deltaUV2 = _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex + 2]].texCoord - _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].texCoord;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].binormal.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].binormal.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[_mvecIndices[iIndex]].binormal.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		}
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position, const CColourf& colour)
	{
		ThrowIfFalse(CResourceVertexBufferBase::EVertexBufferDataType::POS_COL == eVertexBufferType, "Vertex buffer type not correctly set to EVertexBufferDataType::POS_COL");
		Vertex_POS_COL vertex;
		vertex.colour = colour;
		vertex.position = position;
		_mvecVertexData_POS_COL.push_back(vertex);
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position, const CColourf& colour, CVector2f& texcoord)
	{
		if (CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_TEXCOORD != eVertexBufferType)
		{
			if (CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL != eVertexBufferType)
			{
				Throw("Vertex buffer type not correctly set to EVertexBufferDataType::POS_COL_TEXCOORD or EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL");
			}
		}

		Vertex_POS_COL_TEXCOORD vertex;
		vertex.colour = colour;
		vertex.position = position;
		vertex.texCoord = texcoord;
		_mvecVertexData_POS_COL_TEXCOORD.push_back(vertex);
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position, const CColourf& colour, const CVector3f& normal, CVector2f& texcoord)
	{
		ThrowIfFalse(CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD == eVertexBufferType, "Vertex buffer type not correctly set to EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD");
		Vertex_POS_COL_NORMAL_TEXCOORD vertex;
		vertex.colour = colour;
		vertex.normal = normal;
		vertex.position = position;
		vertex.texCoord = texcoord;
		_mvecVertexData_POS_COL_NORMAL_TEXCOORD.push_back(vertex);
	}

	void CResourceVertexBufferBase::addVertex(const CVector3f& position, const CColourf& colour, const CVector3f& normal, CVector2f& texcoord0, CVector2f& texcoord1)
	{
		ThrowIfFalse(CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2 == eVertexBufferType, "Vertex buffer type not correctly set to EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2");
		Vertex_POS_COL_NORMAL_TEXCOORDx2 vertex;
		vertex.colour = colour;
		vertex.normal = normal;
		vertex.position = position;
		vertex.texCoord0 = texcoord0;
		vertex.texCoord1 = texcoord1;
		_mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.push_back(vertex);
	}

	void CResourceVertexBufferBase::freeVertexData(void)
	{
		_mvecVertexData_POS_COL.clear();
		_mvecVertexData_POS_COL_TEXCOORD.clear();
		_mvecVertexData_POS_COL_NORMAL_TEXCOORD.clear();
		_mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.clear();
		_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.clear();
	}

	void CResourceVertexBufferBase::freeVertexIndicies(void)
	{
		_mvecIndices.clear();
	}

	void CResourceVertexBufferBase::freeAll(void)
	{
		freeVertexData();
		freeVertexIndicies();
	}

	void CResourceVertexBufferBase::addIndex(int newIndex)
	{
		_mvecIndices.push_back(newIndex);
	}

	size_t CResourceVertexBufferBase::getNumVertices(void) const
	{
		switch (eVertexBufferType)
		{
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL:
			return _mvecVertexData_POS_COL.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD:
			return _mvecVertexData_POS_COL_NORMAL_TEXCOORD.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2:
			return _mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL:
			return _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.size();
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_TEXCOORD:
			return _mvecVertexData_POS_COL_TEXCOORD.size();
			break;
		default:
			Throw("Invalid geometry data type set.");
			break;
		}
	}

	size_t CResourceVertexBufferBase::getNumIndicies(void) const
	{
		return _mvecIndices.size();
	}

	void CResourceVertexBufferBase::convertObj(const std::string filename) const
	{
		// Used to temporarily hold each line of data from file
		CVector3f vertex;
		CVector3f normal;
		CVector2f texCoord;
		unsigned int index[9];	// Index to vertex, texcoord, normal

		// Used to temporarily hold all unique items from the file
		std::vector<CVector3f> vVertices;
		std::vector<CVector3f> vNormals;
		std::vector<CVector2f> vTexCoords;
		std::vector<unsigned int> vIndicesVertices;
		std::vector<unsigned int> vIndicesNormals;
		std::vector<unsigned int> vIndicesTexCoords;

		FILE* file = 0;
		errno_t err;
		err = fopen_s(&file, filename.c_str(), "r");
		ThrowIfTrue(bool(err != 0), "Failed to open file " + filename);

		char strLine[255] = { 0 };
		char ch = 0;
		// Go through entire file, loading everything to the above vectors
		while (!feof(file))
		{
			// Get the beginning character of the current line in the file
			ch = fgetc(file);

			if ('v' == ch)	// Could be v(vertex), n(normal or t(texcoord)
			{
				ch = fgetc(file);
				if (' ' == ch)	// v(vertex)
				{
					fscanf_s(file, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
					fgets(strLine, 255, file);	// Read the rest of the line
					vVertices.push_back(vertex);
				}
				else if ('n' == ch)	// n(normal)
				{
					fscanf_s(file, "%f %f %f", &normal.x, &normal.y, &normal.z);
					fgets(strLine, 255, file);	// Read the rest of the line
					vNormals.push_back(normal);
				}
				else if ('t' == ch)	// t(texcoord)
				{
					fscanf_s(file, "%f %f", &texCoord.x, &texCoord.y);
					fgets(strLine, 255, file);	// Read the rest of the line
					vTexCoords.push_back(texCoord);
				}
			}
			else if ('f' == ch)	// f vertex/texcoord/normal indicies
			{
				fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &index[0], &index[1], &index[2], &index[3], &index[4], &index[5], &index[6], &index[7], &index[8]);
				fgets(strLine, 255, file);	// Read the rest of the line
				vIndicesVertices.push_back(index[0]);
				vIndicesTexCoords.push_back(index[1]);
				vIndicesNormals.push_back(index[2]);
				vIndicesVertices.push_back(index[3]);
				vIndicesTexCoords.push_back(index[4]);
				vIndicesNormals.push_back(index[5]);
				vIndicesVertices.push_back(index[6]);
				vIndicesTexCoords.push_back(index[7]);
				vIndicesNormals.push_back(index[8]);
			}
			else if ('\n' == ch)	// Newline
			{
			}
			else // Don't care
			{
				fgets(strLine, 255, file);	// Read the rest of the line
			}
		}
		fclose(file);

		// Now we have everything loaded from the file,
		// save out to binary file.
		std::string strOutputFilename = filename;
		for (int i = 0; i < 3; ++i)
		{
			strOutputFilename.pop_back();
		}
		strOutputFilename += "geom";
		err = fopen_s(&file, strOutputFilename.c_str(), "w+b");
		ThrowIfTrue(bool(err != 0), "Failed to open file " + filename + " for saving.");

		// Loop through each face
		Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL geomVertex;
		unsigned int iNumVertices = (unsigned int)vIndicesVertices.size();
		size_t written = fwrite(&iNumVertices, sizeof(unsigned int), 1, file);
		ThrowIfTrue(bool(0 == written), "Failed to write to file " + filename);

		for (unsigned int i = 0; i < vIndicesVertices.size(); ++i)
		{
			geomVertex.position = vVertices[vIndicesVertices[i] - 1];	// Vertex position
			geomVertex.normal = vNormals[vIndicesNormals[i] - 1];		// Normal
			geomVertex.texCoord = vTexCoords[vIndicesTexCoords[i] - 1];	// Texture coordinates
			geomVertex.colour = CColourf(1.0f, 1.0f, 1.0f, 1.0f);
			geomVertex.binormal = CVector3f(0.0f, 1.0f, 0.0f);	// Just set to whatever as calculated during call to update()
			geomVertex.tangent = CVector3f(0.0f, 1.0f, 0.0f);	// Just set to whatever as calculated during call to update()
			written = fwrite(&geomVertex, sizeof(Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL), 1, file);
			ThrowIfTrue(bool(0 == written), "Failed to write to file " + filename);
		}
		fclose(file);
	}

	void CResourceVertexBufferBase::addFromFile(const std::string& strGeometryFilename)
	{

	}

	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* OpenGL
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceVertexBufferOpenGL class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceVertexBufferOpenGL::CPrim
	{
	public:
		CPrim();
		unsigned int _mVertexBufferObject;	// OpenGL vertex buffer object ID
		unsigned int _mVertexArrayObject;	// OpenGL vertex array object ID
		unsigned int _mElementBufferObject;	// OpenGL element buffer object ID
	};

	CResourceVertexBufferOpenGL::CPrim::CPrim()
	{
		_mVertexBufferObject = 0;
		_mVertexArrayObject = 0;
		_mElementBufferObject = 0;
	}

	CResourceVertexBufferOpenGL::CResourceVertexBufferOpenGL()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceVertexBufferOpenGL::~CResourceVertexBufferOpenGL()
	{
		LOG("Destructor called.");
		freeGPU();
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceVertexBufferOpenGL::uploadGPU(void)
	{
		// GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
		// GL_STATIC_DRAW: the data is set only once and used many times.
		// GL_DYNAMIC_DRAW : the data is changed a lot and used many times.

		switch (eVertexBufferType)
		{
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL:
			if (!_mvecVertexData_POS_COL.size())
				return;
			if (!_mvecIndices.size())
				return;
			if (!prim->_mVertexBufferObject)
				glGenBuffers(1, &prim->_mVertexBufferObject);
			if (!prim->_mVertexArrayObject)
				glGenVertexArrays(1, &prim->_mVertexArrayObject);
			if (!prim->_mElementBufferObject)
				glGenBuffers(1, &prim->_mElementBufferObject);
			glBindVertexArray(prim->_mVertexArrayObject);

			// Bind VBO and upload vertex data in first two lines, then indicies in next two
			glBindBuffer(GL_ARRAY_BUFFER, prim->_mVertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_POS_COL) * _mvecVertexData_POS_COL.size(), &_mvecVertexData_POS_COL[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prim->_mElementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _mvecIndices.size(), &_mvecIndices[0], GL_STATIC_DRAW);

			// Position
			glVertexAttribPointer(0,			// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,								// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,						// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,						// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL),			// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)0);						// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(0);

			// Colour
			glVertexAttribPointer(1,			// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				4,								// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,						// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,						// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL),			// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(3 * sizeof(float)));	// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(1);

			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD:
			if (!_mvecVertexData_POS_COL_NORMAL_TEXCOORD.size())
				return;
			if (!_mvecIndices.size())
				return;
			if (!prim->_mVertexBufferObject)
				glGenBuffers(1, &prim->_mVertexBufferObject);
			if (!prim->_mVertexArrayObject)
				glGenVertexArrays(1, &prim->_mVertexArrayObject);
			if (!prim->_mElementBufferObject)
				glGenBuffers(1, &prim->_mElementBufferObject);
			glBindVertexArray(prim->_mVertexArrayObject);

			// Bind VBO and upload vertex data in first two lines, then indicies in next two
			glBindBuffer(GL_ARRAY_BUFFER, prim->_mVertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_POS_COL_NORMAL_TEXCOORD) * _mvecVertexData_POS_COL_NORMAL_TEXCOORD.size(), &_mvecVertexData_POS_COL_NORMAL_TEXCOORD[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prim->_mElementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _mvecIndices.size(), &_mvecIndices[0], GL_STATIC_DRAW);

			// Position
			glVertexAttribPointer(0,					// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,										// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,								// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,								// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)0);								// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(0);

			// Colour
			glVertexAttribPointer(1,					// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				4,										// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,								// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,								// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(3 * sizeof(float)));			// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(1);

			// Normal
			glVertexAttribPointer(2,					// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,										// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,								// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,								// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(7 * sizeof(float)));			// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(3);

			// Texture coordinates
			glVertexAttribPointer(3,					// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				2,										// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,								// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,								// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(10 * sizeof(float)));			// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(2);

			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2:
			if (!_mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.size())
				return;
			if (!_mvecIndices.size())
				return;
			if (!prim->_mVertexBufferObject)
				glGenBuffers(1, &prim->_mVertexBufferObject);
			if (!prim->_mVertexArrayObject)
				glGenVertexArrays(1, &prim->_mVertexArrayObject);
			if (!prim->_mElementBufferObject)
				glGenBuffers(1, &prim->_mElementBufferObject);
			glBindVertexArray(prim->_mVertexArrayObject);

			// Bind VBO and upload vertex data in first two lines, then indicies in next two
			glBindBuffer(GL_ARRAY_BUFFER, prim->_mVertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_POS_COL_NORMAL_TEXCOORDx2) * _mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.size(), &_mvecVertexData_POS_COL_NORMAL_TEXCOORDx2[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prim->_mElementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _mvecIndices.size(), &_mvecIndices[0], GL_STATIC_DRAW);

			// Position
			glVertexAttribPointer(0,						// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,											// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,									// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,									// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORDx2),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)0);									// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(0);

			// Colour
			glVertexAttribPointer(1,						// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				4,											// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,									// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,									// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORDx2),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(3 * sizeof(float)));				// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(1);

			// Normal
			glVertexAttribPointer(2,						// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,											// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,									// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,									// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORDx2),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(7 * sizeof(float)));				// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(3);

			// Texture coordinates 0
			glVertexAttribPointer(3,						// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				2,											// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,									// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,									// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORDx2),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(10 * sizeof(float)));				// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(2);

			// Texture coordinates 1
			glVertexAttribPointer(4,						// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				2,											// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,									// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,									// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORDx2),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(12 * sizeof(float)));				// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(2);

			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL:
			if (!_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.size())
				return;
			if (!_mvecIndices.size())
				return;
			if (!prim->_mVertexBufferObject)
				glGenBuffers(1, &prim->_mVertexBufferObject);
			if (!prim->_mVertexArrayObject)
				glGenVertexArrays(1, &prim->_mVertexArrayObject);
			if (!prim->_mElementBufferObject)
				glGenBuffers(1, &prim->_mElementBufferObject);
			glBindVertexArray(prim->_mVertexArrayObject);

			// Bind VBO and upload vertex data in first two lines, then indicies in next two
			glBindBuffer(GL_ARRAY_BUFFER, prim->_mVertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL) * _mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.size(), &_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prim->_mElementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _mvecIndices.size(), &_mvecIndices[0], GL_STATIC_DRAW);

			// Position
			glVertexAttribPointer(0,										// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,															// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,													// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,													// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)0);													// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(0);

			// Colour
			glVertexAttribPointer(1,										// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				4,															// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,													// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,													// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(3 * sizeof(float)));								// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(1);

			// Normal
			glVertexAttribPointer(2,										// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,															// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,													// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,													// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(7 * sizeof(float)));								// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(3);

			// Texture coordinates
			glVertexAttribPointer(3,									// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				2,														// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,												// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,												// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL),// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(10 * sizeof(float)));							// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(2);

			// Tangent
			glVertexAttribPointer(4,									// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,														// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,												// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,												// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL),// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(12 * sizeof(float)));							// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(4);

			// Binormal
			glVertexAttribPointer(5,									// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,														// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,												// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,												// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL),// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(15 * sizeof(float)));							// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(5);



			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_TEXCOORD:
			if (!_mvecVertexData_POS_COL_TEXCOORD.size())
				return;
			if (!_mvecIndices.size())
				return;
			if (!prim->_mVertexBufferObject)
				glGenBuffers(1, &prim->_mVertexBufferObject);
			if (!prim->_mVertexArrayObject)
				glGenVertexArrays(1, &prim->_mVertexArrayObject);
			if (!prim->_mElementBufferObject)
				glGenBuffers(1, &prim->_mElementBufferObject);
			glBindVertexArray(prim->_mVertexArrayObject);

			// Bind VBO and upload vertex data in first two lines, then indicies in next two
			glBindBuffer(GL_ARRAY_BUFFER, prim->_mVertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_POS_COL_TEXCOORD) * _mvecVertexData_POS_COL_TEXCOORD.size(), &_mvecVertexData_POS_COL_TEXCOORD[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prim->_mElementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _mvecIndices.size(), &_mvecIndices[0], GL_STATIC_DRAW);

			// Position
			glVertexAttribPointer(0,				// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				3,									// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,							// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,							// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_TEXCOORD),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)0);							// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(0);

			// Colour
			glVertexAttribPointer(1,				// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				4,									// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,							// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,							// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_TEXCOORD),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(3 * sizeof(float)));		// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(1);

			// Texture coordinates
			glVertexAttribPointer(2,				// Index. Specifies the index in the shader of the generic vertex attribute to be modified.
				2,									// Size. Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
				GL_FLOAT,							// Type. Specifies the data type of each component in the array. The symbolic constants GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT and GL_UNSIGNED_INT are accepted
				GL_FALSE,							// Normalized. Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
				sizeof(Vertex_POS_COL_TEXCOORD),	// Stride. Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
				(void*)(7 * sizeof(float)));		// Pointer. Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
			glEnableVertexAttribArray(2);
			break;
		default:
			Throw("Invalid geometry data type set.");
			break;
		}

		// Unbind stuff as we're done
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void CResourceVertexBufferOpenGL::freeGPU(void)
	{
		if (prim->_mVertexBufferObject)
		{
			glDeleteBuffers(1, &prim->_mVertexBufferObject);
			prim->_mVertexBufferObject = 0;
		}
		if (prim->_mVertexArrayObject)
		{
			glDeleteVertexArrays(1, &prim->_mVertexArrayObject);
			prim->_mVertexArrayObject = 0;
		}
		if (prim->_mElementBufferObject)
		{
			glDeleteBuffers(1, &prim->_mElementBufferObject);
			prim->_mElementBufferObject = 0;
		}
	}

	void CResourceVertexBufferOpenGL::render(bool bWireframeMode) const
	{
		switch (eVertexBufferType)
		{
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL:
			if (!_mvecVertexData_POS_COL.size())
				return;
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD:
			if (!_mvecVertexData_POS_COL_NORMAL_TEXCOORD.size())
				return;
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORDx2:
			if (!_mvecVertexData_POS_COL_NORMAL_TEXCOORDx2.size())
				return;
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL:
			if (!_mvecVertexData_POS_COL_NORMAL_TEXCOORD_TANGENT_BINORMAL.size())
				return;
			break;
		case CResourceVertexBufferBase::EVertexBufferDataType::POS_COL_TEXCOORD:
			if (!_mvecVertexData_POS_COL_TEXCOORD.size())
				return;
			break;
		default:
			Throw("Invalid geometry data type set.");
			break;
		}

		if (!prim->_mVertexArrayObject)
			return;

		if (0 == _mvecIndices.size())
			return;

		if (bWireframeMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(prim->_mVertexArrayObject);
		glDrawElements(
			GL_TRIANGLES,					// Mode. Specifies what kind of primitives to render. Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.
			(GLsizei)_mvecIndices.size(),	// Count. Specifies the number of elements to be rendered.
			GL_UNSIGNED_INT,				// Type. Specifies the type of the values in indices. Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
			0);								// Indicies. Specifies a pointer to the location where the indices are stored. NOTE: We're using element buffer objects and using the indicies in that, so this is 0.
		glBindVertexArray(0);
	}

	/***********************************************************************************************************************************************************************
	************************************************************************************************************************************************************************
	* Vulkan
	************************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/

	/// \brief Private implementation for CResourceVertexBufferVulkan class
	///
	/// Holds all the members and methods which are private and which we do not wish to expose to any files
	class CResourceVertexBufferVulkan::CPrim
	{
	public:
		CPrim();
	};

	CResourceVertexBufferVulkan::CPrim::CPrim()
	{

	}

	CResourceVertexBufferVulkan::CResourceVertexBufferVulkan()
	{
		LOG("Constructor called.");
		prim = new CPrim;
		ThrowIfMemoryNotAllocated(prim);
	}

	CResourceVertexBufferVulkan::~CResourceVertexBufferVulkan()
	{
		LOG("Destructor called.");
		if (prim)
		{
			delete prim;
			prim = 0;
		}
	}

	void CResourceVertexBufferVulkan::uploadGPU(void)
	{

	}

	void CResourceVertexBufferVulkan::freeGPU(void)
	{

	}

	void CResourceVertexBufferVulkan::render(bool bWireframeMode) const
	{

	}
}	// namespace DCL
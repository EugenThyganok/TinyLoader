#include "TinyLoader.h"

#include <fstream>
#include <sstream>
#include <cstdlib>	//for atoi function

TinyLoader::TinyLoader(std::string objFile, std::string mtlFile)
{
	loadObjFile(objFile);
	loadMtlFIle(mtlFile);
}

void TinyLoader::loadObjFile(std::string filePath)
{
	std::ifstream inputStream(filePath);
	std::string fileLine;

	while (std::getline(inputStream, fileLine))
	{
		if (fileLine[0] == 'v' && fileLine[1] != 'n')
			parseVertex(vertices, &fileLine[2]);

		if (fileLine[0] == 'v' && fileLine[1] == 't')
			parseTexCoords(texCoords, &fileLine[2]);

		if (fileLine[0] == 'v' && fileLine[1] == 'n')
			parseVertex(normals, &fileLine[2]);

		if (fileLine[0] == 'f')
			parseIndices(&fileLine[2]);

	}

}

void TinyLoader::loadMtlFIle(std::string filePath)
{
	std::ifstream inputStream(filePath);
	std::string fileLine;

	while (std::getline(inputStream, fileLine))
	{
		if (fileLine.find("map_Kd") != std::string::npos)
			textureName = &fileLine[7];

		if (fileLine[0] == 'K' && fileLine[1] == 'a')
			parseMaterials(material.ambient, &fileLine[2]);

		if (fileLine[0] == 'K' && fileLine[1] == 'd')
			parseMaterials(material.diffusal, &fileLine[2]);

		if (fileLine[0] == 'K' && fileLine[1] == 's')
			parseMaterials(material.specular, &fileLine[2]);

		if (fileLine[0] == 'K' && fileLine[1] == 'e')
			parseMaterials(material.exponent, &fileLine[2]);

		if (fileLine[0] == 'N' && fileLine[1] == 'i')
		{
			float transperency;
			std::stringstream ss(&fileLine[2]);
			ss >> transperency;
			material.transparency = transperency;
		}
	}
}

void TinyLoader::parseIndices(std::string indexString)
{
	std::stringstream indexLineStream(indexString);
	std::string indices;

	std::vector<std::string> indexVector;	//create a vector of string of type x/y/z

	while (std::getline(indexLineStream, indices, ' '))
		indexVector.push_back(indices);

	for (std::string &i : indexVector) {
		int position = 0;
		std::stringstream s(i);
		std::string str;
		while (std::getline(s, str, '/'))
		{
			int index = atoi(str.c_str()) - 1;//use atoi func to cast string to int



			if (position == 0)
				generateVector(fVertices, vertices, index);
			if (position == 1 && index != -1)
				generateTexCoords(fTexcoords, texCoords, index);
			if (position == 2 && index != -1)
				generateVector(fNormals, normals, index);


			++position;
		}
	}
}

void TinyLoader::parseVertex(std::vector<glm::vec3>& vertices, const std::string & vertexString)
{
	std::stringstream vertexAttribStream(vertexString);
	float x, y, z;
	vertexAttribStream >> x >> y >> z;
	vertices.push_back(glm::vec3(x, y, z));
}

void TinyLoader::parseTexCoords(std::vector<glm::vec2>& texCoords, const std::string & texCoordsString)
{
	std::stringstream texCoordsStream(texCoordsString);
	float x, y;
	texCoordsStream >> x >> y;
	texCoords.push_back(glm::vec2(x, y));

}

void TinyLoader::parseMaterials(glm::vec3 &mat, const std::string &matString)
{
	std::stringstream vertexAttribStream(matString);
	float x, y, z;
	vertexAttribStream >> x >> y >> z;
	mat = glm::vec3(x, y, z);
}

void TinyLoader::generateVector(std::vector<glm::vec3>& fVertices, std::vector<glm::vec3>& vertices, int index)
{
	fVertices.push_back(vertices[index]);
}

void TinyLoader::generateTexCoords(std::vector<glm::vec2>& texCoords, std::vector<glm::vec2>& fTexCoords, int index)
{
	texCoords.push_back(fTexCoords[index]);
}

std::string &TinyLoader::getTextureName()
{
	return textureName;
}

Material * TinyLoader::getMaterialStruct()
{
	return &material;
}

std::vector<glm::vec3> &TinyLoader::getVertices()
{
	return fVertices;
}

std::vector<glm::vec3>& TinyLoader::getNormals()
{
	return fNormals;
}

std::vector<glm::vec2>& TinyLoader::getTexcoords()
{
	return fTexcoords;
}


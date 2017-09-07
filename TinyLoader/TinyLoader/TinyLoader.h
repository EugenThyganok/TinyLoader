/*Create by Eugen work started 16.08.17 10:28
finished	20.06.17 13:53
GitHub Repo */

/*Simple .obj and .mtl file parser
used to get file data in a format
opengl needs. */

/*TODO
Enable file loading +
Parse through the file +
Write the parsed or processed
data into vectors of
vertices, normals, texcoords +
Enable external programs to use
that data in simple most manner +
Use mtl files				+
Store the program in lib format
for later use

27.08.17 Fix the bug which result in vector
index out of bound when no texCoords provided
07.09.17 Bug is fixed appeared that in the
processIndices method when no texCoord provided
index is equal to -1, position counter was
incremented and we try to write element into
vector at -1 position. */


#ifndef TINY_LOADER_H
#define TINY_LOADER_H

//STL libraries
#include <string>
#include <vector>

//glm libraries
#include <glm.hpp>

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffusal;
	glm::vec3 specular;
	glm::vec3 exponent;

	float transparency;
};


class TinyLoader
{
public:
	TinyLoader(std::string objFile, std::string mtlFile);

	void loadObjFile(std::string filePath);
	void loadMtlFIle(std::string filePath);

	std::vector<glm::vec3> &getVertices();
	std::vector<glm::vec3> &getNormals();
	std::vector<glm::vec2> &getTexcoords();

	std::string &getTextureName();

	Material *getMaterialStruct();
protected:
	//bool mtlFileWasRead = false;
	void parseVertex(std::vector<glm::vec3> &vertices, const std::string &vertexString);
	void parseIndices(std::string indexString);
	void parseTexCoords(std::vector<glm::vec2> &texCoords, const std::string &texCoordsString);
	void generateTexCoords(std::vector<glm::vec2> &fTexCoords, std::vector<glm::vec2> &texCoords, int index);
	void generateVector(std::vector<glm::vec3> &fVertices, std::vector<glm::vec3> &vertices, int index);

	void parseMaterials(glm::vec3 &material, const std::string &matString);

	//Used to temporarily store unprocessed vertex data (stored just like it was declared in the file)
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	//Final vertex data in format suitable for opengl
	std::vector<glm::vec2> fTexcoords;
	std::vector<glm::vec3> fVertices;
	std::vector<glm::vec3> fNormals;

	Material material;

	//Texture name if any retrived from mtl file
	std::string textureName;
};

#endif
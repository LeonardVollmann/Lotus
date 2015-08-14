#include "objloading.hpp"
#include "../core/stringfunc.hpp"

#include <fstream>
#include <iostream>

namespace lotus { namespace graphics {

	OBJModel::OBJModel(const std::string &fileName)
	{
		std::ifstream file;
		file.open("res/models/" + fileName + ".obj", std::ios::in | std::ios::binary);

		if (file.is_open())
		{
			std::string line;
			while (file.good())
			{
				getline(file, line);
				removeWhiteSpaceFront(line);
				
				std::vector<std::string> tokens = tokenize(line, ' ');
				
				if (line[0] == 'v')
				{
					if (line[1] == 't')
					{
						m_texCoords.push_back(maths::vec2(atof(tokens[1].c_str()), atof(tokens[2].c_str())));
					}
					else if (line[1] == 'n')
					{
						m_normals.push_back(maths::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str())));
					}
					else
					{
						m_positions.push_back(maths::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str())));
					}
				}
				else if (line[0] == 'f')
				{
					const unsigned int numTokens = tokens.size();
					for (unsigned int i = 0; i < numTokens - 3; i++)
					{
						m_indices.push_back(parseOBJIndex(tokens[1], numTokens));
						m_indices.push_back(parseOBJIndex(tokens[2 + i], numTokens));
						m_indices.push_back(parseOBJIndex(tokens[3 + i], numTokens));
					}
				}
			}
		}
        else
        {
            std::cerr << "ERROR: Failed to load model: " << fileName << std::endl;
        }
	}

	OBJIndex OBJModel::parseOBJIndex(const std::string &token, unsigned int numTokens)
	{
		bool hasDoubleSlash = contains(token, "//");

		OBJIndex result;
		std::vector<std::string> indexTokens = tokenize(token, '/');

		result.positionIndex = stoi(indexTokens[0]) - 1;
		if (numTokens > 1)
		{
			if (hasDoubleSlash)
			{
				result.normalIndex = stoi(indexTokens[1]) - 1;
				m_hasTexCoords = false;
				m_hasNormals = true;
			}
			else
			{
				result.texCoordIndex = stoi(indexTokens[1]) - 1;
				m_hasTexCoords = true;
				m_hasNormals = false;
			}
			if (indexTokens.size() == 3)
			{
				result.normalIndex = stoi(indexTokens[2]) - 1;
				m_hasTexCoords = true;
				m_hasNormals = true;
			}
		}
		else
		{
			m_hasTexCoords = false;
			m_hasNormals = false;
		}

		return result;
	}

} }

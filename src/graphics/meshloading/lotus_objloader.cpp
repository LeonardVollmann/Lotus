#include "lotus_objloader.hpp"
#include "../../utils/lotus_fileutils.hpp"

#include <GL/glew.h>
#include <string.h>
#include <stdlib.h>

namespace lotus { namespace graphics { 

	IndexedModel OBJLoader::loadIndexedModel(const std::string &fileName)
	{
		IndexedModel result;

		std::string text = FileUtils::readFile("res/models/" + fileName + ".obj");
		char *ctext = new char[text.length() + 1];
		strcpy(ctext, text.c_str());

		std::vector<char*> lines;

		char *save_line;
		char *line = strtok_r(ctext, "\n", &save_line);
		while (line)
		{
			if (line[0] != '#' && line[0] != '\n' && line[0] != ' ' && line[0] != '\0')
			{
				std::vector<char*> tokens;

				char *save_token;
				char *token = strtok_r(line, " ", &save_token);
				while (token)
				{
					tokens.push_back(token);

					token = strtok_r(NULL, " ", &save_token);
				}

				if (strcmp(tokens[0], "v") == 0)
				{
					float v[3];
					for (unsigned int i = 0; i < 3; i++)
					{
						v[i] = atof(tokens[i + 1]);
					}

					result.addVertex(v[0], v[1], v[2]);
				}
				else if (strcmp(tokens[0], "vt") == 0)
				{
					float v[2];
					for (unsigned int i = 0; i < 2; i++)
					{
						v[i] = atof(tokens[i + 1]);
					}

					result.addTexCoord(v[0], v[1]);
				}
				else if (strcmp(tokens[0], "vn") == 0)
				{
					float v[3];
					for (unsigned int i = 0; i < 3; i++)
					{
						v[i] = atof(tokens[i + 1]);
					}

					result.addNormal(v[0], v[1], v[2]);
				}
				else if (strcmp(tokens[0], "f") == 0)
				{
					int numIndices = tokens.size() - 1;
					GLushort indices[numIndices];
					for (unsigned int i = 0; i < numIndices; i++)
					{
						indices[i] = (GLushort) atoi(tokens[i + 1]) - 1;
					}

					result.addFace(indices[0], indices[1], indices[2]);
				}
			}

			line = strtok_r(NULL, "\n", &save_line);
		}

		delete ctext;
		return result;
	}

} }
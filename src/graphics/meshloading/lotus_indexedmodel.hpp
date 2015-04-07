#ifndef LOTUS_INDEXED_MODEL_HPP_INCLUDED
#define LOTUS_INDEXED_MODEL_HPP_INCLUDED

#include <GL/glew.h>
#include <vector>

namespace lotus { namespace graphics { 

	class IndexedModel
	{
	private:
		std::vector<GLfloat> 	m_vertices;
		std::vector<GLfloat>	m_texCoords;
		std::vector<GLfloat> 	m_normals;
		std::vector<GLushort> 	m_indices;
	public:
		IndexedModel(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &texCoords, const std::vector<GLfloat> &normals, const std::vector<GLushort> &indices);
		IndexedModel() {}

		void addVertex(GLfloat x, GLfloat y, GLfloat z);
		void addTexCoord(GLfloat x, GLfloat y);
		void addNormal(GLfloat x, GLfloat y, GLfloat z);
		void addFace(GLushort i1, GLushort i2, GLushort i3);

		bool isValid();
		IndexedModel &finalize();

		inline const std::vector<GLfloat> &getVertices() 	const { return m_vertices; }
		inline const std::vector<GLfloat> &getTexCoords() 	const { return m_texCoords; }
		inline const std::vector<GLfloat> &getNormals() 	const { return m_normals; }
		inline const std::vector<GLushort> &getIndices() 	const { return m_indices; }
	private:
		void calcNormals();
	};

} }

#endif
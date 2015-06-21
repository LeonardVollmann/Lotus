#ifndef LOTUS_INDEXED_MODEL_HPP_INCLUDED
#define LOTUS_INDEXED_MODEL_HPP_INCLUDED

#include "lotus_vertex.hpp"

#include <GL/glew.h>
#include <vector>

class IndexedModel
{
private:
	std::vector<GLfloat> 	m_positions;
	std::vector<GLfloat>	m_texCoords;
	std::vector<GLfloat> 	m_normals;
	std::vector<GLfloat>	m_tangents;
	std::vector<GLushort> 	m_indices;
	std::vector<Vertex3D>	m_vertices;
public:
	IndexedModel(const std::vector<GLfloat> &positions, const std::vector<GLfloat> &texCoords, const std::vector<GLfloat> &normals, const std::vector<GLfloat> &tangents, const std::vector<GLushort> &indices);
	IndexedModel() {}

	void addPosition(GLfloat x, GLfloat y, GLfloat z);
	void addTexCoord(GLfloat x, GLfloat y);
	void addNormal(GLfloat x, GLfloat y, GLfloat z);
	void addTangent(GLfloat x, GLfloat y, GLfloat z);
	void addFace(GLushort i1, GLushort i2, GLushort i3);

	bool isValid();
	IndexedModel &finalize();

	inline const std::vector<Vertex3D> &getVertices() 	const { return m_vertices; }
	inline const std::vector<GLushort> &getIndices() 	const { return m_indices; }
private:
	void calcNormals();
	void calcTangents();
};

#endif

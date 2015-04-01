#include "lotus_indexedmodel.hpp"

#include <iostream>

namespace lotus { namespace graphics { 

	IndexedModel::IndexedModel(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &texCoords,
		const std::vector<GLfloat> &normals, const std::vector<GLushort> &indices) :
		m_vertices(vertices),
		m_texCoords(texCoords),
		m_normals(normals),
		m_indices(indices)
	{}

	void IndexedModel::addVertex(GLfloat x, GLfloat y, GLfloat z)
	{
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		m_vertices.push_back(z);
	}

	void IndexedModel::addTexCoord(GLfloat x, GLfloat y)
	{
		m_texCoords.push_back(x);
		m_texCoords.push_back(y);
	}

	void IndexedModel::addNormal(GLfloat x, GLfloat y, GLfloat z)
	{
		m_normals.push_back(x);
		m_normals.push_back(y);
		m_normals.push_back(z);
	}

	void IndexedModel::addFace(GLushort i1, GLushort i2, GLushort i3)
	{
		m_indices.push_back(i1);
		m_indices.push_back(i2);
		m_indices.push_back(i3);
	}

	void IndexedModel::finalize()
	{
		if (m_vertices.size() == m_texCoords.size() &&
			m_vertices.size() == m_normals.size())
		{
			return;
		} 

		if (m_texCoords.size() < m_vertices.size())
		{
			for (int i = m_texCoords.size(); i < m_vertices.size(); i++)
			{
				m_texCoords.push_back(0.0f);
			}
		}

		if (m_normals.size() < m_vertices.size())
		{
			calcNormals();
		}
	}

	void IndexedModel::calcNormals()
	{
		for (int i = m_normals.size(); i < m_vertices.size(); i++)
		{
			m_normals.push_back(0.0f);
		}
	}

} }
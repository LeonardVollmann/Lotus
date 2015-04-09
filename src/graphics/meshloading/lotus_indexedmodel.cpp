#include "lotus_indexedmodel.hpp"
#include "../../maths/lotus_vec3.hpp"

#include <iostream>

namespace lotus { namespace graphics { 

	IndexedModel::IndexedModel(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &texCoords,
		const std::vector<GLfloat> &normals, const std::vector<GLushort> &indices) :
		m_vertices(vertices),
		m_texCoords(texCoords),
		m_normals(normals),
		m_indices(indices) {}

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

	bool IndexedModel::isValid()
	{
		return m_vertices.size() == m_texCoords.size() && m_vertices.size() == m_normals.size();
	}

	IndexedModel &IndexedModel::finalize()
	{
		if (isValid())
		{
			return *this;
		} 

		if (m_texCoords.size() < m_vertices.size())
		{
			for (unsigned int i = m_texCoords.size(); i < m_vertices.size(); i++)
			{
				m_texCoords.push_back(0.0f);
			}
		}

		if (m_normals.size() < m_vertices.size())
		{
			calcNormals();
		}

		return *this;
	}

	void IndexedModel::calcNormals()
	{
		using namespace maths;

		m_normals.clear();
		m_normals.reserve(m_vertices.size());
		
		for(unsigned int i = 0; i < m_vertices.size() * 3; i++)
		{
			m_normals.push_back(0.0f);
		}

		for(unsigned int i = 0; i < m_indices.size(); i += 3)
		{
			GLushort i0 = m_indices[i];
			GLushort i1 = m_indices[i + 1];
			GLushort i2 = m_indices[i + 2];
			
			vec3 v0(m_vertices[i0 * 3 + 0], m_vertices[i0 * 3 + 1], m_vertices[i0 * 3 + 2]);
			vec3 v1(m_vertices[i1 * 3 + 0], m_vertices[i1 * 3 + 1], m_vertices[i1 * 3 + 2]);
			vec3 v2(m_vertices[i2 * 3 + 0], m_vertices[i2 * 3 + 1], m_vertices[i2 * 3 + 2]);

			vec3 d1 = v1 - v0;
			vec3 d2 = v2 - v0;
			
			vec3 normal = cross(d1, d2).normalize();
			
			for (unsigned int j = 0; j < 3; j++)
			{
				unsigned int index = (i0 + j) * 3;
				m_normals[index + 0] = m_normals[index + 0] + normal.x;
				m_normals[index + 1] = m_normals[index + 1] + normal.y;
				m_normals[index + 2] = m_normals[index + 2] + normal.z;
			}
		}
		
		// for(int i = 0; i < m_normals.size(); i += 3)
		// {
		// 	vec3 normal = vec3(m_normals[i], m_normals[i + 1], m_normals[i + 2]).normalize();

		// 	m_normals[i + 0] = normal.x;
		// 	m_normals[i + 1] = normal.y;
		// 	m_normals[i + 2] = normal.z;
		// }
	}

} }
#include "indexedmodel.hpp"
#include "../maths/vec3.hpp"

#include <iostream>

namespace lotus { namespace graphics {

	IndexedModel::IndexedModel(const std::vector<GLfloat> &positions, const std::vector<GLfloat> &texCoords, const std::vector<GLfloat> &normals, const std::vector<GLfloat> &tangents, const std::vector<GLushort> &indices) :
		m_positions(positions),
		m_texCoords(texCoords),
		m_normals(normals),
		m_tangents(tangents),
		m_indices(indices) {}

	void IndexedModel::addPosition(GLfloat x, GLfloat y, GLfloat z)
	{
		m_positions.push_back(x);
		m_positions.push_back(y);
		m_positions.push_back(z);
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

	void IndexedModel::addTangent(GLfloat x, GLfloat y, GLfloat z)
	{
		m_tangents.push_back(x);
		m_tangents.push_back(y);
		m_tangents.push_back(z);
	}

	void IndexedModel::addFace(GLushort i1, GLushort i2, GLushort i3)
	{
		m_indices.push_back(i1);
		m_indices.push_back(i2);
		m_indices.push_back(i3);
	}

	bool IndexedModel::isValid()
	{
		return m_positions.size() / 3 == m_texCoords.size() / 2 && m_positions.size() == m_normals.size() && m_positions.size() == m_tangents.size();
	}

	IndexedModel &IndexedModel::finalize()
	{
		if (isValid())
		{
			return *this;
		} 

		if (m_texCoords.size() < m_positions.size())
		{
			for (unsigned int i = (unsigned int) m_texCoords.size(); i < m_positions.size(); i++)
			{
				m_texCoords.push_back(0.0f);
			}
		}

		if (m_normals.size() < m_positions.size())
		{
			calcNormals();
		}
		
		if (m_tangents.size() < m_positions.size())
		{
			calcTangents();
		}
		
		unsigned int j = 0;
		for (unsigned int i = 0; i < m_positions.size(); i += 3) {
			m_vertices.push_back(Vertex3D(maths::vec3(m_positions[i + 0], m_positions[i + 1], m_positions[i + 2]),
										  maths::vec2(m_texCoords[j + 0], m_texCoords[j + 1]),
										  maths::vec3(m_normals[i + 0], m_normals[i + 1], m_normals[i + 2]),
										  maths::vec3(m_tangents[i + 0], m_tangents[i + 1], m_tangents[i + 2])));
			
			m_vertices[i / 3].normal.normalize();
			m_vertices[i / 3].tangent.normalize();
			
			j += 2;
		}
		
		m_positions.clear();
		m_texCoords.clear();
		m_normals.clear();
		m_tangents.clear();

		return *this;
	}

	void IndexedModel::calcNormals()
	{
		m_normals.clear();
		m_normals.reserve(m_positions.size());
		
		for (unsigned int i = 0; i < m_positions.size(); i++)
		{
			m_normals.push_back(0.0f);
		}

		for (unsigned int i = 0; i < m_indices.size(); i += 3)
		{
			GLushort i0 = m_indices[i];
			GLushort i1 = m_indices[i + 1];
			GLushort i2 = m_indices[i + 2];
			
			maths::vec3 v0(m_positions[i0 * 3 + 0], m_positions[i0 * 3 + 1], m_positions[i0 * 3 + 2]);
			maths::vec3 v1(m_positions[i1 * 3 + 0], m_positions[i1 * 3 + 1], m_positions[i1 * 3 + 2]);
			maths::vec3 v2(m_positions[i2 * 3 + 0], m_positions[i2 * 3 + 1], m_positions[i2 * 3 + 2]);

			maths::vec3 d1 = v1 - v0;
			maths::vec3 d2 = v2 - v0;
			
			maths::vec3 normal = d1.cross(d2);
			
			for (unsigned int j = 0; j < 3; j++)
			{
				unsigned int index = (i0 + j) * 3;
				m_normals[index + 0] = m_normals[index + 0] + normal.x;
				m_normals[index + 1] = m_normals[index + 1] + normal.y;
				m_normals[index + 2] = m_normals[index + 2] + normal.z;
			}
		}
	}

	void IndexedModel::calcTangents()
	{
		m_tangents.clear();
		m_tangents.reserve(m_positions.size());
		
		for (unsigned int i = 0; i < m_positions.size(); i++)
		{
			m_tangents.push_back(0.0f);
		}
		
		for (unsigned int i = 0; i < m_indices.size(); i += 3)
		{
			GLushort i0 = m_indices[i];
			GLushort i1 = m_indices[i + 1];
			GLushort i2 = m_indices[i + 2];
			
			maths::vec3 v0(m_positions[i0 * 3 + 0], m_positions[i0 * 3 + 1], m_positions[i0 * 3 + 2]);
			maths::vec3 v1(m_positions[i1 * 3 + 0], m_positions[i1 * 3 + 1], m_positions[i1 * 3 + 2]);
			maths::vec3 v2(m_positions[i2 * 3 + 0], m_positions[i2 * 3 + 1], m_positions[i2 * 3 + 2]);
			
			maths::vec3 edge0 = v1 - v0;
			maths::vec3 edge1 = v2 - v0;
			
			float deltaU0 = m_texCoords[i1 * 2 + 0] - m_texCoords[i0 * 2 + 0];
			float deltaU1 = m_texCoords[i2 * 2 + 0] - m_texCoords[i0 * 2 + 0];
			float deltaV0 = m_texCoords[i1 * 2 + 1] - m_texCoords[i0 * 2 + 1];
			float deltaV1 = m_texCoords[i2 * 2 + 1] - m_texCoords[i0 * 2 + 1];
			
			float dividend = (deltaU0 * deltaV1 - deltaU1 * deltaV0);
			float f = dividend == 0.0f ? 0.0f : 1.0f / dividend;
			
			maths::vec3 tangent = maths::vec3::ZERO;
			tangent.x = f * (deltaV1 * edge0.x - deltaV0 * edge1.x);
			tangent.y = f * (deltaV1 * edge0.y - deltaV0 * edge1.y);
			tangent.z = f * (deltaV1 * edge0.z - deltaV0 * edge1.z);
			
			for (unsigned int j = 0; j < 3; j++)
			{
				unsigned int index = (i0 + j) * 3;
				m_tangents[index + 0] = m_tangents[index + 0] + tangent.x;
				m_tangents[index + 1] = m_tangents[index + 1] + tangent.y;
				m_tangents[index + 2] = m_tangents[index + 2] + tangent.z;
			}
		}
	}

} }
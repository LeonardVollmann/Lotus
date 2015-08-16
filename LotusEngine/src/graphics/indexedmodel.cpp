#include "indexedmodel.hpp"
#include "../core/stringfunc.hpp"

#include <iostream>
#include <fstream>

namespace lotus { namespace graphics {

	IndexedModel::IndexedModel(const std::vector<maths::vec3> &positions, const std::vector<maths::vec2> &texCoords,
							const std::vector<maths::vec3> &normals, const std::vector<maths::vec3> &tangents,
							const std::vector<GLushort> &indices) :
		m_positions(positions),
		m_texCoords(texCoords),
		m_normals(normals),
		m_tangents(tangents),
		m_indices(indices) {}

	IndexedModel::IndexedModel(OBJModel objModel)
	{
		for (unsigned int i = 0; i < objModel.getIndices().size(); i++)
		{
			const OBJIndex &index = objModel.getIndices()[i];
			maths::vec3 position = objModel.getPositions()[index.positionIndex];
			maths::vec2 texCoord = objModel.hasTexCoords() ? objModel.getTexCoords()[index.texCoordIndex] : maths::vec2::ZERO;
			maths::vec3 normal = objModel.hasNormals() ? objModel.getNormals()[index.normalIndex] : maths::vec3::ZERO;

			m_positions.push_back(position);
			m_texCoords.push_back(texCoord);
			if (normal != maths::vec3::ZERO)
			{
				m_normals.push_back(normal);
			}
			m_indices.push_back(i);
		}
		
		finalize();
	}

	IndexedModel::IndexedModel(const std::string &fileName) :
		IndexedModel(OBJModel(fileName)) {}

	void IndexedModel::addPosition(const maths::vec3 &position)
	{
		m_positions.push_back(position);
	}

	void IndexedModel::addTexCoord(const maths::vec2 &texCoord)
	{
		m_texCoords.push_back(texCoord);
	}

	void IndexedModel::addNormal(const maths::vec3 &normal)
	{
		m_normals.push_back(normal);
	}

	void IndexedModel::addTangent(const maths::vec3 &tangent)
	{
		m_tangents.push_back(tangent);
	}

	void IndexedModel::addFace(GLushort i1, GLushort i2, GLushort i3)
	{
		m_indices.push_back(i1);
		m_indices.push_back(i2);
		m_indices.push_back(i3);
	}

	bool IndexedModel::isValid()
	{
		return m_positions.size() / 3 == m_texCoords.size() / 2 &&
				m_positions.size() == m_normals.size() && m_positions.size() == m_tangents.size();
	}

	IndexedModel &IndexedModel::finalize()
	{
		if (isValid())
		{
			return *this;
		}

		if (m_normals.size() < m_positions.size())
		{
			calcNormals();
		}

		calcTangents();

		for (unsigned int i = 0; i < m_positions.size(); i++)
		{
			Vertex3D vertex;
			vertex.position = m_positions[i];
			vertex.texCoord = m_texCoords[i];
			vertex.normal = m_normals[i];
			vertex.tangent = m_tangents[i];
			m_vertices.push_back(vertex);
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
			m_normals.push_back(maths::vec3(0.0f));
		}

		for (unsigned int i = 0; i < m_indices.size(); i += 3)
		{
			GLushort i0 = m_indices[i];
			GLushort i1 = m_indices[i + 1];
			GLushort i2 = m_indices[i + 2];

			maths::vec3 d1 = m_positions[i1] - m_positions[i0];
			maths::vec3 d2 = m_positions[i2] - m_positions[i0];

			maths::vec3 normal = d1.cross(d2);

			m_normals[i0] += normal;
			m_normals[i1] += normal;
			m_normals[i2] += normal;
		}

		for (auto it = m_normals.begin(); it < m_normals.end(); it++)
		{
			it->normalize();
		}
	}

	void IndexedModel::calcTangents()
	{
		m_tangents.reserve(m_positions.size());

		for (unsigned int i = 0; i < m_positions.size(); i++)
		{
			m_tangents.push_back(maths::vec3(0.0f));
		}

		for (unsigned int i = 0; i < m_indices.size(); i += 3)
		{
			GLushort i0 = m_indices[i];
			GLushort i1 = m_indices[i + 1];
			GLushort i2 = m_indices[i + 2];

			maths::vec3 edge0 = m_positions[i1] - m_positions[i0];
			maths::vec3 edge1 = m_positions[i2] - m_positions[i0];

			maths::vec2 deltaUV0 = m_texCoords[i1] - m_texCoords[i0];
			maths::vec2 deltaUV1 = m_texCoords[i2] - m_texCoords[i0];

			float dividend = (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);
			float f = dividend == 0.0f ? 0.0f : 1.0f / dividend;

			maths::vec3 tangent = (edge0 * deltaUV1.y - edge1 * deltaUV0.y) * f;
			
			m_tangents[i0] += tangent;
			m_tangents[i1] += tangent;
			m_tangents[i2] += tangent;
		}

		for (auto it = m_tangents.begin(); it < m_tangents.end(); it++)
		{
			it->normalize();
		}
	}

} }
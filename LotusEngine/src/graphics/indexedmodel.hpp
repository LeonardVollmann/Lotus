#ifndef LOTUS_INDEXED_MODEL_HPP_INCLUDED
#define LOTUS_INDEXED_MODEL_HPP_INCLUDED

#include "vertex.hpp"
#include "objloading.hpp"
#include "../core/maths.hpp"

#include <GL/glew.h>
#include <vector>

namespace lotus { namespace graphics {

	class IndexedModel
	{
	private:
		std::vector<maths::Vector3f>	m_positions;
		std::vector<maths::Vector2f>	m_texCoords;
		std::vector<maths::Vector3f>	m_normals;
		std::vector<maths::Vector3f>	m_tangents;
		std::vector<GLushort>		m_indices;
		std::vector<Vertex3D>		m_vertices;
	public:
		IndexedModel(const std::vector<maths::Vector3f> &positions, const std::vector<maths::Vector2f> &texCoords,
					const std::vector<maths::Vector3f> &normals, const std::vector<maths::Vector3f> &tangents,
					const std::vector<GLushort> &indices);
		IndexedModel(OBJModel objModel);
		IndexedModel(const std::string &fileName);
		IndexedModel() {}

		bool isValid();
		IndexedModel &finalize();

		void addPosition(const maths::Vector3f &position);
		void addTexCoord(const maths::Vector2f &texCoord);
		void addNormal(const maths::Vector3f &normal);
		void addTangent(const maths::Vector3f &tangent);
		void addFace(GLushort i1, GLushort i2, GLushort i3);

		inline const std::vector<Vertex3D> &getVertices() 	const { return m_vertices; }
		inline const std::vector<GLushort> &getIndices() 	const { return m_indices; }
	private:
		void calcNormals();
		void calcTangents();
	};

} }

#endif

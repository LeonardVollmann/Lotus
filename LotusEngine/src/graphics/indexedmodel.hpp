#ifndef LOTUS_INDEXED_MODEL_HPP_INCLUDED
#define LOTUS_INDEXED_MODEL_HPP_INCLUDED

#include "vertex.hpp"
#include "objloading.hpp"
#include "../maths/types.hpp"

#include <GL/glew.h>
#include <vector>

namespace lotus { namespace graphics {

	class IndexedModel
	{
	public:
		IndexedModel(const std::vector<maths::vec3f> &positions, const std::vector<maths::vec2f> &texCoords,
					const std::vector<maths::vec3f> &normals, const std::vector<maths::vec3f> &tangents,
					const std::vector<GLushort> &indices);
		IndexedModel(OBJModel objModel);
		IndexedModel(const std::string &fileName);
		IndexedModel() {}

		bool isValid();
		IndexedModel &finalize();

		void addPosition(const maths::vec3f &position);
		void addTexCoord(const maths::vec2f &texCoord);
		void addNormal(const maths::vec3f &normal);
		void addTangent(const maths::vec3f &tangent);
		void addFace(GLushort i1, GLushort i2, GLushort i3);

		inline const std::vector<Vertex3D> &getVertices() 	const { return m_vertices; }
		inline const std::vector<GLushort> &getIndices() 	const { return m_indices; }
	private:
		void calcNormals();
		void calcTangents();
	private:
		std::vector<maths::vec3f>	m_positions;
		std::vector<maths::vec2f>	m_texCoords;
		std::vector<maths::vec3f>	m_normals;
		std::vector<maths::vec3f>	m_tangents;
		std::vector<GLushort>			m_indices;
		std::vector<Vertex3D>			m_vertices;
	};

} }

#endif

#ifndef LOTUS_INDEXED_MODEL_HPP_INCLUDED
#define LOTUS_INDEXED_MODEL_HPP_INCLUDED

#include "vertex.hpp"
#include "objloading.hpp"
#include "../maths/vec2.hpp"
#include "../maths/vec3.hpp"

#include <GL/glew.h>
#include <vector>

namespace lotus { namespace graphics {

	class IndexedModel
	{
	private:
		std::vector<maths::vec3>	m_positions;
		std::vector<maths::vec2>	m_texCoords;
		std::vector<maths::vec3>	m_normals;
		std::vector<maths::vec3>	m_tangents;
		std::vector<GLushort>		m_indices;
		std::vector<Vertex3D>		m_vertices;
	public:
		IndexedModel(const std::vector<maths::vec3> &positions, const std::vector<maths::vec2> &texCoords,
					const std::vector<maths::vec3> &normals, const std::vector<maths::vec3> &tangents,
					const std::vector<GLushort> &indices);
		IndexedModel(OBJModel objModel);
		IndexedModel(const std::string &fileName);
		IndexedModel() {}

		bool isValid();
		IndexedModel &finalize();

		void addPosition(const maths::vec3 &position);
		void addTexCoord(const maths::vec2 &texCoord);
		void addNormal(const maths::vec3 &normal);
		void addTangent(const maths::vec3 &tangent);
		void addFace(GLushort i1, GLushort i2, GLushort i3);

		inline const std::vector<Vertex3D> &getVertices() 	const { return m_vertices; }
		inline const std::vector<GLushort> &getIndices() 	const { return m_indices; }
	private:
		void calcNormals();
		void calcTangents();
	};

} }

#endif

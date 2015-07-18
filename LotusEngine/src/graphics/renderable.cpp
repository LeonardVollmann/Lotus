#include "renderable.hpp"
#include "objloader.hpp"

#include <typeinfo>
#include <cstdlib>

namespace lotus { namespace graphics {

	template<typename VERTEX_T>
	Renderable<VERTEX_T>::Renderable(const VERTEX_T *vertices, const GLushort *indices, GLsizei numVertices, GLsizei numIndices) :
		m_vertices(vertices),
		m_indices(indices),
		m_numVertices(numVertices),
		m_numIndices(numIndices)
	{
		unsigned char vertexType = 0;
		const std::type_info &vertexInfo = typeid(VERTEX_T);
		if (vertexInfo == typeid(Vertex2D))
		{
			vertexType = VERTEX_TYPE_2D;
		}
		else if (vertexInfo == typeid(Vertex3D))
		{
			vertexType = VERTEX_TYPE_3D;
		}
		
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(VERTEX_T), m_vertices, GL_STATIC_DRAW);
		
		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLushort), m_indices, GL_STATIC_DRAW);
		
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		if (vertexType & VERTEX_POSITION)
		{
			glEnableVertexAttribArray(ATTRIB_LOCATION_POSITION);
			glVertexAttribPointer(ATTRIB_LOCATION_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_T), (const GLvoid*) offsetof(VERTEX_T, position));
		}
		if (vertexType & VERTEX_TEXCOORD)
		{
			glEnableVertexAttribArray(ATTRIB_LOCATION_TEXCOORD);
			glVertexAttribPointer(ATTRIB_LOCATION_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_T), (const GLvoid*) offsetof(VERTEX_T, texCoord));
		}
		if (vertexType & VERTEX_NORMAL)
		{
			glEnableVertexAttribArray(ATTRIB_LOCATION_NORMAL);
			glVertexAttribPointer(ATTRIB_LOCATION_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_T), (const GLvoid*) offsetof(Vertex3D, normal));
		}
		if (vertexType & VERTEX_TANGENT)
		{
			glEnableVertexAttribArray(ATTRIB_LOCATION_TANGENT);
			glVertexAttribPointer(ATTRIB_LOCATION_TANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_T), (const GLvoid*) offsetof(Vertex3D, tangent));
		}
	}

	template<typename VERTEX_T>
	Renderable<VERTEX_T>::Renderable(IndexedModel indexedModel) :
		Renderable<VERTEX_T>((const VERTEX_T*) indexedModel.getVertices().data(), indexedModel.getIndices().data(), (GLsizei) indexedModel.getVertices().size(), (GLsizei) indexedModel.getIndices().size()) {}

	template<typename VERTEX_T>
	Renderable<VERTEX_T>::Renderable(const std::string &fileName) :
		Renderable<VERTEX_T>(OBJLoader::loadIndexedModel(fileName).finalize()) {}

	template<typename VERTEX_T>
	Renderable<VERTEX_T>::~Renderable()
	{
		glDeleteBuffers(1, &m_ibo);
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}

	template<typename VERTEX_T>
	void Renderable<VERTEX_T>::bind() const
	{
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	}

	template class Renderable<Vertex2D>;
	template class Renderable<Vertex3D>;

} }
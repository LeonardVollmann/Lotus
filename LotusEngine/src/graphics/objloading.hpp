#ifndef LOTUS_OBJ_LOADING_HPP_INCLUDED
#define LOTUS_OBJ_LOADING_HPP_INCLUDED

#include "../maths/types.hpp"

#include <vector>
#include <string>

namespace lotus { namespace graphics {

	struct OBJIndex
	{
		unsigned int positionIndex;
		unsigned int texCoordIndex;
		unsigned int normalIndex;
	};

	class OBJModel
	{
	public:
		OBJModel(const std::string &fileName);

		inline const std::vector<OBJIndex> &getIndices() 		const { return m_indices; }
		inline const std::vector<maths::vec3f> &getPositions() 	const { return m_positions; }
		inline const std::vector<maths::vec2f> &getTexCoords() 	const { return m_texCoords; }
		inline const std::vector<maths::vec3f> &getNormals() 	const { return m_normals; }
		inline bool hasTexCoords() 								const { return m_hasTexCoords;}
		inline bool hasNormals()								const { return m_hasNormals; }
	protected:
	private:
		OBJIndex parseOBJIndex(const std::string &token, unsigned int numTokens);

		std::vector<OBJIndex>		m_indices;
		std::vector<maths::vec3f>	m_positions;
		std::vector<maths::vec2f>	m_texCoords;
		std::vector<maths::vec3f>	m_normals;
		bool						m_hasTexCoords;
		bool						m_hasNormals;
	};

} }

#endif

#ifndef LOTUS_OBJ_LOADER_HPP_INCLUDED
#define LOTUS_OBJ_LOADER_HPP_INCLUDED

#include "indexedmodel.hpp"

#include <string>
#include <vector>

namespace lotus { namespace graphics {

	class OBJLoader
	{
	public:
		static IndexedModel loadIndexedModel(const std::string &fileName);
	};

} }

#endif
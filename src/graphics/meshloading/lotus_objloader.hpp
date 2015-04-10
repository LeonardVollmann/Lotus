#ifndef LOTUS_OBJ_LOADER_HPP_INCLUDED
#define LOTUS_OBJ_LOADER_HPP_INCLUDED

#include "lotus_indexedmodel.hpp"

#include <string>
#include <vector>

class OBJLoader
{
public:
	static IndexedModel loadIndexedModel(const std::string &fileName);
};

#endif
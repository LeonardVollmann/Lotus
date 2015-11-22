#pragma once

#include "../id.hpp"

#include <vector>
#include <deque>

namespace lotus
{

#define ENTITY_MANAGER_MIN_FREE_INDICES 1024

typedef ID<24, 8> EntityID;

class EntityWorld
{
private:
	std::vector<unsigned char> m_generation;
	std::deque<unsigned int> m_freeIndices;

public:
	EntityID create();
	void destroy(const EntityID &entity);
	bool alive(const EntityID &entity);
};

} // namespace lotus
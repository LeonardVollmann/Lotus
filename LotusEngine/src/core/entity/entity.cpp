#include "entity.hpp"

namespace lotus {

	EntityID EntityWorld::create()
	{
		unsigned int index;
  		if (m_freeIndices.size() > ENTITY_MANAGER_MIN_FREE_INDICES)
  		{
  			index = m_freeIndices.front();
  			m_freeIndices.pop_front();
		}
		else
		{
			m_generation.push_back(0);
			index = m_generation.size() - 1;
  		}

  		return EntityID{index, m_generation[index]};
	}

	void EntityWorld::destroy(const EntityID &entity)
	{
		const unsigned int index = entity.index;
		m_generation[index]++;
		m_freeIndices.push_back(index);
	}

	bool EntityWorld::alive(const EntityID &entity)
	{
		return entity.generation == m_generation[entity.index];
	}

}
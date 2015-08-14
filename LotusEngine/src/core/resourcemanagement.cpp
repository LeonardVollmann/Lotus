#include "resourcemanagement.hpp"

namespace lotus {

	std::map<std::string, Resource*> ResourceManager::s_resources;

	template <typename T>
	T *ResourceManager::get(const std::string &name)
	{
		T *resource = nullptr;

		auto it = s_resources.find(name);
		if (it == s_resources.end())
		{
			T *resource = new T(name);
			s_resources.insert(std::pair<std::string, Resource*>(name, resource));
		}
		else
		{
			resource = *it;
		}

		resource->addReference();
		return resource;
	}

	template <typename T>
	void ResourceManager::destroy(const std::string &name)
	{
		auto it = s_resources.find(name);
		if (it == s_resources.end()) return;

		T *ptr = &(*it);
		s_resources.erase(it);
		delete ptr;
	}

}

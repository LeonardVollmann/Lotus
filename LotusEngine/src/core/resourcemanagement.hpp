#pragma once

#include <string>
#include <cassert>
#include <map>

namespace lotus
{

class Resource
{
	friend class ResourceManager;

protected:
	std::string m_name;
	unsigned int m_references;

public:
	Resource(const std::string &name)
	: m_name(name)
	, m_references(0)
	{
	}
	virtual ~Resource() { assert(m_references == 0); }

	inline void addReference() { m_references++; }
	inline void removeReference() { m_references--; }

	inline unsigned int getReferences() const { return m_references; }
	inline const std::string &getName() const { return m_name; }
};

namespace
{
static std::map<std::string, Resource *> s_resources;
}

class ResourceManager
{
public:
	static inline bool exists(const std::string &name)
	{
		auto it = s_resources.find(name);
		return it != s_resources.end();
	}

	template <typename T>
	static inline T *get(const std::string &name)
	{
		T *resource = nullptr;

		auto it = s_resources.find(name);
		if (it == s_resources.end())
		{
			resource = new T(name);
			s_resources.insert(std::pair<std::string, Resource *>(name, resource));
		}
		else
		{
			resource = (T *)it->second;
		}

		resource->addReference();
		return resource;
	}

	template <typename T, typename... ARGS>
	static inline T *create(const std::string &name, bool returnResult, ARGS &&... args)
	{
		auto it = s_resources.find(name);
		if (it != s_resources.end())
		{
			if (returnResult)
			{
				(it->second)->addReference();
				return (T *)it->second;
			}
			else
			{
				return nullptr;
			}
		}

		T *resource = new T(name, args...);
		s_resources.insert(std::pair<std::string, Resource *>(name, resource));

		if (returnResult)
		{
			resource->addReference();
			return resource;
		}
		else
		{
			return nullptr;
		}
	}

	template <typename T>
	static inline void destroy(const std::string &name)
	{
		auto it = s_resources.find(name);
		if (it == s_resources.end())
			return;

		T *ptr = &(*it);
		s_resources.erase(it);
		delete ptr;
	}

private:
	ResourceManager() {}
	virtual ~ResourceManager() {}
};

} // namespace lotus
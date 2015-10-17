#ifndef LOTUS_RESOURCE_MANAGEMENT_HPP_INCLUDED
#define LOTUS_RESOURCE_MANAGEMENT_HPP_INCLUDED

#include <string>
#include <cassert>
#include <map>

namespace lotus {

	class Resource
	{
	friend class ResourceManager;
	public:
		Resource(const std::string &name) :
			m_name(name),
			m_references(0) {}
		virtual ~Resource()
		{
			assert(m_references == 0);
		}

		inline void addReference()		{ m_references++; }
		inline void removeReference()	{ m_references--; }

		inline unsigned int getReferences() const { return m_references; }
		inline const std::string &getName() const { return m_name; }
	protected:
		std::string		m_name;
		unsigned int	m_references;
	};

	class ResourceManager
	{
	private:
		static std::map<std::string, Resource*> s_resources;
	public:
		template <typename T>
		static inline T *get(const std::string &name)
		{
			T *resource = nullptr;

			auto it = s_resources.find(name);
			if (it == s_resources.end())
			{
				resource = new T(name);
				s_resources.insert(std::pair<std::string, Resource*>(name, resource));
			}
			else
			{
				resource = (T*) it->second;
			}

			resource->addReference();
			return resource;
		}

		template <typename T, typename... ARGS>
		static inline void create(const std::string &name, ARGS&&... args)
		{
			auto it = s_resources.find(name);
			if (it != s_resources.end()) return;

			s_resources.insert(std::pair<std::string, Resource*>(name, new T(name, args...)));
		}

		template <typename T>
		static inline void destroy(const std::string &name)
		{
			auto it = s_resources.find(name);
			if (it == s_resources.end()) return;

			T *ptr = &(*it);
			s_resources.erase(it);
			delete ptr;
		}
	private:
		ResourceManager() {}
		virtual ~ResourceManager() {}
	};

}

#endif

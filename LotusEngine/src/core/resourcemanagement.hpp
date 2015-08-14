#ifndef LOTUS_RESOURCE_MANAGEMENT_HPP_INCLUDED
#define LOTUS_RESOURCE_MANAGEMENT_HPP_INCLUDED

#include <string>
#include <cassert>
#include <map>

namespace lotus {

	class Resource
	{
	friend class ResourceManager;
	protected:
		std::string		m_name;
		unsigned int	m_references;
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
	};

	class ResourceManager
	{
	private:
		static std::map<std::string, Resource*> s_resources;
	public:
		template <typename T>
		T *get(const std::string &name);

		template <typename T>
		void destroy(const std::string &name);
	private:
		ResourceManager() {}
		virtual ~ResourceManager() {}
	};

}

#endif

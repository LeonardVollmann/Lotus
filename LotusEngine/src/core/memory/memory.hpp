#ifndef LOTUS_MEMORY_HPP_INCLUDED
#define LOTUS_MEMORY_HPP_INCLUDED

#include "iallocator.hpp"
#include "heapallocator.hpp"

#include <new>

namespace lotus { namespace memory {

	namespace
	{
		struct MemoryGlobals
		{
			unsigned char buffer[sizeof(HeapAllocator)];

			HeapAllocator *defaultAllocator = nullptr;
		} g_memoryGlobals;
	}

	inline void init()
	{
		unsigned char *ptr = g_memoryGlobals.buffer;

		g_memoryGlobals.defaultAllocator = new (ptr) HeapAllocator();
	}

	inline void shutdown()
	{
		g_memoryGlobals.defaultAllocator->~HeapAllocator();
	}

	inline IAllocator &getDefaultAllocator()
	{
		return *g_memoryGlobals.defaultAllocator;
	}

	template <typename T, typename... ARGS>
	inline T *make_new(ARGS&&... args)
	{
		return getDefaultAllocator().make_new<T>(args...);
	}

	template <typename T>
	inline void make_delete(T *ptr)
	{
		getDefaultAllocator().make_delete<T>(ptr);
	}

} }

#endif

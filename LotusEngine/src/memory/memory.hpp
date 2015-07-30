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

	void init()
	{
		unsigned char *ptr = g_memoryGlobals.buffer;

		g_memoryGlobals.defaultAllocator = new (ptr) HeapAllocator();
	}

	void shutdown()
	{
		g_memoryGlobals.defaultAllocator->~HeapAllocator();
	}

	IAllocator &defaultAllocator()
	{
		return *g_memoryGlobals.defaultAllocator;
	}

} }

#endif

#ifndef LOTUS_HEAP_ALLOCATOR_HPP_INCLUDED
#define LOTUS_HEAP_ALLOCATOR_HPP_INCLUDED

#include "iallocator.hpp"

namespace lotus { namespace memory {

	class HeapAllocator : public IAllocator
	{
	private:
		size_t m_allocated;
	public:
		HeapAllocator();

		virtual void *allocate(size_t size, size_t align) override;
		virtual void deallocate(void *ptr) override;
		virtual size_t allocatedSize(void *ptr) override;
	private:
		size_t *getHead(void *ptr);
	};

} }

#endif

#include "heapallocator.hpp"

#include <cstdlib>

namespace lotus { namespace memory {

	HeapAllocator::HeapAllocator() :
		m_allocated(0) {}

	void *HeapAllocator::allocate(size_t size, size_t align)
	{
		const size_t total = size + align + sizeof(size_t);
		size_t *head = (size_t*) malloc(total);
		void *ptr = (void*) (head + 1);

		ptr = alignForward(ptr, align);
		pad(head, ptr, total);

		return ptr;
	}

	void HeapAllocator::deallocate(void *ptr)
	{
		if (ptr)
		{
			size_t *head = getHead(ptr); 
			m_allocated -= *head;
			free(head);
		}
	}

	size_t HeapAllocator::allocatedSize(void *ptr)
	{
		return *getHead(ptr);
	}

	size_t *HeapAllocator::getHead(void *ptr)
	{
		size_t *head = (size_t*) ptr;
		while (*(--head) == (size_t) -1) {}
		return head - 1;
	}

} }

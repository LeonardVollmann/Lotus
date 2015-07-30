#ifndef LOTUS_IALLOCATOR_HPP_INCLUDED
#define LOTUS_IALLOCATOR_HPP_INCLUDED

#include <cstddef>
#include <cstdint>

namespace lotus { namespace memory {

	class IAllocator
	{
	public:
		IAllocator() {}
		virtual ~IAllocator() {}

		virtual void *allocate(size_t size, size_t align) = 0;
		virtual void deallocate(void *ptr) = 0;
		virtual size_t allocatedSize(void *ptr) = 0;

		template <typename T, typename... ARGS>
		inline T *make_new(ARGS&&... args)
		{
			return new (allocate(sizeof(T), alignof(T))) T(args...);
		}

		template <typename T>
		inline void make_delete(T *ptr)
		{
			if (ptr)
			{
				ptr->~T();
				deallocate(ptr);
			}
		}
	protected:
		IAllocator(IAllocator const&) = delete;
		void operator=(IAllocator const&) = delete;

		inline void *alignForward(void *ptr, size_t align)
		{
			uintptr_t p = (uintptr_t) ptr;
			const size_t mod = p % align;

			if (mod)
			{
				p += (uintptr_t) (align - mod);
			}

			return (void*) p;
		}

		inline void pad(size_t *head, void *data, size_t size)
		{
			*head = size;
			size_t *start = head + 1;
			
			while (start < data)
			{
				*start++ = (size_t) -1;
			}
		}
	};

} }

#endif

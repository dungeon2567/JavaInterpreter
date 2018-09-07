#pragma once
#include "BatchAllocator.h"

template <size_t objectSize>
class PoolAllocator
{
	struct Block {
		union {
			Block* previous;
			char padding[objectSize];
		};
	};

	static BatchAllocator batchAllocator;

	static Block* first;
public:
	static char* allocate() {
		if (first != nullptr) {
			Block* r = first;

			first = r->previous;

			return reinterpret_cast<char*>(r);
		}
		else
		{
			return batchAllocator.allocate(objectSize);
		}
	}

	static void free(void* mem) {
		Block* block = reinterpret_cast<Block*>(mem);

		block->previous = first;

		first = block;
	}
};

template <size_t objectSize>
	BatchAllocator PoolAllocator<objectSize>::batchAllocator(objectSize * 1024);

template <size_t objectSize>
	typename PoolAllocator<objectSize>::Block* PoolAllocator<objectSize>::first = nullptr;

template<typename T>
struct ObjectPool {
	static constexpr size_t nextPowerOf2(size_t n) {
		size_t k = 1;

		while (k < n)
			k *= 2;

		return k;
	}

	static T* allocate() {
		return reinterpret_cast<T*>(PoolAllocator<nextPowerOf2(sizeof(T))>::allocate());
	}

	static void free(T* t) {
		PoolAllocator<nextPowerOf2(sizeof(T))>::free(t);
	}
};

template<typename T>
struct EnablePoolFromThis {
	void* operator new(size_t size) {
		return ObjectPool<T>::allocate();
	}
};
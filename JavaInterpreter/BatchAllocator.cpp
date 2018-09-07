#include "BatchAllocator.h"

BatchAllocator::~BatchAllocator()
{
	delete this->node;
}

char* BatchAllocator::allocate(size_t size) {
	if (this->node->size - this->node->position >= size) {
		char* pMemory = &this->node->memory[this->node->position];

		this->node->position += size;

		return pMemory;
	}
	else
	{
		this->node = new(malloc(offsetof(struct Node, memory[this->node->size]))) Node(this->node->size, this->node);

		return this->allocate(size);
	}
}

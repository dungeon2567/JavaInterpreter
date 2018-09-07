#pragma once
#include <new>

class BatchAllocator
{
	struct Node {
		size_t size;
		size_t position;
		Node* previous;
		char memory[1];

		Node(size_t size, Node* previous = nullptr) {
			this->size = size;
			this->position = 0;
			this->previous = previous;
		}

		~Node() {
			if (previous)
				delete previous;
		}
	};

	Node* node;

public:
	BatchAllocator(size_t size = 1024* 1024) {
		this->node = new(malloc(offsetof(struct Node, memory[size]))) Node(size, nullptr);
	}

	char* allocate(size_t size); // size ja deve estar alinhado em 8 bytes (sizeof(double) ?)

	template<typename T, typename... TParams>
	T* construct(TParams... params) {
		return new (allocate(sizeof(T))) T(params...);
	}

	~BatchAllocator();
};



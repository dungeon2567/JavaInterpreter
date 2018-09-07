#pragma once
#include "Object.h"
#include "Nodes.h"

class Heap
{
	Object** objects;

	size_t size;
	size_t count;
public:
	Heap(size_t size = 4096) {// MAXIMO DE 4096 OBJETOS NA HEAP (ATUALMENTE)
		this->size = size;
		this->count = 0;
		this->objects = new Object*[size]; 
	}

	Object* allocate();

	void mark(StackFrame* stack);
	void sweep();

	~Heap();
};


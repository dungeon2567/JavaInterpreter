#include "Heap.h"


void Heap::mark(StackFrame* stack) {
	StackFrame* frame = stack;

	while (frame != nullptr) {
		for (auto v : frame->fields) {
			v.second.mark();
		}

		frame = frame->previous;
	}
}

void Heap::sweep() {
	size_t moveIndex = 0;
	size_t resultingCount = 0;

	for (size_t index = 0; index < this->count; ++index) {
		Object* obj = this->objects[index];

		if (obj->marked) {
			obj->marked = false;

			this->objects[moveIndex] = this->objects[index];
			++moveIndex;
			++resultingCount;
		}
		else
		{
			delete this->objects[index];
		}
	}

	this->count = resultingCount;
}
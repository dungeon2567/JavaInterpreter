#include "Object.h"


void Object::mark() {
	this->marked = true;
	
	for (auto it: *this) {
		it.second.mark();
	}
}
#include "Value.h"
#include "Object.h"

void Value::mark() {
	if (this->type->isObject()) {
		this->obj->mark();
	}
}


#pragma once
#include <unordered_map>
#include "Value.h"

class Variable;

struct StackFrame {
	std::unordered_map<Variable*, Value> fields;
	StackFrame* previous;

	StackFrame(StackFrame* previous = nullptr) {
		this->previous = previous;
	}
};

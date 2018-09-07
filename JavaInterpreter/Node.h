#pragma once
#include "Context.h"
#include <array>

class Expression;
class Value;

class Node: public virtual Context
{
public:
	virtual Expression* call(Expression* left, Expression* right) {
		return nullptr;
	}

	virtual void free() = 0;
};



#pragma once
#include "Node.h"
#include "Value.h"
#include "StackFrame.h"
#include "Expression.h"
#include <unordered_map>

class Type;

class Variable : public Node {
	Identifier* identifier;
	Type* type;
public:
	Variable(Identifier* identifier, Type* type) {
		this->identifier = identifier;
		this->type = type;
	}
};


class Parameter : public Variable {

};

class Field : public Variable {

};

class BinaryFunction : public Node {
public:
	virtual Value execute(StackFrame* frame, Value left, Value right) = 0;

	virtual Expression* call(Expression* left, Expression* right);
};
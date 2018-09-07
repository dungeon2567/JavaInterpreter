#include "Type.h"
#include "Identifier.h"
#include "Nodes.h"

class IntegerAdditionFunction : public BinaryFunction {
	virtual Value execute(StackFrame* frame, Value left, Value right) override {
		return Value(left.i + right.i);
	}

	virtual void free() override {

	}
};

IntegerType::IntegerType() {
	this->additionFunction = new IntegerAdditionFunction();
}

Node* IntegerType::lookup(Identifier* identifier) {
	if (identifier == &BinaryOpIdentifier::sum) {
		return this->additionFunction;
	}

	return nullptr;
}

Node* StringType::lookup(Identifier* identifier) {
	return nullptr;
}

IntegerType IntegerType::instance;
StringType StringType::instance;

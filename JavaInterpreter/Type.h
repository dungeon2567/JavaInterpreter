#pragma once
#include "Node.h"

class Type: public Node
{
public:
	virtual bool isObject() {
		return false;
	}
};

class ReferenceType : public Type {

};

class ValueType : public Type {

};

class VoidType : public Type {

};

class BinaryFunction;

class IntegerType : public ValueType {
	BinaryFunction* additionFunction;
public:
	IntegerType();

	virtual Node* lookup(Identifier* identifier) override;

	static IntegerType instance;

	virtual void free() override {

	}
};

class DoubleType : public ValueType {
public:
	virtual Node* lookup(Identifier* identifier) override;
};

class FloatType : public ValueType {
public:
	virtual Node* lookup(Identifier* identifier) override;
};

class ObjectType : public ReferenceType, public MapContext {
public:
	virtual bool isObject() override {
		return true;
	}
};

class StringType : public ObjectType {
public:
	virtual Node* lookup(Identifier* identifier) override;

	static StringType instance;

	virtual void free() override {

	}
};

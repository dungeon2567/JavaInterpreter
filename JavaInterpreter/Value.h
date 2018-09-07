#pragma once
#include "Node.h"
#include "Identifier.h"
#include "Type.h"

class Object;

struct Value: public Identifier { // Herda de identifier para ser usado como valor temporario na tabela de valores
	Type* type;

	union {
		double d;
		float f;
		int i;
		const wchar_t* str;
		Object* obj;
	};

	void mark();

	Value(const wchar_t* val) {
		this->str = val;
		this->type = &StringType::instance;
	}

	/*
	Value(double d) {
		this->d = d;
		this->type = &DoubleType::instance;
	}

	Value(float f) {
		this->f = f;
		this->type = &FloatType::instance;
	}
	*/

	Value(int i) {
		this->i = i;
		this->type = &IntegerType::instance;
	}

	Value(Object* obj, ObjectType* type) {
		this->obj = obj;
		this->type = type;
	}

	Value() {

	}
};


struct ValueList {

};
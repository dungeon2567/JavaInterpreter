#pragma once
#include "Type.h"
#include "Value.h"
#include "Node.h"
#include "Nodes.h"
#include "PoolAllocator.h"
#include "StackFrame.h"
#include <array>

class Expression
{
public:
	virtual Value execute(StackFrame* frame) = 0;

	virtual Type* type() {
		return nullptr;
	}

	virtual void free() = 0;
};

class IntegerConstantExpression : public Expression, public EnablePoolFromThis<IntegerConstantExpression> {
	int val;
public:
	IntegerConstantExpression(int val) {
		this->val = val;
	}

	virtual void free() override {
		ObjectPool<IntegerConstantExpression>::free(this);
	}

	virtual Type* type() override;

	virtual Value execute(StackFrame* frame) override;
};


class StringConstantExpression : public Expression, public EnablePoolFromThis<StringConstantExpression> {
	const wchar_t* val;
public:
	StringConstantExpression(const wchar_t* val) {
		this->val = val;
	}

	virtual void free() override {
		ObjectPool<StringConstantExpression>::free(this);
	}


	virtual Value execute(StackFrame* frame) override;
};

class BinaryFunction;

class BinaryFunctionCallExpression : public Expression, public EnablePoolFromThis<BinaryFunctionCallExpression> {
	BinaryFunction* f;

	Expression* left;
	Expression* right;
public:
	BinaryFunctionCallExpression(BinaryFunction* f, Expression* left, Expression* right)
	{
		this->f = f;
		this->left = left;
		this->right = right;
	}

	virtual void free() override {
		ObjectPool<BinaryFunctionCallExpression>::free(this);
	}

	virtual Value execute(StackFrame* frame) override;
};


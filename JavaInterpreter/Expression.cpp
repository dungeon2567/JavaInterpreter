#include "Expression.h"
#include "Nodes.h"

Value IntegerConstantExpression::execute(StackFrame* frame) {
	return Value(this->val);
}

Value StringConstantExpression::execute(StackFrame* frame) {
	return Value(this->val);
}

Value BinaryFunctionCallExpression::execute(StackFrame* frame) {
	return f->execute(frame, left->execute(frame), right->execute(frame));
}

Type* IntegerConstantExpression::type() {
	return &IntegerType::instance;
}

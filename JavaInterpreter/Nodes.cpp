#include "Nodes.h"
#include "Expression.h"

Expression* BinaryFunction::call(Expression* left, Expression* right) {
	return new BinaryFunctionCallExpression(this, left, right);
}
#include "Parser.h"
#include <new>


Parser::ExpressionFactory* Parser::parseExpression(int minPrecedence) {
	ExpressionFactory* lhs = parseAtom();

	while (true) {
		if (tok.type != Token::BINARY_OPERATOR)
			break;

		BinaryOpIdentifier* op = tok.op;

		if (op->prec < minPrecedence)
			break;

		int nextMinPrecedence = op->assoc == 1 ? op->prec + 1 : op->prec;

		consumeToken();

		ExpressionFactory* rhs = parseExpression(nextMinPrecedence);

		struct OperatorExpressionFactory: public ExpressionFactory {
			ExpressionFactory* lhs;
			ExpressionFactory* rhs;

			BinaryOpIdentifier* op;

			OperatorExpressionFactory(ExpressionFactory* lhs, ExpressionFactory* rhs, BinaryOpIdentifier* op) {
				this->lhs = lhs;
				this->rhs = rhs;
				this->op = op;
			}

			virtual Expression* create(Context* ctx) override {
				Expression* left = lhs->create(ctx);
				Expression* right = rhs->create(ctx);

				return left->type()->lookup(op)->call(left, right);
			}
		};

		lhs = allocator->construct<OperatorExpressionFactory>(lhs, rhs, op);
	}

	return lhs;
}

Parser::ExpressionFactory* Parser::parseAtom() {
	switch (tok.type) {
		case Token::OPEN_PARENTHESIS:
			{			
				consumeToken();
				ExpressionFactory* f = parseExpression(1);
				consumeToken(); // CLOSE_PARENTHESIS?

				return f;
			}
		case Token::INTEGER:
		{
			int val = tok.integer;

			consumeToken();

			struct IntegerConstantExpressionFactory : public ExpressionFactory {
				int val;

				IntegerConstantExpressionFactory(int val) {
					this->val = val;
				}

				virtual Expression* create(Context* ctx) override {
					return new IntegerConstantExpression(val);
				}
			};

			return allocator->construct<IntegerConstantExpressionFactory>(val);
		}
		case Token::STRING:
		{
			const wchar_t* val = tok.string;

			consumeToken();

			struct StringConstantExpressionFactory : public ExpressionFactory {
				const wchar_t* val;

				StringConstantExpressionFactory(const wchar_t* val) {
					this->val = val;
				}

				virtual Expression* create(Context* ctx) override {
					return new StringConstantExpression(val);
				}
			};

			return allocator->construct<StringConstantExpressionFactory>(val);
		}
		default:
			return nullptr; // preguiça de criar a excessão =/
	}
}

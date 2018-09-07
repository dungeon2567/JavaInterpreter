#pragma once
#include "Lexer.h"
#include "Nodes.h"
#include "Context.h"
#include "Expression.h"
#include "BatchAllocator.h"

class Parser
{
	Lexer* lexer;
	BatchAllocator* allocator;
	Token tok;

	struct NodeFactory {
		virtual Node* create(Context* ctx) = 0;
	};

	struct ExpressionFactory {
		virtual Expression* create(Context* ctx) = 0;
	};


public:
	Parser(BatchAllocator* allocator, Lexer* lexer) {
		this->allocator = allocator;	
		this->lexer = lexer;

		this->tok = lexer->readToken();
	}

	void consumeToken() {
		this->tok = lexer->readToken();
	}

	ExpressionFactory* parseAtom();

	ExpressionFactory* parseExpression(int minPrecedence);
};


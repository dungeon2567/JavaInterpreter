#pragma once
#include "Identifier.h"

struct Token {
	union {
		int integer;
		Identifier* identifier;
		BinaryOpIdentifier* op;
		const wchar_t* string;
	};

	enum TokenType: char {
		INTEGER,
		IDENTIFIER,
		STRING,
		DOT,
		OPEN_BRACE,
		CLOSE_BRACE,
		OPEN_PARENTHESIS,
		CLOSE_PARENTHESIS,
		CLASS_SYMBOL,
		END_OF_INPUT,
		BINARY_OPERATOR,
		ERROR
	} type;

	Token(int val) {
		this->integer = val;
		this->type = INTEGER;
	}

	Token(const wchar_t* val) {
		this->string = val;
		this->type = IDENTIFIER;
	}

	Token(Identifier* val, TokenType type = IDENTIFIER) {
		this->identifier = val;
		this->type = type;
	}

	Token(BinaryOpIdentifier* op) {
		this->op = op;
		this->type = BINARY_OPERATOR;
	}

	Token(TokenType type) {
		this->type = type;
	}

	Token() {

	}
};

class Lexer
{
	const wchar_t* input;
	size_t index;
public:
	Lexer(const wchar_t* input) {
		this->input = input;
		this->index = 0;
	}

	Token readToken();
};


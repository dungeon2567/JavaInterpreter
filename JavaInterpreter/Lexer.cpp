#include "Lexer.h"
#include "Identifier.h"
#include <ctype.h>

Token Lexer::readToken() {
	if (isalpha(input[index])) {
		Symbol* sb = SymbolPool::instance.append(input[index++]);

		while (isalnum(input[index])) {
			sb = sb->append(input[index++]);
		}

		Token::TokenType tp;

		if (sb == SymbolPool::classSymbol) {
			tp = Token::CLASS_SYMBOL;
		}
		else
			tp = Token::IDENTIFIER;

		return Token(sb, tp);
	}
	else
		if (isdigit(input[index])) {
			int val = input[index++] - '0';

			while (isdigit(input[index])) {
				val = val * 10 + input[index++] - '0';
			}

			return Token(val);
		}
		else
		{
			switch (input[index]) {
			case '\0':
				return Token(Token::END_OF_INPUT);
			case '+':
				++index;
				return Token(&BinaryOpIdentifier::sum);
			case '-':
				++index;
				return Token(&BinaryOpIdentifier::sub);
			case '*':
				++index;
				return Token(&BinaryOpIdentifier::mul);
			case '/':
				++index;
				return Token(&BinaryOpIdentifier::div);
			case '{':
				++index;
				return Token(Token::OPEN_BRACE);
			case '}':
				++index;
				return Token(Token::CLOSE_BRACE);
			case '.':
				++index;
				return Token(Token::DOT);
			case '(':
				++index;
				return Token(Token::OPEN_PARENTHESIS);
			case ')':
				++index;
				return Token(Token::CLOSE_PARENTHESIS);
			case '\"':
				++index;
				{
					size_t startIndex = index;

					while (input[index++] != '\"');

					size_t length = index - startIndex;

					wchar_t* string = new wchar_t[length + 1];

					memcpy(string, input + startIndex, sizeof(wchar_t) * (length));

					string[length] = '\0';

					return Token(string);
				}


			default:
				if (isspace(input[index])) {
					++index;

					return readToken();
				}
				else
					return Token(Token::ERROR);
			}
		}
}

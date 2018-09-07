#include "Identifier.h"

Symbol* SymbolPool::append(wchar_t ch) {
	Symbol*& sb = this->child[ch];

	if (sb == nullptr) {
		return sb = new Symbol(ch, this);
	}

	return sb;
}

SymbolPool SymbolPool::instance;
Symbol* SymbolPool::classSymbol = SymbolPool::instance.append('c')->append('l')->append('a')->append('s')->append('s');

BinaryOpIdentifier BinaryOpIdentifier::sum(1, 0);
BinaryOpIdentifier BinaryOpIdentifier::sub(1, 0);
BinaryOpIdentifier BinaryOpIdentifier::mul(2, 0);
BinaryOpIdentifier BinaryOpIdentifier::div(2, 0);
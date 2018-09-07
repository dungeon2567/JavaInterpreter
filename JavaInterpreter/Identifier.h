#pragma once

#include <unordered_map>

class Symbol;

class Identifier {
public:
};


class BinaryOpIdentifier : public Identifier {
public:
	const int prec;
	const int assoc;

	BinaryOpIdentifier(int prec, int assoc):
		prec(prec), assoc(assoc){

	}

	static BinaryOpIdentifier sum;
	static BinaryOpIdentifier sub;
	static BinaryOpIdentifier mul;
	static BinaryOpIdentifier div;
};

class SymbolPool : public Identifier {
	std::unordered_map<wchar_t, Symbol*> child;
public:
	Symbol* append(wchar_t ch);

	static SymbolPool instance;

	static Symbol* classSymbol;
};

class Symbol: public SymbolPool {
	wchar_t ch;
	SymbolPool* parent;
public:
	Symbol(wchar_t ch, SymbolPool* parent) {
		this->ch = ch;
		this->parent = parent;
	}
};
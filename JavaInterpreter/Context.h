#pragma once
class Node;
class Identifier;
#include <unordered_map>

class Context
{
public:
	virtual Node* lookup(Identifier* identifier) {
		return nullptr;
	}

	virtual void add(Identifier* identifier, Node* node) {

	}
};

class MapContext : public virtual Context {
	std::unordered_map<Identifier*, Node*> nodes;
public:
	virtual Node* lookup(Identifier* identifier) override;

	virtual void add(Identifier* identifier, Node* node) override;
};

class CompoundContext : public Context {
	Context* upper;
	Context* lower;
public:
	CompoundContext(Context* upper, Context* lower) {
		this->upper = upper;
		this->lower = lower;
	}

	virtual Node* lookup(Identifier* identifier) override;
	virtual void add(Identifier* identifier, Node* node) override;
};



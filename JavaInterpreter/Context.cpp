#include "Context.h"



Node* CompoundContext::lookup(Identifier* identifier) {
	Node* n = upper->lookup(identifier);

	if (n == nullptr)
		n = lower->lookup(identifier);

	return n;
}


Node* MapContext::lookup(Identifier* identifier) {
	auto it = this->nodes.find(identifier);

	if (it != this->nodes.end())
		return it->second;
	else
		return nullptr;
}

void MapContext::add(Identifier* identifier, Node* node) {
	this->nodes.insert({ identifier, node });
}

void CompoundContext::add(Identifier* identifier, Node* node) {
	this->upper->add(identifier, node);
}
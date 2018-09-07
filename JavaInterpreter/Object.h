
#pragma once
#include <unordered_map>
#include "Value.h"
#include "Nodes.h"

class Object: public std::unordered_map<Field*, Value>
{
public:
	bool marked;
	void mark();
};


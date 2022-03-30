#pragma once
#include "Malloc.h"
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <map>


using namespace std;

class Interpreter
{
private:
	int memsAloocated = 0;
	struct Var
	{
		void* ptr;
		int refs;
	};
	map<string, Var*> vars;
	bool decreaseVarRefs(map<string, Var*>::iterator findVar);

public:
	int getAllocated() const;
	void interpret(const vector<string>& lines);
};


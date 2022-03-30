#pragma once
#include <string>
#include <vector>
#include <regex>
#include <stack>
#include <map>
#include <exception>
#include <iostream>
#include "MemoryAllocator.h"

using namespace std;


class Interpreter
{
private:
	struct Var
	{
		void* ptr;
		int sz;
	};
	deque<map<string, Var>> varStacks;
	stack<Var> varsToDelete;
	MemoryAllocator mem;
	void freeMem();
	void extractLast();
public:
	Interpreter();
	~Interpreter();
	void interpret(const vector<string>& lines);
};


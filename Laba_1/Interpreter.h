#pragma once
#include "Malloc.h"
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <map>
#include <string>
#include <exception>

using namespace std;

class Interpreter
{
private:
	struct Var
	{
		void* ptr = nullptr;
		int refs = 0;
	};
	map<string, Var*> vars;
	int mallocCnt = 0;
public:
	int getMallocCount() const;
	bool tryDeleteObject(map<string, Var*>::iterator var);

	void interpret(const vector<string>& lines);
};


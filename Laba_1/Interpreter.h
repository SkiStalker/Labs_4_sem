#pragma once
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <map>
#include "Malloc.h"


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

	bool tryRemoveVar(map<string, Var*>::iterator findVar)
	{
		findVar->second->refs--;
		if (!findVar->second->refs)
		{
			w_free(findVar->second->ptr);
			return true;
		}
		return false;
	}

public:
	int getAllocated() const
	{
		return memsAloocated;
	}
	void interpret(const vector<string>& lines)
	{
		for (auto line : lines)
		{
			cout << line << endl;

			cmatch res;
			regex regAlloc("^([a-zA-Z]+\\d*)=alloc\\(([0-9]\\d*)\\);$");
			regex regDealloc("^dealloc\\(([a-zA-Z]+\\d*)\\);$");
			regex regCopy("^([a-zA-Z]+\\d*)=([a-zA-Z]+\\d*);$");


			if (regex_search(line.c_str(), res, regAlloc))
			{
				auto findVar = vars.find(res[1]);
				if (findVar == vars.end())
				{
					auto curVar = new Var();
					curVar->ptr = w_malloc(stoi(res[2]));
					curVar->refs = 1;
					vars[res[1]] = curVar;
					memsAloocated++;
				}
				else
				{
					tryRemoveVar(findVar);
					findVar->second->ptr = w_malloc(stoi(res[2]));
					findVar->second->refs = 1;
				}
			}
			else if (regex_search(line.c_str(), res, regDealloc))
			{
				auto findVar = vars.find(res[1]);
				if (tryRemoveVar(findVar))
				{
					vars.erase(findVar);
					memsAloocated--;
				}
			}
			else if (regex_search(line.c_str(), res, regCopy))
			{
				auto findVar = vars.find(res[1]);
				if (findVar != vars.end())
				{
					tryRemoveVar(findVar);
				}

				if (vars.find(res[2]) != vars.end())
				{
					vars[res[1]] = vars[res[2]];
					vars[res[2]]->refs++;
				}
				else
				{
					cout << "Unknow variable" << endl;
				}
			}
		}
	}
};


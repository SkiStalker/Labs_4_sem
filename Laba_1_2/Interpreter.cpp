#include "Interpreter.h"

bool Interpreter::decreaseVarRefs(map<string, Var*>::iterator findVar)
{
	findVar->second->refs--;
	if (!findVar->second->refs)
	{
		w_free(findVar->second->ptr);
		return true;
	}
	return false;
}


int Interpreter::getAllocated() const
{
	return memsAloocated;
}

void Interpreter::interpret(const vector<string>& lines)
{
	for (auto line : lines)
	{
		cout << line << endl;

		cmatch res;
		regex regAlloc("([a-zA-Z]+\\d*)=alloc\\(([0-9]\\d*)\\);");
		regex regDealloc("dealloc\\(([a-zA-Z]+\\d*)\\);");
		regex regCopy("([a-zA-Z]+\\d*)=([a-zA-Z]+\\d*);");


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
				decreaseVarRefs(findVar);

				findVar->second = new Var();
				findVar->second->ptr = w_malloc(stoi(res[2]));
				findVar->second->refs = 1;
			}
		}
		else if (regex_search(line.c_str(), res, regDealloc))
		{
			auto findVar = vars.find(res[1]);
			if (decreaseVarRefs(findVar))
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
				decreaseVarRefs(findVar);
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
		else
		{
			cout << "Unknown command" << endl;
		}
	}
}

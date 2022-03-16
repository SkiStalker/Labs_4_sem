#include "Interpreter.h"

int Interpreter::getMallocCount() const
{
	return mallocCnt;
}

bool Interpreter::tryDeleteObject(map<string, Var*>::iterator var)
{
	(*var).second->refs--;
	if (!(*var).second->refs)
	{
		w_free((*var).second->ptr);
		delete (*var).second;
		mallocCnt--;
		return true;
	}
	return false;
}

void Interpreter::interpret(const vector<string>& lines)
{
	for (auto line : lines)
	{
		cmatch res;

		regex alloc_reg("([a-zA-Z]+\\d*)=alloc\\(([0-9]\\d*)\\)");

		regex dealloc_reg("dealloc\\(([a-zA-z]+\\d*)\\)");

		regex copy_reg("([a-zA-Z]+\\d*)=([a-zA-Z]+\\d*)");

		if (regex_search(line.c_str(), res, alloc_reg))
		{
			auto findVar = vars.find(res[1]);
			if (findVar != vars.end())
			{
				tryDeleteObject(findVar);
				(*findVar).second->ptr = w_malloc(stoi(res[2]));
				if (!(*findVar).second->ptr)
				{
					cout << "No memory allocated" << endl;
					vars.erase(findVar);
					continue;
				}
				else
				{
					(*findVar).second->refs = 1;
				}
			}
			else
			{
				mallocCnt++;
				Var* var = new Var();
				var->ptr = w_malloc(stoi(res[2]));

				if (!var->ptr)
				{
					cout << "No memory allocated" << endl;
					delete var;
					continue;
				}
				else
				{
					var->refs = 1;
					vars[res[1]] = var;
				}
			}
		}
		else if (regex_search(line.c_str(), res, dealloc_reg))
		{
			auto findVar = vars.find(res[1]);

			if (findVar == vars.end())
			{
				cout << "Unknown variable" << endl;
				continue;
			}

			if (tryDeleteObject(findVar))
			{
				vars.erase(findVar);
			}
		}
		else if (regex_search(line.c_str(), res, copy_reg))
		{
			auto findVar = vars.find(res[1]);
			if (findVar == vars.end())
			{
				vars[res[1]] = vars[res[2]];
				vars[res[1]]->refs++;
			}
			else
			{
				tryDeleteObject(findVar);
				vars[res[1]] = vars[res[2]];
			}
		}
		else
		{
			cout << "Unknown line" << endl;
		}
	}
}

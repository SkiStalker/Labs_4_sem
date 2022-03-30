#include "Interpreter.h"

void Interpreter::interpret(const vector<string>& lines)
{
	for (auto line : lines)
	{
		cmatch res;
		regex regNew("([a-zA-Z]+\\d*)=new\\(([0-9]\\d*)\\);");
		regex regShowVar("ShowVar;");
		regex regOpenBreak("\\{");
		regex regCloseBreak("\\}");

		if (regex_search(line.c_str(), res, regNew))
		{
			auto& curVars = varStacks.back();

			auto findVar = curVars.find(res[1]);

			if (findVar != curVars.end())
			{
				varsToDelete.push(findVar->second);
			}

			Var& var = curVars[res[1]];
			var.sz = stoi(res[2]);
			var.ptr = mem.w_alloc(var.sz);

			if (!var.ptr)
			{
				freeMem();
				var.ptr = mem.w_alloc(var.sz);
				if (!var.ptr)
					throw exception("Can not allocate memory");
			}
		}
		else if (regex_search(line.c_str(), res, regShowVar))
		{
			for (auto& vars : varStacks)
			{
				for (auto& var : vars)
				{
					cout << var.first << " : " << var.second.sz << endl;
				}
			}
		}
		else if (regex_search(line.c_str(), res, regOpenBreak))
		{
			varStacks.push_back(map<string, Var>());
		}
		else if (regex_search(line.c_str(), res, regCloseBreak))
		{
			extractLast();
		}
	}
}

Interpreter::Interpreter()
{

}

void Interpreter::freeMem()
{
	while (!varsToDelete.empty())
	{
		mem.w_free(varsToDelete.top().ptr);
		varsToDelete.pop();
	}
}

void Interpreter::extractLast()
{
	auto& vars = varStacks.back();
	for (auto& var : vars)
	{
		varsToDelete.push(var.second);
	}
	varStacks.pop_back();
}

Interpreter::~Interpreter()
{
	while (!varStacks.empty())
	{
		extractLast();
	}
	freeMem();
}

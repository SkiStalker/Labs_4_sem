#pragma once
#include <vector>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

class Interpreter
{
public:
	void interpret(const vector<string>& lines)
	{
		for (auto line : lines)
		{
			cout << line << endl;

			cmatch res;
			regex regular("[a-zA-Z]+\\d*=alloc\\(([0-9]\\d*)\\)");
			if (regex_search(line.c_str(), res,
				regular))
			{
				cout << res[0] << " " << res[1] << endl;
			}
		}
	}


};


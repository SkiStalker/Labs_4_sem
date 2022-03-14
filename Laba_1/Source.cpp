#include <iostream>
#include "Interpreter.h"

int main()
{

	vector<string> lines;
	lines.push_back("var1=alloc(12);");
	lines.push_back("var2=var1;");
	lines.push_back("dealloc(var2);");
	Interpreter().interpret(lines);

	getchar();
	return 0;
}
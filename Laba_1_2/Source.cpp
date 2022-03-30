#include <iostream>
#include "Interpreter.h"
#include <vector>
#include <fstream>

int errorMsg()
{
	cout << "File not existed" << endl;
	getchar();
	exit(0);
}

void appendLinesFromFile(const string fileName, vector<string>& lines)
{
	ifstream in(fileName);

	if (!in.is_open())
	{
		errorMsg();
	}

	while (!in.eof())
	{
		string buf;
		while (!in.eof() && in.peek() != ';')
		{
			buf += in.get();
		}
		if (in.peek() == ';')
			buf += in.get();

		if (buf.back() != EOF)
			lines.push_back(buf);
	}
	in.close();
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		errorMsg();
	}

	vector<string> lines;

	for (int i = 1; i < argc; i++)
	{
		appendLinesFromFile(argv[i], lines);
	}

	Interpreter inter;
	inter.interpret(lines);

	int maxFreeSpace = 0;
	int allFreeSpace = 0;
	cout << endl << "Memory view : " << endl;
	char* cur = heap;
	while (cur != heap + N)
	{
		bool is_free = getFree(cur);
		int sz = getSize(cur);
		if (is_free)
		{
			allFreeSpace += sz;
			if (sz > maxFreeSpace)
				maxFreeSpace = sz;
		}
		for (int i = 0; i < sz; i++)
		{
			cout << (is_free ? "_" : "*");
		}

		cur += sz;
	}

	cout << endl << endl << "Allocated blocks = " << inter.getAllocated() << endl;
	cout << "All free memory = " << allFreeSpace << endl;
	cout << "Max free block size = " << maxFreeSpace << endl;
	getchar();

	return 0;
}

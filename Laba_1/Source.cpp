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

void appendLinesFromFile(const string fileName, vector<string> & lines)
{
	ifstream in(fileName);

	if (!in.is_open())
	{
		errorMsg();
	}

	while (!in.eof())
	{
		string buf;
		getline(cin, buf);
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
		appendLinesFromFile(string(argv[i]), lines);
	}

	Interpreter inter;
	inter.interpret(lines);

	int allFreeMem = 0;
	int maxFreeMem = 0;
	for (int i = 0; i < HEAP_SIZE; i++)
	{
		auto curFreeBlock = LIST[IN_USE - 1];
		if (&vm.heap[i] == curFreeBlock.ptr)
		{
			allFreeMem += curFreeBlock.size;
			if (curFreeBlock.size > maxFreeMem)
				maxFreeMem = curFreeBlock.size;

			for (int j = 0; j < curFreeBlock.size; j++)
			{
				cout << "_";
			}
			i += curFreeBlock.size;
			IN_USE--;
		}
		else
		{
			cout << "*";
		}
	}
	cout << endl << "Free memory size = " << allFreeMem << endl;
	cout << "Maximum free block size = " << maxFreeMem << endl;
	cout << "Allocated memory blocks = " << inter.getMallocCount() << endl;
	getchar();


	return 0;
}

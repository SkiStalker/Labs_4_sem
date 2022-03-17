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
	lines.push_back("var1=alloc(12);");
	lines.push_back("var2=var1;");
	lines.push_back("dealloc(var2);");
	lines.push_back("dealloc(var1);");
	Interpreter inter;
	inter.interpret(lines);

	entity* curFreeBlock = _LIST;
	int maxFreeSpace = 0;
	int allFreeSpace = 0;
	cout << endl << "Memory view : " << endl;
	for (int i = 0; i < HEAP_SIZE; i++)
	{
		if (curFreeBlock && &vm.heap[i] == curFreeBlock->ptr)
		{
			for (int j = 0; j < curFreeBlock->size; j++)
			{
				cout << "_";
			}
			i += curFreeBlock->size;
			allFreeSpace += curFreeBlock->size;
			if (curFreeBlock->size > maxFreeSpace)
				maxFreeSpace = curFreeBlock->size;
			curFreeBlock = curFreeBlock->next;
		}
		else
		{
			cout << "*";
		}
	}

	cout << endl << endl << "Allocated blocks = " << inter.getAllocated() << endl;
	cout << "All free memory = " << allFreeSpace << endl;
	cout << "Max free block size = " << maxFreeSpace << endl;
	getchar();


	return 0;
}

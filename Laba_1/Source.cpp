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
		while (!in.eof() && in.peek() != ';')
		{
			buf += in.get();
		}
		if (in.peek() == ';')
			buf += in.get();

		if(buf.back() != EOF)
			lines.push_back(buf);
	}
	in.close();
}

void clear()
{
	delete vm.heap;
	while (_LIST)
	{
		auto t = _LIST;
		_LIST = _LIST->next;
		delete t;
	}
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

	clear();
	return 0;
}

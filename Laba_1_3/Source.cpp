#include "Interpreter.h"
#include <fstream>

using namespace std;


void readLines(const string& path, vector<string> &lines)
{
	ifstream in(path);

	if(!in.is_open())
	{
		cout << "File is not exist" << endl;
		return;
	}

	while (!in.eof())
	{
		string buf;
		getline(in, buf);
		lines.push_back(buf);
	}

	in.close();
}

int main(int argc, char* argv[])
{
	vector<string> lines;
	for (int i = 1; i < argc; i++)
	{
		readLines(argv[i], lines);
	}
	Interpreter().interpret(lines);


	//MemoryAllocator mem;
	//auto ptr1 = mem.w_alloc(5);
	//auto ptr2 = mem.w_alloc(6);
	//auto ptr3 = mem.w_alloc(7);
	//mem.w_free(ptr2);
	//mem.w_free(ptr3);
	//mem.w_free(ptr1);
	getchar();
	return 0;
}
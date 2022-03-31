#pragma once
#include <stdint.h>

using uint = unsigned int;

class MemoryAllocator
{
private:

	const int CHAROFF = (1 << (sizeof(char) - 1));
	const int CHAROFFINV = ~CHAROFF;

	char** freeBlocks = nullptr;
	uint getNormalizePow(uint size);
	int getBlockNumber(uint pow);

	int N = 10;

	char* heap = nullptr;

	inline void setTag(char* ptr, bool tag);
	inline bool getTag(char* ptr);

	char* extractFreeBlock(int j);

	inline char* getTween(char* ptr, int k);

	inline uint getKVal(char* ptr);

	inline char* getLinkB(char* ptr);

	inline char* getLinkF(char* ptr);

	inline void setLinkB(char* ptr, char* linkb);

	inline void setLinkF(char* ptr, char* linkf);

	inline void setKVal(char* ptr, uint k);

public:
	MemoryAllocator();
	~MemoryAllocator();
	void* w_alloc(uint size);
	void w_free(void * ptr);
	int getN() const;
	void setN(int N);
};


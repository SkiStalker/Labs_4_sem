#include "MemoryAllocator.h"

MemoryAllocator::MemoryAllocator()
{
}

MemoryAllocator::~MemoryAllocator()
{
	delete heap;
	delete freeBlocks;
}

uint MemoryAllocator::getNormalizePow(uint size)
{
	uint pow = 0;
	uint val = 1;
	while (val < size)
	{
		pow++;
		val <<= 1;
	}
	return pow;
}

int MemoryAllocator::getBlockNumber(uint pow)
{
	int j = pow;
	if (!freeBlocks)
	{
		heap = new char[1 << N];
		freeBlocks = new char* [N];
		for (int i = 0; i < N - 1; i++)
			freeBlocks[i] = nullptr;

		auto& last = freeBlocks[N - 1];
		last = heap;
		setTag(last, true);
		setKVal(last, N-1);
		setLinkB(last, nullptr);
		setLinkF(last, nullptr);
	}
	while (j < N)
	{
		if (freeBlocks[j])
			break;
		j++;
	}

	if (j == N)
		return -1;
	return j;
}


void* MemoryAllocator::w_alloc(uint size)
{
	uint newSize = size + 1 + 4 + 4;

	int k = getNormalizePow(newSize);
	int j = getBlockNumber(k);
	char* L = extractFreeBlock(j);

	while (j != k)
	{
		j--;
		char* P = L + (1 << j);
		setTag(P, true);
		setKVal(P, j);
		setLinkB(P, nullptr);
		setLinkF(P, nullptr);
		freeBlocks[j] = P;
	}
	setKVal(L, k);
	return L + 1 + 4 + 4;
}

void MemoryAllocator::w_free(void* ptr)
{
	char* L = (char*)ptr - 9;
	uint k = getKVal(L);
	char* P = nullptr;


	while (true)
	{

		if (k == N - 1)
			break;

		P = getTween(L, k);

		if (!getTag(P))
			break;

		if (getKVal(P) != k)
			break;

		auto lb = getLinkB(P);
		if (lb)
			setLinkF(lb, getLinkF(P));
		auto lf = getLinkF(P);
		if (lf)
			setLinkB(lf, getLinkB(P));
		k++;
		if (P < L)
		{
			L = P;
		}
	}

	setTag(L, true);
	P = freeBlocks[k];
	setLinkF(L, P);
	if(P)
		setLinkB(P, L);
	setKVal(L, k);
	setLinkB(L, nullptr);
	freeBlocks[k] = L;
}

void MemoryAllocator::setTag(char* ptr, bool tag)
{
	if (tag)
	{
		*ptr |= (1 << 7);
	}
	else
	{
		*ptr &= ~(1 << 7);
	}
}

bool MemoryAllocator::getTag(char* ptr)
{
	return (*ptr >> 7);
}

char* MemoryAllocator::extractFreeBlock(int j)
{
	char* L = freeBlocks[j];
	char* P = getLinkF(L);
	freeBlocks[j] = P;
	if (P)
		setLinkB(P, nullptr);
	setTag(L, false);
	return L;
}

char* MemoryAllocator::getTween(char* ptr, int k)
{
	int x = ptr - heap;
	int mod = x % (1 << k + 1);
	if (mod)
	{
		return ptr - (1 << k);
	}
	else
	{
		return ptr + (1 << k);
	}
}

uint MemoryAllocator::getKVal(char* ptr)
{
	return (unsigned char)((*ptr) & ((char)(~(1 << 7))));
}

inline char* MemoryAllocator::getLinkB(char* ptr)
{
	return (char*)*((int*)(ptr + 1) + 1);
}

inline char* MemoryAllocator::getLinkF(char* ptr)
{
	return (char*)*(int*)(ptr + 1);
}

inline void MemoryAllocator::setLinkB(char* ptr, char* linkb)
{
	*((int*)(ptr + 1) + 1) = (int)linkb;
}

inline void MemoryAllocator::setLinkF(char* ptr, char* linkf)
{
	*(int*)(ptr + 1) = (int)linkf;
}

inline void MemoryAllocator::setKVal(char* ptr, uint k)
{
	bool bit = *ptr >> 7;
	*ptr = k | (bit << 7);
}

int MemoryAllocator::getN() const
{
	return N;
}

void MemoryAllocator::setN(int N)
{
	this->N = N;
}

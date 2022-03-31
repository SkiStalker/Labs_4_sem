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
		setKVal(last, N - 1);
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
	uint newSize = size + sizeof(char) + sizeof(int*) * 2;

	int k = getNormalizePow(newSize);
	int j = getBlockNumber(k);
	char* L = extractFreeBlock(j);

	while (j != k)
	{
		j--;
		char* P = L + (1ll << j);
		setTag(P, true);
		setKVal(P, j);
		setLinkB(P, nullptr);
		setLinkF(P, nullptr);
		freeBlocks[j] = P;
	}
	setKVal(L, k);
	return L + sizeof(char) + sizeof(int*) * 2;
}

void MemoryAllocator::w_free(void* ptr)
{
	char* L = (char*)ptr - sizeof(char) - sizeof(int*) * 2;
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
	if (P)
		setLinkB(P, L);
	setKVal(L, k);
	setLinkB(L, nullptr);
	freeBlocks[k] = L;
}

void MemoryAllocator::setTag(char* ptr, bool tag)
{
	if (tag)
	{
		*ptr |= CHAROFF;
	}
	else
	{
		*ptr &= CHAROFFINV;
	}
}

bool MemoryAllocator::getTag(char* ptr)
{
	return (*ptr >> (sizeof(char) - 1));
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
	int mod = x % (1ll << (k + 1));
	if (mod)
	{
		return ptr - (1ll << k);
	}
	else
	{
		return ptr + (1ll << k);
	}
}

uint MemoryAllocator::getKVal(char* ptr)
{
	return (unsigned char)((*ptr) & ((char)CHAROFFINV));
}

inline char* MemoryAllocator::getLinkB(char* ptr)
{
	return (char*)(*(ptrdiff_t*)(ptr + sizeof(char) + sizeof(int*)));
}

inline char* MemoryAllocator::getLinkF(char* ptr)
{
	return (char*)(*(ptrdiff_t*)(ptr + sizeof(char)));
}

inline void MemoryAllocator::setLinkB(char* ptr, char* linkb)
{
	*(ptrdiff_t*)(ptr + sizeof(char) + sizeof(int*)) = (ptrdiff_t)linkb;
}

inline void MemoryAllocator::setLinkF(char* ptr, char* linkf)
{
	*(ptrdiff_t*)(ptr + sizeof(char)) = (ptrdiff_t)linkf;
}

inline void MemoryAllocator::setKVal(char* ptr, uint k)
{
	bool bit = *ptr >> (sizeof(char) - 1);
	*ptr = k | (bit << (sizeof(char) - 1));
}

int MemoryAllocator::getN() const
{
	return N;
}

void MemoryAllocator::setN(int N)
{
	this->N = N;
}

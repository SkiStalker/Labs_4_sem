#include "Malloc.h"


unsigned int N = 256;
char* heap = nullptr;
char* availPtr;

const int TAGPOS = 1 << (sizeof(int) * 8 - 1);

const int TAGPOSINV = ~(1 << (sizeof(int) * 8 - 1));

const int HEADERLEN = (sizeof(int) + sizeof(int*)) * 2;

const int INTOFF = sizeof(int) * 8 - 1;



void* w_malloc(uint size)
{
	uint newSize = size + HEADERLEN;

	char* ptr = getBlock(newSize);

	char* userPtr = ptr;

	char* next = getNext(ptr);
	char* prev = getPrev(ptr);

	int sz = getSize(ptr);

	bool firstBlock = (availPtr == ptr);

	ptr += newSize;
	sz -= newSize;

	if (sz > HEADERLEN)
	{
		writeBlockInfo(ptr, sz, next, prev);
		if (firstBlock)
			availPtr = ptr;
	}
	else
	{
		newSize += sz;
		if (prev)
		{
			setNext(prev, next);
			if (firstBlock)
				availPtr = prev;
		}
		if (next)
		{
			setPrev(next, prev);
			if (!prev && firstBlock)
				availPtr = next;
		}
	}

	setSize(userPtr, newSize);
	setFree(userPtr, false);
	return userPtr + sizeof(int) + sizeof(int*) * 2;
}


void writeBlockInfo(char* ptr, int sz, char* next, char* prev)
{
	*((int*)ptr) = TAGPOS | sz;
	*(ptrdiff_t*)(ptr + sizeof(int)) = (ptrdiff_t)next;
	*(ptrdiff_t*)(ptr + sizeof(int) + sizeof(int*)) = (ptrdiff_t)prev;
	*((int*)(ptr + sz - sizeof(int))) = TAGPOS | sz;
}

char* getBlock(uint size)
{
	if (!availPtr)
	{
		heap = new char[N];
		writeBlockInfo(heap, N, nullptr, nullptr);
		availPtr = heap;
	}

	char* cur = availPtr;

	while (cur)
	{
		if (getSize(cur) >= size)
		{
			return cur;
		}
		cur = getNext(cur);
	}

	return nullptr;
}

void setHeapSize(uint size)
{
	N = size;
}

void w_free(void* ptr)
{
	char* start = (char*)ptr - sizeof(int*) * 2 - sizeof(int);
	char* P = nullptr;
	if (start != heap)
	{
		int szPrev = (*((int*)(start - sizeof(int)))) & TAGPOSINV;
		P = start - szPrev;
		int szCur = getSize(start);
		if (getFree(P))
		{
			char* P1 = getNext(P);
			char* P2 = getPrev(P);
			if (P1)
				setPrev(P1, P2);
			if (P2)
				setNext(P2, P1);
			setSize(P, szPrev + szCur);
			start = P;
		}
	}

	P = start + getSize(start);

	if (P != (heap + N))
	{
		if (getFree(P))
		{
			char* P1 = getNext(P);
			char* P2 = getPrev(P);
			if (P1)
			{
				setPrev(P1, P2);
			}
			if (P2)
			{
				setNext(P2, P1);
			}
			setSize(start, getSize(start) + getSize(P));

			P = P + getSize(P);
		}
	}

	char* prevP = P - (*(((int*)P - 1)) & TAGPOSINV);

	setSize(prevP, getSize(start));
	setNext(start, availPtr);
	setPrev(start, nullptr);
	setPrev(availPtr, start);
	availPtr = start;
	setFree(start, true);
	setFree(prevP, true);
}

bool getFree(char* ptr)
{
	return (*((int*)ptr)) >> INTOFF;
}

uint getSize(char* ptr)
{
	return ((*(int*)ptr)) & TAGPOSINV;
}

char* getNext(char* ptr)
{
	return (char*)(*(ptrdiff_t*)(ptr + sizeof(int)));
}

char* getPrev(char* ptr)
{
	return (char*)(*(ptrdiff_t*)(ptr + sizeof(int) + sizeof(int*)));
}

void setFree(char* ptr, bool val)
{

	*((int*)ptr) = (* ((int*)ptr) & TAGPOSINV) | (val << INTOFF);
	ptr += getSize(ptr) - sizeof(int);
	*((int*)ptr) = (* ((int*)ptr) & TAGPOSINV) | (val << INTOFF);
}

void setSize(char* ptr, int sz)
{
	bool bit = (*(int*)ptr) >> INTOFF;
	*((int*)ptr) = sz | (bit << INTOFF);
	ptr += sz - sizeof(int);
	*((int*)ptr) = sz | (bit << INTOFF);
}

void setNext(char* ptr, char* next)
{
	*((ptrdiff_t*)(ptr + sizeof(int))) = (ptrdiff_t)next;
}

void setPrev(char* ptr, char* prev)
{
	*((ptrdiff_t*)(ptr + sizeof(int) + sizeof(int*))) = (ptrdiff_t)prev;
}
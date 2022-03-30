#include "Malloc.h"

unsigned int N = 256;
char* heap = nullptr;
char* availPtr;

const int TAGPOS = 1 << 31;

const int TAGPOSINV = ~(1 << 31);


void* w_malloc(uint size)
{
	uint newSize = size + 16;

	char* ptr = getBlock(newSize);

	char* userPtr = ptr;

	char* next = getNext(ptr);
	char* prev = getPrev(ptr);

	int sz = getSize(ptr);

	bool firstBlock = (availPtr == ptr);

	ptr += newSize;
	sz -= newSize;

	if (sz > 16)
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
			if(firstBlock)
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
	return (int*)userPtr + 3;
}


void writeBlockInfo(char* ptr, int sz, char* next, char* prev)
{
	*((int*)ptr) = TAGPOS | sz;
	*(int*)(ptr + 4) = (int)next;
	*(int*)(ptr + 8) = (int)prev;
	*((int*)(ptr + sz - 4)) = TAGPOS | sz;
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
	int* start = (int*)ptr - 3;
	char* P = nullptr;
	if ((char*)start != heap)
	{
		int szPrev = (*(start - 1)) & TAGPOSINV;
		P = (char*)start - szPrev;
		int szCur = *start;
		if (getFree(P))
		{
			char* P1 = getNext(P);
			char* P2 = getPrev(P);
			if(P1)
				setPrev(P1, P2);
			if(P2)
				setNext(P2, P1);
			setSize(P, szPrev + szCur);
			start = (int*)P;
		}
	}

	P = (char*)start + getSize((char*)start);

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
			setSize((char*)start, getSize((char*)start) + getSize(P));

			P = P + getSize(P);
		}
	}

	char* prevP = P - (* ((int*)P - 1) & TAGPOSINV);

	setSize(prevP, getSize((char*)start));
	setNext((char*)start, availPtr);
	char* availPrev = getPrev(availPtr);
	setPrev((char*)start, availPrev);
	setPrev(availPtr, (char*)start);

	if(availPrev)
		setNext(availPrev, (char*)start);

	availPtr = (char*)start;
	setFree((char*)start, true);
	setFree(prevP, true);
}

bool getFree(char* ptr)
{
	return (*((int*)ptr)) >> 31;
}

uint getSize(char* ptr)
{
	return ((*(int*)ptr)) & TAGPOSINV;
}

char* getNext(char* ptr)
{
	return (char*)(*((int*)ptr + 1));
}

char* getPrev(char* ptr)
{
	return (char*)(*((int*)ptr + 2));
}

void setFree(char* ptr, bool val)
{

	*((int*)ptr) = *((int*)ptr) & TAGPOSINV | (val << 31);
	ptr += getSize(ptr) - 4;
	*((int*)ptr) = *((int*)ptr) & TAGPOSINV | (val << 31);
}

void setSize(char* ptr, int sz)
{
	bool bit = (*(int*)ptr) >> 31;
	*((int*)ptr) = sz | (bit << 31);
	ptr += sz - 4;
	*((int*)ptr) = sz | (bit << 31);
}

void setNext(char* ptr, char* next)
{
	*((int*)ptr + 1) = (int)next;
}

void setPrev(char* ptr, char* prev)
{
	*((int*)ptr + 2) = (int)prev;
}
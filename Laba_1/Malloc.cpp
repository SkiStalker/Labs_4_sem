#include "Malloc.h"

entity LIST[HEAP_SIZE];
u16 IN_USE = 0;
virtual_memory vm;

entity* new_entity(size_t size, entity* pre_best)
{
	if (LIST[0].ptr == NULL && LIST[0].size == 0)
	{

		LIST[0].ptr = vm.heap;
		LIST[0].size = HEAP_SIZE;
		IN_USE++;
	}


	entity* best = nullptr;
	entity* cur = &LIST[IN_USE - 1];
	entity* pre_cur = nullptr;


	for (unsigned i = 0; i < IN_USE; i++)
	{
		if (cur->size >= size)
		{
			if (!best || cur->size < best->size)
			{
				best = cur;
				pre_best = pre_cur;
			}
		}
		pre_cur = cur;
		cur = cur->next;
	}

	return best;
}

void moveList(entity* entry)
{
	int ind = (entry - LIST) / sizeof(entity);
	for (int i = ind; i < IN_USE - 1; i++)
	{
		LIST[ind] = LIST[ind + 1];
	}
	entity* last = &LIST[IN_USE - 1];
	last->ptr = nullptr;
	last->size = 0;
	last->next = nullptr;
	IN_USE--;
}

void* w_malloc(size_t size)
{
	size += HEADER;

	entity* pre_e = nullptr;

	entity* e = new_entity(size, pre_e);

	u8* start = e->ptr;
	u8* user_ptr = start + HEADER;

	*start = size;

	e->ptr += size;
	e->size -= size;

	if (!e->size)
	{
		if (pre_e)
		{
			pre_e->next = e->next;
			moveList(e);
		}
	}

	return user_ptr;
}

void w_free(void* ptr)
{
	u8* start = (u8*)ptr - HEADER;

	entity* Q = nullptr;
	entity* P = nullptr;

	P = &LIST[IN_USE - 1];

	while (!(!P->ptr || P->ptr > start))
	{
		Q = P;
		P = Q->next;
	}


	bool mergetop = true;
	if (start + *start == P->ptr)
	{
		P->ptr = start;
		P->size += *start;
	}
	else
	{
		mergetop = false;
	}


	bool mergebot = true;
	if (Q && Q->ptr + Q->size == start)
	{
		Q->size += *start;
	}
	else
	{
		mergebot = false;
	}

	if (!mergetop && !mergebot)
	{
		entity* cur = &LIST[IN_USE];
		cur->ptr = start;
		cur->size = *start;
		cur->next = P;
		if (Q)
			Q->next = cur;

		IN_USE++;
	}
	else if (mergetop && mergebot)
	{
		Q->size += (P->size - *start);
		moveList(P);
	}

}
#include "Malloc.h"

u16 IN_USE;
entity* _LIST = nullptr;
virtual_memory vm;


entity* new_entity(size_t size, entity* pre_best)
{
	if (!_LIST)
	{
		vm.heap = new u8[HEAP_SIZE];
		_LIST = new entity();
		_LIST->ptr = vm.heap;
		_LIST->size = HEAP_SIZE;
	}

	entity* best = _LIST;
	entity* cur = _LIST;
	entity* pre_cur = nullptr;

	while (cur)
	{
		if (cur->size >= size && cur->size < best->size)
		{
			best = cur;
			pre_best = pre_cur;
		}
		pre_cur = cur;
		cur = cur->next;
	}
	return best;
}

void w_free(void* ptr)
{
	u8* start = (u8*)ptr - HEADER;

	entity* Q = nullptr;
	entity* P = _LIST;

	while (true)
	{
		if (!P->ptr || P->ptr > start)
		{
			break;
		}
		else
		{
			Q = P;
			P = Q->next;
		}
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


	bool mergebot = false;

	if (Q && Q->ptr + Q->size == start)
	{
		Q->size += *start;
	}
	else
	{
		mergebot = false;
	}

	if (mergebot && mergetop)
	{
		Q->size += P->size;
		removeNextEntity(Q);

	}
	else if (!mergebot && !mergetop)
	{
		if (Q)
		{
			addNextEntity(start, *start, Q);
		}
		else
		{
			addFirstEntity(start, *start);
		}
	}
}

void* w_malloc(size_t size)
{
	size += HEADER;

	entity* pre_best = nullptr;

	entity* e = new_entity(size, pre_best);

	u8* start = e->ptr;
	u8* user_ptr = start + HEADER;

	*start = size;

	e->ptr += size;
	e->size -= size;

	if (!e->size)
	{
		if (pre_best)
		{
			pre_best->next = e->next;
			delete e;
		}
		else
		{
			//
		}
	}
	return user_ptr;
}

void addFirstEntity(u8* ptr, int size)
{
	auto newFreeBlock = new entity();
	newFreeBlock->ptr = ptr;
	newFreeBlock->size = size;
	entity* t = _LIST;
	_LIST = newFreeBlock;
	_LIST->next = t;
}

void addNextEntity(u8* ptr, int size, entity* previous)
{
	entity* t = new entity();
	t->ptr = ptr;
	t->size = size;
	t->next = previous->next;
	previous->next = t;
}


void removeNextEntity(entity* cur)
{
	entity* t = cur->next;
	cur->next = cur->next->next;
	delete t;
}
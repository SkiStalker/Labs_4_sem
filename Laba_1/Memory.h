#pragma once
#include <cstdlib>
#include <stdint.h>
#include <string.h>

#define u8 uint8_t
#define u16 uint16_t
#define STACKSIZE 32
#define HEAPSIZE (STACKSIZE * 4)

#define HEADER 4

static u8 IN_USE;


struct entity
{
	u8* ptr;
	int size;
};


entity LIST[40];

struct virtual_memory
{
	u8 heap[HEAPSIZE];
};


entity* new_entity(size_t size)
{
	if (!LIST[0].ptr && !LIST[0].size)
	{
		static virtual_memory vm;
		LIST[0].ptr = vm.heap;
		LIST[0].size = HEAPSIZE;
	}

	entity* best = LIST;

	for (int i = 0; i < IN_USE; i++)
	{
		if (LIST[i].size >= size && LIST[i].size < best->size)
		{
			best = &LIST[i];
		}
	}


}

void* w_malloc(size_t size)
{
	size += HEADER;
	entity* e = 
}
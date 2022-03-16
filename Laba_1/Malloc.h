#pragma once
#include <string.h>
#include <stdint.h>

#define u8 uint8_t 
#define u16 uint16_t 
#define STACK_SIZE 32
#define HEAP_SIZE STACK_SIZE * 4
#define HEADER 4

extern u16 IN_USE;

struct virtual_memory
{
	u8 heap[HEAP_SIZE];
};

struct entity
{
	u8* ptr;
	int size;
	entity* next;
};


extern virtual_memory vm;
extern entity LIST[];

entity* new_entity(size_t size, entity* pre_best);

void moveList(entity* entry);

void* w_malloc(size_t size);

void w_free(void* ptr);
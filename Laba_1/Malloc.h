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
	u8* heap;
};
	u8 heap[HEAP_SIZE];

struct entity
{
typedef struct entity
{
	u8* ptr;
	int size;
	entity* next;
};

extern entity* _LIST;
void addFirstEntity(u8* ptr, int size);

void addNextEntity(u8* ptr, int size, entity* previous);
	printf("Entities in use:[%d]\n", (sizeof(LIST) / sizeof(LIST[0]) - IN_USE));
void removeNextEntity(entity* cur);
}
entity* new_entity(size_t size, entity* pre_best);

void* w_malloc(size_t size);

void w_free(void* ptr);

}


void w_free(void* ptr);
#pragma once
//https://www.youtube.com/watch?v=xrJfaLBMu2w&list=PLR4wcBxrUGPBED2vUPaPY0Eo__ba1LJGC&index=4

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

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


struct entity
{
	u8* ptr;
	int size;
	entity* next;
};

extern entity* _LIST;
extern virtual_memory vm;

void addFirstEntity(u8* ptr, int size);

void addNextEntity(u8* ptr, int size, entity* previous);

void removeNextEntity(entity* cur);

entity* new_entity(size_t size, entity* pre_best);

void* w_malloc(size_t size);

void w_free(void* ptr);



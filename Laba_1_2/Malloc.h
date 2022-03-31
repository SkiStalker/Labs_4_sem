#pragma once
#include <stdint.h>

using uint = unsigned int;

extern uint N;
extern char* heap;

extern char* availPtr;

char* getBlock(uint size);

void setHeapSize(uint size);

void* w_malloc(uint size);

void w_free(void* ptr);

inline bool getFree(char* ptr);

inline uint getSize(char* ptr);

inline char* getNext(char* ptr);

inline char* getPrev(char* ptr);

inline void setFree(char* ptr, bool val);

inline void setSize(char* ptr, int sz);

inline void setNext(char* ptr, char* next);

inline void setPrev(char* ptr, char* prev);

void writeBlockInfo(char* ptr, int sz, char* next, char* prev);

void writeAllocInfo(char* ptr, int sz);

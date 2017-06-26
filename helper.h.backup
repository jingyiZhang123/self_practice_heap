#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>

typedef void (*sortfunc_p)(int*, int);

typedef struct MaxHeap{
    int* elems;
    int num_elems;
    int capacity;

}maxheap_t;

typedef maxheap_t* maxheap_p;

int* GenerateRandomArray(int start, int end, long long size);
void TestSorting(sortfunc_p func, char* func_name, int*arr, long long size);
int* GenerateNearlyOrderedArray(long long size, int num_swap);
void swap(int* arr, int index1, int index2);

void MaxHeap_Init(maxheap_p maxheap, int capacity);
void MaxHeap_ArrInit(maxheap_p maxheap, int* arr, int n);
bool MaxHeap_Insert(maxheap_p maxheap, int value);
int MaxHeap_Pop(maxheap_p maxheap);
void MaxHeap_Del(maxheap_p maxheap);
bool MaxHeap_IsEmpty(maxheap_p maxheap);
int MaxHeap_Size(maxheap_p maxheap);


#endif

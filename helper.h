#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>

typedef int (*cmpfunc_p)(void*, void*);
typedef void (*sortfunc_p)(void*, int, int, cmpfunc_p);

typedef void (*freefunc_p)(void*);

typedef struct {
    void* elems;
    int elem_num;
    int elem_size;
    int capacity;
    freefunc_p freefunc;
    cmpfunc_p cmpfunc;
}maxheap_t;

typedef maxheap_t* maxheap_p;


extern void swap(void* elem1, void* elem2, int elem_size);
extern int* GenerateRandomArray(int start, int end, long long size);
extern int* GenerateNearlyOrderedArray(int size, int num_swap);
extern void TestSorting(sortfunc_p func, char* func_name, void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);


extern maxheap_p MaxHeap_Init(const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern maxheap_p MaxHeap_InitWithArr(void* arr, const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern bool MaxHeap_IsEmpty(maxheap_p mh);
extern void MaxHeap_Append(maxheap_p mh, void* elem);
extern void MaxHeap_Pop(maxheap_p mh, void* poped_elem);
extern void MaxHeap_Del(maxheap_p mh);



#endif

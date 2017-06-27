#ifndef INDEXHEAP_H
#define INDEXHEAP_H

#include "helper.h"

typedef struct {
    void* elems;
    int* indexes;

    int elem_num;
    int elem_size;
    int capacity;
    freefunc_p freefunc;
    cmpfunc_p cmpfunc;
}index_maxheap_t;

typedef index_maxheap_t* index_maxheap_p;


extern index_maxheap_p IndexMaxHeap_InitWithArr(void* arr, const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern void IndexMaxHeap_Append(index_maxheap_p mh, void* elem, int i);
extern void IndexMaxHeap_Pop(index_maxheap_p mh, void* poped_elem);
extern void IndexMaxHeap_Del(index_maxheap_p mh);


#endif

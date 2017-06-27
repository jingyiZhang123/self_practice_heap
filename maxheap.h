#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "helper.h"
#include <stdbool.h>

typedef struct {
    void* elems;
    int elem_num;
    int elem_size;
    int capacity;
    freefunc_p freefunc;
    cmpfunc_p cmpfunc;
}maxheap_t;

typedef maxheap_t* maxheap_p;

extern maxheap_p MaxHeap_Init(const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern maxheap_p MaxHeap_InitWithArr(void* arr, const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern bool MaxHeap_IsEmpty(maxheap_p mh);
extern void MaxHeap_Append(maxheap_p mh, void* elem);
extern void MaxHeap_Pop(maxheap_p mh, void* poped_elem);
extern void MaxHeap_Del(maxheap_p mh);



#endif

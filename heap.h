#ifndef HEAP_H
#define HEAP_H

#include "helper.h"

extern void HeapSort1(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);
extern void HeapSort2(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);
extern void HeapSort3(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);
extern void HeapSort4(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);


void _shiftdown(void* arr, int elem_num, int elem_size, int index, cmpfunc_p cmpfunc);



#endif

#ifndef HELPER_H
#define HELPER_H

typedef int (*cmpfunc_p)(void*, void*);
typedef void (*sortfunc_p)(void*, int, int, cmpfunc_p);

typedef void (*freefunc_p)(void*);


extern void swap(void* elem1, void* elem2, int elem_size);
extern int* GenerateRandomArray(int start, int end, long long size);
extern int* GenerateNearlyOrderedArray(int size, int num_swap);
extern void TestSorting(sortfunc_p func, char* func_name, void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);


#endif

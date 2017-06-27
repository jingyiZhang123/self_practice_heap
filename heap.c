#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "helper.h"
#include "maxheap.h"
#include "indexheap.h"

extern void HeapSort1(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);
extern void HeapSort2(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);
extern void HeapSort3(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);
extern void HeapSort4(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);

static void _shiftdown(void* arr, int elem_num, int elem_size, int index, cmpfunc_p cmpfunc);



void HeapSort1(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc){
    maxheap_p maxheap = MaxHeap_Init(elem_num, elem_size, NULL, cmpfunc);
    for (int i = 0; i < elem_num; i++)
        MaxHeap_Append(maxheap, (char*)arr + i*elem_size);

    void* aux = malloc(elem_size);
    for (int i = 0; i < elem_num; i++) {
        MaxHeap_Pop(maxheap, aux);
        memcpy((char*)arr + i*elem_size, aux, elem_size);
    }
    MaxHeap_Del(maxheap);
    free(aux);
}

void HeapSort2(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc){
    maxheap_p maxheap = MaxHeap_InitWithArr(arr, elem_num, elem_size, NULL, cmpfunc);

    void* aux = malloc(elem_size);
    for (int i = 0; i < elem_num; i++) {
        MaxHeap_Pop(maxheap, aux);
        memcpy((char*)arr + i*elem_size, aux, elem_size);
    }
    MaxHeap_Del(maxheap);
    free(aux);
}



void HeapSort3(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc){
    for (int i = (elem_num-1)/2; i >= 0; i--)
        _shiftdown(arr, elem_num, elem_size, i, cmpfunc);
    for (int i=elem_num-1; i > 0; i--) {
        swap((char*)arr + 0*elem_size,\
             (char*)arr + i*elem_size,\
             elem_size);
        _shiftdown(arr, i, elem_size, 0, cmpfunc);
    }
}

void HeapSort4(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc){
    index_maxheap_p maxheap = IndexMaxHeap_InitWithArr(arr, elem_num, elem_size, NULL, cmpfunc);
    void* aux = malloc(elem_size);
    for (int i = 0; i < elem_num; i++) {
        IndexMaxHeap_Pop(maxheap, aux);
        memcpy((char*)arr + i*elem_size, aux, elem_size);
    }
    IndexMaxHeap_Del(maxheap);
    free(aux);
}



void _shiftdown(void* arr, int elem_num, int elem_size, int index, cmpfunc_p cmpfunc){

    while(index*2+1 < elem_num){
        int left_child_index = index * 2 + 1;
        int right_child_index = index * 2 + 2;
        int smaller_child = left_child_index;
        if((right_child_index < elem_num) &&                                    \
           (cmpfunc((char*)arr + right_child_index*elem_size, (char*)arr + left_child_index*elem_size) > 0))
            smaller_child = right_child_index;
        if(cmpfunc((char*)arr + index*elem_size, (char*)arr + smaller_child*elem_size) < 0){
            swap((char*)arr + index*elem_size,        \
                 (char*)arr + smaller_child*elem_size,    \
                 elem_size);
            index = smaller_child;
        }
        else
            break;
    }
}

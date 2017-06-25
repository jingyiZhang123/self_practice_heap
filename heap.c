#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "helper.h"

#define ARR_SIZE 1000000

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


int Int_Compare(void* a, void* b){
    return *(int*)a - *(int*)b;
}


/* int main(int argc, char *argv[]) */
/* { */
/*     int arr[12]; */
/*     for (int i=0; i<12; i++) */
/*         arr[i] = rand()%10; */

/*     for (int i=0; i<12; i++) { */
/*         printf("%d ", arr[i]); */
/*     } */
/*     printf("\n"); */
/*     HeapSort3(arr, 12, sizeof(int), Int_Compare); */
/*     for (int i=0; i<12; i++) { */
/*         printf("%d ", arr[i]); */
/*     } */
/*     printf("\n"); */
/*     return 0; */
/* } */


int main(int argc, char *argv[])
{
    int* arr = GenerateNearlyOrderedArray(ARR_SIZE, 500);
    TestSorting(HeapSort1, "HeapSort1 (Nearly Sort)", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    arr = GenerateNearlyOrderedArray(ARR_SIZE, 500);
    TestSorting(HeapSort2, "HeapSort2 (Nearly Sort)", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    arr = GenerateNearlyOrderedArray(ARR_SIZE, 500);
    TestSorting(HeapSort3, "HeapSort3 (Nearly Sort)", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);

    printf("---------------------------\n");

    arr = GenerateRandomArray(0,ARR_SIZE, ARR_SIZE);
    TestSorting(HeapSort1, "HeapSort1 (Normal)     ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    arr = GenerateRandomArray(0,ARR_SIZE, ARR_SIZE);
    TestSorting(HeapSort2, "HeapSort2 (Normal)     ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    arr = GenerateRandomArray(0,ARR_SIZE, ARR_SIZE);
    TestSorting(HeapSort3, "HeapSort3 (Normal)     ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    printf("---------------------------\n");

    arr = GenerateRandomArray(0,256, ARR_SIZE);
    TestSorting(HeapSort1, "HeapSort1 (Duplicates) ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    arr = GenerateRandomArray(0,256, ARR_SIZE);
    TestSorting(HeapSort2, "HeapSort2 (Duplicates) ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    arr = GenerateRandomArray(0,256, ARR_SIZE);
    TestSorting(HeapSort3, "HeapSort3 (Duplicates) ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    printf("---------------------------\n");

    return 0;
}

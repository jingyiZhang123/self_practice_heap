#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "helper.h"

#define ARR_SIZE 1000000

void HeapSort(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc){
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

int Int_Compare(void* a, void* b){
    return *(int*)a - *(int*)b;
}



int main(int argc, char *argv[])
{
    int* arr = GenerateNearlyOrderedArray(ARR_SIZE, 500);
    TestSorting(HeapSort, "HeapSort  (Nearly Sort)", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    /* arr = GenerateNearlyOrderedArray(ARR_SIZE, 500); */
    /* TestSorting(HeapSort2_Int,"HeapSort2 (Nearly Sort)", arr, ARR_SIZE); */
    /* free(arr); */
    printf("---------------------------\n");

    arr = GenerateRandomArray(0,ARR_SIZE, ARR_SIZE);
    TestSorting(HeapSort,"HeapSort  (Normal)     ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    /* arr = GenerateRandomArray(0,ARR_SIZE, ARR_SIZE); */
    /* TestSorting(HeapSort2_Int,"HeapSort2 (Normal)     ", arr, ARR_SIZE); */
    /* free(arr); */
    printf("---------------------------\n");

    arr = GenerateRandomArray(0,20, ARR_SIZE);
    TestSorting(HeapSort,"HeapSort  (Duplicates) ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    /* arr = GenerateRandomArray(0,20, ARR_SIZE); */
    /* TestSorting(HeapSort2_Int,"HeapSort2 (Duplicates) ", arr, ARR_SIZE); */
    /* free(arr); */
    printf("---------------------------\n");

    return 0;
}

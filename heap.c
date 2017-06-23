#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "helper.h"

#define ARR_SIZE 3200000

void HeapSort_Int(int* arr, int size){
    maxheap_p mh = malloc(sizeof(maxheap_t));
    MaxHeap_Init(mh, size);
    for (int i=0; i < size; i++) {
        MaxHeap_Insert(mh, arr[i]);
    }
    for(int i=size-1; i>=0;i--){
        arr[i] = MaxHeap_Pop(mh);
    }
    MaxHeap_Del(mh);
    free(mh);
}

void HeapSort2_Int(int* arr, int size){
    maxheap_p mh = malloc(sizeof(maxheap_t));
    MaxHeap_ArrInit(mh, arr, size);
    for(int i=size-1; i>=0;i--)
        arr[i] = MaxHeap_Pop(mh);
    MaxHeap_Del(mh);
    free(mh);
}




int main(int argc, char *argv[])
{
    int* arr = GenerateNearlyOrderedArray(ARR_SIZE, 500);
    TestSorting(HeapSort_Int,"HeapSort  (Nearly Sort)", arr, ARR_SIZE);
    free(arr);
    arr = GenerateNearlyOrderedArray(ARR_SIZE, 500);
    TestSorting(HeapSort2_Int,"HeapSort2 (Nearly Sort)", arr, ARR_SIZE);
    free(arr);
    printf("---------------------------\n");

    arr = GenerateRandomArray(0,ARR_SIZE, ARR_SIZE);
    TestSorting(HeapSort_Int,"HeapSort  (Normal)     ", arr, ARR_SIZE);
    free(arr);
    arr = GenerateRandomArray(0,ARR_SIZE, ARR_SIZE);
    TestSorting(HeapSort2_Int,"HeapSort2 (Normal)     ", arr, ARR_SIZE);
    free(arr);
    printf("---------------------------\n");

    arr = GenerateRandomArray(0,20, ARR_SIZE);
    TestSorting(HeapSort_Int,"HeapSort  (Duplicates) ", arr, ARR_SIZE);
    free(arr);
    arr = GenerateRandomArray(0,20, ARR_SIZE);
    TestSorting(HeapSort2_Int,"HeapSort2 (Duplicates) ", arr, ARR_SIZE);
    free(arr);
    printf("---------------------------\n");

    return 0;
}

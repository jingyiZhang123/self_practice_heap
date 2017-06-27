#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "helper.h"

#define ARR_SIZE 2000000

int Int_Compare(void* a, void* b){
    return *(int*)a - *(int*)b;
}



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

    arr = GenerateNearlyOrderedArray(ARR_SIZE, 500);
    TestSorting(HeapSort4, "HeapSort4 (Nearly Sort)", arr, ARR_SIZE, sizeof(int), Int_Compare);
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
    arr = GenerateRandomArray(0,ARR_SIZE, ARR_SIZE);
    TestSorting(HeapSort4, "HeapSort4 (Normal)     ", arr, ARR_SIZE, sizeof(int), Int_Compare);
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
    arr = GenerateRandomArray(0,256, ARR_SIZE);
    TestSorting(HeapSort4, "HeapSort4 (Duplicates) ", arr, ARR_SIZE, sizeof(int), Int_Compare);
    free(arr);
    printf("---------------------------\n");

    return 0;
}



/* int main(int argc, char *argv[]) */
/* { */
/*     int arr[12]; */
/*    for (int i=0; i<12; i++) */
/*         arr[i] = rand()%10; */

/*     for (int i=0; i<12; i++) { */
/*         printf("%d ", arr[i]); */
/*     } */
/*     printf("\n"); */
/*     HeapSort4(arr, 12, sizeof(int), Int_Compare); */
/*     for (int i=0; i<12; i++) { */
/*         printf("%d ", arr[i]); */
/*     } */
/*     printf("\n"); */
/*     return 0; */
/* } */

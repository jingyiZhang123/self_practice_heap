#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

extern int* GenerateRandomArray(int start,int end,long long size);
extern void TestSorting(sortfunc_p func,char* func_name,int* arr,long long size);
extern int* GenerateNearlyOrderedArray(long long size, int num_swap);
extern void swap(int* arr, int index1, int index2);

extern void MaxHeap_Init(maxheap_p maxheap, int capacity);
extern bool MaxHeap_Insert(maxheap_p maxheap, int value);
extern int MaxHeap_Pop(maxheap_p maxheap);
extern void MaxHeap_Del(maxheap_p maxheap);
extern bool MaxHeap_IsEmpty(maxheap_p maxheap);
extern int MaxHeap_Size(maxheap_p maxheap);
extern void MaxHeap_ArrInit(maxheap_p maxheap, int* arr, int n);


static bool IsSorted(int* arr,int size);
static void _shiftup(maxheap_p maxheap, int k);
static void _shiftdown(maxheap_p maxheap, int k);

/*
 * Public functions
 */

inline void swap(int* arr, int index1, int index2){
  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;

  return;
}


void MaxHeap_Init(maxheap_p maxheap, int capacity){
    assert(capacity > 0);

    maxheap->elems = malloc(sizeof(int) * (capacity + 1));
    memset(maxheap->elems, sizeof(int)*(capacity+1), 0);
    assert(maxheap->elems != NULL);

    maxheap->num_elems = 0;
    maxheap->capacity = capacity;
}

void MaxHeap_ArrInit(maxheap_p maxheap, int* arr, int n){
  maxheap->elems = malloc(sizeof(int) * (n + 1));
  maxheap->capacity = n;
  for (int i = 0; i < n; i++)
    maxheap->elems[i+1] = arr[i];

  maxheap->num_elems = n;
  for (int i = maxheap->num_elems/2; i >= 1; i--) {
    _shiftdown(maxheap, i);
  }

}

bool MaxHeap_Insert(maxheap_p maxheap, int value){
    if(maxheap->num_elems+1 <= maxheap->capacity){
        maxheap->elems[++(maxheap->num_elems)] = value;
        _shiftup(maxheap, maxheap->num_elems);
        return true;
    }
    return false;
}

int MaxHeap_Pop(maxheap_p maxheap){
    if(maxheap->num_elems <= 0)
        return -1;
    int ret = maxheap->elems[1];
    swap(maxheap->elems, 1, maxheap->num_elems--);
    _shiftdown(maxheap, 1);
    return ret;

}

void MaxHeap_Del(maxheap_p maxheap){
    assert(maxheap != NULL);
    free(maxheap->elems);
}

bool MaxHeap_IsEmpty(maxheap_p maxheap){
    assert(maxheap != NULL);
    return maxheap->num_elems == 0;
}

int MaxHeap_Size(maxheap_p maxheap){
    assert(maxheap != NULL);
    return maxheap->num_elems;
}



int* GenerateRandomArray(int start, int end, long long size){
  srand(time(NULL));
  int* arr = malloc(sizeof(int) * size);
  assert(arr != NULL);
  int range = end - start;
  for (int i = 0; i < size; i++) {
    arr[i] = rand()%range + start;
  }

  return arr;
}


int* GenerateNearlyOrderedArray(long long size, int num_swap){
  srand(time(NULL));
  int* arr = malloc(sizeof(int) * size);
  for (long long i = 0; i < size; i++)
    arr[i] = i;
  for (long long i = 0; i < num_swap; i++) {
    long long index1 = rand()%size;
    long long index2 = rand()%size;
    swap(arr, index1, index2);
  }
  return arr;
}


void TestSorting(sortfunc_p func,char* func_name,int* arr, long long size){
  clock_t t1, t2;

  t1 = clock();
  func(arr, size);
  assert(IsSorted(arr,size));
  /* for (int i = 0 ; i < size; i++) { */
  /*   printf("%d ", arr[i]); */
  /* } */
  /* printf("\n"); */
  t2 = clock();

  float diff = ((float)(t2 - t1) / 1000000.0F );
  /* printf("%f",diff); */

  printf("%s: %f seconds. Size: %lld\n", func_name, diff, size);
}

/*
 * Private functions
 */

bool IsSorted(int* arr, int size){
  for (int i = 1; i < size; i++) {
    if (arr[i] < arr[i-1]) {
      return false;
    }
  }
  return true;
}


void _shiftup(maxheap_p maxheap, int k){
  while(maxheap->elems[k/2] < maxheap->elems[k]){
    swap(maxheap->elems, k/2, k);
    k /= 2;
  }
}

void _shiftdown(maxheap_p maxheap, int k){
  while(2*k <= maxheap->num_elems){
    int j = 2*k;
    if(j + 1 <= maxheap->num_elems && maxheap->elems[j+1] > maxheap->elems[j])
      j += 1;
    if(maxheap->elems[k] >= maxheap->elems[j])
      break;
    swap(maxheap->elems, k, j);
    k = j;
  }
}

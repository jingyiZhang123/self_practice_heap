#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>


extern void swap(void* elem1, void* elem2, int elem_size);
extern int* GenerateRandomArray(int start, int end, long long size);
extern int* GenerateNearlyOrderedArray(int size, int num_swap);
extern void TestSorting(sortfunc_p func, char* func_name, void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);



static bool IsSorted(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);

/*
 * Public functions
 */

inline void swap(void* elem1, void* elem2, int elem_size){
  void* temp = malloc(elem_size);
  memcpy(temp, elem1, elem_size);
  memcpy(elem1, elem2, elem_size);
  memcpy(elem2, temp, elem_size);
  free(temp);
}


int* GenerateRandomArray(int start, int end, long long size){
  srand(time(NULL));
  int* arr = malloc(sizeof(int) * size);
  assert(arr != NULL);
  int range = end - start;
  for (int i = 0; i < size; i++)
    arr[i] = rand()%range + start;

  return arr;
}


int* GenerateNearlyOrderedArray(int size, int num_swap){
  srand(time(NULL));
  int* arr = malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++)
    arr[i] = i;
  for (int i = 0; i < num_swap; i++) {
    int index1 = rand()%size;
    int index2 = rand()%size;
    swap(&arr[index1], &arr[index2], sizeof(int));
  }
  return arr;
}

void TestSorting(sortfunc_p func, char* func_name, void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc){
  clock_t t1, t2;

  t1 = clock();
  func(arr, elem_num, elem_size, cmpfunc);
  assert(IsSorted(arr, elem_num, elem_size, cmpfunc));
  t2 = clock();

  float diff = ((float)(t2 - t1) / 1000000.0F );

  printf("%s: %f seconds. Size: %d\n", func_name, diff, elem_num);
}



/*
 * Private functions
 */


bool IsSorted(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc){
  void* cur_elem = NULL;
  void* prev_elem = NULL;
  for (int i = 1; i < elem_num; i++) {
    cur_elem = (char*)arr + i*elem_size;
    prev_elem = (char*)arr + (i-1)*elem_size;
    if (cmpfunc(cur_elem, prev_elem) < 0)
      return false;
  }
  return true;
}

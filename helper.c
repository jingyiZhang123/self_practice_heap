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

extern maxheap_p MaxHeap_Init(const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern maxheap_p MaxHeap_InitWithArr(void* arr, const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern bool MaxHeap_IsEmpty(maxheap_p mh);
extern void MaxHeap_Del(maxheap_p mh);
extern void MaxHeap_Append(maxheap_p mh, void* elem);
extern void MaxHeap_Pop(maxheap_p mh, void* poped_elem);


extern index_maxheap_p IndexMaxHeap_Init(const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern void IndexMaxHeap_Append(index_maxheap_p mh, void* elem, int i);
extern void IndexMaxHeap_Pop(index_maxheap_p mh, void* poped_elem);
extern void IndexMaxHeap_Del(index_maxheap_p mh);


static bool IsSorted(void* arr, int elem_num, int elem_size, cmpfunc_p cmpfunc);
static void _shiftup(maxheap_p maxheap, int index);
static void _shiftdown(maxheap_p mh, int index);
static void _shiftup_index(index_maxheap_p maxheap, int index);
static void _shiftdown_index(index_maxheap_p mh, int index);

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


index_maxheap_p IndexMaxHeap_Init(const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc){
  assert(capacity > 0 && elem_size > 0 && cmpfunc != NULL);
  index_maxheap_p mh = malloc(sizeof(maxheap_t));
  assert(mh != NULL);
  memset(mh, sizeof(maxheap_t), 0);

  mh->cmpfunc = cmpfunc;
  mh->elem_size = elem_size;
  mh->elem_num = 0;
  mh->capacity = capacity;
  mh->elems = malloc(elem_size * (capacity+1));
  mh->indexes = malloc(sizeof(int) * (capacity + 1));
  assert(mh->elems != NULL);
  memset(mh->elems, elem_size * (capacity+1), 0);
  mh->freefunc = freefunc;

  return mh;

}
void IndexMaxHeap_Append(index_maxheap_p mh, void* elem, int i){
  assert(mh->elem_num < mh->capacity);
  assert(i + 1 >= 1 && i+1 <= mh->capacity);
  i += 1;

  memcpy((char*)(mh->elems) + (mh->elem_num+1) * mh->elem_size, elem, mh->elem_size);
  mh->indexes[mh->elem_num + 1] = i;

  mh->elem_num++;
  _shiftup_index(mh, mh->elem_num);
}



void IndexMaxHeap_Pop(index_maxheap_p mh, void* poped_elem){
  assert(poped_elem != NULL && mh->elem_num > 0);

  memcpy(poped_elem, (char*)mh->elems + mh->indexes[1]*mh->elem_size, mh->elem_size);

  swap((char*)mh->indexes + 1 * sizeof(int),                      \
       (char*)mh->indexes + mh->indexes[mh->elem_num--] * sizeof(int), \
       sizeof(int));
  _shiftdown_index(mh, 1);
}


void IndexMaxHeap_Del(index_maxheap_p mh){
  if(mh->freefunc == NULL)
    free(mh->elems);
  else
    mh->freefunc(mh->elems);
  free(mh->indexes);
  free(mh);
  return;

}


maxheap_p MaxHeap_Init(const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc){
  assert(capacity > 0 && elem_size > 0 && cmpfunc != NULL);
  maxheap_p mh = malloc(sizeof(maxheap_t));
  assert(mh != NULL);
  memset(mh, sizeof(maxheap_t), 0);

  mh->cmpfunc = cmpfunc;
  mh->elem_size = elem_size;
  mh->elem_num = 0;
  mh->capacity = capacity;
  mh->elems = malloc(elem_size * (capacity+1));
  assert(mh->elems != NULL);
  memset(mh->elems, elem_size * (capacity+1), 0);
  mh->freefunc = freefunc;

  return mh;
}

maxheap_p MaxHeap_InitWithArr(void* arr, const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc){
  assert(capacity > 0 && elem_size > 0 && cmpfunc != NULL);
  maxheap_p mh = malloc(sizeof(maxheap_t));
  assert(mh != NULL);
  memset(mh, sizeof(maxheap_t), 0);

  mh->cmpfunc = cmpfunc;
  mh->elem_size = elem_size;
  mh->elem_num = capacity;
  mh->capacity = capacity;
  mh->elems = malloc(elem_size * (capacity+1));
  assert(mh->elems != NULL);
  memset(mh->elems, elem_size * (capacity+1), 0);
  mh->freefunc = freefunc;
  for (int i=0; i<capacity; i++)
    memcpy((char*)mh->elems + (i+1)*elem_size,\
           (char*)arr + i*elem_size,\
           elem_size);
  for (int i=capacity; i>0; i--)
    _shiftdown(mh, i);
  return mh;
}



void MaxHeap_Append(maxheap_p mh, void* elem){
  assert(mh->elem_num < mh->capacity);
  memcpy((char*)(mh->elems) + (mh->elem_num+1) * mh->elem_size, elem, mh->elem_size);
  mh->elem_num++;
  _shiftup(mh, mh->elem_num);
}

void MaxHeap_Pop(maxheap_p mh, void* poped_elem){
  assert(poped_elem != NULL && mh->elem_num > 0);

  memcpy(poped_elem, (char*)mh->elems + 1*mh->elem_size, mh->elem_size);

  swap((char*)mh->elems + 1 * mh->elem_size,        \
       (char*)mh->elems + mh->elem_num-- * mh->elem_size,    \
       mh->elem_size);
  _shiftdown(mh, 1);

}


bool MaxHeap_IsEmpty(maxheap_p mh){
  return mh->elem_num == 0;
}

void MaxHeap_Del(maxheap_p mh){

  if(mh->freefunc == NULL)
    free(mh->elems);
  else
    mh->freefunc(mh->elems);
  free(mh);
  return;
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

void _shiftup(maxheap_p maxheap, int index){
  while(maxheap->cmpfunc((char*)maxheap->elems + index*maxheap->elem_size,(char*)maxheap->elems + (index/2)*maxheap->elem_size) < 0){
    swap((char*)maxheap->elems + index*maxheap->elem_size,\
         (char*)maxheap->elems + (index/2)*maxheap->elem_size,\
         maxheap->elem_size);
    index /= 2;
  }
}

void _shiftdown(maxheap_p mh, int index){
  while(index * 2 <= mh->elem_num){
    int smaller_child = index * 2;
    if((index*2+1 <= mh->elem_num) && \
       (mh->cmpfunc((char*)mh->elems + index*2*mh->elem_size, (char*)mh->elems + (index*2+1)*mh->elem_size) > 0))
      smaller_child += 1;
    if(mh->cmpfunc((char*)mh->elems + index*mh->elem_size, (char*)mh->elems + smaller_child*mh->elem_size) > 0){
      swap((char*)mh->elems + index*mh->elem_size,\
           (char*)mh->elems + smaller_child*mh->elem_size,\
           mh->elem_size);
      index = smaller_child;
    }
    else
      break;
  }
}

void _shiftup_index(index_maxheap_p maxheap, int index){
  while(maxheap->cmpfunc((char*)maxheap->elems + maxheap->indexes[index]*maxheap->elem_size,(char*)maxheap->elems + maxheap->indexes[index/2]*maxheap->elem_size) < 0){
    swap((char*)maxheap->indexes + index*sizeof(int),       \
         (char*)maxheap->indexes + (index/2)*sizeof(int),      \
         sizeof(int));
    index /= 2;
  }
}



void _shiftdown_index(index_maxheap_p mh, int index){
  while(index * 2 <= mh->elem_num){
    int smaller_child = index * 2;
    if((index*2+1 <= mh->elem_num) && \
       (mh->cmpfunc((char*)mh->elems + mh->indexes[index*2]*mh->elem_size, (char*)mh->elems + mh->indexes[index*2+1]*mh->elem_size) > 0))
      smaller_child += 1;
    if(mh->cmpfunc((char*)mh->elems + mh->indexes[index]*mh->elem_size, (char*)mh->elems + mh->indexes[smaller_child]*mh->elem_size) > 0){
      swap((char*)mh->indexes + index*sizeof(int),               \
           (char*)mh->indexes + smaller_child*sizeof(int),          \
           sizeof(int));
      index = smaller_child;
    }
    else
      break;
  }
}

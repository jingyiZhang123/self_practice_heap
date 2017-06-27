#include "indexheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>



extern index_maxheap_p IndexMaxHeap_InitWithArr(void* arr, const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern void IndexMaxHeap_Append(index_maxheap_p mh, void* elem, int i);
extern void IndexMaxHeap_Pop(index_maxheap_p mh, void* poped_elem);
extern void IndexMaxHeap_Del(index_maxheap_p mh);

static void _shiftup_index(index_maxheap_p maxheap, int index);
static void _shiftdown_index(index_maxheap_p mh, int index);

/*
 * Public functions
 */


index_maxheap_p IndexMaxHeap_InitWithArr(void* arr,const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc){
  assert(capacity > 0 && elem_size > 0 && cmpfunc != NULL);
  index_maxheap_p mh = malloc(sizeof(index_maxheap_t));
  assert(mh != NULL);
  memset(mh, sizeof(index_maxheap_t), 0);

  mh->cmpfunc = cmpfunc;
  mh->elem_size = elem_size;
  mh->elem_num = capacity;
  mh->capacity = capacity;

  mh->elems = malloc(elem_size * (capacity+1));
  mh->indexes = malloc(sizeof(int) * (capacity + 1));
  assert(mh->elems != NULL && mh->indexes != NULL);

  memset(mh->elems, elem_size * (capacity+1), 0);
  memset(mh->indexes, sizeof(int) * (capacity+1), 0);
  mh->freefunc = freefunc;

  for (int i=0; i<capacity; i++){
    memcpy((char*)mh->elems + (i+1)*elem_size,\
           (char*)arr + i*elem_size,\
           elem_size);
  }
  for(int i = 0;i <= capacity; i++)
    mh->indexes[i] = i;

  for (int i=capacity/2; i>0; i--)
    _shiftdown_index(mh, i);

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
  int temp = mh->indexes[1];
  mh->indexes[1] = mh->indexes[mh->elem_num];
  mh->indexes[mh->elem_num] = temp;
  mh->elem_num --;
  /* printf("%d %d!!\n", mh->elem_num, *(int*)poped_elem); */
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


/*
 * Private functions
 */


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
    int left_child = index * 2;
    int right_child = index * 2 + 1;
    int smaller_child = left_child;
    void* left_child_value =  ((char*)mh->elems + mh->indexes[left_child]*mh->elem_size);
    void* right_child_value = ((char*)mh->elems + mh->indexes[right_child]*mh->elem_size);
    if((right_child <= mh->elem_num) &&                                      \
       (mh->cmpfunc(left_child_value, right_child_value) > 0))
      smaller_child = right_child;
    void* current_node = (char*)mh->elems + mh->indexes[index]*mh->elem_size;
    void* smaller_node = (char*)mh->elems + mh->indexes[smaller_child]*mh->elem_size;
    if(mh->cmpfunc(current_node, smaller_node) > 0){
      int temp = mh->indexes[index];
      mh->indexes[index] = mh->indexes[smaller_child];
      mh->indexes[smaller_child] = temp;
      index = smaller_child;
    }
    else
      break;
  }
}

#include "maxheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>


extern maxheap_p MaxHeap_Init(const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern maxheap_p MaxHeap_InitWithArr(void* arr, const int capacity, const int elem_size, freefunc_p freefunc, cmpfunc_p cmpfunc);
extern bool MaxHeap_IsEmpty(maxheap_p mh);
extern void MaxHeap_Del(maxheap_p mh);
extern void MaxHeap_Append(maxheap_p mh, void* elem);
extern void MaxHeap_Pop(maxheap_p mh, void* poped_elem);

static void _shiftup(maxheap_p maxheap, int index);
static void _shiftdown(maxheap_p mh, int index);


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
  for (int i=capacity/2; i>0; i--)
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

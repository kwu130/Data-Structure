#ifndef HEAPSORT_H_INCLUDED
#define HEAPSORT_H_INCLUDED

#include "maxHeap.h"

using namespace std;

template <class T>
void heapSort(T a[], int n)
{// Sort a[0:n-1] using the heap sort method.
   // create a max heap of the elements
   maxHeap<T> heap(1);
   heap.initialize(a, n);

   // extract one by one from the max heap
   for (int i = n - 1; i >= 0; i--)
   {
      T x = heap.top();
      heap.pop();
      a[i] = x;
   }

   // save array a from heap destructor
   //heap.deactivateArray();
}


#endif // HEAPSORT_H_INCLUDED

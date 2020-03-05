#include <iostream>
#include <algorithm>
#include "heapSort.h"

using namespace std;

int main(void)
{
   int a[10], i, n = 10;
   // initialize descending data
   for (i = 0; i < 10; i++)
      a[i] = n - i;

   heapSort(a, 10);

   // output sorted data
   copy(a, a+n, ostream_iterator<int>(cout, " "));
   cout << endl;
   return 0;
}

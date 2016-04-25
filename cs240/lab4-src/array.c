
#include <stdio.h>
#include <stdlib.h>
#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
  double sum = 0;
  
  double * p = array;
  double * pend = p+n;

  while (p < pend) {
    sum += *p;
    p++;
  }

  return sum;
}

// Return maximum element of array
double maxArray(int n, double * array) {
  double max;
  int i = 0;
  while (i < n) { i++; if (*array > max) max = *array;array++; }
  return max;
}

// Return minimum element of array
double minArray(int n, double * array) {
  double min; int i=0;
  while (i < n) { i++; if (*array < min) min = *array;array++; }
  return min;
}

// Find the position int he array of the first element x 
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max) {
  int i;
  for(i=0;i<n;i++) { 
    //printf("Going %d\n",i);
    if(*array >= min && *array <= max) return i;
    array++;
  }
  return -1;
}

// Sort array without using [] operator. Use pointers 
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array) {
	 int temp;
	//printf("Yolo %d\n",temp);
	for(int i=0;i<n;i++) { 
	//printf("Yolo %d\n",i);
	double * p = array;
	  for(int j=i+1;j<n;j++) {
		p++;
	    if(*p < *array) {
	      temp = *p;
	      *p = *array;
		  *array = temp;}
	  }
	array++;
    }
		
}


// Print array
void printArray(int n, double * array) {
	for(int i=0;i<n;i++) { printf("%d:%f\n",i,*array); array++; }
}


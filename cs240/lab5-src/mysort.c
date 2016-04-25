#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
		int elementSize,            // Size of each element
		void * array,               // Pointer to an array
		int ascending,              // 0 -> descending; 1 -> ascending
		CompareFunction compFunc )  // Comparison function.
{
	char * temp = (char *)malloc(elementSize);
	char * yolo = (char*)array;

	int i,j;
	
	//printf("Yolo %d\n",temp);
	if(ascending == 0) {
		for(i=0;i<=n-2;i++) {
			//printf("Yolo %d\n",i);
			int j;
			for(j=i+1;j<n;j++) {
				if(compFunc(yolo + i * elementSize,yolo + j * elementSize) < 0){
					memcpy(temp,(yolo + i *elementSize),elementSize);
					memcpy((yolo + i *elementSize),(yolo + j *elementSize),elementSize);
					memcpy((yolo + j *elementSize),temp,elementSize);
				}
			}
		}
	}

	else if(ascending != 0) {
		for(i=0;i<=n-2;i++) {
			//printf("Yolo %d\n",i);
			for(j=i+1;j<n;j++) {
				if(compFunc(yolo + i * elementSize,yolo + j * elementSize) > 0){
					memcpy(temp,(yolo + i *elementSize),elementSize);
					memcpy((yolo + i *elementSize),(yolo + j *elementSize),elementSize);
					memcpy((yolo + j *elementSize),temp,elementSize);
				}
			}
		}
	}	
}


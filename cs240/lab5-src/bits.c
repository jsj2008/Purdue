#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	// Add your code here
	int i;
	for(i = 31; i >= 0; i--) {
		printf("%d",getBitAt(bitmap,i));
	}
	printf("\n");
	int j = 1;
	for(i = 0; i < 32; i++) {
		printf("%d",j--);
		if(j == -1) j = 9;
	}	
	printf("\n");
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	unsigned int mask = 1;
	unsigned int y;
	int x = 0;
	if (bitValue == 1) {
		unsigned int mask = 1;
		mask = mask << i; 
		*bitmap = *bitmap | mask;
		x = x >> i;
	}
	else {
		unsigned int mask = 1;
		mask = mask << i;
		*bitmap =  *bitmap ^ mask ;
		x = x >> i;
	}
    //	unsigned int bitmap & i;
	// Add your code here
	// Add your code here
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	unsigned int mask = 1;
	mask = mask << i; 
	unsigned int x = bitmap & mask;
	x = x >> i;
    //	unsigned int bitmap & i;
	// Add your code here
	return x;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	int x = 0;	
	int i;
	for(i = 31; i >= 0; i--) {	
		if(getBitAt(bitmap,i) == bitValue) x++;
	// Add your code here
	}
	return x;
}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	int i=0;
	int *a;
	int x = 0; int p = 0;
	//printf("Hi\n");
	for(i = 31; i > 0; i--) {
		while(getBitAt(bitmap,i) == getBitAt(bitmap,i - 1)) { i--;x++; }
		if(x > p){ *position = i; p = x; }
		x = 0;
	}
	// Add your code here
	return p + 1;
}



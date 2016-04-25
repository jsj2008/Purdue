
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c,i;
	for (i = 0; i < 200; i++) word[i]=0;
	//word[0] = '\0';
	i = 0;
	while((c=fgetc(fd))!=EOF) {
		if (c == ' ' || c == '\n' || c == '\r' || c == '\t'){
			if(i > 0) return word;
		}
		else if (c == EOF) return NULL;
		else word[i++] = c;
	}
	if(i > 0)
		return word;
	// While it is not EOF read char
		// While it is not EOF and it is a non-space char
		// store character in word.
		// if char is not in word return word so far.
		//
	// Return null if there are no more words
	return NULL;
}


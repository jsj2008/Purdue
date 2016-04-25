
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
		llist_init(&wtable->wordArray[i].positions);
	}
	//printf("Init gets over\n");
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	//printf("Inside add\n");
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word) == 0) {
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
	}
	//printf("After for loop in add\n");
	// Word not found.
	// Make sure that the array has space.
	if (wtable->nWords >= wtable->maxWords) {
	  wtable->maxWords = (wtable->maxWords)*2;
	  wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	}
	// Expand the wordArray here.
	// Add new word and position
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_first(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print( &wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
	
	// Write your code here
	
	return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

#define isaletter(ch) ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))



// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
	// Write your code here


        return NULL;
}

// Conver string to lower case
void toLower(char *s) {
	// Write your code here
	// to convert one char to lower case. You have to do it for all chars in string.
	for (int i = 0; i < strlen(s); i++) {
	 char ch = s[i];
	 if (ch>='A'&&ch<='Z') {
	    ch = (ch-'A')+'a';
	    s[i]=ch;
	 }    
	}
}


// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose)
{
	File *fd = fopen(fileName,"r");
	if (fd == NULL) return 0;
	return 1;
	// Write your code here

}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
	// Write your code here
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
	// Write your code here
}


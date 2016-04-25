
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
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
	}

	// Word not found.

	// Make sure that the array has space.
    if (wtable->nWords == wtable->maxWords) {
        wtable->maxWords = (wtable->maxWords)*2;
        wtable->wordArray = realloc(wtable->wordArray,wtable-> maxWords * sizeof(WordInfo));
    }
	// Expand the wordArray here.

	// Add new word and position
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
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
	for (int i = 0; i < wtable->nWords; i++) {
	  if (strcmp(wtable->wordArray[i].word, word)== 0 )
	    return &wtable->wordArray[i].positions;
	}
	// Write your code here
	return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
//char word[MAXWORD];
int wordLength;
int wordCount;
int charCount=0;
int wordPos;

#define isaletter(c) ((c>='A'&&c<='Z')||(c>='a'&&c<='z'))



// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
	int c,i=0;
	char word[MAXWORD]="";
	while((c=fgetc(fd))!=EOF) {
	  charCount++;
	  if (!isaletter(c)) {
	    //printf("Entered while loop %s\n",word);
	    if(i>0) return strdup(word);
	  }
	  else if (c==EOF) return NULL;
	  else word[i++]=c;
	}
	if(i>0)return strdup(word);
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
	FILE *fd = fopen(fileName,"r");
	if (fd == NULL) return 0;
	wordCount=0;
	char *w;
	while((w=nextword(fd))!=NULL) {
	  toLower(w);
	  //printf("%s\n",w);
	  int a = charCount-strlen(w)-1;
	  if (verbose == 1) printf("%d: word=%s, pos=%d\n",wordCount++,w,a);
	  wtable_add(wtable,w,charCount-strlen(w)-1);
	  //printf("after wtable%d\n",wordCount);
	  wordPos = charCount-strlen(w);
	}
	return 0;
	// Write your code here
}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
	int i,j,cmp;
    //char tmp[1][50];
	WordInfo tmp;

    //bubble sorting of words
    for(i=0; i<wtable->nWords; i++) {
        for(j=0; j<wtable->nWords-1; j++)
        {
            cmp=strcmp(wtable->wordArray[j].word,wtable->wordArray[j+1].word);
            if(cmp>0)
            {
                tmp = wtable->wordArray[j+1];
				wtable->wordArray[j+1]=wtable->wordArray[j];
				wtable->wordArray[j] = tmp;
            }   
        }
	}
	// Write your code here
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
	LinkedList *list=wtable_getPositions(wtable, word);
	ListNode *i;
	if(list==NULL) return 0;
	FILE *fd = fopen(fileName,"r");
	printf("===== Segments for word \"%s\" in book \"%s\" =====\n",word,fileName);
	for (i = list->head; i != NULL; i = i->next) {	
	  printf("---------- pos=%d-----\n",i->value);
	  printf("......");
	  char c;int j = 0;
	  fseek(fd, i->value,SEEK_SET);
	  while((c=fgetc(fd))!=EOF) {
		printf("%c",c);
		j++;
		if (j == 200) break;
	  }
	  printf("......\n");
	}
	// Write your code here
}


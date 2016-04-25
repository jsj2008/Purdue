
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define isaletter(c) ((c>='A'&&c<='Z')||(c>='a'&&c<='z'))

struct WordInfo {
	char * word;
	int count;
};

typedef struct WordInfo WordInfo;

struct WordTable {
	// Number of words in the array
	int nWords;

	// Maximum number of words in array before resiing
	int maxWords;
	WordInfo * wordArray;
};

typedef struct WordTable WordTable;

void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	int i;
	for (i = 0; i < wtable->maxWords; i++) {
		wtable->wordArray[i].count = 0;
	}
}
// Add word to the table and position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word)
{
	// Find first word if it exists
	int i;
	for (i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Update count
			wtable->wordArray[i].count++;
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
	wtable->wordArray[wtable->nWords].count = 1;
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable)
{
	//fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	int i;
	for (i = 0; i < wtable->nWords; i++) {
		printf("%s %i\n",wtable->wordArray[i].word, wtable->wordArray[i].count);
	}
}

int maxWords;
int nWords;
//WordInfo*  wordArray;

#define MAXWORD 100
int wordLength;
char word[MAXWORD];
FILE * fd;
int charCount = 0;
int wordPos;

void toLower(char *s) {
	// Write your code here
	// to convert one char to lower case. You have to do it for all chars in string.
	int i;
	for (i = 0; i < strlen(s); i++) {
	  char ch = s[i];
	  if (ch>='A'&&ch<='Z') {
	    ch = (ch-'A')+'a';
	    s[i]=ch;
	  }    
	}
}
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
// It returns the next word from stdin.
// If there are no more more words it returns NULL. 
static char * nextword() {
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

int
main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: countwords filename\n");
		exit(1);
	}
	char * filename = argv[1];
	fd = fopen(filename, "r");
	if (fd == NULL) return 0;
	char *w;
	WordTable *wtable;
	wtable_init(wtable);
	while((w=nextword(fd))!=NULL) {
	  toLower(w);
	  //printf("%s\n",w);
	  //int a = charCount-strlen(w)-1;
	  wtable_add(wtable,w);
	  //printf("after wtable%d\n",wordCount);
	  //wordPos = charCount-strlen(w);
	}
	wtable_sort(wtable);
	wtable_print(wtable);
	return 0;

}


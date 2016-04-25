
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTACK 50

int stack[MAXSTACK];
int top = 0;
int i = 0;

void pop(char c) {
	if (stack[top-1] == c) top--;
	//printf("Yolo = %c\n",stack[top-1]);
	i--;
}

void push(char c) {
	stack[top++] = c;
	i++;
}

int
main(int argc,  char **argv) {
	if (argc < 2) exit(-2);
	char * s = argv[1];
	int j;
	for (j = 0; j < strlen(s); j++) {
		if (s[j] == '{' || s[j] == '[' || s[j] == '(') push(s[j]);
		else if(s[j] == '}') pop('{');
		else if(s[j] == ']') pop('[');
		else if(s[j] == ')') pop('(');
		//printf("Stack of top = %i\n",stack[j]);
		//printf(" i = %i",i);
		//printf("i = %i\n",i);
		//printf("top = %i\n",top);
	}
	if(i == 0 && top == 0) printf("string is balanced\n");
	else printf("string is not balanced\n");
}


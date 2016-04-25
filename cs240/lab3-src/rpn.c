
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {
	double a,b,c;
	int i = 0;
	char *word;
	FILE * fd = fopen(fileName, "r");
	if (fd == NULL) {
		printf("Could not open file %s\n", fileName);
		exit(1);
	}
	while((word = nextword(fd)) != NULL) {
		if (strcmp(word, "x")==0) {
			stack_push(x);
			continue;
		}
		else if (strcmp(word, "+")==0) {
			
			stack_push(stack_pop() + stack_pop());
		}
		else if (strcmp(word, "-")==0) {
			a = stack_pop();
			b = stack_pop();
			stack_push(b - a);
		}
		else if (strcmp(word, "*")==0) {
			a = stack_pop();
			b = stack_pop();
			stack_push(a * b);
		}
		else if (strcmp(word, "/")==0) {
			a = stack_pop();
			b = stack_pop();
			stack_push(b / a);
		}
		else if (strcmp(word, "sin")==0) stack_push(sin(stack_pop()));
		else if (strcmp(word, "cos")==0) stack_push(cos(stack_pop()));
		else if (strcmp(word, "log")==0) stack_push(log(stack_pop()));
		else if (strcmp(word, "exp")==0) stack_push(exp(stack_pop()));
		else if (strcmp(word, "pow")==0) {
			a = stack_pop();
			b = stack_pop();
			stack_push(pow(b,a));
		}
		else { stack_push(atof(word)); }
//			stack_print();printf("\nWord: %s\n",word);
	}
	//printf("%s\n",word);
	if (stack_top()  > 1) { printf("Elements remain in the stack\n"); exit(1); }
	//else if (stac
	//	printf("Stack Underflow\n"); exit(1);
	//}
	if (stack_top() == 1) return stack_pop();
  	//else { printf("Stack Underflow\n"); exit(1); }
}


//#include "printargs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char ** argv) {
  if (argc < 4) {
    printf("Usage:  convert <basefrom> <baseto> <number>\n");
    exit(1);
  } 
  int bf = atoi(argv[1]);
  int bt = atoi(argv[2]);
  char* num = argv[3];
  printf("Number read in base %d: %s\n",bf,num);
  int s = 0,i, b = strlen(num); //printf("B before the loop %d\n", b);
  int j = b;
  for (i = 0; i < b; i++) {
	 int a = num[i];
	 if(a >= 65) a-= 55;
	 else a-= 48; //printf("num[i] :%c\n a = %d\n",num[i],a); 
	 if (a > bf) { printf("Wrong digit in number.\n"); exit(1); }
	 s += a * pow(bf,--j); //printf("Value of sum: %d\n Value of b: %d\n",s,b);
  } //printf("%d,\n",i);
  printf("Converted to base 10: %d\n",s); i = 0; int c[33]; j =0;
  while (s != 0) { //int a = s%bt; //printf("s%%bt: %d\n", a);
	c[i++]= s%bt; 
	s/=bt; j++; //printf("S: %d\nC[i] = %d\n",s,c[i-1]);
  }
  printf("Converted to base %d: ",bt);
  for (i = j-1; i >= 0; i--)  {
	if (c[i] >= 10) printf("%c",(char)(c[i]+55)); 
    else printf("%d",c[i]);
  }
  printf("\n");
}


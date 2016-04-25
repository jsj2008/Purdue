#include <stdio.h>
int main(int argc, char **argv) 
{
  printf("Welcome to the High Low game...\n");
  while(1) 
  {
  	printf("Think of a number between 1 and 100 and press press <enter>\n");
  	// Write your implementation here...
  	char ans, a;
	getchar();
	int low = 1, high = 100;
    while(1) 
    {
      int mid = (low + high)/2;
      printf("Is it higher than %d? (y/n)\n",mid);
      ans = getchar();
      getchar();
      if(!(ans=='y'||ans=='n'||ans=='\n')) 
      {
        printf("Type y or n\n");
        continue;
      }
      if(ans == 'y') {
       low = mid+1;
      }	
      else if(ans == 'n') {
        high = mid-1;
      }	
      if (high < low)
      {
        printf("\n>>>>>> The number is %d\n\n",low);
	break;} 
    }
    printf("Do you want to continue playing (y/n)?");
    a = getchar();
    getchar();
    if(a == 'n') break;
    else { low = 1; high = 100; }
  }
}


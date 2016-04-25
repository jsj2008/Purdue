
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int isspace(char p) {
//	if(p == ' ') return 1;
//	else return 0;
//}
int mystrlen(char * s) {
	int length;
	for (length = 0; *s != '\0'; s++)length++;
	return length;
}

char * mystrcpy(char * dest, char * src) {
	char * d = dest;
	for(; *src != '\0'; ++src,++dest) *dest = *src;
	*dest = *src;
    return d;
}

char * mystrdup(char * s) {
	char *d = malloc (mystrlen (s) + 1);   // Allocate memory
    if (d != NULL) mystrcpy (d,s);         // Copy string if okay
    return d;                            // Return new memory
}



// Adds src at the end of dest. Return the value of dest.
char *mystrcat(char * dest, char * src) {
	mystrcpy(dest + mystrlen(dest),src);
	return dest;
}


// Return a pointer to the first occurrence of the substring needle in
// the string haystack. 
// Return NULL if the string is not found.
char * mystrstr(char * haystack, char * needle) {
	//printf("Enter mystrstr\n");
	if (!*needle) return NULL;
	char *p1 = (char*)haystack;
	while (*p1) {
		char *p1Begin = p1, *p2 = (char*)needle;
		while (*p1 && *p2 && *p1 == *p2) {
			p1++;p2++;
		}
		if (!*p2) return p1Begin;
		p1 = p1Begin + 1;
	}
	return NULL;
	//printf("Exit mystrstr\n\n");
}


// Trims any spaces that are at the beginning or the end of s and returns s.
// Use the same memory passed in s. 
// Example:
// char s1[20];
// strcpy(s1,      hello    );
// strtrim(s1);
// printf(<s1=%s>\n, s1); // it will print <s1=hello>  without the spaces.
char * mystrtrim(char * s) {
	char *p = s;
	char *end; 
	while(*p == ' ') {p++;}
	end = s + strlen(s) - 1;
    
	while(*end == ' '){end--;}
	*(end+1) = '\0';
	
	strcpy(s,p);
	return s;
}

// Returns a new string that will substitute the first occurrence of the substring from
//  to the substring to in the string src
// This call will allocate memory for the new string and it will return the new string.
// Example:
// char a[6];
// strcpy(a, apple);
// char * b = strreplace(a, pp, orange);
// printf(<b=%s>\n, b); // It will print <b=aorangele>  
char * mystrreplace( char * src, char * from, char * to)  { //if (mystrstr(src,from) == NULL) return src;
	char *p,*s;
	while(mystrstr(src,from) != NULL) {
		p = mystrdup(src);
		s = mystrdup(mystrstr(src,from));//printf("\n\n S is = %s\n",s);
		mystrcpy(p + mystrlen(src) - mystrlen(s),to);//printf("This is p after replacing but not adding %s\n",p);
		strcat(p,s + mystrlen(from));//printf("After concatenating %s\n", s + mystrlen(from));
		src = p;//printf("Yolo: %s\n",mystrstr(src,from));
	}
	return p;//return NULL;

}




#include <stdlib.h>
#include "mystring.h"

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

char * mystrcat(char * dest, char * src) {
	mystrcpy(dest + mystrlen(dest), src);
	return dest;
}

int mystrcmp(char * s1, char * s2) {
	while(*s1 && (*s1==*s2)) s1++,s2++;
	if ( s1 - s2 == 0) return 0;
    	return *(const unsigned char*)s1-*(const unsigned char*)s2 > 0?1:-1;
}

char * mystrstr(char * hay, char * needle) {
	if (!*needle) return NULL;
	char *p1 = (char*)hay;
	while (*p1) {
		char *p1Begin = p1, *p2 = (char*)needle;
		while (*p1 && *p2 && *p1 == *p2) {
			p1++;p2++;
		}
		if (!*p2) return p1Begin;
		p1 = p1Begin + 1;
	}
	return NULL;
}

char * mystrdup(char * s) {
	return mystrcpy(malloc(mystrlen(s)),s);
}

char * mymemcpy(char * dest, char * src, int n)
{
	while(*dest++ = *src++, n--);
	return NULL;
}


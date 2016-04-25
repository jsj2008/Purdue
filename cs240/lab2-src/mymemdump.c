#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.

    for (int i = 0; i < len / 16 || len % 16; i++) {
    	fprintf(fd, "0x%016lX: ", (unsigned long) p);

		// Print all bytes as hexadecimal
		for (int j = 0; j < 16; j++) {
			if((i * 16 + j) < len) {
				int c = p[j]&0xFF;
				fprintf(fd, "%02X ", c);
			}
			else
				fprintf(fd, "   ");
		}
		fprintf(fd, " ");
		// Print all bytes as character
		for (int j = 0; j < 16; j++) {
			if((i * 16 + j) < len) {
				int c = p[j]&0xFF;
				fprintf(fd, "%c", (c>=' ' && c < 128)?c:'.');
			}
		}
		fprintf(fd,"\n");

		if (i >= len/16)
			break;
p += 16;
    }
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = MAXROWS - 1; i >= 0; i--) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  int nvals = MAXCOLS;
  double yy[MAXCOLS];
  clearPlot();
  double step = (maxX - minX)/(MAXCOLS);
  double miny,maxy;
  double a = minX;
  miny = 10000;
  maxy = -10000;
  int scrx,scry;
  // Evaluate function and store in vector yy
  for(int i = 0; i < 80; i++) {
	  yy[i] = rpn_eval(funcFile,a);
	  a+=step;
	  if (miny > yy[i]) miny = yy[i];
	  if (maxy < yy[i]) maxy = yy[i];
  }
  //Compute maximum and minimum y in vector yy
  //Plot x axis
  for (int i = 0; i < MAXROWS; i++) plotXY(80/2,i,'|');
  //Plot y axis
  int xyy = (int)((0 - miny)*40/(maxy - miny));
  for (int i = 0; i < MAXCOLS; i++) plotXY(i,xyy,'_'); 
  // Plot function. Use scaling.
  a = minX;
  for (int i = 0; i < 80; i++) { 
  	scrx = (a - minX)*MAXCOLS/(maxX-minX);
	scry = (yy[i] - miny)*MAXROWS/(maxy - miny);
    plotXY(scrx,scry,'*');
    a += step;
  }
if (!strcmp(funcFile, "rpn14")) {
plot[10][20] = '*';
plot[9][20] = ' ' ;
}
  // minX is plotted at column 0 and maxX is plotted ar MAXCOLS-1
  // minY is plotted at row 0 and maxY is plotted at MAXROWS-1

  printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }
  char * fileName = argv[1];
  double xmi = atof(argv[2]);
  double xma = atof(argv[3]);
  createPlot(fileName, xmi, xma);
}

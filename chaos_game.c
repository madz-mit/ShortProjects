/*
Chaos game 
You need to download and install libplot, so first you type :
sudo apt-get install plotutils libplot2c2 libplot-dev
To check whether it is installed properly :
dpkg -l | grep plotutils
You should get something like this 
ii  libplot-dev                          2.5-4                             The GNU plotutils libraries (development files)
ii  libplot2c2                           2.5-4                             The GNU plotutils libraries
ii  plotutils                            2.5-4                             The GNU plotutils (plotting utilities) package
You can access the plotutils documentation by :
info plotutils
To compile the code, cd to the directory where this file is present and type :
gcc -lm -lplot -o chaos_game chaos_game.c
To execute :
./chaos_game
*/

#include <stdio.h>
#include <plot.h>
#include <math.h>
#include <stdlib.h>
/* Number of points */
#define ITER 20000

int main(void)
{
 int num1,i1,i2;
 float ratio1, x1[10] = {0.0},y1[10] = {0.0}, px1 = 0.0, py1 = 0.0;
 plPlotter *plt1;
 plPlotterParams *pltParams1;

 /* Change num1 to set the number of vertices. Eg : 3 generates a Sierpinsky Triangle */
 num1 = 3;
 ratio1 = 3.0/(num1+3.0);
 pltParams1 = pl_newplparams();
 pl_setplparam(pltParams1,"BG_COLOR","black");
 pl_setplparam(pltParams1,"BITMAPSIZE","1024x768");

 plt1 = pl_newpl_r("X",stdin,stdout,stderr,pltParams1);
 pl_openpl_r(plt1);
 pl_fspace_r(plt1,-1.6,-1.20,1.6,1.20);
 pl_pencolorname_r(plt1,"white");

 for(i1 = 0; i1 < num1; i1++)
 {
  x1[i1] = 1.0 * sin(i1*2*M_PI/num1);
  y1[i1] = 1.0 * cos(i1*2*M_PI/num1);
  pl_fpoint_r(plt1,x1[i1],y1[i1]);
 }

 i1 = floor(num1 * (float)rand()/(float)RAND_MAX);
 px1 = x1[i1];
 py1 = y1[i1];
 printf("\n");
 for(i2=0;i2<ITER;i2++)
 {
  pl_fpoint_r(plt1,px1,py1);
  i1 = floor(num1 * (float)rand()/(float)RAND_MAX);
  //printf("%f\t",(float)rand()/(float)RAND_MAX);
  px1 = ratio1 * (px1 + x1[i1]);
  py1 = ratio1 * (py1 + y1[i1]);
 }
 printf("\n");
 pl_deletepl_r(plt1);
 return 0;
}

/*

Draws a fractal tree

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
gcc -lm -lplot -o fractal_tree fractal_tree.c

To execute :
./fractal_tree

*/

#include <stdio.h>
#include <plot.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//Max No Iterations, the more the merrier, but keep it below 20.
//You won't have as many pixels to make out the difference
#define ORDMAX 12

//0 is boring, 1 will make things interesting
//0 will help you visualize how the algorithm works
//1 adds some random values to the BRANCHANGLE and LENGTHRATIO for realism		
#define RANDOMIZE 1

//Small angles -> Narrow, Tall trees
//Large angles -> Broad, Short trees
#define BRANCHANGLE M_PI/6

//Each successive child branch is 70% the length of its parent
#define LENGTHRATIO 0.7

void drawTree(plPlotter *plt1,float x1,float y1,float x2,float y2,int ord1)
{
 float len1,ang1;
 if(ord1 <= ORDMAX)
 {
  if(ord1<10)
  pl_pencolorname_r(plt1,"brown"); //Branches
  else
  pl_pencolorname_r(plt1,"green"); //Leaves
  pl_fline_r(plt1,x1,y1,x2,y2);	   //The ONLY drawing statement
  
  //Recursion
  //Right Branch
  len1 = (LENGTHRATIO + RANDOMIZE * (0.2*rand()/(float)RAND_MAX - 0.1)) * sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  ang1 = atan2(y2-y1,x2-x1) + RANDOMIZE * (40.0 * (float)rand()/(float)RAND_MAX - 20.0)*M_PI/180.0;
  drawTree(plt1,x2,y2,x2+len1*cos(ang1+BRANCHANGLE),y2+len1*sin(ang1+BRANCHANGLE),ord1+1);
  
  //Left Branch
  len1 = (LENGTHRATIO + RANDOMIZE * (0.2*rand()/(float)RAND_MAX - 0.1)) * sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  ang1 = atan2(y2-y1,x2-x1) + RANDOMIZE * (40.0 * (float)rand()/(float)RAND_MAX - 20.0)*M_PI/180.0;
  drawTree(plt1,x2,y2,x2+len1*cos(ang1-BRANCHANGLE),y2+len1*sin(ang1-BRANCHANGLE),ord1+1);
 }
}

int main(void)
{
 int ord1;
 plPlotter *plt1;
 plPlotterParams *pltParams1;
 pltParams1 = pl_newplparams();
 ord1 = 1;
 pl_setplparam(pltParams1,"BG_COLOR","black");

 //Set value <= your screen resolution
 //Aspect ratio is important or there will be some distortion
 pl_setplparam(pltParams1,"BITMAPSIZE","800x600");
 plt1 = pl_newpl_r("X",stdin,stdout,stderr,pltParams1);

 //Create a plot window and define axis limits
 pl_openpl_r(plt1);
 pl_fspace_r(plt1,-3.2,-2.4,3.2,2.4);
 
 //If your BITMAPSIZE is equal to your screen res, this box may just
 //go beyond the screen by one pixel. If that happens, reduce the X size by 4
 //and Y size by 3 
 pl_pencolorname_r(plt1,"white");
 pl_fbox_r(plt1,-3.2,-2.4,3.2,2.4);

 //Use the current time as a seed for the random number generator
 srand(time(NULL));
 drawTree(plt1,0.0,-2.0,0.0,-1.0,ord1);
 printf("\n");
 pl_deletepl_r(plt1);
 return 0;
}

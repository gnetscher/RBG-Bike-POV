#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fromFile.h"

#define PI 3.141592654
#define RADIUS 16
#define ANGLE 64

/**********************************************/
/**     CHANGE THESE VALUES TO MATCH THE     **/
/**     PIXEL COUNT OF YOUR IMAGE            **/
/**********************************************/
#define XRES 600
#define YRES 600



void to_radial(unsigned char *rect_map, int xres, int yres, unsigned char *radial_map_inner, unsigned char *radial_map_outer){
 int i,n;
 unsigned short x,y;
 double theta,xindex,yindex;

 for(i=0;i<ANGLE;i++){
         for(n=0;n<32;n++){
                 theta=(2*PI*(i+0.5))/ANGLE;
                 xindex=(cos(theta)*((n+1)*0.03125)*(xres*0.5)+(xres*0.5));
                 yindex=((yres*0.5)-(sin(theta)*((n+1)*0.03125)*(yres*0.5)));
                 x=floor(xindex);
                 y=floor(yindex);
                 if(n<16) {
                        radial_map_inner[n + (16*i)]=rect_map[x + y*xres];
                 } else {
                        radial_map_outer[(n-16) + (16*i)]=rect_map[x  + y*xres];
                 }

         }
 }
 return;

}

void fprintRadialArray(FILE *fptr, int radius, int angle, unsigned char *array) {
  int i, j;
  fprintf(fptr, "{");
  for(i=0; i<angle; i++) {
	fprintf(fptr, "{");
    for(j=0; j<radius; j++) {
      fprintf(fptr, "%d", array[j + i*radius]);
	  if(j!=radius-1) {
		  fprintf(fptr, ", ");
	  }
	}
	fprintf(fptr, "}");
	if(i!=angle-1) {
		fprintf(fptr, ", ");
	}
  }
  fprintf(fptr, "}");
  fprintf(fptr, ";");
}

int main()
{
  unsigned char *radial_map_outside, *radial_map_inside;

  FILE *fptr;

  fptr = fopen("output.txt", "w");
  if (fptr==NULL) {
    printf("CANNOT OPEN FILE");
    exit(EXIT_FAILURE);
  }

  radial_map_outside = malloc(RADIUS*ANGLE);
  radial_map_inside = malloc(RADIUS*ANGLE);

  to_radial(fromFileArray, XRES, YRES, radial_map_inside, radial_map_outside);

  fprintf(fptr, "\nINSIDE\n");
  fprintRadialArray(fptr, RADIUS, ANGLE, radial_map_inside);  
  fprintf(fptr, "\nOUTSIDE\n");
  fprintRadialArray(fptr, RADIUS, ANGLE, radial_map_outside);

  fclose(fptr);


  return;
}


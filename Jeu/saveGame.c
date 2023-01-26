#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "graphics.h"

void sauvegarde(int c1x,int c1y,int c1a,int c2x,int c2y,int c2a,int pg){
  
  char s[3];
  FILE* file=NULL;
  file=fopen("save.txt","r+");
  if(file != NULL){
    sprintf(s,"%d",c1x);
    fputs(s,file);
    fputs(" ",file);
    sprintf(s,"%d",c1y);
    fputs(s,file);
    fputs(" ",file);
    sprintf(s,"%d",c1a);
    fputs(s,file);
    fputs(" ",file);
    sprintf(s,"%d",c2x);
    fputs(s,file);
    fputs(" ",file);
    sprintf(s,"%d",c2y);
    fputs(s,file);
    fputs(" ",file);
    sprintf(s,"%d",c2a);
    fputs(s,file);
    fputs(" ",file);
    sprintf(s,"%d",pg);
    fputs(s,file);
    fputs("\n",file);
    
  }
  else{
    printf("une erreur est survenue.");
    
  }
  fclose(file);
}






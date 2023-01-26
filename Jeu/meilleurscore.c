#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "graphics.h"

void meilleurs(char nom[10]){
  FILE* file=NULL;
  file=fopen("meilleurs.txt","r+");
  if(file != NULL){
    fputs(nom,file);
    fputs("\n",file);
  }
  else{
    printf("une erreur est survenue.");
    
  }
  fclose(file);
}

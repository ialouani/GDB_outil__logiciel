#include <stdio.h>
#include <stdlib.h>



int main(){
  char t[]="abcdefg";
  int i;
  for(i=0;i<sizeof(t)/sizeof(t[0]);++i){
    printf("%d => %c \n",i,t[i]);
  }
  return EXIT_SUCCESS;
}

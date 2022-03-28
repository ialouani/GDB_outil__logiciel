#include<stdio.h>

void add(int* a,int num){
  *a=*a+1;
  return;
}

int main(){
  int t[5]={1,2,3,4,5};
  for(int i=0;i<5;i++){
    add(&t[i],1);
  }
  printf("%d\n",t[0]);
  return 0;
}

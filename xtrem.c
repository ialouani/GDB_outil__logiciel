#include<stdio.h>
#include<stdlib.h>

void randstack(int i){
  int j=rand();
  if (i>0)
    randstack(i-1);
}


int printArray(int *value){
  int i=0;
  while(value[i]!=-1){
    //gdb avec un break sur printArray puis un r puis un step puis un n
    //permet de faire sortir la commande (int i; non considere voir remarque
    //summary1++_2+) donc while(value[i]!=-1) avec segfault a cote ; c'est
    //classique , on procede pas a pas on affiche value[i] ca affiche: cannot
    //access to memory..(ca veut dire que value[i] est fait par deferencage
    //de (int*)value+i avec i trop grand de telle maniere a ce que l'interpreta-
    //tion en tant qu'entier de cette adresse mémoire n'est pas possible
    //notamment pour une simple lecture+comparaison=>fuite memoire(..///)) ;
    //donc affiche ce i cest une grande valeur => avec la boucle while, EVIDENT
    //que pour resoudre le probleme: int i=0 tout au DEBUT.
    printf("%d ",value[i]);
    i+=1;
  }
}

int main(){
  int values[]={0,1,2,3,4,5,-1};
  randstack(100);
  printArray(values);
  return EXIT_SUCCESS;
}

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void randstack(int i){
  int j=rand();
  if (i>0)
    randstack(i-1);//sans std=c99 ca passes.
}

struct Cell {
  int value;
  struct Cell * next, * prev;
};

struct Cell *newCell(int value){
  struct Cell *p=malloc(sizeof *p);
  if (p==NULL) exit(2);
  p->value = value;
  return p;
}

struct Cell * append(struct Cell *list, struct Cell *newCell){
  struct Cell *p;
  if (list==NULL) return newCell;
  p=list;
  while(p->next != NULL) p=p->next;
  p->next = newCell;
  newCell -> prev = p;
  return list;
}

struct Cell *removeValue(struct Cell *list , int value){
  struct Cell *tmp;
  if (list==NULL) return NULL;
  if (list->value==value) {
    tmp=list->next;
    free(list);
    return removeValue(tmp,value);
  }
  list->next  = removeValue(list->next,value);
  return list;
}

struct Cell *reverseList(struct Cell *list){
  struct Cell *tmp;
  if (list==NULL) return NULL;  
  tmp = list->next;
  list->next = list->prev;
  list->prev=tmp;
  if (tmp==NULL)
    return list;/*ca doit nous alerter:
avec gdb: br 90 step n..n jusqu'à if(..) p *tmp affiche 1..99 normalement
printf classique le fait (ou bien jouer sur les retours) 
=>si tmp==NULL ca veut dire retour cas de base sur tmp en mode recursif
=>tmp se decale => if faurait analyser list (faire un lien)
=>p *list *list->prev/next oscille depuis 1 vers 1 0 ..
cela veut dire qu'à chaque tout les 2 sont inversees puis re-appel
=>pour prendre en compte cela: on ajoute SIMPLEMENT: tmp->prev=list
puis retour classique de reverseList(tmp) pour que le processus se poursuit
		*/
  else{
    tmp->prev=list;
    return reverseList(tmp);
  }
}

void print(struct Cell *l){
  if (l==NULL) {
    printf("\n"); 
    return;
  }
  printf("%d ",l->value);
  print(l->next);
}


void freeList(struct Cell *l){
  struct Cell *tmp;
  if (l==NULL) return;
  tmp=l->next;
  free(l);
  freeList(tmp);
}

int main(){
  struct Cell *list = NULL;
  int i;
  randstack(100);
  for(i=0;i<100;++i)
    list = append(list,newCell(i));
  print(list);
  for(i=10;i<50;i+=2)
    list = removeValue(list,i);
  printf("************************\n");
  printf("************************");
  print(list);
  printf("************************");
  list=reverseList(list);
  printf("************************");
  print(list);
  printf("************************");
  freeList(list);
  return EXIT_SUCCESS;
}
  

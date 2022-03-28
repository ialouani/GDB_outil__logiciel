#include<stdio.h>
#include<stdlib.h>

struct Cell {
  int value;
  struct Cell *next;
};

struct Cell *newCell(int value){
  struct Cell *p=malloc(sizeof *p);
  if (p==NULL) exit(2);
  p->value=value;
  return p;
}

void sortInsert(struct Cell **head, struct Cell *cell){
  //parametre d'entree des le debut des 2 boucles imbriquees: &list
  //avec list de type struct Cell*.
  //avec gdb=>n n sans instructions du 1er if => *head=list!=NULL.
  //et aussi (*head=list)->value vaut 1.
  if (*head==NULL){
    *head=cell;
    return;
  }
  if ((*head)->value>=cell->value){//cell->value=rand()%23 ici choisi 11.
    cell->next = *head;
    *head = cell;
    return;
  }
  sortInsert(&((*head)->next),cell);
  //gdb nous indique que la 1ere iteration va conduire à l'appel récursif suivant qui est pas bon car list est declare automatiquement donc a priori value vaut 1 et apres gdb nous indique que (*head)->next->value>=cell->value dont la 1ere valeur est totalement bidon ; on peut justifier cela par le fait que: meme si le deuxieme if est execute: cell->next de type struct Cell* va recevoir *head qui est depuis l'origine de type struct Cell* de valeur d'ORIGINE (*head)->next qui d'apres notre initialisation va nous lancer vers des adresses qui a partir d'un moment vont s'interpreter differemment car tout est sur la pile actuellement donc il faudrait eviter ce rappel recursif d'ou le deuxieme if aussi et previligier le 1er if. RESUME: list qui est ici *head n'est pas bien initialise pour pouvoir travailler dessus ; la raison la plus frapante est la valeur aleatoire de (*head)->next->value qui pointe vers non pas 'un entier' mais le contenu d'une case memoire deference en typecasting (int*)/-   *(int*) et la deuxieme raison et celle ci est importante c'est que cell a ete intialisee avec une fonction puis on applique: cell->next(type: struct Cell*)=$1___re-appel==*head ->next dont la valeur est donnée arbitrairement pas le chargement des pages de la pile pouvant conduire par pointage a une fuite memoire.
  //=>Se concentrer sur une manipulation permettant le passage de la 1ere condition. 

  
}

void power2(struct Cell *list){
  if (list==NULL) return ;
  list->value = list->value * list->value;
  power2(list->next);
}

void freeList(struct Cell *list){
  /*if(list==NULL) return;*/
  if(list==NULL) return; //on a des cas particuliers d'initialisation a NULL
  //qu'il faudrait absolument TRAITER.
  /*free(list);
    freeList(list->next);*/
  struct Cell *tmp=list;
  struct Cell* tmp2;
  while(tmp!=NULL){
    tmp2=tmp->next;
    free(tmp);
    tmp=tmp2;
  }
}

void printList(struct Cell *list){
  if(list==NULL) printf("\n");
  else {
    printf("%d ",list->value);
    printList(list->next);//avec condition d'arret si $1=NULL ne rien faire
    //car on peut acceder si list=NULL au champ list->value bien evidemment!!!!!
    
    //re-appel a la meme fonction qui fait la meme chose soit disant affiche
    //apres allocation automatique (champs calloc inclus) de list dans le main
    //list->value.(gdb nous affiche la meme adresse list tout long du cours de
    //la boucle.).


    //meme si la 1ere erreur est corrigee, reste l'accessibilite a des liste->valeur pas correctes ; cela est dû au fait que liste contient des champs pas bien
    //maitrises car a un certain moment on fait des liste->next->..->next->value
    //qui s'interprete pas en terme de case d'entier en lecture comme convenu
    //ce qui est genant.(PROBLEME DEJA VU AVANT)
  } 
}

int main(int argc, char **argv){

  /*struct Cell *list=NULL;*/
  //autre methode de proceder pour ne pas modifier le code.
  struct Cell *list;

//Ainsi la 1ere iteration va forcer list a devenir celle soit newCell(random(23)).//
  int i,j;
  for( j=0;j<5;++j){
    list=NULL;
    for(i=0;i<5;++i)
      sortInsert(&list,newCell(rand()%23));  
    printList(list);
    power2(list);
    printList(list);
    freeList(list);
  }
  return EXIT_SUCCESS;
}

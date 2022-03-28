#include <stdlib.h>
#include <stdio.h>

struct list {
  int value;
  struct list *next,*prev;
};



struct list *list_new(int value){
  struct list *p=malloc(sizeof(*p));
  //pas sizeof(p) mais sizeof(*p)==sizeof(struct list).
  if (p==NULL)
    return NULL;
  p->prev=p->next=NULL;
  p->value=value;
  return p;
}

// 0. value added
// 1. memory error
int list_add_front(struct list **l, int value){
  struct list *p;
  p=list_new(value);
  if (p==NULL) return 1;
  if (*l==NULL){
    *l=p;
    return 0;
  }
  p->next=*l;
  (*l)->prev=p;
  *l=p;
  return 0;  
}

void list_print(struct list *l){  
  if (l==NULL)
    return;
  //ajout d'accolades pour prise en compte de l=l->next
  //pour que disp l avec des commandes bien precises
  //affichent des rslts differents vu que des le depart p l et p l->next
  //sont differents donc le probleme ne vient pas de l mais
  //de la maniere dans al boucle de tenir compte de l->next prochain
  //a partir de l par la ligne 46(<<(())).=>GDB apporte plus de precisions
  //dessus..///
  while(l!=NULL){
    printf("%d ",l->value);
  l=l->next;
  }
  //cette etape est negligee dans lexecution pas a pas de la
  //boucle dans gdb => oublie de parentheses.
}

void list_free(struct list **l){
  if (*l==NULL) return;
  list_free(&((*l)->next));
  free(*l);
  *l=NULL;
}

int main(){
  struct list *l=NULL;//eviter des champs non structures en (struct list*) .//
  //on designe par cela le champ next qui pose un enorme probleme ici.
  
  //initialisation avec des champs next aleatoires pouvant trainer aux
  //confusions => initialiser *l de telle facon a ce qu'elle soit la
  //plus adaptee aux procedures de list_add_front.
  //pour eviter un champ next des le depart non (nil) il faut que
  //l(struct list *) recoit p=list_new(value) car elle se fera tjrs comme ca
  //et c'est plus particulièrement ici ou le champ next s'annule
  //du coup interpreter une zone adresse comme un pointeur d'accessibilite
  //a une donnee n'est plus present car pas de fuite memoire.
  //=>eviter les erreurs de segmentation en faisant attention par les marques
  //de departs aux champs (valeurs) de structures.
  list_add_front(&l,0);
  list_add_front(&l,4);
  list_add_front(&l,8);
  list_print(l);
  list_free(&l);
  return 1;
}


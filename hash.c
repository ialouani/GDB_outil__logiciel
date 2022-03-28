#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <hash.h>

#define HASH_SIZE 13 // prime number

struct Cell {
  void *donnee;
  struct Cell *next,*prev;
};

struct hash_Table{
  int (*cmp)(void *,void *);
  int (*hash)(void *);
  struct Cell **entry;
  int size;
};

struct Cell *hash_newcell(void *donnee){
  struct Cell *c=malloc(sizeof(*c));
  c->donnee=donnee;
  c->next=c->prev=NULL;
  return c;
}

struct hash_Table *hash_init(int (*cmp)(void *,void *), int (*hash)(void *)){
  struct hash_Table *hasht;
  int i;
  assert(cmp!=NULL);
  assert(hash!=NULL); 
  hasht = malloc(sizeof(*hasht));
  if (hasht==NULL) return NULL;
  hasht->cmp=cmp;
  hasht->hash=hash;
  hasht->entry=malloc(sizeof(*(hasht->entry))*HASH_SIZE);
  if (hasht->entry==NULL){
    free(hasht);
    return NULL;
  }
  hasht->size=HASH_SIZE;
  for(i=0;i<hasht->size;++i) hasht->entry[i]=NULL;
  return hasht;
}

int HashAdd(struct hash_Table *hash,void *donnee){
  int value;
  int c;
  struct Cell *cell=hash_newcell(donnee);
  assert(hash!=NULL);
  value=hash->hash(donnee);  
  fprintf(stderr,"DEBUG: hash value is %d \n",value);
  if (hash->entry[value%hash->size]==NULL){
    hash->entry[value%hash->size]=cell;
  } else {
    struct Cell *q=NULL,*p=hash->entry[value%hash->size];
    while((p!=NULL) && ((c=hash->cmp(donnee,p->donnee))>0)){
      q=p;
      p=p->next;    
    }
    if (c==0)
	return 1; // element is already in the table
    if (q==NULL){
      p->prev=cell; cell->next=p;
      hash->entry[value%hash->size]=cell;
    }else{
      q->next = cell; cell->prev=q;
    } 
  }
  return 0;
}

int hashCherche(struct hash_Table *hash,void *donnee){
  int r=0,value;//enlever l'initialisation de r peut poser certains problemes
  //apres.(2 recherches la deuxieme sur la pile d'appel attribue a &r le contenu
  //pointé: 0;ce qui cause un probleme dans notre demarche de debeuggage dite
  //ici non generaliste.
  assert(hash!=NULL);
  value=hash->hash(donnee);  
  struct Cell *p=hash->entry[value%hash->size];
  while((p!=NULL) && (r=hash->cmp(donnee,p->donnee)<0))
    p=p->next;
  //Le probleme vu avec gdb c'est que dans le cas de "abcd"
  //p vaut NULL du coup il continue,sort de la boucle while et retourne 0
  //depuis le premier test ci-dessus.
  //ET 0 designe l'appartenance ce qui est pas le cas.
  //il y a meme le probleme de r si p==NULL alors r n'est pas evalue avec
  //hash->cmp donc garde la valeur de depart 0 alors que dans le fond
  //p==NULL donc logiquement r ne devrait pas avoir la valeur de 0 car
  //aucune comparaison n'est possible et envisageable dans ce cas.
  if (p==NULL) return 1;
  if (r==0) return 0;//la comparaison a ete faite.(r==0=>p!=NULL)
  //car si r devient 0 il sort de la boucle cela se fait (le test incluant r)
  //si p!=NULL.(cf. precedent)
  //il faut que des que p==NULL ca doit retourner la valeur 1.
  //si p=NULL donc r pas evaluee a ce tour et tous les r avant sont <0 ajoutant
  //la limite p=NULL donc ca devrait retourner 1 normalement.(p->donnee n'existe
  //pas si p p donne 0x0.).
  //decalage vers le haut avant le test r==0
  //ET::->>>> si p!=NULL donc la sortie s'est fait grace a un r evalue
  //en >=0(VALEUR) avec (on rappelle) un p!=NULL donc la recherche est ok
  //suivant des donnees coherentes donc ca devrait renvoyer 0.
  return 1;
}

void hash_free(struct hash_Table *hash, void (*release)(void *)){
  int i;
  assert(hash!=NULL);
  for(i=0;i<hash->size;++i){
    struct Cell *p=hash->entry[i];
    if (p==NULL) continue;
    while(p->next!=NULL){
      p=p->next;
      if (release!=NULL)
	release(p->prev->donnee);
      free(p->prev);
    }
  }
  free(hash->entry);
  free(hash);    
}



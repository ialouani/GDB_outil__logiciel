#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>//pour reconnaitre la fonction toupper.(IMPORTANT)

void randstack(int i){
  int j=rand();//random de la biblio mise a jour stdlib.h et rand renvoient
  //tous les deux une valeur aleatoire non comprise forcement dans un intervalle
  //choisi a lavance => ce sont les memes fonctions ; le change de random()
  //en rand() ne change absolument rien au code(meme pour XTREM.c). 
  if (i>0)
    randstack(i-1);
}

char *getStr(int size){
  static char memBuffer[4096];
  static int id=0;
  char *tmp=memBuffer+id;
  id+=size+1;
  //ajouter un +1 pour commencer l'ecriture depuis a+6 au lieu de a+5 car une
  //case a été ajouté pour le charactere d'échappement.
  return tmp;
}


char *toUpper(char *str){
  int i;
  char *buffer=getStr(strlen(str));
  for(i=0;i<strlen(str);++i){
    buffer[i]=toupper(str[i]);
  }
  buffer[i]='\0';//on ajoute un charactere d'echappement permettant
  //de dire que la lecture de buffer par incrementation en printf %s (char*)
  //va se terminer ici pour eviter d'afficher le reste a savoir b(WOLRD!).
  return buffer;  
}

int main(){
  char *a,*b;
  randstack(100);
  a=toUpper("hello");
  b=toUpper("world!");
  printf("%s %s\n",a,b);
  //a va s'afficher suivant le %s en printf (char*!!) tout en s'arretant
  //a l'ETAPE: '\0' qui va determiner la fin de chaine (fin d'incrementation
  //des adresses(correspond a *(a+5) '\000')) puis l'affichage de b commencera
  //a l'adresse suivante puis le reste qui sera pas visible au terminal.
  //(QUE DES ESPACES BLANCS..)
  return EXIT_SUCCESS;
}

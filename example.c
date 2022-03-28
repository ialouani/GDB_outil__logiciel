#include <string.h>
#include <stdio.h>
#include <hash.h>
#include <stdlib.h>

int str_hash(unsigned char *str)
{
  int hash = 5381;
  int c;
  
  while ((c = *str++)!='\0')
    hash = ((hash << 5) + hash) + c; 
  
  return hash;
}


int main(){
  struct hash_Table *hash=hash_init((void *)strcmp,(void *)str_hash);
  printf("add toto %d \n",HashAdd(hash,"toto"));
  printf("abcd => %d\n",hashCherche(hash,"abcd"));
  printf("add titi %d \n",HashAdd(hash,"titi"));
  printf("ajout titi %d \n",HashAdd(hash,"titi"));
  printf("add azerty %d \n",HashAdd(hash,"azerty"));
  printf("add tbtb %d \n",HashAdd(hash,"tbtb"));
  printf("add wxyz %d \n",HashAdd(hash,"wxyz"));
  printf("add wxyz %d \n",HashAdd(hash,"wxyz"));
  printf("toto => %d\n",hashCherche(hash,"toto"));
  printf("titi => %d\n",hashCherche(hash,"titi"));
  printf("tbtb => %d\n",hashCherche(hash,"tbtb"));
  printf("azerty => %d\n",hashCherche(hash,"azerty"));
  printf("wxyz => %d\n",hashCherche(hash,"wxyz"));
  printf("wxyz => %d\n",hashCherche(hash,"wxyz"));
  printf("abcd => %d\n",hashCherche(hash,"abcd"));
  //"abcd" n'est pas dedans mais ca renvoie 0 donc ca existe
  //=>bug dans la fonction hashCherche.
  //a retenir: bug au niveau de la recherche => element test existant
  //avant avec HashAdd ou non existant aleatoirement choisi.
  hash_free(hash,NULL);
  return EXIT_SUCCESS;
}

#include<stdio.h>


int homer(int);
//probleme dans l'appel de bart avec une grande valeur (explosion de la pile
//d'appels recursifs) => entree dans homer tout au long de l'execution d'une
//suite de valeur $1_arg__func-2 n'atteignant jamais 0
//donc il faut rectifier le cas de base dans homer.
//homer renvoie 10-1 qui renvoie (decrementation pas possible de demarrer de 2,n
//>2) homer(7)+1 donc calculer homer(7) puis bart(6) puis homer(4)
//puis bart(3) puis homer(1) puis bart(0) => homer(-2)=>balancement dans
//les calculs d'entrées negatives.
//La solution: stopper les appels recursifs de homer depuis bart en
//faisant une restriction logique(voir CI-DESSUS) du cas de base en:
//if(value==0)=>if(value==1).


int bart(int value){
  if (value==1) return 1;
  return homer(value-2)+1;//value-2 telque sa valeur doit a un instant
  //verifier le cas de base vu que 10 est paire donc value2-2 va atteindre
  //forcement 1 (soustraction de 1:2 en toutes etapes) => eviter la 'boucle
  //recursive (loop) infinie en changeant le cas de base de homer par if(value
  //==1) au lieu de if (value==0).
}

int homer(int value){
  if (value==1) return 1;
  return bart(value-1)+3;
  //le probleme est dans homer donc value-2 n'atteind pas 0 mais vu que
  //homer(10) conduit a l'appel bart(9) qui conduit a l'appel de homer(7)
  //donc les (bart(6) & homer(4) & bart(3) homer(1)) sous-appels en 4 catégories
  //dispatchées en 2 se terminent forcement par un appel de homer suivant 1
  //donc le cas de base serait 1 et non pas 0 sinon ca va appliquer bart(0) qui
  //va renvoyer 1 donc dernier appel a bart et pas dernier appel a homer+erreur.
  //(respect du context).
  //RQ:(!!!!!!!!!!) bart(0) (avant dernier bart c'etait en 3>1) qui va renvoyer
  //homer(-2) avec -2<0 pas de cas de base pour homer verifie apres
  //=>sefgault par tracage depuis l'origine par le post-appel de bart(0) suivant
  //le traceback de homer.
  //ET voilà.////
}


int main(){
  homer(10);
  //l'execution est direct suivant un chiffre paire , normalement
  //gdb dho fournit un segfault sur homer(value-2) exprimant par cela
  //que value-2 > 0 et si il devient <=0 ca sera par egalite strict.
  //=>recurrence de rappels infinie => fuite memoire a un instant.
  //si on reflechit bien homer renvoie une evaluation de bart en decrementant
  //unse seule fois $1 qui a son role renvoie une evaluation de homer par
  //double decrementation (impaire resultat tout a la fin) et c'est homer son
  //appel qui pose probleme donc l'appel de homer doit se terminer pas un cas
  //de base de %2==1 car l'entreee est toujours impair pour eviter un re-appel
  //supplementaire a bart qui conduirait a une valeur =0<1 donc des decrementations lointaines de faire le boulot precedent => fuite memoire.(resolution ci-dessus).
}


#include<stdio.h>
#include<stdlib.h>
/*#include<string.h>//juste pour verification.*/
//comparaison de resultats.

int strcmp_rec(char *s,char *t){
  if ((s[0]=='\0') && (t[0]=='\0'))
    return 0;
  if (s[0]<t[0]) return -1;
  if (s[0]>t[0]) return 1;
  //on peut comparer un '\0' avec un char dont la valeur est differente de '\0'.
  else {
    /*if(strcmp_rec(s+1,t+1)==0)
      return 0;
      return 1;*/
    //ici on a s[0]==t[0]
    return strcmp_rec(s+1,t+1);
  }
}

int main(int argc, char **argv){
  char s[]="abcdfh";
  char t[]="abcdge";
  //printf("%d\n",strcmp(s,t));
  switch(strcmp_rec(s,t)){
    case 0:
      puts("equal");
      break;
    case 1:
      puts("greater");
      break;
    case -1:
      puts("smaller");
      break;
    }
  return EXIT_SUCCESS;
   
}
//plus facile celui-la.

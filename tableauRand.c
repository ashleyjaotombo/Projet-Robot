#include "moves.h"
#include <stdlib.h>
#include "tableauRand.h"
#include "stack.h"

t_stack* tableauRand()
{
  // On affecte un nombre à chaque mouvement selon leurs probabilités
  int F10_count=22;
  int F20_count=15;
  int F30_count=7;
  int B10_count=7;
  int T_LEFT_count=21;
  int T_RIGHT_count=21;
  int T_UP_count=7;

  t_move* tableau=(t_move*)malloc(sizeof(t_move)*100);
  int n=0;
  while (n<100){
    int i=rand()%7; // rand pour que le tableau soit créé de façon aléatoire
    if (i==0 && F10_count>0) // on vérifie s'il reste encore des probabilités pour F10
    {
        tableau[n]=F_10;
        F10_count--;
        n++;
    }
    else if (i==1 && F20_count>0){ // on vérifie s'il reste encore des probabilités pour F20
      tableau[n]=F_20;
      F20_count--;
      n++;
    }
    else if (i==2 && F30_count>0){ // on vérifie s'il reste encore des probabilités pour F30
      tableau[n]=F_30;
      F30_count--;
      n++;
    }
    else if (i==3 && B10_count>0){ // on vérifie s'il reste encore des probabilités pour B10
      tableau[n]=B_10;
      B10_count--;
      n++;
    }
    else if (i==4 && T_LEFT_count>0){ // on vérifie s'il reste encore des probabilités pour T_LEFT
      tableau[n]=T_LEFT;
      T_LEFT_count--;
      n++;
    }
    else if (i==5 && T_RIGHT_count > 0){ // on vérifie s'il reste encore des probabilités pour T_RIGHT
      tableau[n]=T_RIGHT;
      T_RIGHT_count--;
      n++;
    }
    else if (i==6 && T_UP_count > 0){  // on vérifie s'il reste encore des probabilités pour T_UP
      tableau[n]=T_UP;
      T_UP_count--;
      n++;
    }
  }

  t_stack* tableauFinal;
  tableauFinal=create_stack(100); //on crée dynamiquement une pile de 100 éléments
  tableauFinal->values=tableau;  //la pile est constitué du tableau aléatoire
  tableauFinal->nbElts=100;
  return tableauFinal;
}
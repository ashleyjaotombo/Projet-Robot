#include "moves.h"
#include <stdlib.h>
#include "tableauRand.h"
#include "stack.h"

t_move* tableauRand()
{
    t_move* tableau=(t_move*)malloc(sizeof(t_move)*100);
    for (int i=0; i<100; i++){ // On crée un tableau en fonction des probabilités
      if (i<22)
        tableau[i]=F_10;
      else if (i<37)
        tableau[i]=F_20;
      else if (i<44)
        tableau[i]=F_30;
      else if (i<51)
        tableau[i]=B_10;
      else if (i<72)
        tableau[i]=T_LEFT;
      else if (i<93)
        tableau[i]=T_RIGHT;
      else
        tableau[i]=U_TURN;
    }
    t_move* tableauFinal=(t_move*)malloc(sizeof(t_move)*5);  // On crée un tableau de 5 mouvements pour faire la phase
    int indice;
    for (int j=0; j<5; j++){
      indice=rand() % 100;
      tableauFinal[j]=tableau[indice];
    }
    free(tableau); //On libère l'espace de tableau
    return tableauFinal;
}
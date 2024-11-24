//
// Created by Ashley on 18/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "parcoursLargeur.h"
#include "moves.h"

//La fonction qui nous permet de parcourir l'arbre et de récupérer toutes les feuilles + case finale
void parcourirArbre(t_node* node, t_node** tableauFeuilles, int* nbFeuilles) {
    if (node == NULL) {
        return; // Condition d'arrêt
    }

    // Si le nœud n'a pas d'enfants, il s'agit d'une feuille, on l'ajoute au tableau
    if (node->enfants == NULL) {
        tableauFeuilles[*nbFeuilles] = node;
        (*nbFeuilles)++; // On incrémente le compteur de feuilles
        return;
    }

    //Si jamais on tombe sur la Base du Robot, même pendant une phase intermédiaire, on l'ajoute au tableau
    if (node->value == 0) {
      tableauFeuilles[*nbFeuilles] = node;
      (*nbFeuilles)++; // On incrémente le compteur de feuilles
      return;
    }

    // Parcours des enfants
    for (int i = 0; i < node->nb_enfants; i++) {
        parcourirArbre(node->enfants[i], tableauFeuilles, nbFeuilles); // Appel récursif pour chaque enfant
    }
}


//Fonction qui permet d'identifier la feuille la moins coûteuse
t_node* choixFeuille(t_node** tableauFeuilles, int* nbFeuilles) {
    int minimum=tableauFeuilles[0]->value; // On initialise le minimum
    t_node* choix=tableauFeuilles[0];
    for (int i = 1; i < *nbFeuilles; i++) { //Boucle qui cherche le minimum
        if (tableauFeuilles[i]->value < minimum && tableauFeuilles[i]->value >=0) {
            choix=tableauFeuilles[i];
            minimum=tableauFeuilles[i]->value;
        }
    }
    return choix;
}

//Fonction qui permet d'afficher une orientation
void conversionOrientation(t_orientation orientation){
  if (orientation == NORTH)
    printf("NORTH\n");
  else if (orientation == SOUTH)
    printf("SOUTH\n");
  else if (orientation == EAST)
    printf("EAST\n");
  else
    printf("WEST\n");
  return;
}


//Fonction qui permet d'afficher un mouvement
void conversionMouvement(t_move mouvement){
  if (mouvement == F_10)
    printf(" F_10 ");
  else if (mouvement == F_20)
    printf(" F_20 ");
  else if (mouvement == F_30)
    printf(" F_30 ");
  else if (mouvement == B_10)
    printf(" B_10 ");
  else if (mouvement == T_LEFT)
    printf(" T_LEFT ");
  else if (mouvement == T_RIGHT)
    printf(" T_RIGHT ");
  else
    printf(" U_TURN ");
}

void afficherParcours(t_node nodeFinale){
  t_node* parcours=&nodeFinale;
  t_node* temp;
  printf("On est arrivé à la position : (%d,%d) et orienté vers ", parcours->localisation.pos.x, parcours->localisation.pos.y);
  conversionOrientation(parcours->localisation.ori);
  while (parcours->parent != NULL) {
    temp=parcours;
    parcours=parcours->parent;
    printf("On a appliqué le mouvement ");
    conversionMouvement(temp->mouvement);
    printf("depuis La position : (%d,%d) et orienté vers  ", parcours->localisation.pos.x, parcours->localisation.pos.y);
    conversionOrientation(parcours->localisation.ori);

  }
  free(temp);
  free(parcours);
}
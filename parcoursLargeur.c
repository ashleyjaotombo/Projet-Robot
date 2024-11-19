//
// Created by Ashley on 18/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "parcoursLargeur.h"
#include "moves.h"


void parcourirArbre(t_node* node, t_node** tableauFeuilles, int* nbFeuilles) {
    if (node == NULL) {
        return; // Condition d'arrêt
    }

    // Si le nœud n'a pas d'enfants, il s'agit d'une feuille, on l'ajoute au tableau
    if (node->nb_enfants == 0) {
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

t_node* choixFeuille(t_node** tableauFeuilles, int* nbFeuilles) {
    int minimum=tableauFeuilles[0]->value; // On initialise le minimum
    t_node* choix=tableauFeuilles[0];
    for (int i = 1; i < *nbFeuilles; i++) {
        if (tableauFeuilles[i]->value < minimum) {
            choix=tableauFeuilles[i];
            minimum=tableauFeuilles[i]->value;
        }
    }
    return choix;
}


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

void conversionMouvement(t_move mouvement){
  if (mouvement == F_10)
    printf("F_10\n");
  else if (mouvement == F_20)
    printf("F_20\n");
  else if (mouvement == F_30)
    printf("F_30\n");
  else if (mouvement == B_10)
    printf("B_10\n");
  else if (mouvement == T_LEFT)
    printf("T_LEFT\n");
  else if (mouvement == T_RIGHT)
    printf("T_RIGHT\n");
  else
    printf("U_TURN\n");
}

void afficherParcours(t_node nodeFinale){
  t_node* parcours=&nodeFinale;
  t_node* temp;
  printf("On est à la position : %d,%d et 
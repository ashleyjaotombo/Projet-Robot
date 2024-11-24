//
// Created by Ashley on 18/11/2024.
//

#ifndef PARCOURSLARGEUR_H
#define PARCOURSLARGEUR_H

#endif //PARCOURSLARGEUR_H
#include "moves.h"
#include "tree.h"
#include "loc.h"


void parcourirArbre(t_node*, t_node**, int*);
t_node* choixFeuille(t_node**, int*);
void conversionOrientation(t_orientation);
void conversionMouvement(t_move);
void afficherParcours(t_node);
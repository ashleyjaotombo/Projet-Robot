//
// Created by Ashley on 10/11/2024.
//

#ifndef TREE_H
#define TREE_H
#include "map.h"
#include "loc.h"
#include "moves.h"


#endif //TREE_H




typedef struct s_node
{
    int value;
    struct s_node** enfants;
    int nb_enfants;
    struct s_node* parent;
    t_move mouvement;
    int depth;
    t_move* mouvementsRestants;
    t_localisation localisation;
}t_node;

typedef struct s_tree
{
    t_node* root;
}t_tree;

t_tree* creer_tree(int, int, t_move* moves, t_localisation);
// On initialise un arbre avec une racine val et n nombre d'enfants

void completerTreeRec(t_node*, int, t_map);
//on complète l'arbre récursivement en prenant en compte les différents mouvements

void completerParcours(t_tree*, int, t_map);
// fait appel à la fonction récursive
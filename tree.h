//
// Created by Ashley on 10/11/2024.
//

#ifndef TREE_H
#define TREE_H

#endif //TREE_H




typedef struct s_node
{
    int value;
    struct s_node** enfants;
    int nb_enfants;
}t_node;

typedef struct s_tree
{
    t_node* root;
}t_tree;

t_tree* creer_tree(int val,int n);
// On initialise un arbre avec une racine val et n nombre d'enfants

void completerTreeRec(t_node*, t_localisation, int, t_map, int, t_stack*);
//on complète l'arbre récursivement en prenant en compte les différents mouvements

void completerTree(t_tree*, int n, t_map);
// fait appel à la fonction récursive
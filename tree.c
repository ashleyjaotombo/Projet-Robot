#include "tree.h"
#include "tableauRand.h"
#include <stdlib.h>
#include <stdio.h>
#include "loc.h"
#include "moves.h"


t_tree* creer_tree(int val,int n)
{
    t_tree* tree=(t_tree*)malloc(sizeof(t_tree));
    t_node* node=(t_node*)malloc(sizeof(t_node));
    node->value=val;
    node->enfants=(t_node**)malloc(n*sizeof(t_node*));

    // On initialise chaque enfant comme un noeud sans sous-enfant
    for (int i = 0; i < n; i++) {
        node->enfants[i] = (t_node*)malloc(sizeof(t_node));
        node->enfants[i]->value = 0;        // Valeur par défaut
        node->enfants[i]->enfants = NULL;   // Aucun sous-enfant
        node->enfants[i]->nb_enfants = 0;
    }
    node->nb_enfants=n;
    tree->root=node;
    return tree;
}


void completerTreeRec(t_node* node, t_localisation loc, int n, t_map map, int depth, t_stack* tableau) {
    // On va jusqu'à 3 de profondeur car on fait 3 mouvements
    if (depth == 3) {
        return; // la condition d'arrêt de la récursion
    }

    // On complète les enfants par niveau
    for (int i = 0; i < n; i++) {
        t_move mouvement = pop(*tableau); // On récupère un mouvement du tableau aléatoire
        t_localisation nouvelle_loc = move(loc, mouvement); // On calcule la nouvelle localisation après le mouvement

        // Vérification de la validité de la nouvelle position
        if (isValidLocalisation(nouvelle_loc.pos, map.x_max, map.y_max)) {
            node->enfants[i]->value = map.costs[nouvelle_loc.pos.y][nouvelle_loc.pos.x]; // On affecte la valeur à l'enfant
        } else {
            node->enfants[i]->value = 65000; // On affecte une valeur élevée si la position est hors-map
        }

        // On initialise les enfants (qui ne sont pas encore créés) des noeuds
        if (node->enfants[i]->enfants == NULL) {
            node->enfants[i]->enfants = (t_node**)malloc(n * sizeof(t_node*));
            for (int j = 0; j < n; j++) {
                node->enfants[i]->enfants[j] = (t_node*)malloc(sizeof(t_node));
                node->enfants[i]->enfants[j]->value = 0;        // On donne 0 comme valeur par défaut
                node->enfants[i]->enfants[j]->enfants = NULL;   // On ne leur donne aucun enfant
                node->enfants[i]->enfants[j]->nb_enfants = 0;
            }
            node->enfants[i]->nb_enfants = n;
        }

        // Appel récursif pour les sous-enfants
        completerTreeRec(node->enfants[i], nouvelle_loc, n, map, depth + 1, tableau);
    }
}

void completerTree(t_tree* tree, int n, t_map map)
{
    t_localisation loc = loc_init(4, 6, NORTH); // Il s'agit de la position initiale de localisation
    t_stack tableau = tableauRand(); // On crée un tableau de mouvements à utiliser pour tout l'arbre
    completerTreeRec(tree->root, loc, n, map, 0, &tableau);
}


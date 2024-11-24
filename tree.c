#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "loc.h"
#include "moves.h"
#include "map.h"
//Ce code sert à retirer du tableau de mouvement, le mouvement qu'on a utilisé
t_move* nouveauTableau(t_move* moves, int taille, int indice) {
    // On va allouer un tableau pour les mouvements restants
    t_move* nouveauTableau = (t_move*)malloc((taille - 1) * sizeof(t_move));

    int j = 0; // L'indice pour remplir le nouveau tableau
    for (int i = 0; i < taille; i++) {
        if (i != indice) {
            nouveauTableau[j] = moves[i];
            j++;
        }
    }

    return nouveauTableau; // Retourne le nouveau tableau avec les mouvements restants
}


//Ce code sert à initialiser un arbre qu'on complètera par la suite
t_tree* creer_tree(int val, int nbreEnfts, t_move* moves, t_localisation localisation)
{
    t_tree* tree=(t_tree*)malloc(sizeof(t_tree));
    t_node* node=(t_node*)malloc(sizeof(t_node));
    node->value=val;
    node->enfants=(t_node**)malloc(nbreEnfts*sizeof(t_node*));
    node->parent=NULL;
    node->mouvementsRestants=moves;
    node->depth=0;
    node->localisation=localisation;

    // On initialise chaque enfant comme un noeud sans sous-enfant
    for (int i = 0; i < nbreEnfts; i++) {
        node->enfants[i] = (t_node*)malloc(sizeof(t_node));
        node->enfants[i]->value = 0;        // Valeur par défaut
        node->enfants[i]->enfants = NULL;   // Aucun sous-enfant
        node->enfants[i]->nb_enfants =0;
        node->enfants[i]->parent=node;
    }
    node->nb_enfants=nbreEnfts;
    tree->root=node;
    return tree;
}

//Ce code servira à compléter notre arbre
//Dans ces étapes, nous allons considérer chaque contrainte et consignes du sujet
void completerTreeRec(t_node* node, int n, t_map map) {
    if (node->depth == 5) return; // Condition d'arrêt au niveau 5

    t_localisation loc = node->localisation;
    t_move* tableau = node->mouvementsRestants;

    int nombre_enfants = n - node->depth; // On diminue le nombre d'enfants à chaque niveau
    node->enfants = (t_node**)malloc(nombre_enfants * sizeof(t_node*));

    for (int i = 0; i < nombre_enfants; i++) {   //Initialisation de chaque enfant
        // Allocation d'un enfant
        node->enfants[i] = (t_node*)malloc(sizeof(t_node));
        node->enfants[i]->parent = node;
        node->enfants[i]->depth = node->depth + 1;
        node->enfants[i]->nb_enfants = nombre_enfants - 1;


        // Mise à jour de la localisation
        //CONTRAINTE SUR LES SOLS REG
        if (isValidLocalisation(loc.pos, 7, 6))
        {
            if (map.soils[loc.pos.x][loc.pos.y] == 3 && node->depth==0) // Sols REG type : 3
                node->depth = node->depth + 1;  //La condition d'arrêt est accélérée
        }

        t_localisation new_loc = loc;


        // CONTRAINTE SUR LES SOLS ERG
        if (map.soils[loc.pos.x][loc.pos.y] == 2) //Sols REG type : 2
        {
            if (tableau[i]==F_20)
            {
                node->enfants[i]->mouvement = F_10;  //F_20 devient F_10
                updateLocalisation(&new_loc, F_10);
            }
            else if (tableau[i]==F_30)
            {
                node->enfants[i]->mouvement = F_20;
                updateLocalisation(&new_loc, F_20); //F_30 devient F_20
            }
            else if (tableau[i]==U_TURN)
            {
                node->enfants[i]->mouvement = T_LEFT; //U_TURN devient T_LEFT
                updateLocalisation(&new_loc, T_LEFT);
            }
        }
        else //On se trouve sur une case normale
        {
            updateLocalisation(&new_loc, tableau[i]); //On met à jour la localisation normalement
            node->enfants[i]->mouvement = tableau[i];
        }

        // On vérifie si la localisation est dans la map et si oui, on la met à jour
        if (isValidLocalisation(new_loc.pos, 7, 6))
            node->enfants[i]->localisation = new_loc;
        else
        {
            node->enfants[i]->value=65000;
            break; //Sinon on passe au prochain enfant car hors map donc on ne continue pas
        }




        // Mise à jour des coûts
        if (node->value <= 500) { //Si on est pas dans une crevasse ou Hors map
            node->enfants[i]->value = map.costs[new_loc.pos.x][new_loc.pos.y];
        } else {
            //CONTRAINTE CREVASSE ou HORS MAP
            node->enfants[i]->value=65000;
            break; // On passe à l'enfant d'après car le robot est considéré comme perdu
        }

        // Création des mouvements restants
        node->enfants[i]->mouvementsRestants = nouveauTableau(tableau, nombre_enfants, i);

        // On fait la récursion
        completerTreeRec(node->enfants[i], n, map);
    }
}

//La fonction qui fait appel à la récursivité
void completerParcours(t_tree* tree, int n, t_map map)
{
    completerTreeRec(tree->root, n, map);
}


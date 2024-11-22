#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "loc.h"
#include "moves.h"
#include "map.h"

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

    return nouveauTableau; // Retourne le tableau nouvellement créé
}

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
    node->mouvement=B_10;
    tree->root=node;
    return tree;
}


void completerTreeRec(t_node* node, int n, t_map map) {
  t_localisation nouvelle_loc=node->localisation;
  t_localisation loc=node->localisation;
  t_move* tableau=node->mouvementsRestants;

  //CONTRAINTE SUR LES SOLS REG
  if (isValidLocalisation(loc.pos, map.x_max, map.y_max)){
    if (map.soils[loc.pos.x][loc.pos.y] == REG && node->depth==0)
      node->depth=1;
  }

  // On complète les enfants par niveau
  for (int i = 0; i < n; i++) {
      //CONTRAINTE SUR LES SOLS ERG
    if (map.soils[nouvelle_loc.pos.x][nouvelle_loc.pos.y] == ERG) {
        if (tableau[i]==F_20)
          nouvelle_loc = move(loc, F_10);
        if (tableau[i]==F_30)
          nouvelle_loc = move(loc, F_20);
        if (tableau[i]==U_TURN)
          nouvelle_loc = move(loc, T_LEFT);
    }else{
        nouvelle_loc = move(loc, tableau[i]); // On calcule la nouvelle localisation après le mouvement si on est pas dans la case ERG
    }

    node->enfants[i]->mouvementsRestants=nouveauTableau(tableau,n,i);

    // Vérification de la validité de la nouvelle position
  	if (isValidLocalisation(nouvelle_loc.pos, map.x_max, map.y_max) && node->value<=500) {
          node->enfants[i]->value = map.costs[nouvelle_loc.pos.x][nouvelle_loc.pos.y]; // On affecte la valeur à l'enfant
    }
    else
    {
      node->enfants[i]->value = 65000; // On affecte une valeur élevée si la position est hors-map
    }

    node->enfants[i]->parent=node; // On met à jour le parent
    node->enfants[i]->mouvement=tableau[i]; //On stocke le mouvement qu'on a effectué
    node->enfants[i]->depth=node->depth+1; //On incrémente la profondeur
    node->enfants[i]->nb_enfants=node->nb_enfants-1;
    node->enfants[i]->localisation=nouvelle_loc;

	//LA CONTRAINTE CREVASSE
    if (node->value>500)
    	node->enfants[i]->value = 65000; // Si la valeur de la case du parent est de 65000, on garde cette valeur pour tous les futurs enfants

	// On va jusqu'à 3 de profondeur car on fait 3 mouvements
    if (node->enfants[i]->depth == 2) {
        node->enfants[i]->nb_enfants=0;
        return; // la condition d'arrêt de la récursion
    }

    // On initialise les enfants (qui ne sont pas encore créés) des noeuds
    if (node->enfants[i]->enfants == NULL) {
      node->enfants[i]->enfants = (t_node**)malloc((n-1) * sizeof(t_node*));
      for (int j = 0; j < n-1; j++) {
        node->enfants[i]->enfants[j] = (t_node*)malloc(sizeof(t_node));
        node->enfants[i]->enfants[j]->value = 0;        // On donne 0 comme valeur par défaut
        node->enfants[i]->enfants[j]->enfants = NULL;   // On ne leur donne aucun enfant
        node->enfants[i]->enfants[j]->nb_enfants = 0;
        node->enfants[i]->enfants[j]->parent=node->enfants[i];
      }
    }
	// On fait un appel récursif pour les sous-enfants
	completerTreeRec(node->enfants[i], n-1, map);
  }
}

void completerParcours(t_tree* tree, int n, t_map map)
{
    completerTreeRec(tree->root, n, map);
}


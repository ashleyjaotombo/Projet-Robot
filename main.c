#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "loc.h"
#include "moves.h"
#include "stack.h"
#include "tree.h"
#include "tableauRand.h"
#include "parcoursLargeur.h"

int main() {
    t_map map = createMapFromFile("..\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    t_localisation localisation;
    localisation.pos.x=6;
    localisation.pos.y=4;
    localisation.ori=NORTH;
    t_move* tableauRandom = tableauRand();
    t_tree* tree = creer_tree(8, 5, tableauRandom, localisation);

    //On commence le parcours :
    completerParcours(tree, 5, map);
    return 0;

    //On va maintenant parcourir l'arbre pour chercher le chemin le plus court
    int nombreFeuilles = 0;
    t_node** tableauFeuilles = (t_node**)malloc(sizeof(t_node*) * 60);

    // On appelle la fonction pour remplir tableauFeuilles
    parcourirArbre(tree->root, tableauFeuilles, &nombreFeuilles);

    // On choisit la feuille représentant le meilleur chemin
    t_node* arrivee_phase = choixFeuille(tableauFeuilles, &nombreFeuilles);

    // Affichage du parcours
    afficherParcours(arrivee_phase);

    // Libération de la mémoire
    free(tableauFeuilles);  // Libération du tableau des feuilles
    return 0;
}

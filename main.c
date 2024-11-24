#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loc.h"
#include "moves.h"
#include "parcoursLargeur.h"

int main()
{
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("../maps/example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

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

    //Initialisation de la case de départ
    t_localisation localisation;
    localisation.pos.x=6;
    localisation.pos.y=4;
    localisation.ori=NORTH;
    int num_phase = 1;


    while (localisation.pos.x!=1 && localisation.pos.y!=2) // On est arrivé à la base
    {
        printf("PHASE %d:\n", num_phase);
        t_move* tableauRandom = getRandomMoves(9);
        printf("Les mouvements aléatoires sont : ");
        for (int z=0; z<9; z++)
        {
            conversionMouvement(tableauRandom[z]);
        }
        printf("\n");

        t_tree* tree = creer_tree(9, 9, tableauRandom, localisation);

        // Compléter l'arbre en fonction de la carte
        completerParcours(tree, 9, map);

        // On parcourt l'arbre pour remplir le tableau des feuilles
        int nombreFeuilles = 0;
        t_node** tableauFeuilles = (t_node**)malloc(sizeof(t_node*) * 1000);

        // On remplit le tableauFeuilles
        parcourirArbre(tree->root, tableauFeuilles, &nombreFeuilles);

        // Choisir la feuille avec la valeur minimale
        t_node* arrivee_phase = choixFeuille(tableauFeuilles, &nombreFeuilles);
        printf("Le coût de la case au bout de la phase %d est %d. ", num_phase, arrivee_phase->value);
        printf("Cela correspond à la position (%d,%d).\n", arrivee_phase->localisation.pos.x, arrivee_phase->localisation.pos.y);

        // Afficher le parcours
        printf("Historique des mouvements de la phase %d :\n", num_phase);
        afficherParcours(*arrivee_phase);

        // Libérer la mémoire
        free(tableauFeuilles);
        num_phase++;
        localisation=arrivee_phase->localisation;
        printf("\n");
    }
    return 0;
}
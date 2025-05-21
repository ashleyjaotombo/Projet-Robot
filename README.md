# Projet Robot

Ce projet consiste à développer un algorithme en langage C permettant à un rover martien de rejoindre une base située sur une carte, tout en évitant les obstacles du terrain.  
L'algorithme utilise un arbre N-aire pour prendre des décisions en fonction du coût des cases, afin de choisir le chemin le plus sûr (en évitant les cases crevasses) et le plus efficace parmi plusieurs mouvements possibles (pour faire le moins de déplacement).

## Structure du projet

- `main.c` : Point d'entrée du programme.
- `map.c` / `map.h` : Gestion de la carte et des obstacles.
- `loc.c` / `loc.h` : Gestion de la position et des déplacements du rover.
- `moves.c` / `moves.h` : Définition des mouvements possibles du rover.
- `parcoursLargeur.c` / `parcoursLargeur.h` : Implémentation de l'algorithme de parcours en largeur.
- `tree.c` / `tree.h` : Structure de l'arbre N-aire pour la prise de décision.
- `queue.c` / `queue.h` : Implémentation d'une file (queue) pour le parcours en largeur.
- `stack.c` / `stack.h` : Implémentation d'une pile (stack), utilisée si nécessaire.
- `example1.map` à `example4.map`, `training.map` : Exemples de cartes pour tester l'algorithme.
- `CMakeLists.txt` : Fichier de configuration pour la compilation avec CMake.

## Fonctionnalités

- Lecture et interprétation de cartes contenant des obstacles et une base.
- Calcul du chemin optimal pour atteindre la base en évitant les obstacles.
- Utilisation d'un arbre N-aire pour explorer les différentes possibilités de mouvement.
- Implémentation d'un algorithme de parcours en largeur pour la recherche de chemin.
- Affichage du chemin trouvé sur la carte.

# Générateur de labyrinthe en C

Génère un labyrinthe parfait aléatoire et l'affiche en ASCII dans le terminal. Projet de première année à l'ISEN Ouest (cycle CIR).

```
+--+--+--+--+--+
|        |     |
+--+--+  +--+  +
|     |  |     |
+  +--+  +  +--+
|        |     |
+  +--+--+  +  +
|        |  |  |
+--+--+  +--+  +
|              |
+--+--+--+--+--+
```

## Compiler et lancer

```bash
gcc -Wall -o labyrinthe labyrinthe.c
./labyrinthe
```

Chaque exécution produit un labyrinthe différent (graine basée sur l'heure).

## Fonctionnement

- **Grille** : chaque case garde 4 pointeurs vers ses voisines (nord, sud, ouest, est). Un pointeur `NULL` correspond à un mur.
- **Génération par parcours en profondeur (DFS) récursif** : on part de la case (0, 0), on mélange les 4 directions (mélange de Fisher-Yates), puis on avance vers chaque voisine pas encore visitée en ouvrant le mur entre les deux. Comme chaque case n'est visitée qu'une fois, le résultat est un arbre couvrant : il existe exactement un chemin entre deux cases quelconques, donc pas de boucle ni de zone inaccessible.
- **Ouverture du mur dans les deux sens** : l'énumération est ordonnée `NORTH, SOUTH, WEST, EAST`, si bien que `direction ^ 1` donne la direction opposée (0↔1, 2↔3). Ça évite un `switch` pour relier la voisine à la case de départ.
- **Affichage** : deux passes par ligne de cases, une pour les murs horizontaux (`+--+`) et une pour les murs verticaux (`|`).

La taille est fixée à 5×5 dans `main`.

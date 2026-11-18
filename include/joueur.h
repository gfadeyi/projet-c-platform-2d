#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>

typedef struct {
    float x, y;
    float vx, vy;
    int largeur, hauteur;
    int au_sol;
} Joueur;

void joueur_initialiser(Joueur *joueur, float x, float y);

void joueur_lire_clavier(Joueur *joueur, const Uint8 *touches);

void joueur_mettre_a_jour(Joueur *joueur, float dt);

void joueur_dessiner(const Joueur *joueur, SDL_Surface *ecran);

#endif

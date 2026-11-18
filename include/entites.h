#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "joueur.h"

typedef enum {
    ENT_ENNEMI = 0,
    ENT_OBJET  = 1
} TypeEntite;

typedef struct Entity {
    TypeEntite type;

    float x, y;
    float vx, vy;
    int largeur, hauteur;

    int direction;

    int pv;
    int pv_max;
    float invincibilite;

    float patrouille_min_x;
    float patrouille_max_x;

    int actif;           
    struct Entity *next;
} Entity;

Entity *entity_creer(TypeEntite type, float x, float y, int largeur, int hauteur);
void entity_ajouter(Entity **tete, Entity *nouvelle);
void entity_liberer_tout(Entity **tete);

void entity_infliger_degats_joueur(Joueur *joueur, int degats);
void entity_mettre_a_jour(Entity *tete, Joueur *joueur, float dt);

void entity_dessiner_tout(const Entity *tete, SDL_Surface *ecran);

#endif
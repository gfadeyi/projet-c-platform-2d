#include "joueur.h"
#include "config.h"

#define VITESSE_COURSE    300.0f
#define VITESSE_SAUT      700.0f
#define GRAVITE          1800.0f
#define VITESSE_CHUTE_MAX 900.0f

#define LARGEUR_JOUEUR 32
#define HAUTEUR_JOUEUR 48

#define PV_MAX_JOUEUR 5

void joueur_initialiser(Joueur *joueur, float x, float y)
{
    joueur->x = x;
    joueur->y = y;
    joueur->vx = 0.0f;
    joueur->vy = 0.0f;
    joueur->largeur = LARGEUR_JOUEUR;
    joueur->hauteur = HAUTEUR_JOUEUR;
    joueur->au_sol = 0;
    joueur->pv_max = PV_MAX_JOUEUR;
    joueur->pv = PV_MAX_JOUEUR;
    joueur->invincibilite = 0.0f;
}

void joueur_changer_pv(Joueur *joueur, int delta)
{
    joueur->pv += delta;
    if (joueur->pv < 0) {
        joueur->pv = 0;
    }
    if (joueur->pv > joueur->pv_max) {
        joueur->pv = joueur->pv_max;
    }
}

void joueur_lire_clavier(Joueur *joueur, const Uint8 *touches)
{
    joueur->vx = 0.0f;
    if (touches[SDLK_LEFT]) {
        joueur->vx -= VITESSE_COURSE;
    }
    if (touches[SDLK_RIGHT]) {
        joueur->vx += VITESSE_COURSE;
    }

    if ((touches[SDLK_SPACE] || touches[SDLK_UP]) && joueur->au_sol) {
        joueur->vy = -VITESSE_SAUT;
        joueur->au_sol = 0;
    }
}

void joueur_mettre_a_jour(Joueur *joueur, float dt)
{
    joueur->vy += GRAVITE * dt;
    if (joueur->vy > VITESSE_CHUTE_MAX) {
        joueur->vy = VITESSE_CHUTE_MAX;
    }

    joueur->x += joueur->vx * dt;
    joueur->y += joueur->vy * dt;

    if (joueur->y + joueur->hauteur >= SOL_Y) {
        joueur->y = (float)(SOL_Y - joueur->hauteur);
        joueur->vy = 0.0f;
        joueur->au_sol = 1;
    } else {
        joueur->au_sol = 0;
    }

    if (joueur->x < 0.0f) {
        joueur->x = 0.0f;
    }
    if (joueur->x + joueur->largeur > LARGEUR_FENETRE) {
        joueur->x = (float)(LARGEUR_FENETRE - joueur->largeur);
    }
}

void joueur_dessiner(const Joueur *joueur, SDL_Surface *ecran)
{
    SDL_Rect rectangle;

    rectangle.x = (Sint16)joueur->x;
    rectangle.y = (Sint16)joueur->y;
    rectangle.w = (Uint16)joueur->largeur;
    rectangle.h = (Uint16)joueur->hauteur;

    SDL_FillRect(ecran, &rectangle, SDL_MapRGB(ecran->format, 255, 255, 255));
}

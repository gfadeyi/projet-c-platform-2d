#include "hud.h"

#define BARRE_VIE_X 20
#define BARRE_VIE_Y 20

#define BARRE_VIE_LARGEUR 200
#define BARRE_VIE_HAUTEUR 20
#define BORDURE 2

void hud_dessiner_barre_vie(SDL_Surface *ecran, int pv, int pv_max)
{
    SDL_Rect cadre;
    SDL_Rect fond;
    SDL_Rect barre_remplissage;
    Uint32 couleur;
    int largeur_pleine;

    if (pv_max <= 0) {
        return;
    }

    if (pv < 0) {
        pv = 0;
    }
    if (pv > pv_max) {
        pv = pv_max;
    }

    largeur_pleine = BARRE_VIE_LARGEUR * pv / pv_max;

    cadre.x = BARRE_VIE_X - BORDURE;
    cadre.y = BARRE_VIE_Y - BORDURE;
    cadre.w = BARRE_VIE_LARGEUR + 2 * BORDURE;
    cadre.h = BARRE_VIE_HAUTEUR + 2 * BORDURE;

    fond.x = BARRE_VIE_X;
    fond.y = BARRE_VIE_Y;
    fond.w = BARRE_VIE_LARGEUR;
    fond.h = BARRE_VIE_HAUTEUR;

    barre_remplissage.x = BARRE_VIE_X;
    barre_remplissage.y = BARRE_VIE_Y;
    barre_remplissage.w = (Uint16)largeur_pleine;
    barre_remplissage.h = BARRE_VIE_HAUTEUR;

    if (pv * 2 > pv_max) {
        couleur = SDL_MapRGB(ecran->format, 40, 200, 60);
    } else if (pv * 4 > pv_max) {
        couleur = SDL_MapRGB(ecran->format, 240, 150, 0);
    } else {
        couleur = SDL_MapRGB(ecran->format, 220, 30, 30);
    }

    SDL_FillRect(ecran, &cadre, SDL_MapRGB(ecran->format, 20, 20, 20));
    SDL_FillRect(ecran, &fond, SDL_MapRGB(ecran->format, 90, 0, 0));
    if (largeur_pleine > 0) {
        SDL_FillRect(ecran, &barre_remplissage, couleur);
    }
}

#include "entites.h"
#include <stdlib.h>

#define VITESSE_PATROUILLE 90.0f
#define DUREE_INVINCIBILITE 1.0f

Entity *entity_creer(TypeEntite type, float x, float y, int largeur, int hauteur)
{
    Entity *e = (Entity *)malloc(sizeof(Entity));
    if (e == NULL) {
        return NULL;
    }
    e->type = type;
    e->x = x;
    e->y = y;
    e->vx = (type == ENT_ENNEMI) ? VITESSE_PATROUILLE : 0.0f;
    e->vy = 0.0f;
    e->largeur = largeur;
    e->hauteur = hauteur;
    e->direction = 1;
    e->pv_max = (type == ENT_ENNEMI) ? 2 : 1;
    e->pv = e->pv_max;
    e->invincibilite = 0.0f;
    e->patrouille_min_x = x - 100.0f;
    e->patrouille_max_x = x + 100.0f;
    e->actif = 1;
    e->next = NULL;
    return e;
}

void entity_ajouter(Entity **tete, Entity *nouvelle)
{
    if (tete == NULL || nouvelle == NULL) {
        return;
    }
    nouvelle->next = *tete;
    *tete = nouvelle;
}
void entity_liberer_tout(Entity **tete)
{
    Entity *courant;
    Entity *suivant;
    if (tete == NULL) {
        return;
    }
    courant = *tete;
    while (courant != NULL) {
        suivant = courant->next;
        free(courant);
        courant = suivant;
    }
    *tete = NULL;
}

static int collision_avec_joueur(const Entity *e, const Joueur *j)
{
    if (e == NULL || j == NULL || !e->actif) {
        return 0;
    }
    return (e->x < j->x + j->largeur &&
            e->x + e->largeur > j->x &&
            e->y < j->y + j->hauteur &&
            e->y + e->hauteur > j->y);
}
void entity_infliger_degats_joueur(Joueur *joueur, int degats)
{
    if (joueur == NULL || joueur->invincibilite > 0.0f) {
        return;
    }
    joueur->pv -= degats;
    if (joueur->pv < 0) {
        joueur->pv = 0;
    }
    joueur->invincibilite = DUREE_INVINCIBILITE;
}

void entity_mettre_a_jour(Entity *tete, Joueur *joueur, float dt)
{
    Entity *e = tete;

    if (joueur != NULL && joueur->invincibilite > 0.0f) {
        joueur->invincibilite -= dt;
        if (joueur->invincibilite < 0.0f) {
            joueur->invincibilite = 0.0f;
        }
    }
    while (e != NULL) {
        if (e->actif) {
            if (e->type == ENT_ENNEMI) {
                e->x += e->vx * dt;
                if (e->x <= e->patrouille_min_x) {
                    e->x = e->patrouille_min_x;
                    e->vx = VITESSE_PATROUILLE;
                    e->direction = 1;
                } else if (e->x >= e->patrouille_max_x) {
                    e->x = e->patrouille_max_x;
                    e->vx = -VITESSE_PATROUILLE;
                    e->direction = -1;
                }
                if (collision_avec_joueur(e, joueur)) {
                    entity_infliger_degats_joueur(joueur, 1);
                }
            } else if (e->type == ENT_OBJET) {
                if (collision_avec_joueur(e, joueur)) {
                    e->actif = 0;
                }
            }
        }
        e = e->next;
    }
}

void entity_dessiner_tout(const Entity *tete, SDL_Surface *ecran)
{
    const Entity *e = tete;
    while (e != NULL) {
        if (e->actif) {
            SDL_Rect rect;
            Uint32 couleur;

            rect.x = (Sint16)e->x;
            rect.y = (Sint16)e->y;
            rect.w = (Uint16)e->largeur;
            rect.h = (Uint16)e->hauteur;
            if (e->type == ENT_ENNEMI) {
                couleur = SDL_MapRGB(ecran->format, 230, 60, 60); /* Rouge */
            } else {
                couleur = SDL_MapRGB(ecran->format, 255, 215, 0); /* Jaune */
            }

            SDL_FillRect(ecran, &rect, couleur);
        }
        e = e->next;
    }
}
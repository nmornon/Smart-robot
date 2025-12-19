/**
 * @file direction.c
 * @brief Fonctions utilitaires pour la gestion des directions.
 */

#include "direction.h"

/**
 * @brief Calcule la direction opposée à celle fournie.
 * * @param dir La direction d'origine (NORD, SUD, EST, OUEST).
 * @return La direction inverse, ou PAS_DE_DIRECTION si l'entrée est invalide.
 */
Direction directionOpposee(Direction dir) {
    switch(dir) {
        case NORD: return SUD;
        case SUD:  return NORD;
        case EST:  return OUEST;
        case OUEST: return EST;
        default:   return PAS_DE_DIRECTION; 
    }
}

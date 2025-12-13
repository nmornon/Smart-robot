/**
 * \file direction.h
 * \brief Gestion des points cardinaux et de l'orientation.
 * \author Groupe 2-6
 * \date 07/12/2025
 *
 * Ce fichier définit les 4 directions cardinales et fournit des outils
 * pour les manipuler (notamment pour trouver l'opposé).
 */

#ifndef __DIRECTION__
#define __DIRECTION__

/**
 * \enum Direction
 * \brief Les points cardinaux.
*/
typedef enum {
    NORD = 0,   /**< Orientation vers le Nord (Haut de la grille) */
    EST = 1,    /**< Orientation vers l'Est (Droite de la grille) */
    SUD = 2,    /**< Orientation vers le Sud (Bas de la grille) */
    OUEST = 3   /**< Orientation vers l'Ouest (Gauche de la grille) */
} Direction;

#define PAS_DE_DIRECTION -1 // En cas d'erreur 

/**
 * \brief Calcule la direction opposée à une direction donnée.
 *
 * Fonction  permettant de connaître le "dos" du robot
 * ou la provenance d'un mouvement.
 *
 * \param dir La direction d'origine.
 * \return La direction opposée (ex: NORD renvoie SUD).
 */
Direction directionOpposee(Direction dir);

#endif

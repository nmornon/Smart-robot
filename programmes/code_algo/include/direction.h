/**
 * \file direction.h
 * \brief Gestion des points cardinaux pour le robot.
 * \author Groupe 2-6
 * \date 07/12/2025
 *
 * Ce fichier définit comment le robot se repère sur la grille (Haut, Bas, Gauche, Droite)
 * et permet de calculer facilement un demi-tour.
 */

#ifndef __DIRECTION__
#define __DIRECTION__

/**
 * \enum Direction
 * \brief Les 4 orientations possibles.
 */
typedef enum {
    NORD = 0,   /**< Vers le haut */
    EST = 1,    /**< Vers la droite */
    SUD = 2,    /**< Vers le bas */
    OUEST = 3   /**< Vers la gauche */
} Direction;

/** \brief Valeur de secours si aucune direction n'est définie. */
#define PAS_DE_DIRECTION -1 

/**
 * \brief Donne la direction opposée (ex: NORD devient SUD).
 * * Très utile pour connaître la provenance d'un mouvement ou
 * pour faire faire demi-tour au robot.
 *
 * \param dir La direction actuelle.
 * \return La direction inverse.
 */
Direction directionOpposee(Direction dir);

#endif

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
    NORD = 0, 
    EST = 1,   
    SUD = 2,   
    OUEST = 3  
} Direction;

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
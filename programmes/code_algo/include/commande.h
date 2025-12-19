/**
 * \file commande.h
 * \brief Définition des commandes de déplacement du robot.
 * \author Groupe 2-6
 * \date 07/12/2025
 *
 * Ce fichier définit l'énumération utilisée pour représenter les actions
 * atomiques que le robot peut effectuer (Avancer ou Tourner).
 */

#ifndef __COMMANDE__
#define __COMMANDE__

/**
 * \enum COM_Commande
 * \brief Liste des actions possibles pour le robot.
 */
typedef enum {
    AV,  /*!< Avancer d'une case dans la direction actuelle */
    TD,  /*!< Tourner à Droite  */
    TG   /*!< Tourner à Gauche  */
} COM_Commande;

#endif
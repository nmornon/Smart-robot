/**
 * \file IHM.h
 * \brief Gestion des interactions (fichiers et affichage console).
 * \author Groupe 2-6
 * \date 10/12/2025
 */

#ifndef __IHM__
#define __IHM__

#include "ville.h"
#include "chemin.h"

/**
 * \brief Crée une ville à partir d'un fichier texte.
 * \param nom_fichier Chemin vers le fichier de description (.txt).
 * \return Pointeur vers la ville créée, ou NULL si le fichier est invalide.
 */
V_Ville* IHM_chargerVilleDepuisFichier(const char *nom_fichier);

/**
 * \brief Affiche la carte de la ville dans la console.
 * \param v Pointeur vers la ville à visualiser.
 */
void IHM_afficher_ville(V_Ville *v);

/**
 * \brief Affiche le chemin final et sa distance totale.
 * \param chemin Le chemin calculé à afficher.
 */
void IHM_afficherChemin(Ch_Chemin *chemin);

/**
 * \brief Traduit un chemin en instructions concrètes (ordres de mouvement).
 * \param chemin Le chemin à convertir.
 */
void IHM_genererOrdres(Ch_Chemin *chemin);

#endif

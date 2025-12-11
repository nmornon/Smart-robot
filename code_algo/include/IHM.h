/**
 * \file IHM.h
 * \brief Fonctions d'Interface Homme-Machine (ici, lecture/écriture de fichiers).
 * \author Groupe 2-6
 * \date 10/12/2025
 */

#ifndef __IHM__
#define __IHM__

#include "ville.h"

/**
 * \brief Charge une ville à partir d'un fichier texte de description.
 *
 * Cette fonction lit le flux texte pour :
 * 1. Créer la structure V_Ville (largeur).
 * 2. Fixer la position de départ du robot.
 * 3. Ajouter les passages (connexions) entre les cases.
 * 4. Marquer les cases obligatoires.
 *
 * \param nom_fichier Le chemin du fichier décrivant la ville (ex: "ville_test.txt").
 * \return Un pointeur vers la ville créée (V_Ville*), ou NULL en cas d'erreur.
 */
V_Ville* IHM_chargerVilleDepuisFichier(const char *nom_fichier);

#endif

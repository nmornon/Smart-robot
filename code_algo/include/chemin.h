/**
 * \file chemin.h
 * \brief Gestion de la strucutre de données représentante le plus court chemin du robot.
 * \author Groupe 2-6
 * \date 13/12/2025
 *
 * Ce .h définit la structure d'un chemin qui sera la structure qui permet de représenter
 * de manière cohérente le chemin le plus court que le robot va parcourir
 */

#ifndef __CHEMIN__
#define __CHEMIN__

#include <stdbool.h>
#include "ville.h" 
#include "direction.h"

/**
 * \struct Ch_Chemin
 * \brief Structure représentant un chemin (suite de cases).
 */
typedef struct{
    unsigned int nb_cases;           /*!< Nombre de déplacements (longueur du chemin) */
    C_Case* tab_cases;               /*!< Tableau des cases visitées dans l'ordre */
    unsigned int num_case_depart;    /*!< Numéro de la case où le robot commence */
    Direction dir_depart;            /*!< Direction initiale du robot au départ */
} Ch_Chemin;

/**
 * \brief Alloue et initialise un chemin vide.
 * \return Un pointeur vers la structure Ch_Chemin initialisée.
 */
Ch_Chemin* Ch_creerChemin();

/**
 * \brief Libère la mémoire associée à un chemin.
 * \param c Le chemin à libérer.
 */
void Ch_liberer(Ch_Chemin *c);

/**
 * \brief Génère un chemin valide en utilisant un algorithme de force brute.
 * \param v La ville à parcourir.
 * \return Le chemin trouvé (peut être vide si aucune solution).
 */
Ch_Chemin* Ch_genererCheminBrute(V_Ville *v);

/**
 * \brief Récupère le nombre de cases (étapes) dans le chemin.
 * \param c Le chemin.
 * \return Le nombre de cases.
 */
int Ch_nbrCases(Ch_Chemin *c);

/**
 * \brief Récupère la direction initiale du robot au début du chemin.
 * \param c Le chemin.
 * \return La direction (NORD, EST, SUD, OUEST).
 */
Direction Ch_obtenirDirDepart(Ch_Chemin *c);

/**
 * \brief Récupère une case spécifique du chemin à un index donné.
 * \param c Le chemin.
 * \param index L'index de la case dans le tableau (0 à nb_cases).
 * \return Un pointeur vers la case ou NULL si l'index est hors limites.
 */
C_Case* Ch_obtenirCaseAuChemin(Ch_Chemin *c, unsigned int index);

#endif
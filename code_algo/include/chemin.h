/**
 * \file chemin.h
 * \brief Gestion de la strucutre de donnÃ©es reprÃ©sentante le plus court chemin du robot.
 * \author Groupe 2-6
 * \date 13/12/2025
 *
 * Ce .h défini la structure d'un chemin qui sera la structure qui permet de reprÃ©senter
 * de maniÃ¨re cohÃ©rente le chemin le plus court que le robot va parcourir
 */

#ifndef __CHEMIN__
#define __CHEMIN__

#include <stdbool.h>
#include "ville.h" 
#include "direction.h"

#define TAILLE_MAX_CHEMIN 100
#define MAX_OBJECTIFS 10

typedef struct {
    int distance;
    unsigned int *predecesseurs; 
} ResultatBFS;


/**
 * \struct Ch_Chemin
 * \brief Structure représentant un chemin (suite de cases).
 */
typedef struct{
    unsigned int nb_cases;           /*!< Nombre de dÃ©placements (longueur du chemin) */
    C_Case* tab_cases;               /*!< Tableau des cases visitÃ©es dans l'ordre */
    unsigned int num_case_depart;    /*!< NumÃ©ro de la case oÃ¹ le robot commence */
    Direction dir_depart;            /*!< Direction initiale du robot au dÃ©part */
} Ch_Chemin;

/**
 * \brief Alloue et initialise un chemin vide.
 * \return Un pointeur vers la structure Ch_Chemin initialisÃ©e.
 */
Ch_Chemin* Ch_creerChemin();

/**
 * \brief LibÃ¨re la mémoire associée à un chemin.
 * \param c Le chemin Ã  libérer.
 */
void Ch_liberer(Ch_Chemin *c);

/**
 * \brief Génère le chemin le plus court visitant tous les points obligatoires 
 * et revenant au départ, en utilisant une approche optimisÃ©e (BFS + TSP sur objectifs).
 * \param v La ville Ã  parcourir.
 * \return Le chemin trouvé (peut ếtre vide si aucune solution).
 */
Ch_Chemin* Ch_genererCheminOptimal(V_Ville *v);

/**
 * \brief Récupère le nombre de cases (Etapes) dans le chemin.
 * \param c Le chemin.
 * \return Le nombre de cases.
 */
int Ch_nbrCases(Ch_Chemin *c);

/**
 * \brief Récupère la direction initiale du robot au dÃ©but du chemin.
 * \param c Le chemin.
 * \return La direction (NORD, EST, SUD, OUEST).
 */
Direction Ch_obtenirDirDepart(Ch_Chemin *c);

/**
 * \brief Récupère une case spécifique du chemin à un index donné.
 * \param c Le chemin.
 * \param index L'index de la case dans le tableau (0 Ã  nb_cases).
 * \return Un pointeur vers la case ou NULL si l'index est hors limites.
 */
C_Case* Ch_obtenirCaseAuChemin(Ch_Chemin *c, unsigned int index);

#endif

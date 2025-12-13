/**
 * \file case.h
 * \brief Gestion des cases individuelles (sommets du graphe).
 * \author Groupe 2-6
 * \date 07/12/2025
 *
 * Ce .h définit la structure d'une case, qui est l'élément atomique
 * de la ville. Une case connait ses voisins (adjacences) et ses propriétés
 * (si elle est une étape obligatoire ou non).
 */

#ifndef __CASE__
#define __CASE__

#include <stdio.h>
#include <stdbool.h>
#include "direction.h"

/**
 * \struct C_Case
 * \brief Représente une case de la ville.
 */
typedef struct {
    unsigned int numero_case;        /*!< Identifiant unique de la case (de 1 à largeur au carré) */
    bool est_obligatoire;            /*!< Indique si le robot doit obligatoirement passer par ici */
    unsigned int cases_adjacents[4]; /*!< Tableau stockant les ID des voisins (indexé par Direction) */
} C_Case;

/**
 * \brief Crée et initialise une case.
 *
 * \param num Le numéro unique de la case.
 * \param obligatoire true si la case est un point de passage, false sinon.
 * \return Une structure C_Case initialisée avec des voisins vides.
 */
C_Case C_creerCase(unsigned int num, bool obligatoire);

/**
 * \brief Récupère l'identifiant d'une case.
 * \param c La case concernée.
 * \return Le numéro de la case.
 */
unsigned int C_obtenirNumeroCase(C_Case c);

/**
 * \brief Vérifie si une case est un point de passage obligatoire.
 * \param c La case concernée.
 * \return true si obligatoire, false sinon.
 */
bool C_estObligatoire(C_Case c); 

/**
 * \brief Récupère l'identifiant du voisin dans une direction donnée.
 *
 * \param c La case actuelle.
 * \param dir La direction dans laquelle regarder (NORD, EST, SUD, OUEST).
 * \return Le numéro de la case voisine, ou une valeur sentinelle (ex: 0) s'il n'y a pas de voisin (mur).
 */
unsigned int C_obtenirVoisin(C_Case c, Direction dir);

/**
 * \brief Modifie le statut "obligatoire" d'une case.
 *
 * \param c Pointeur vers la case à modifier.
 * \param est_obligatoire Le nouveau statut (true/false).
 */
void C_fixerObligatoire(C_Case *c, bool est_obligatoire);

/**
 * \brief Définit une connexion (un passage) vers une case voisine.
 *
 * \param c Pointeur vers la case à modifier.
 * \param dir La direction de la connexion.
 * \param num_case_adj Le numéro de la case voisine.
 */
void C_fixerCaseAdj(C_Case *c, Direction dir, unsigned int num_case_adj);

#endif
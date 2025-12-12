/**
 * \file ville.h
 * \brief Gestion de la ville (le graphe complet).
 * \author Groupe 2-6
 * \date 07/12/2025
 *
 * Ce module gère la structure globale de la ville, qui contient l'ensemble
 * des cases. Il fait le lien entre la grille (largeur) et le graphe (connexions).
 * Il stocke également les informations de départ du robot.
 */

#ifndef __VILLE__
#define __VILLE__

#include <stdbool.h>
#include "case.h"
#include "direction.h"

/**
 * \struct V_Ville
 * \brief Structure représentant la ville entière.
 */
typedef struct {
    unsigned int largeur;            /*!< Largeur de la ville (nombre de colonnes) */
    unsigned int nb_cases;           /*!< Nombre total de cases (largeur * largeur) */
    C_Case* tab_cases;              /*!< Tableau dynamique contenant toutes les cases */
    unsigned int num_case_depart;    /*!< Numéro de la case où le robot commence */
    Direction dir_depart;            /*!< Direction initiale du robot au départ */
} V_Ville;

/**
 * \brief Alloue la mémoire pour une nouvelle ville vide.
 *
 * Cette fonction prépare le terrain (allocation du tableau de cases)
 * mais ne crée pas encore les murs (connexions).
 *
 * \param largeur La largeur de la ville (la ville sera carrée de taille largeur*largeur).
 * \return Un pointeur vers la ville créée, ou NULL en cas d'erreur d'allocation.
 */
V_Ville* V_creerVille(unsigned int largeur);

/**
 * \brief Libère toute la mémoire associée à la ville.
 *
 * Libère le tableau de cases puis la structure de la ville elle-même.
 * \param ville Pointeur vers la ville à détruire.
 */
void V_liberer(V_Ville *ville);

/**
 * \brief Accède à une case spécifique de la ville via son ID.
 *
 * \param ville Pointeur vers la ville.
 * \param numero_case L'identifiant unique de la case (commence à 1).
 * \return Un pointeur vers la case demandée, ou NULL si l'ID est invalide.
 */
C_Case* V_obtenirCase(V_Ville *ville, unsigned int numero_case);

C_Case* V_obtenirToutesLesCases(V_Ville *ville);

/**
 * \brief Configure la position et l'orientation de départ du robot.
 *
 * \param ville Pointeur vers la ville.
 * \param numero_case L'ID de la case de départ.
 * \param dir La direction initiale.
 */
void V_fixerDepart(V_Ville *ville, unsigned int numero_case, Direction dir);

/**
 * \brief Récupère la largeur de la ville.
 * \param ville Pointeur vers la ville.
 * \return La largeur (nombre de colonnes).
 */
 
 /**
 * \brief Récupère le nombre total de cases dans la ville.
 * \param ville Pointeur vers la ville.
 * \return Le nombre total de cases (largeur * largeur).
 */
unsigned int V_obtenirNbCases(V_Ville *ville);

/**
 * \brief Récupère le numéro de la case de départ du robot.
 * \param ville Pointeur vers la ville.
 * \return Le numéro de la case de départ.
 */
unsigned int V_obtenirNumCaseDepart(V_Ville *ville);

/**
 * \brief Récupère la direction de départ initiale du robot.
 * \param ville Pointeur vers la ville.
 * \return La direction de départ.
 */
Direction V_obtenirDirDepart(V_Ville *ville);

unsigned int V_obtenirLargeur(V_Ville *ville);

/**
 * \brief Charge une ville à partir d'un fichier texte de description.
 *
 * \param nom_fichier Le chemin du fichier décrivant la ville.
 * \return Un pointeur vers la ville créée (V_Ville*)
 */
V_Ville* V_chargerVilleDepuisFichier(const char *nom_fichier);

/**
 * \brief permet de donner le nombre de cases obligatoires dans la ville
 *
 * \param ville Le chemin du fichier décrivant la ville.
 * \return Un pointeur vers la ville créée (V_Ville*)
 */
int V_nbCasesObligatoire(V_Ville* ville);

#endif

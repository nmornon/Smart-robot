/**
 * @file ville.c
 * @brief Gestion de la structure de la ville, de sa création à sa libération.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ville.h"
#include "case.h"

/**
 * @brief Initialise une nouvelle ville carrée.
 * @param largeur Nombre de cases de côté.
 * @return Un pointeur vers la ville créée (mémoire allouée dynamiquement).
 */
V_Ville* V_creerVille(unsigned int largeur) {
    V_Ville *v = (V_Ville*)malloc(sizeof(V_Ville));
    v->largeur = largeur;
    v->nb_cases = largeur * largeur;
    
    v->num_case_depart = 1; 
    v->dir_depart = NORD;

    v->tab_cases = (C_Case*)malloc(v->nb_cases * sizeof(C_Case));
    for (unsigned int i = 0; i < v->nb_cases; i++) {
        // false = non obligatoire par défaut
        v->tab_cases[i] = C_creerCase(i + 1, false);
    }
    return v;
}

/**
 * @brief Libère la mémoire de la ville et de toutes ses cases.
 * @param ville Pointeur vers la ville à détruire.
 */
void V_liberer(V_Ville *ville) {
    if (ville != NULL) {
        if (ville->tab_cases != NULL) {
            free(ville->tab_cases);
            ville->tab_cases = NULL;
        }
        free(ville);
    }
}

/**
 * @brief Récupère un pointeur vers une case spécifique à partir de son numéro.
 * @param numero_case L'identifiant de la case (commence à 1).
 */
C_Case* V_obtenirCase(V_Ville *ville, unsigned int numero_case) {
    // Conversion ID (1..N) vers Index tableau (0..N-1)
    return &(ville->tab_cases[numero_case - 1]);
}

/**
 * @brief Retourne le tableau complet des cases de la ville.
 */
C_Case* V_obtenirToutesLesCases(V_Ville *ville) {
    return ville->tab_cases;
}

/**
 * @brief Définit le point de départ et l'orientation initiale.
 */
void V_fixerDepart(V_Ville *ville, unsigned int numero_case, Direction dir) {
    ville->num_case_depart = numero_case;
    ville->dir_depart = dir;
}

/**
 * @brief Retourne la largeur de la ville.
 */
unsigned int V_obtenirLargeur(V_Ville *ville) {
    return ville->largeur;
}

/**
 * @brief Retourne le numéro de la case où commence le trajet.
 */
unsigned int V_obtenirNumCaseDepart(V_Ville *ville) {
    return ville->num_case_depart;
}

/**
 * @brief Retourne le nombre total de cases (largeur * largeur).
 */
unsigned int V_obtenirNbCases(V_Ville *ville) {
    return ville->nb_cases;
}

/**
 * @brief Retourne la direction initiale au départ.
 */
Direction V_obtenirDirDepart(V_Ville *ville) {
    return ville->dir_depart;
}

/**
 * @brief Compte combien de cases sont marquées comme "obligatoires" dans la ville.
 * @return Le nombre de cases à visiter impérativement.
 */
int V_nbCasesObligatoire(V_Ville* ville) {
    int compteur = 0;

    for (unsigned int i = 0; i < ville->nb_cases; i++) {
        if (C_estObligatoire(ville->tab_cases[i])) {
            compteur++;
        }
    }
    return compteur;
}

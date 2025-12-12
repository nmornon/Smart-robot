#ifndef __CHEMIN__
#define __CHEMIN__

#include <stdbool.h>
#include "ville.h" 

typedef struct{
    unsigned int nb_cases;
    C_Case* tab_cases;
    unsigned int num_case_depart;    /*!< Numéro de la case où le robot commence */
    Direction dir_depart;            /*!< Direction initiale du robot au départ */
} Ch_Chemin ;

Ch_Chemin* Ch_genererCheminBrute(V_Ville *v);

int Ch_nbrCases(Ch_Chemin *c);

Ch_Chemin* Ch_genererCheminBrute(V_Ville *v);

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

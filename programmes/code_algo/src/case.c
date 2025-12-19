/**
 * @file case.c
 * @brief Gestion des cases de la ville.
 * * Ce module définit les fonctions permettant de manipuler une case : 
 * son numéro, son caractère obligatoire ou non, et ses voisins directs.
 * * @author Groupe 2-6
 * @date 10/12/2025
 */

#include "case.h"

/**
 * @brief Initialise une nouvelle case avec un numéro et son statut.
 * @param num Le numéro unique de la case.
 * @param obligatoire Vrai si le robot doit absolument passer par ici.
 * @return Une structure C_Case prête à l'emploi.
 */
C_Case C_creerCase(unsigned int num, bool obligatoire) {
    C_Case c;
    c.numero_case = num;
    c.est_obligatoire = obligatoire; 
    
    // Initialisation propre des voisins à 0 (aucune connexion par défaut)
    for (int i = 0; i < 4; i++) {
        c.cases_adjacents[i] = 0;
    }
    return c;
}

/**
 * @brief Retourne le numéro d'identification de la case.
 */
unsigned int C_obtenirNumeroCase(C_Case c) {
    return c.numero_case;
}

/**
 * @brief Indique si la case est un point de passage obligatoire.
 */
bool C_estObligatoire(C_Case c) {
    return c.est_obligatoire;
}

/**
 * @brief Modifie le statut obligatoire d'une case.
 */
void C_fixerObligatoire(C_Case *c, bool est_obligatoire) {
        c->est_obligatoire = est_obligatoire;
}

/**
 * @brief Récupère le numéro du voisin dans une direction donnée.
 * @return Le numéro de la case voisine, ou 0 s'il n'y a pas de route.
 */
unsigned int C_obtenirVoisin(C_Case c, Direction dir) {
    return c.cases_adjacents[(int)dir];
}

/**
 * @brief Définit ou modifie le voisin d'une case dans une direction précise.
 * @param c Pointeur vers la case à modifier.
 * @param dir Direction du voisin (NORD, EST, SUD, OUEST).
 * @param num_case_adj Numéro de la case voisine à l'autre bout.
 */
void C_fixerCaseAdj(C_Case *c, Direction dir, unsigned int num_case_adj) {
        c->cases_adjacents[(int)dir] = num_case_adj;
}

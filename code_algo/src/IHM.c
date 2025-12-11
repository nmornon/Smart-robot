/**
 * \file IHM.c
 * \brief Implémentation de la fonction de conversion du fichier texte en structure V_Ville.
 * \author Groupe 2-6
 * \date 10/12/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IHM.h"
#include "ville.h"
#include "case.h"
#include "direction.h" // Assure que Direction est connu

#define MAX_LIGNE 256

// -----------------------------------------------------------------------------
// Fonctions utilitaires privées (statiques)
// -----------------------------------------------------------------------------

/**
 * \brief Convertit un caractère (N, E, S, O) en une valeur Direction.
 */
static Direction charToDirection(char c) {
    switch (c) {
        case 'N': return NORD;
        case 'E': return EST;
        case 'S': return SUD;
        case 'O': return OUEST;
        default: 
            fprintf(stderr, "Erreur: Direction inconnue '%c'.\n", c);
            return NORD; // Retour par défaut
    }
}

/**
 * \brief Détermine la direction orthogonale (N, E, S, O) d'une case adjacente.
 *
 * Nécessite la largeur de la grille pour calculer les voisins Nord/Sud.
 *
 * \param case_dep Numéro de la case de départ.
 * \param case_adj Numéro de la case d'arrivée.
 * \param largeur Largeur de la grille.
 * \return La Direction vers case_adj, ou (Direction)-1 si non adjacente.
 */
static Direction determinerDirection(unsigned int case_dep, unsigned int case_adj, unsigned int largeur) {
    if (case_adj == case_dep + 1) return EST;
    if (case_adj == case_dep - 1) return OUEST;
    if (case_adj == case_dep + largeur) return SUD;
    if (case_adj == case_dep - largeur) return NORD;
    
    return (Direction)-1; // Non adjacente orthogonalement
}

// -----------------------------------------------------------------------------
// Fonction publique
// -----------------------------------------------------------------------------

V_Ville* IHM_chargerVilleDepuisFichier(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier de ville");
        return NULL;
    }

    V_Ville *ville = NULL;
    char ligne[MAX_LIGNE];
    int etat = 0; // 0: Largeur, 1: Départ, 2: Passages/Obligatoires
    unsigned int largeur = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        // Supprimer le saut de ligne
        size_t len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[--len] = '\0';
        }
        
        if (len == 0) continue; // Ignorer les lignes vides
        if (strcmp(ligne, ".") == 0) break; // Fin du flux

        if (etat == 0) {
            // Étape 0 : Lecture de la largeur
            if (sscanf(ligne, "%u", &largeur) == 1 && largeur > 0) {
                ville = V_creerVille(largeur);
                if (ville == NULL) {
                    fclose(f);
                    return NULL;
                }
                etat = 1;
            } else {
                fprintf(stderr, "Erreur de format ou largeur invalide (ligne 1)\n");
                fclose(f);
                return NULL;
            }
        } else if (etat == 1) {
            // Étape 1 : Lecture du départ et orientation
            unsigned int num_depart;
            char dir_char;
            if (sscanf(ligne, "%u%c", &num_depart, &dir_char) == 2) {
                Direction dir = charToDirection(dir_char);
                // Vérifier si la case de départ est valide avant de fixer
                if (V_obtenirCase(ville, num_depart) != NULL) {
                    V_fixerDepart(ville, num_depart, dir);
                    etat = 2;
                } else {
                    fprintf(stderr, "Erreur : Case de départ %u invalide.\n", num_depart);
                    V_liberer(ville);
                    fclose(f);
                    return NULL;
                }
            } else {
                fprintf(stderr, "Erreur de format pour le départ et la direction (ligne 2)\n");
                V_liberer(ville);
                fclose(f);
                return NULL;
            }
        } else if (etat == 2) {
            // Étape 2 : Lecture des passages (X-Y) ou des cases obligatoires (X)
            
            unsigned int case1, case2;
            
            // Tente de lire un passage (format X-Y)
            if (sscanf(ligne, "%u-%u", &case1, &case2) == 2) {
                C_Case *c1 = V_obtenirCase(ville, case1);
                C_Case *c2 = V_obtenirCase(ville, case2);
                
                if (c1 != NULL && c2 != NULL) {
                    // Passage bidirectionnel : déterminer la direction pour c1 <-> c2
                    Direction dir1_vers_2 = determinerDirection(case1, case2, largeur);
                    Direction dir2_vers_1 = determinerDirection(case2, case1, largeur);

                    if (dir1_vers_2 != (Direction)-1 && dir2_vers_1 != (Direction)-1) {
                        C_fixerCaseAdj(c1, dir1_vers_2, case2);
                        C_fixerCaseAdj(c2, dir2_vers_1, case1);
                    } else {
                         fprintf(stderr, "Avertissement : Passage non orthogonal ou non adjacent entre %u et %u ignoré.\n", case1, case2);
                    }
                } else {
                    fprintf(stderr, "Avertissement: Passage entre cases non valides (%u-%u) ignoré.\n", case1, case2);
                }
            } 
            // Tente de lire une case obligatoire (format X)
            else if (sscanf(ligne, "%u", &case1) == 1) {
                C_Case *c = V_obtenirCase(ville, case1);
                if (c != NULL) {
                    C_fixerObligatoire(c, true);
                } else {
                    fprintf(stderr, "Avertissement: Case obligatoire non valide (%u) ignorée.\n", case1);
                }
            } else {
                fprintf(stderr, "Avertissement: Ligne ignorée avec format non reconnu: %s\n", ligne);
            }
        }
    }

    fclose(f);
    return ville;
}

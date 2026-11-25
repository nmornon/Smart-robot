/**
 * @file IHM.c 
 * @brief Gestion de l'interface et lecture des fichiers de ville.
 * * Ce module permet de transformer un fichier texte en structure de ville,
 * d'afficher les résultats à l'écran et de traduire un chemin en ordres 
 * compréhensibles pour le robot (AV, TG, TD).
 * * @author Groupe 2-6
 * @date 10/12/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IHM.h"
#include "ville.h"
#include "case.h"
#include "direction.h"
#include "chemin.h"

#define MAX_LIGNE 256

// -----------------------------------------------------------------------------
// Fonctions utilitaires (internes au fichier)
// -----------------------------------------------------------------------------

/**
 * @brief Convertit une lettre (N, E, S, O) en type Direction.
 */
static Direction charToDirection(char c) {
    switch (c) {
        case 'N': return NORD;
        case 'E': return EST;
        case 'S': return SUD;
        case 'O': return OUEST;
        default: 
            fprintf(stderr, "Erreur: Direction inconnue '%c'.\n", c);
            return NORD;
    }
}

/**
 * @brief Trouve la direction à prendre pour aller d'une case A vers une case B.
 * @return La direction (NORD, SUD, etc.) ou -1 si les cases ne se touchent pas.
 */
static Direction determinerDirection(unsigned int case_dep, unsigned int case_adj, unsigned int largeur) {
    if (case_adj == case_dep + 1) return EST;
    if (case_adj == case_dep - 1) return OUEST;
    if (case_adj == case_dep + largeur) return SUD;
    if (case_adj == case_dep - largeur) return NORD;
    
    return (Direction)-1;
}

// -----------------------------------------------------------------------------
// Fonctions publiques
// -----------------------------------------------------------------------------

/**
 * @brief Charge les données d'une ville depuis un fichier texte.
 * * Le fichier doit suivre le format : 
 * 1. Largeur, 2. Case départ + Orientation, 3. Passages (X-Y) ou cases obligatoires (X).
 * * @param nom_fichier Chemin vers le fichier .txt
 * @return Un pointeur vers la ville créée, ou NULL en cas d'erreur.
 */
V_Ville* IHM_chargerVilleDepuisFichier(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier de ville");
        return NULL;
    }

    V_Ville *ville = NULL;
    char ligne[MAX_LIGNE];
    int etat = 0; 
    unsigned int largeur = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        size_t len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[--len] = '\0';
        }
        
        if (len == 0) continue;
        if (strcmp(ligne, ".") == 0) break;

        if (etat == 0) {
            // Lecture de la largeur
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
            // Lecture du départ
            unsigned int num_depart;
            char dir_char;
            if (sscanf(ligne, "%u%c", &num_depart, &dir_char) == 2) {
                Direction dir = charToDirection(dir_char);
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
                fprintf(stderr, "Erreur de format pour le départ (ligne 2)\n");
                V_liberer(ville);
                fclose(f);
                return NULL;
            }
        } else if (etat == 2) {
            // Lecture des routes (X-Y) ou des objectifs (X)
            unsigned int case1, case2;
            if (sscanf(ligne, "%u-%u", &case1, &case2) == 2) {
                C_Case *c1 = V_obtenirCase(ville, case1);
                C_Case *c2 = V_obtenirCase(ville, case2);
                
                if (c1 != NULL && c2 != NULL) {
                    Direction dir1_vers_2 = determinerDirection(case1, case2, largeur);
                    Direction dir2_vers_1 = determinerDirection(case2, case1, largeur);

                    if (dir1_vers_2 != (Direction)-1 && dir2_vers_1 != (Direction)-1) {
                        C_fixerCaseAdj(c1, dir1_vers_2, case2);
                        C_fixerCaseAdj(c2, dir2_vers_1, case1);
                    } else {
                         fprintf(stderr, "Avertissement : Passage non adjacent entre %u et %u.\n", case1, case2);
                    }
                }
            } 
            else if (sscanf(ligne, "%u", &case1) == 1) {
                C_Case *c = V_obtenirCase(ville, case1);
                if (c != NULL) {
                    C_fixerObligatoire(c, true);
                }
            }
        }
    }

    fclose(f);
    return ville;
}

/**
 * @brief Affiche dans la console le chemin complet de manière lisible.
 */
void IHM_afficherChemin(Ch_Chemin *chemin) {
    if (chemin == NULL) {
        printf("\n>> Erreur : Pointeur de chemin NULL.\n");
        return;
    }
    if (Ch_nbrCases(chemin) == 0 && chemin->tab_cases == NULL) {
        printf("\n>> Resultat : Aucun chemin valide trouve.\n");
        return;
    }

    printf("\n=======================================\n");
    printf("       CHEMIN OPTIMAL TROUVE           \n");
    printf("=======================================\n");
    printf("Longueur du trajet : %d deplacements\n", Ch_nbrCases(chemin));
    printf("Sequence : [ ");

    for (int i = 0; i <= Ch_nbrCases(chemin); i++) {
        printf("%u", chemin->tab_cases[i].numero_case);
        if (i < Ch_nbrCases(chemin)) printf(" -> ");
    }
    printf(" ]\n");
}

/**
 * @brief Affiche l'état interne de la ville (utile pour le débogage).
 */
void IHM_afficher_ville(V_Ville *v) {
    if (v == NULL) return;
    
    printf("\n--- Debug Ville ---\n");
    printf("Largeur: %u | Total cases: %u\n", V_obtenirLargeur(v), V_obtenirNbCases(v));

    for (unsigned int i = 1; i <= V_obtenirNbCases(v); i++) {
        C_Case *c = V_obtenirCase(v, i);
        if (c != NULL) {
            printf("Case %2u: [%s] | Voisins: N=%u, E=%u, S=%u, O=%u\n", 
                   C_obtenirNumeroCase(*c), 
                   C_estObligatoire(*c) ? "OBLIGATOIRE" : "Libre",
                   C_obtenirVoisin(*c, NORD), C_obtenirVoisin(*c, EST), 
                   C_obtenirVoisin(*c, SUD), C_obtenirVoisin(*c, OUEST));
        }
    }
}

/**
 * @brief Génère les ordres textuels (AV, TG, TD) pour le robot.
 * * Analyse chaque étape du chemin pour décider s'il faut tourner 
 * ou avancer en fonction de l'orientation actuelle.
 */
void IHM_genererOrdres(Ch_Chemin *chemin) {
    int nb_mouvements = Ch_nbrCases(chemin);
    
    if (chemin == NULL || nb_mouvements <= 0) {
        printf(".\n");
        return;
    }

    Direction dir_courante = Ch_obtenirDirDepart(chemin);
    printf("AV\n"); // Premier mouvement

    for (int i = 0; i < nb_mouvements; i++) {
        C_Case *case_actuelle = Ch_obtenirCaseAuChemin(chemin, i);
        C_Case *case_suivante = Ch_obtenirCaseAuChemin(chemin, i + 1);

        if (case_actuelle == NULL || case_suivante == NULL) break;

        unsigned int num_suivante = C_obtenirNumeroCase(*case_suivante);
        Direction dir_cible = NORD;
        bool direction_trouvee = false;

        for (int d = 0; d < 4; d++) {
            if (C_obtenirVoisin(*case_actuelle, (Direction)d) == num_suivante) {
                dir_cible = (Direction)d;
                direction_trouvee = true;
                break;
            }
        }

        if (direction_trouvee) {
            // Vérification des intersections
            Direction dir_g = (dir_courante + 3) % 4;
            Direction dir_d = (dir_courante + 1) % 4;
            bool est_intersection = (C_obtenirVoisin(*case_actuelle, dir_g) != 0) || 
                                    (C_obtenirVoisin(*case_actuelle, dir_d) != 0);

            int diff = (dir_cible - dir_courante + 4) % 4;

            if (diff == 1) { // Droite
                printf("TD\nAV\n");
            } 
            else if (diff == 3) { // Gauche
                printf("TG\nAV\n");
            } 
            else if (diff == 0 && est_intersection) {
                printf("AV\n");
            }

            dir_courante = dir_cible;
        }
    }
    printf(".\n");
}

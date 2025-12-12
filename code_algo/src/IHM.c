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
#include "direction.h"
#include "chemin.h"

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
// Fonctions publiques
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

void IHM_afficherChemin(Ch_Chemin *chemin) {
    if (chemin == NULL) {
        printf("\n>> Erreur : Pointeur de chemin NULL.\n");
        return;
    }
    if (Ch_nbrCases(chemin) == 0 && chemin->tab_cases == NULL) {
        printf("\n>> Resultat : Aucun chemin valide trouve avec ces contraintes.\n");
        return;
    }

    printf("\n=======================================\n");
    printf("       CHEMIN OPTIMAL TROUVE           \n");
    printf("=======================================\n");
    
    // Affichage de la longueur
    printf("Longueur du trajet : %d deplacements\n", Ch_nbrCases(chemin));
    
    printf("Sequence du parcours :\n");
    printf("[ ");

    // On parcourt de 0 à nb_cases inclus (car N déplacements = N+1 cases visitées)
    for (int i = 0; i <= Ch_nbrCases(chemin); i++) {
        unsigned int num = chemin->tab_cases[i].numero_case;
        
        printf("%u", num);

        // Affiche une flèche si ce n'est pas la dernière case
        if (i < Ch_nbrCases(chemin)) {
            printf(" -> ");
        }
    }
    printf(" ]\n");
}

// Fonction d'affichage pour vérifier les données chargées
void IHM_afficher_ville(V_Ville *v) {
    if (v == NULL) {
        printf("Erreur : Ville non chargée.\n");
        return;
    }
    
    // Affichage des informations générales
    printf("\n--- Chargement de la ville réussi ---\n");
    printf("Largeur: %u, Total cases: %u\n", V_obtenirLargeur(v), V_obtenirNbCases(v));
    printf("Départ: Case %u, Direction: %d\n", V_obtenirNumCaseDepart(v), V_obtenirDirDepart(v));

    // Affichage détaillé des cases et des connexions
    for (unsigned int i = 1; i <= V_obtenirNbCases(v); i++) {
        C_Case *c = V_obtenirCase(v, i);
        if (c != NULL) {
            printf("Case %2u: ", C_obtenirNumeroCase(*c));
            printf("Obligatoire: %s | ", C_estObligatoire(*c) ? "OUI" : "NON");
            printf("Voisins: N=%u, E=%u, S=%u, O=%u\n", 
                   C_obtenirVoisin(*c, NORD), 
                   C_obtenirVoisin(*c, EST), 
                   C_obtenirVoisin(*c, SUD), 
                   C_obtenirVoisin(*c, OUEST));
        }
    }
}

void IHM_genererOrdres(Ch_Chemin *chemin) {
    int nb_mouvements = Ch_nbrCases(chemin);
    
    // Sécurité
    if (chemin == NULL || nb_mouvements <= 0) {
        printf(".\n");
        return;
    }

    Direction dir_courante = Ch_obtenirDirDepart(chemin);

    printf("AV\n");

    for (int i = 0; i < nb_mouvements; i++) {
        C_Case *case_actuelle = Ch_obtenirCaseAuChemin(chemin, i);
        C_Case *case_suivante = Ch_obtenirCaseAuChemin(chemin, i + 1);

        if (case_actuelle == NULL || case_suivante == NULL) break;

        unsigned int num_suivante = C_obtenirNumeroCase(*case_suivante);
        Direction dir_cible = NORD;
        bool direction_trouvee = false;

        // Trouver où l'on va (Direction cible)
        for (int d = 0; d < 4; d++) {
            if (C_obtenirVoisin(*case_actuelle, (Direction)d) == num_suivante) {
                dir_cible = (Direction)d;
                direction_trouvee = true;
                break;
            }
        }

        if (direction_trouvee) {
            // Détecter si on est sur une intersection
            Direction dir_gauche_relative = (dir_courante + 3) % 4;
            Direction dir_droite_relative = (dir_courante + 1) % 4;

            bool route_a_gauche = (C_obtenirVoisin(*case_actuelle, dir_gauche_relative) != 0);
            bool route_a_droite = (C_obtenirVoisin(*case_actuelle, dir_droite_relative) != 0);
            
            bool est_intersection = (route_a_gauche || route_a_droite);

            // Calcul du mouvement
            int diff = (dir_cible - dir_courante + 4) % 4;

            if (diff == 1) {
                // On tourne à droite
                printf("TD\n");
                printf("AV\n");
            } 
            else if (diff == 3) {
                // On tourne à gauche
                printf("TG\n");
                printf("AV\n");
            } 
            else if (diff == 0) {
                // Intersection détectée mais on va tout droit
                if (est_intersection) {
                    printf("AV\n");
                }
                // Sinon le robot suit la ligne.
            }

            // Mise à jour pour le tour suivant
            dir_courante = dir_cible;
        }
    }

    printf(".\n");
}

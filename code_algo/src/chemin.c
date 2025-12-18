#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <limits.h>
#include "ville.h"
#include "case.h"
#include "chemin.h"
#include "direction.h" 

#define INFINITY INT_MAX 


Ch_Chemin* Ch_creerChemin() {
    Ch_Chemin *c = (Ch_Chemin*)malloc(sizeof(Ch_Chemin));
    c->nb_cases = 0;
    c->num_case_depart = 1;
    c->dir_depart = NORD;
    c->tab_cases = NULL;
    return c;
}

Direction Ch_obtenirDirDepart(Ch_Chemin *c) {
    if (c != NULL) return c->dir_depart;
    return PAS_DE_DIRECTION;
}

C_Case* Ch_obtenirCaseAuChemin(Ch_Chemin *c, unsigned int index) {
    return &(c->tab_cases[index]);
}

static Ch_Chemin* construire_chemin_final(V_Ville *v, int *ids_chemin, 
                                         int longueur, unsigned int depart, 
                                         Direction dir) {
    Ch_Chemin *c = Ch_creerChemin();
    c->nb_cases = longueur;
    c->num_case_depart = depart;
    c->dir_depart = dir;
    c->tab_cases = (C_Case*)malloc((longueur + 1) * sizeof(C_Case));
    
    for (int i = 0; i <= longueur; i++) {
        C_Case *case_orig = V_obtenirCase(v, ids_chemin[i]);
        if (case_orig) {
            c->tab_cases[i] = *case_orig;
        }
    }
    return c;
}

/**
 * BFS : Trouve le plus court chemin entre deux cases
 */
static ResultatBFS bfs_chemin_court(V_Ville *v, unsigned int depart, unsigned int arrivee) {
    ResultatBFS resultat;
    resultat.distance = INT_MAX;
    resultat.predecesseurs = NULL;

    // Cas : départ = arrivée
    if (depart == arrivee) {
        resultat.distance = 0;
        return resultat;
    }

    unsigned int nb_cases = V_obtenirNbCases(v);
    
    // Allouer les structures de recherche
    resultat.predecesseurs = calloc(nb_cases + 1, sizeof(unsigned int));
    int *distances = malloc((nb_cases + 1) * sizeof(int));
    unsigned int *file = malloc((nb_cases + 1) * sizeof(unsigned int));
    
    // Initialiser toutes les distances à l'infini
    for (unsigned int i = 0; i <= nb_cases; i++) {
        distances[i] = INT_MAX;
    }
    
    // Démarrer la recherche
    int debut = 0, fin = 0;
    distances[depart] = 0;
    file[fin] = depart;  
    fin = fin + 1;       

    // Parcours en largeur (comme un arbre niveau par niveau)
    while (debut < fin) {
        unsigned int case_actuelle = file[debut++];
        
        // Objectif est trouvé 
        if (case_actuelle == arrivee) {
            resultat.distance = distances[arrivee];
            break;
        }

        // On explore les 4 voisins
        C_Case *ptr_case = V_obtenirCase(v, case_actuelle);
        if (ptr_case == NULL) continue;
        
        for (int i = 0; i < 4; i++) {
            unsigned int voisin = C_obtenirVoisin(*ptr_case, (Direction)i);
            
            // Si le voisin existe et n'a pas été visité
            if (voisin != 0 && distances[voisin] == INT_MAX) {
                distances[voisin] = distances[case_actuelle] + 1;
                resultat.predecesseurs[voisin] = case_actuelle;
                file[fin] = voisin; 
                fin = fin + 1;       
            }
        }
    }

    // Pas de chemin trouvé
    if (resultat.distance == INT_MAX) {
        free(resultat.predecesseurs);
        resultat.predecesseurs = NULL;
    }
    
    free(file);
    free(distances);
    return resultat;
}

//Reconstruit le chemin à partir des prédécesseurs du BFS

static int reconstruire_chemin(unsigned int depart, unsigned int arrivee,
                               unsigned int *predecesseurs, int *chemin_sortie) {
    if (predecesseurs == NULL) return -1;
    if (predecesseurs[arrivee] == 0 && depart != arrivee) return -1;

    int longueur = 0;
    unsigned int actuel = arrivee;
    
    // Remonter de l'arrivée au départ
    while (actuel != 0) {
        chemin_sortie[longueur++] = (int)actuel;
        if (actuel == depart) break;
        actuel = predecesseurs[actuel];
    }

    // Inverser le chemin
    for (int i = 0; i < longueur / 2; i++) {
        int temp = chemin_sortie[i];
        chemin_sortie[i] = chemin_sortie[longueur - 1 - i];
        chemin_sortie[longueur - 1 - i] = temp;
    }
    
    return longueur - 1;
}

// Exploration récursive pour trouver le meilleur ordre de visite
static void explorer_ordre_objectifs(int position, int nb_obj,
                                     int *sequence_temp, bool *visites,
                                     int cout_actuel, int **distances,
                                     int *meilleure_sequence, int *min_cout) {
    
    // On abandonne si c'est trop long 
    if (cout_actuel >= *min_cout) return;

    // Tous les objectifs sont placés
    if (position == nb_obj) {
        // Ajouter le cout du retour au départ
        int cout_retour = distances[sequence_temp[nb_obj - 1]][0];
        if (cout_retour == INT_MAX) return;
        
        int cout_total = cout_actuel + cout_retour;
        
        if (cout_total < *min_cout) {
            *min_cout = cout_total;
            for (int i = 0; i < nb_obj; i++) {
                meilleure_sequence[i] = sequence_temp[i];
            }
        }
        return;
    }

    // On essaie chaque objectif 
    for (int i = 1; i < nb_obj; i++) {
        if (!visites[i]) {
            int cout_segment = distances[sequence_temp[position - 1]][i];
            if (cout_segment == INT_MAX) continue;
            
            visites[i] = true;
            sequence_temp[position] = i;
            
            explorer_ordre_objectifs(position + 1, nb_obj, sequence_temp, visites,
                                    cout_actuel + cout_segment, distances,
                                    meilleure_sequence, min_cout);
            
            visites[i] = false;
        }
    }
}


// Génère le chemin optimal qui visite tous les objectifs obligatoires
Ch_Chemin* Ch_genererCheminOptimal(V_Ville *v) {
    if (!v) return Ch_creerChemin();

    unsigned int nb_cases = V_obtenirNbCases(v);
    unsigned int depart = V_obtenirNumCaseDepart(v);
    
   
   // Ici on cherche tous les objectifs obligatoires  
    unsigned int *objectifs = malloc((nb_cases + 1) * sizeof(unsigned int));
    objectifs[0] = depart;  // Le dÃ©part est toujours le premier
    
    int nb_objectifs = 1;
    for (unsigned int i = 1; i <= nb_cases; i++) {
        C_Case *c = V_obtenirCase(v, i);
        if (C_estObligatoire(*c) && i != depart) {
            objectifs[nb_objectifs++] = i;
        }
    }
    
    //  Le cas où aucun objectif
    if (nb_objectifs <= 1) {
        Ch_Chemin *res = construire_chemin_final(v, (int*)&depart, 0, depart, 
                                                 V_obtenirDirDepart(v));
        free(objectifs);
        return res;
    }
    
    
    // On calcule les distances entre objectifs avec BFS
    
    int **distances = malloc(nb_objectifs * sizeof(int*));
    unsigned int ***predecesseurs = malloc(nb_objectifs * sizeof(unsigned int**));
    
    for (int i = 0; i < nb_objectifs; i++) {
        distances[i] = malloc(nb_objectifs * sizeof(int));
        predecesseurs[i] = malloc(nb_objectifs * sizeof(unsigned int*));
        
        for (int j = 0; j < nb_objectifs; j++) {
            if (i == j) {
                distances[i][j] = 0;
                predecesseurs[i][j] = NULL;
            } else {
                ResultatBFS res = bfs_chemin_court(v, objectifs[i], objectifs[j]);
                distances[i][j] = res.distance;
                predecesseurs[i][j] = res.predecesseurs;
                
                if (res.distance == INT_MAX) {
                    // libération de la mémoire
                    free(objectifs);
                    for (int k = 0; k <= i; k++) {
                        for (int l = 0; l < nb_objectifs; l++) {
                            if (predecesseurs[k][l]) free(predecesseurs[k][l]);
                        }
                        free(predecesseurs[k]);
                        free(distances[k]);
                    }
                    free(predecesseurs);
                    free(distances);
                    return Ch_creerChemin();
                }
            }
        }
    }
    
    // Ici on cherche le meilleur ordre des visites des points obligatoires
    int *sequence_temp = malloc(nb_objectifs * sizeof(int));
    int *meilleure_sequence = malloc(nb_objectifs * sizeof(int));
    bool *visites = calloc(nb_objectifs, sizeof(bool));
    int min_cout = INT_MAX;
    
    sequence_temp[0] = 0; 
    visites[0] = true;
    
    explorer_ordre_objectifs(1, nb_objectifs, sequence_temp, visites, 0,
                            distances, meilleure_sequence, &min_cout);
    
    if (min_cout == INT_MAX) {
        fprintf(stderr, "Aucune solution trouvÃ©e\n");
        free(sequence_temp);
        free(meilleure_sequence);
        free(visites);
        free(objectifs);
        for (int i = 0; i < nb_objectifs; i++) {
            for (int j = 0; j < nb_objectifs; j++) {
                if (predecesseurs[i][j]) free(predecesseurs[i][j]);
            }
            free(predecesseurs[i]);
            free(distances[i]);
        }
        free(predecesseurs);
        free(distances);
        return Ch_creerChemin();
    }
    
    // On assemble le chemin complét
    
    int taille_max = (int)(nb_cases * 2) + 2;
    int *chemin_final = malloc(taille_max * sizeof(int));
    int longueur_totale = 0;
    
    // Pour chaque segment entre objectifs
    for (int i = 0; i < nb_objectifs; i++) {
        int idx_depart = meilleure_sequence[i];
        int idx_arrivee;

        if (i == nb_objectifs - 1) {
            idx_arrivee = 0;
        } else {
        idx_arrivee = meilleure_sequence[i + 1];
        } 
        
        int *segment = malloc((nb_cases + 1) * sizeof(int));
        int longueur_segment = reconstruire_chemin(objectifs[idx_depart],
                                                   objectifs[idx_arrivee],
                                                   predecesseurs[idx_depart][idx_arrivee],
                                                   segment);
        
        if (longueur_segment < 0) {
            free(segment);
            continue;
        }
        
        // Copier le segment et permet d'éviter les doublons aux jonctions
        int debut;
        if (i == 0) {
        debut = 0;
        } else {
        debut = 1;
        }
        for (int j = debut; j <= longueur_segment; j++) {
            chemin_final[longueur_totale++] = segment[j];
        }
        
        free(segment);
    }
    
    // Construction du chemin final
    Ch_Chemin *resultat = construire_chemin_final(v, chemin_final, 
                                                  longueur_totale - 1,
                                                  depart, V_obtenirDirDepart(v));
    
    // libération de la mémoire
    free(objectifs);
    free(chemin_final);
    free(sequence_temp);
    free(meilleure_sequence);
    free(visites);
    
    for (int i = 0; i < nb_objectifs; i++) {
        for (int j = 0; j < nb_objectifs; j++) {
            if (i != j && predecesseurs[i][j] != NULL) {
                free(predecesseurs[i][j]);
            }
        }
        free(predecesseurs[i]);
        free(distances[i]);
    }
    free(predecesseurs);
    free(distances);

    return resultat;
}


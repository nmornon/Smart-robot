#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#include "ville.h"
#include "case.h"
#include "chemin.h"
#include "direction.h" 

Ch_Chemin* Ch_creerChemin() {
    Ch_Chemin *c = (Ch_Chemin*)malloc(sizeof(Ch_Chemin));

    c->nb_cases = 0;
    c->num_case_depart = 1;
    c->dir_depart = NORD;
    c->tab_cases = NULL;

    return c;
}

Direction Ch_obtenirDirDepart(Ch_Chemin *c) {
    if (c != NULL) {
        return c->dir_depart;
    } else {
        return PAS_DE_DIRECTION;
    }
}

C_Case* Ch_obtenirCaseAuChemin(Ch_Chemin *c, unsigned int index) {
    return &(c->tab_cases[index]);
}

int Ch_nbrCases(Ch_Chemin *c) {
    return c->nb_cases;
}

void Ch_liberer(Ch_Chemin *c) {
    if (c != NULL) {
        if (c->tab_cases != NULL) {
            free(c->tab_cases);
            c->tab_cases = NULL;
        }
        free(c);
    }
}


static void explorer_force_brute(V_Ville *v,
                                 unsigned int num_case,
                                 unsigned int num_depart,
                                 Direction dir_actuelle,
                                 int *chemin_temp,
                                 int profondeur,
                                 int obj_trouves,
                                 int obj_total,
                                 int *meilleur_chemin,
                                 int *min_len,
                                 int *objectif_collecte,
                                 int taille_max) {

    if (profondeur >= taille_max || profondeur >= *min_len) return;

    C_Case *ptr_case = V_obtenirCase(v, num_case);
    if (ptr_case == NULL) return;

    chemin_temp[profondeur] = (int)num_case;
    
    bool a_ramasse_objet = false;
    if (C_estObligatoire(*ptr_case) && objectif_collecte[num_case] == 0) {
        objectif_collecte[num_case] = 1;
        obj_trouves++;
        a_ramasse_objet = true;
    }

    bool retour_depart = (num_case == num_depart && profondeur > 0);

    if (retour_depart) {
        if (obj_trouves >= obj_total) {
            *min_len = profondeur;
            for (int i = 0; i <= profondeur; i++) {
                meilleur_chemin[i] = chemin_temp[i];
            }
        }
    } 
    else {
        for (int i = 0; i < 4; i++) {
            Direction dir_test = (Direction)i;
            if (dir_test == directionOpposee(dir_actuelle)) continue;

            unsigned int voisin_id = C_obtenirVoisin(*ptr_case, dir_test);
            
            if (voisin_id != 0) {
                explorer_force_brute(v, voisin_id, num_depart, dir_test,
                                     chemin_temp, profondeur + 1, obj_trouves,
                                     obj_total, meilleur_chemin, min_len,
                                     objectif_collecte, taille_max);
            }
        }
    }

    if (a_ramasse_objet) {
        objectif_collecte[num_case] = 0;
    }
}

static Ch_Chemin* construire_chemin_final(V_Ville *v, int *ids_chemin, int longueur, unsigned int depart, Direction dir) {

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

Ch_Chemin* Ch_genererCheminBrute(V_Ville *v) {
    if (!v) return Ch_creerChemin();

    unsigned int nb_cases = V_obtenirNbCases(v);
    
    // Calcul taille max sécurisée
    int taille_max = (int)(nb_cases * 2) + 2; 
    if (taille_max < 4) taille_max = 4;

    int *chemin_temp = malloc(taille_max * sizeof(int));
    int *meilleur_chemin = malloc(taille_max * sizeof(int));
    int *objectifs = calloc(nb_cases + 1, sizeof(int)); // calloc initialise à 0 directement


    int min_len = TAILLE_MAX_CHEMIN;
    
    explorer_force_brute(v, 
                         V_obtenirNumCaseDepart(v), 
                         V_obtenirNumCaseDepart(v), 
                         V_obtenirDirDepart(v),
                         chemin_temp, 
                         0, 0,                      
                         V_nbCasesObligatoire(v),   
                         meilleur_chemin, 
                         &min_len, 
                         objectifs, 
                         taille_max);

    Ch_Chemin *resultat = construire_chemin_final(v, 
                                                  meilleur_chemin, 
                                                  min_len, 
                                                  V_obtenirNumCaseDepart(v), 
                                                  V_obtenirDirDepart(v));

    free(chemin_temp);
    free(meilleur_chemin);
    free(objectifs);

    return resultat;
}
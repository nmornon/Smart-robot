#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ville.h"
#include "case.h"
#include "chemin.h"
#include "IHM.h"
#include "direction.h" 

Ch_Chemin* Ch_creerChemin() {
    Ch_Chemin *c = (Ch_Chemin*)malloc(sizeof(Ch_Chemin));
    if (!c) return NULL;

    c->nb_cases = 0;
    c->num_case_depart = 1;
    c->dir_depart = NORD;
    c->tab_cases = NULL;

    return c;
}

Direction Ch_obtenirDirDepart(Ch_Chemin *c) {
    return (c != NULL) ? c->dir_depart : NORD; 
}

C_Case* Ch_obtenirCaseAuChemin(Ch_Chemin *c, unsigned int index) {
    if (c == NULL || c->tab_cases == NULL || index > c->nb_cases) {
        return NULL;
    }
    return &(c->tab_cases[index]);
}

int Ch_nbrCases(Ch_Chemin *c) {
    return c ? c->nb_cases : 0;
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

/*
 * explorer_force_brute :
 * - permet de revisiter des cases (pas de 'est_deja_visitee')
 * - interdit le demi-tour immédiat (conforme à la demande "pas de demi tour")
 * - utilise objectif_collected avec backtracking correct (sauvegarde/restauration)
 * - protège la profondeur avec taille_max pour éviter overflows
 */
static void explorer_force_brute(V_Ville *v,
                                 unsigned int case_id,
                                 unsigned int depart_id,
                                 Direction dir_actuelle,
                                 int *chemin_temp,
                                 int profondeur,
                                 int obj_trouves,
                                 int obj_total,
                                 int *meilleur_chemin,
                                 int *min_len,
                                 int *objectif_collected,
                                 int taille_max) {

    /* Protection contre dépassement de chemin_temp */
    if (profondeur >= taille_max) return;

    /* Si on a déjà une solution plus courte, on coupe pour optimiser */
    if (profondeur >= *min_len) return;

    C_Case *c_actuelle = V_obtenirCase(v, case_id);
    if (c_actuelle == NULL) return;

    /* Sauvegarde pour backtracking */
    int ancien_obj = objectif_collected[case_id];
    int nouvel_obj_trouves = obj_trouves;

    /* Collecte de l'objectif si présent et non encore collecté */
    if (C_estObligatoire(*c_actuelle) && objectif_collected[case_id] == 0) {
        objectif_collected[case_id] = 1;
        nouvel_obj_trouves++;
    }

    chemin_temp[profondeur] = (int)case_id;

    /* Si on est de retour au départ (et pas au tout début), vérifier la condition */
    if (case_id == depart_id && profondeur > 0) {
        if (nouvel_obj_trouves >= obj_total) {
            /* On a trouvé un chemin valide plus court */
            *min_len = profondeur;
            for (int i = 0; i <= profondeur; i++) {
                meilleur_chemin[i] = chemin_temp[i];
            }
        }
        /* Restauration avant retour */
        objectif_collected[case_id] = ancien_obj;
        return;
    }

    /* Exploration des 4 directions */
    for (int dir = 0; dir < 4; dir++) {
        /* Interdiction du demi-tour immédiat (conformément à "pas de demi tour") */
        if ((Direction)dir == directionOpposee(dir_actuelle)) {
            continue;
        }

        unsigned int voisin_id = C_obtenirVoisin(*c_actuelle, (Direction)dir);

        if (voisin_id != 0) {
            /* On autorise TOUS les passages (revisites permises) */
            explorer_force_brute(v,
                                 voisin_id,
                                 depart_id,
                                 (Direction)dir,
                                 chemin_temp,
                                 profondeur + 1,
                                 nouvel_obj_trouves,
                                 obj_total,
                                 meilleur_chemin,
                                 min_len,
                                 objectif_collected,
                                 taille_max);
            /* Après retour d'un appel récursif, on continue d'explorer les autres voisins.
               On ne restaure pas objectif_collected[case_id] ici, car l'état pour la
               case courante doit rester le même pour tous les voisins explorés.
               La restauration se fait à la sortie de la fonction (plus bas). */
        }
    }

    /* Restauration de l'état avant de remonter dans la pile */
    objectif_collected[case_id] = ancien_obj;
}

Ch_Chemin* Ch_genererCheminBrute(V_Ville *v) {
    if (v == NULL) return Ch_creerChemin();

    unsigned int nb_cases = V_obtenirNbCases(v);
    unsigned int depart_id = V_obtenirNumCaseDepart(v);
    Direction dir_depart = V_obtenirDirDepart(v);

    int obj_total = 0;

    /* Compter le nombre d'objectifs obligatoires */
    for (unsigned int i = 1; i <= nb_cases; i++) {
        C_Case *c = V_obtenirCase(v, i);
        if (c != NULL && C_estObligatoire(*c)) {
            obj_total++;
        }
    }

    /* Taille maximale raisonnable (prévenir overflow) */
    int taille_max = (int)((nb_cases * 2) + 2);
    if (taille_max < 4) taille_max = 4; /* sécurité minimale */

    int *chemin_temp = (int*)malloc(taille_max * sizeof(int));
    int *meilleur_chemin_ids = (int*)malloc(taille_max * sizeof(int));
    int *objectif_collected = (int*)malloc((nb_cases + 1) * sizeof(int));  /* indexé par case_id */

    if (chemin_temp == NULL || meilleur_chemin_ids == NULL || objectif_collected == NULL) {
        /* libérer ce qui a été alloué avant de retourner */
        if (chemin_temp) free(chemin_temp);
        if (meilleur_chemin_ids) free(meilleur_chemin_ids);
        if (objectif_collected) free(objectif_collected);
        return Ch_creerChemin();
    }

    memset(objectif_collected, 0, (nb_cases + 1) * sizeof(int));  /* aucun objectif collecté au départ */

    int min_len = INT_MAX;

    /* Lancement de l'exploration en force brute */
    explorer_force_brute(v,
                         depart_id,
                         depart_id,
                         dir_depart,
                         chemin_temp,
                         0,              /* profondeur initiale */
                         0,              /* obj_trouves initial */
                         obj_total,
                         meilleur_chemin_ids,
                         &min_len,
                         objectif_collected,
                         taille_max);

    Ch_Chemin *chemin_final = Ch_creerChemin();

    if (min_len != INT_MAX) {
        chemin_final->nb_cases = min_len;
        chemin_final->tab_cases = (C_Case*)malloc((min_len + 1) * sizeof(C_Case));
        if (chemin_final->tab_cases == NULL) {
            /* Allocation échouée : nettoyage et retour */
            Ch_liberer(chemin_final);
            chemin_final = Ch_creerChemin();
        } else {
            for (int i = 0; i <= min_len; i++) {
                unsigned int id = (unsigned int)meilleur_chemin_ids[i];
                C_Case *c_orig = V_obtenirCase(v, id);
                if (c_orig != NULL) {
                    chemin_final->tab_cases[i] = *c_orig;
                } else {
                    /* Si une case manquait (improbable), on met une case nulle pour éviter comportement indéfini */
                    memset(&chemin_final->tab_cases[i], 0, sizeof(C_Case));
                }
            }
            chemin_final->num_case_depart = depart_id;
            chemin_final->dir_depart = dir_depart;
        }
    } else {
        /* Aucun chemin trouvé */
        printf("Aucun chemin trouvé respectant les contraintes (Force Brute).\n");
    }

    free(chemin_temp);
    free(meilleur_chemin_ids);
    free(objectif_collected);

    return chemin_final;
}

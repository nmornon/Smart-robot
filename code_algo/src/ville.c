#include <stdio.h>
#include <stdlib.h>
#include "ville.h"

V_Ville* V_creerVille(unsigned int largeur) {
    V_Ville *v = (V_Ville*)malloc(sizeof(V_Ville));
    if (v == NULL) {
        fprintf(stderr, "Erreur : Impossible d'allouer la structure V_Ville\n");
        return NULL;
    }
    v->largeur = largeur;
    v->nb_cases = largeur * largeur;
    
    v->num_case_depart = 1; 
    v->dir_depart = NORD;

    v->tab_cases = (C_Case*)malloc(v->nb_cases * sizeof(C_Case));
    if (v->tab_cases == NULL) {
        fprintf(stderr, "Erreur : Impossible d'allouer le tableau de cases\n");
        free(v); 
        return NULL;
    }
    for (unsigned int i = 0; i < v->nb_cases; i++) {
        // false = non obligatoire par défaut
        v->tab_cases[i] = C_creerCase(i + 1, false);
    }
    return v;
}

void V_liberer(V_Ville *ville) {
    if (ville != NULL) {
        if (ville->tab_cases != NULL) {
            free(ville->tab_cases);
            ville->tab_cases = NULL;
        }
        free(ville);
    }
}

C_Case* V_obtenirCase(V_Ville *ville, unsigned int numero_case) {
    // Vérification de sécurité
    if (ville == NULL || numero_case < 1 || numero_case > ville->nb_cases) {
        return NULL;
    }
    // Conversion ID (1..N) vers Index tableau (0..N-1)
    return &(ville->tab_cases[numero_case - 1]);
}

void V_fixerDepart(V_Ville *ville, unsigned int numero_case, Direction dir) {
    ville->num_case_depart = numero_case;
    ville->dir_depart = dir;
}

unsigned int V_obtenirLargeur(V_Ville *ville) {
    return ville->largeur;
}
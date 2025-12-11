#include <stdio.h>
#include <stdlib.h>
#include "IHM.h"
#include "ville.h"
#include "case.h"
#include "direction.h"

// Fonction d'affichage pour vérifier les données chargées
void afficher_ville(V_Ville *v) {
    if (v == NULL) {
        printf("Erreur : Ville non chargée.\n");
        return;
    }
    
    // Affichage des informations générales
    printf("\n--- Chargement de la ville réussi ---\n");
    printf("Largeur: %u, Total cases: %u\n", V_obtenirLargeur(v), V_obtenirNbCases(v));
    printf("Départ: Case %u, Direction: %d\n", V_obtenirNumCaseDepart(v), V_obtenirDirDepart(v));
    printf("---------------------------------------\n");

    // Affichage détaillé des cases et des connexions
    for (unsigned int i = 1; i <= v->nb_cases; i++) {
        C_Case *c = V_obtenirCase(v, i);
        if (c != NULL) {
            printf("Case %2u: ", c->numero_case);
            printf("Obligatoire: %s | ", C_estObligatoire(*c) ? "OUI" : "NON");
            printf("Voisins: N=%u, E=%u, S=%u, O=%u\n", 
                   C_obtenirVoisin(*c, NORD), 
                   C_obtenirVoisin(*c, EST), 
                   C_obtenirVoisin(*c, SUD), 
                   C_obtenirVoisin(*c, OUEST));
        }
    }
    printf("---------------------------------------\n");
}

/**
 * \brief Point d'entrée du programme. Charge la ville à partir d'un fichier.
 *
 * \param argc Le nombre d'arguments passés au programme.
 * \param argv Le tableau des arguments (argv[0] est le nom du programme, 
 * argv[1] devrait être le nom du fichier de ville).
 * \return EXIT_SUCCESS ou EXIT_FAILURE.
 */
int main(int argc, char *argv[]) {
    // 1. Vérification du nombre d'argumentss
    if (argc != 2) {
        fprintf(stderr, "Erreur: Usage: %s <fichier_de_description_ville>\n", argv[0]);
        // Il est crucial de s'assurer que le premier argument est le nom du fichier 
        return EXIT_FAILURE;
    }

    const char *nom_fichier = argv[1];

    // 2. Chargement de la ville
    V_Ville *ma_ville = IHM_chargerVilleDepuisFichier(nom_fichier);

    // 3. Traitement du résultat
    if (ma_ville != NULL) {
        printf("Le fichier '%s' a été chargé avec succès.\n", nom_fichier);
        afficher_ville(ma_ville);
        
        // Libération de la mémoire
        V_liberer(ma_ville);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Échec du chargement de la ville à partir de '%s'.\n", nom_fichier);
        return EXIT_FAILURE;
    }
}

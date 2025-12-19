/**
 * @file main.c
 * @brief Point d'entrée pour la gestion et l'optimisation de trajets en ville.
 */

#include <stdio.h>
#include <stdlib.h>
#include "IHM.h"
#include "ville.h"
#include "case.h"
#include "direction.h"
#include "chemin.h"

/**
 * @brief Charge une ville, calcule le meilleur chemin et affiche les instructions.
 * * @param argc Nombre d'arguments.
 * @param argv Tableau d'arguments (attend le chemin du fichier de ville en argv[1]).
 * @return EXIT_SUCCESS si tout s'est bien passé, sinon EXIT_FAILURE.
 */
int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    if (argc != 2) {
        fprintf(stderr, "Erreur: Usage: %s <fichier_de_description_ville>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *nom_fichier = argv[1];

    // Chargement de la ville
    V_Ville *ville = IHM_chargerVilleDepuisFichier(nom_fichier);

    // Traitement du résultat
    if (ville != NULL) {
        // Calcule le chemin le plus court (méthode brute)
        Ch_Chemin* chemin_opti = Ch_genererCheminBrute(ville);
        
        // Affiche la liste des ordres à suivre
        IHM_genererOrdres(chemin_opti);
        
        // Nettoyage de la mémoire
        V_liberer(ville);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Échec du chargement de la ville à partir de '%s'.\n", nom_fichier);
        return EXIT_FAILURE;
    }
}

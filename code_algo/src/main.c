#include <stdio.h>
#include <stdlib.h>
#include "IHM.h"
#include "ville.h"
#include "case.h"
#include "direction.h"
#include "chemin.h"

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
    V_Ville *ville = IHM_chargerVilleDepuisFichier(nom_fichier);

    // 3. Traitement du résultat
    if (ville != NULL) {
        printf("Le fichier '%s' a été chargé avec succès.\n", nom_fichier);
        IHM_afficher_ville(ville);
        
        Ch_Chemin* chemin_opti = Ch_genererCheminBrute(ville);
        if (chemin_opti != NULL){
           IHM_afficherChemin(chemin_opti);
        }
        
        IHM_genererOrdres(chemin_opti);
        
        // Libération de la mémoire
        V_liberer(ville);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Échec du chargement de la ville à partir de '%s'.\n", nom_fichier);
        return EXIT_FAILURE;
    }
}

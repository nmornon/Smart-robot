/**
 * @file main.c
 * @brief Point d'entrée du programme. 
 * * Ce fichier orchestre la lecture d'une ville, le calcul de l'itinéraire 
 * et l'affichage des instructions finales.
 */

#include <stdio.h>
#include <stdlib.h>
#include "IHM.h"
#include "ville.h"
#include "case.h"
#include "direction.h"
#include "chemin.h"

/**
 * @brief Fonction principale qui pilote le projet.
 *
 * @param argc Nombre d'arguments (on en attend 2 : nom du programme + fichier ville).
 * @param argv Tableau d'arguments (argv[1] doit être le chemin vers le fichier de ville).
 * @return EXIT_SUCCESS si le trajet est généré, EXIT_FAILURE en cas d'erreur.
 */
int main(int argc, char *argv[]) {
    // On s'assure que l'utilisateur a bien précisé un fichier source
    if (argc != 2) {
        fprintf(stderr, "Erreur: Usage: %s <fichier_de_description_ville>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *nom_fichier = argv[1];

    // Tentative de chargement de la ville
    V_Ville *ville = IHM_chargerVilleDepuisFichier(nom_fichier);

    if (ville != NULL) {
        // Calcul du meilleur itinéraire possible
        Ch_Chemin* chemin_opti = Ch_genererCheminOptimal(ville);
        
        // Affichage des ordres de direction à suivre
        IHM_genererOrdres(chemin_opti);
        
        // Nettoyage propre de la mémoire
        V_liberer(ville);
        return EXIT_SUCCESS;
    } else {
        // Cas où le fichier est introuvable ou mal formé
        fprintf(stderr, "Échec du chargement de la ville à partir de '%s'.\n", nom_fichier);
        return EXIT_FAILURE;
    }
}

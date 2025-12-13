#include <stdio.h>
#include <stdlib.h>
#include "IHM.h"
#include "ville.h"
#include "case.h"
#include "direction.h"
#include "chemin.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Erreur: Usage: %s <fichier_de_description_ville>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *nom_fichier = argv[1];

    V_Ville *ville = IHM_chargerVilleDepuisFichier(nom_fichier);

    if (ville != NULL) {
        printf("Le fichier '%s' a été chargé avec succès.\n", nom_fichier);
        IHM_afficher_ville(ville);
        
        Ch_Chemin* chemin_opti = Ch_genererCheminBrute(ville);
        if (chemin_opti != NULL){
            IHM_afficherChemin(chemin_opti);
        }

       
        FILE *f = fopen("directions.txt", "w");     // créer le fichier
        IHM_definirFluxOrdres(f);                    //  dire où écrire
        IHM_genererOrdres(chemin_opti);              //  générer les ordres
        fclose(f);                                   // fermer le fichier
    

        V_liberer(ville);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Échec du chargement de la ville à partir de '%s'.\n", nom_fichier);
        return EXIT_FAILURE;
    }
}

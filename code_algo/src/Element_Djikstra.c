#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include "ensembleTrie.h" //pour utiliser la constante INT_MAX, qui représente une distance infinie
#include "ville.h" 

// Structure pour stocker un noeud dans la file de priorité (Ensemble Trié)
typedef struct {
    int id_case;
    int distance;
} ElementDijkstra;

/**
 * \brief Copie un ElementDijkstra (pour ET_EnsembleTrie)
 */
void* ED_copier(void* pElement) {
    ElementDijkstra* original = (ElementDijkstra*)pElement;
    ElementDijkstra* copie = (ElementDijkstra*)malloc(sizeof(ElementDijkstra));
    if (copie != NULL) {
        copie->id_case = original->id_case;
        copie->distance = original->distance;
    }
    return copie;
}

/**
 * \brief Libère un ElementDijkstra (pour ET_EnsembleTrie)
 */
void ED_liberer(void* pElement) {
    free(pElement);
}

/**
 * \brief Compare deux ElementDijkstra selon la distance (pour le tri)
 * Si les distances sont égales, on compare les ID pour assurer la stabilité
 */
int ED_comparer(void* pElement1, void* pElement2) {
    ElementDijkstra* e1 = (ElementDijkstra*)pElement1;
    ElementDijkstra* e2 = (ElementDijkstra*)pElement2;

    if (e1->distance != e2->distance) {
        return e1->distance - e2->distance;
    }
    return e1->id_case - e2->id_case;
}
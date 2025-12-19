#include "case.h"

C_Case C_creerCase(unsigned int num, bool obligatoire) {
    C_Case c;
    c.numero_case = num;
    c.est_obligatoire = obligatoire; 
    
    // Initialisation propre des voisins à 0
    for (int i = 0; i < 4; i++) {
        c.cases_adjacents[i] = 0;
    }
    return c;
}

unsigned int C_obtenirNumeroCase(C_Case c) {
    return c.numero_case;
}

bool C_estObligatoire(C_Case c) {
    return c.est_obligatoire;
}


void C_fixerObligatoire(C_Case *c, bool est_obligatoire) {
        c->est_obligatoire = est_obligatoire;
}

unsigned int C_obtenirVoisin(C_Case c, Direction dir) {
    return c.cases_adjacents[(int)dir];
}

void C_fixerCaseAdj(C_Case *c, Direction dir, unsigned int num_case_adj) {
        c->cases_adjacents[(int)dir] = num_case_adj;
}
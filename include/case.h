#ifndef __Case__
#define __Case__

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int numero_case;
    bool case_obligatoire;
    unsigned int cases_adjacents[4]; 
} CH_Case;

CH_Case creerCase(unsigned int numCase, bool obligatoire, unsigned int cases_adjacents[4]);
unsigned int CH_obtenirNumCase(CH_Case case);
bool CH_estObligatoire(CH_case case);
CH_Case obtenirCaseAPartirDUnNum(unsigned int num);

#endif

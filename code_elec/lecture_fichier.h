#ifndef LECTURE_FICHIER_H
#define LECTURE_FICHIER_H

#include <stdio.h>
#include <string.h>
#include "configurer.h"

#define MAX 100

Instruction Chaine_en_Instructions(char* instruc);
void lire_fichier(Instruction* instructions,unsigned int* nombreInstruc);

#endif

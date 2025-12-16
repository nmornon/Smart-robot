#include "lecture_fichier.h"

Instruction Chaine_en_Instructions(char* instruc)
{
	if (strcmp(instruc,"AV")==0){
		return AV;
	} else if (strcmp(instruc,"TD")==0){
		return TD;
	} else if (strcmp(instruc,"TG")==0){
		return TG;
	}  else if (strcmp(instruc,".")==0){
		return ARRET;
	} else {
		printf("Commande non reconnue : %s\n",instruc);
		return -1;
	}
}

void lire_fichier(Instruction* instructions,unsigned int* nombreInstruc)
{
	char entree[MAX];
	Instruction instruc;
	*nombreInstruc=0;
	
	while (fgets(entree,sizeof(entree),stdin)!=NULL){
		entree[strcspn(entree,"\n")]='\0';
		
		instruc=Chaine_en_Instructions(entree);
		if(instruc !=-1){
			printf("Instructions lues : %s\n",entree);
		}else{
			printf("Instruction non reconnue : %s\n", entree);
		}
		
		if (instruc!=-1)
			instructions[*nombreInstruc]=instruc;
		
		(*nombreInstruc)++;
	}
}


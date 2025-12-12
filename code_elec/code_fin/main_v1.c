#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include "lecture_fichier.h"
#include "lcd_bip.h"
#include "rgb_sensor.h"
#include <stdbool.h> 
#include "commande_final.h"
#include "configurer.h"

// gcc -o robot main.c lcd_bip.c rgb_sensor.c lecture_fichier.c commande_final.c configurer.c -lwiringPi -lpthread -lwiringPiDev -lm

const char* Instruction_en_chaine(Instruction instruc) {
    switch (instruc) {
        case AV: return "AV";
        case TG: return "TG";
        case TD: return "TD";
        case ARRET: return "ARRET";
        default: return "??";
    }
}

void afficher_instruction(int lcd, Instruction instruc){
	lcdClear(lcd);
        lcdPosition(lcd, 0, 0);
        lcdPrintf(lcd, "Commande :");
        lcdPosition(lcd, 0, 1);
        lcdPrintf(lcd,Instruction_en_chaine(instruc));
}

void deplacer(Instruction* listeInstructions,int nb_instruc,int lcd){
	for (int i = 0; i < nb_instruc; i++){
		afficher_instruction(lcd,listeInstructions[i]);
		switch (listeInstructions[i]) {
			case AV: 
				avancer();
				break;
			case TG: 
				tournerGauche();
				break;
			case TD:
				tournerDroite();
				break;
			default:
				printf("non reconnue\n");
				break;
		}
	}
}

int main()
{
    if (wiringPiSetupGpio() == -1) 
    	return 1;
    
    configurerRobot();
    
    int lcd = IHM_initialiserLcd(); //Configure LCD
    
    Instruction instruc[MAX];
    unsigned int nbreInstruc=0;
    
    lire_fichier(instruc,&nbreInstruc);
    while (1){
    deplacer(instruc,nbreInstruc,lcd);
    
    arreter();}
    return 0;
}

	

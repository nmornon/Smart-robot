#include "lcd_bip.h"

// gcc -o lcd_bip lcd_bip.c -lwiringPi -lpthread -lwiringPiDev -lm

int IHM_initialiserLcd()
{
    
    pcf8574Setup(AF_BASE,0x27); //mettre l’adresse I2C
    
    int handle = lcdInit(2, 16, 4, AF_RS, AF_E, AF_DB4, AF_DB5, AF_DB6, AF_DB7, 0, 0, 0, 0);
   // 2lignes , 16 colonnes, mode 4 bits , le reste c’est les pins du WiringPI qui correspond aux broches du LCD
   
   if(handle < 0)
    {
        fprintf(stderr, "Erreur : initialisation du LCD\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < 8; i++) {   //on parcourt les 8 broches virtuelles 
	pinMode(AF_BASE+i,OUTPUT); //chaque broche est mise en sortie
	}
    digitalWrite(AF_LED,1);   //allume la broche du LED sur le PCF8574
    digitalWrite(AF_RW,0); //mode écriture
    lcdClear(handle); //efface tout l'écran 
    lcdPosition(handle, 0, 0); //deplacer le curseur en 0,0
    return handle;
}

void IHM_afficherCouleur(int handle, const char* couleur)
{

    lcdClear(handle); //efface
    
    lcdPosition(handle, 0, 0); //position 0,0
    lcdPuts(handle, "Couleur detectee:"); 

    lcdPosition(handle, 0, 1); // position deuxième ligne
    lcdPuts(handle, couleur); //affiche la couleur
}

void init_Bip() {
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
}

void bip() {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(2000);
    digitalWrite(PIN_BUZZER, LOW);
}
